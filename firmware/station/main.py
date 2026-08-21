import time
import json
import os
import sys
import rp2
from machine import Pin
from utime import sleep
import neopixel
import network
import asyncio
import urequests as requests
import komihash
import binascii

urlbase = "https://z88608jzej.execute-api.us-east-1.amazonaws.com/default/Saintcon26StationUpdate/"
api_key = "rutMtymi8q1R1E1qZ4Qku3QZIN9y0TJS3LAIK76Q"
StationName = "Unknown"

rp2.country('US') 
pin = Pin("LED", Pin.OUT)

try:
    from station.uart_ports import build_ports
except ImportError:
    from uart_ports import build_ports

# ======= Configuration =======
# Adjust these pin mappings to your connector layout.
UART_PORTS = [
    {"name": "UART0", "type": "hw",  "uart_id": 0, "tx": 0,  "rx": 1,  "detect": 2,  "baud": 9600},
    {"name": "UART1", "type": "hw",  "uart_id": 1, "tx": 4,  "rx": 5,  "detect": 6,  "baud": 9600},
    {"name": "UART2", "type": "pio", "sm_base": 0, "tx": 8,  "rx": 9,  "detect": 10, "baud": 9600},
    {"name": "UART3", "type": "pio", "sm_base": 2, "tx": 12, "rx": 13,  "detect": 14, "baud": 9600},
    {"name": "UART4", "type": "pio", "sm_base": 4, "tx": 16, "rx": 17,  "detect": 18, "baud": 9600},
]

WS2812_PIN = 20
WS2812_COUNT = 5
LED_UPDATE_MS = 100
POLL_MS = 50

# Initialize NeoPixel object on your chosen pin
wspin = Pin(WS2812_PIN, Pin.OUT)


wlan = network.WLAN(network.STA_IF)
wlan.active(True)

ssid = 'REMOVED_WIFI_SECRET'
password = 'REMOVED_WIFI_SECRET'

wlan.connect(ssid, password)

for i in range(10):
    if wlan.status() < 0 or wlan.status() >= 3:
        break
    time.sleep(1)

if wlan.status() != 3:
    print("Network connection failed")
else:
    print("Connected to wifi")
    network_config = wlan.ifconfig()
    print('IP Address:', network_config[0])


def ensure_network(timeout=10):
    """Ensure the WLAN is connected. Try to (re)connect for up to `timeout` seconds.
    Returns True if connected, False otherwise.
    """
    global wlan, ssid, password
    try:
        # Quick path: some ports expose isconnected()
        if hasattr(wlan, 'isconnected'):
            try:
                if wlan.isconnected():
                    return True
            except Exception:
                pass

        # Fallback to status check (status() == 3 means connected on many ports)
        try:
            if wlan.status() == 3:
                return True
        except Exception:
            pass

        print("Network disconnected — attempting reconnect")
        wlan.active(True)
        wlan.connect(ssid, password)

        for _ in range(timeout):
            try:
                if hasattr(wlan, 'isconnected') and wlan.isconnected():
                    print('Reconnected, IP:', wlan.ifconfig()[0])
                    return True
                if wlan.status() == 3:
                    try:
                        print('Reconnected (status==3), IP:', wlan.ifconfig()[0])
                    except Exception:
                        pass
                    return True
            except Exception:
                pass
            time.sleep(1)

        print('Failed to reconnect after', timeout, 'seconds')
        return False
    except Exception as e:
        print('ensure_network error', e)
        return False


rocket_db = {}
vote_db = {}
update_db = {}
modified = False
vote_data = None
motd = "Drink more ovalteen"

highroller = {'name':b'', 'class':b'A'[0],'score':0}


with open('/station.txt', 'r') as f:
    StationName = f.read().strip()


def log_exception(context, exc):
    print("[ERROR] {}".format(context))
    try:
        sys.print_exception(exc)
    except Exception:
        print(str(exc))

def verify_hash(line, rocketId):
    signkey = int.from_bytes(rocketId, 'little')
    hash = komihash.komihash(line[:-4], signkey)
    b64hash = binascii.b2a_base64(hash.to_bytes(8, 'little'))
    if b64hash[:4] != line[-4:]:
        print("Signature verify failed!", hex(signkey), b64hash[:4], line[-4:])
        raise ValueError


def safe_parse_line(port, line):
    if not line:
        return

    try:
        if line.startswith(b"$ID "):
            parse_rocket(line, port)
        elif line.startswith(b'$GAME '):
            parse_game(line, port)
        elif line.startswith(b'$VOTE '):
            parse_vote(line, port)
        elif line.startswith(b'$EOL '):
            parse_eol(line, port)
    except Exception as exc:
        log_exception("parse_line({})".format(port.name if port else 'unknown'), exc)

try:
    if '/data/rockets.json' in os.listdir():
        with open('/data/rockets.json', "r") as f:
            # JSON keys are always saved as strings, convert them back to ints
            rocket_db = json.load(f)
        for k,v in rocket_db.items():
            if v['S'] > highroller['score']:
                highroller["score"] = v['S']
    else:
        rocket_db = {}
except Exception as e:
    print("Error loading rocket DB, starting fresh:", e)
    rocket_db = {}

try:
    with open('/data/leader.txt', 'r') as f:
        highroller["name"] = f.read()
except Exception as e:
    print("Error loading leader name", e)

try:
    if '/data/votes.json' in os.listdir():
        with open('/data/votes.json', "r") as f:
            vote_db = json.load(f)
    else:
        vote_db = {}
except Exception as e:
    print("Error loading vote DB, starting fresh:", e)
    vote_db = {}


class Rocket:
    def __init__(self, idstr):
        if idstr[0:4] != b'$ID ':
            raise ValueError(b"Invalid Rocket ID str: " + idstr) 
        self.role = idstr[4]
        self.id = idstr[5:10]
        self.name = idstr[10:24]
        self.unlocks = int(idstr[24:32], 16)
        self.str = idstr[4:]
        verify_hash(idstr, self.id)

    def get_id_str(self):
        idstr = b"%c%5s%14s " % (self.role, self.id, self.name)
        return idstr


def format_bytes(data):
    if not data:
        return ""
    return "".join(chr(b) if 32 <= b < 127 else "." for b in data)


def parse_rocket(line, port):
    try:
        port.rocket = Rocket(line)
        if vote_data is not None:
            vcount = summerize_votes()
            #port.write(b'$DIALOG ' + vote_data['prompt'] + b'\r\n')
            line = '$OPTIONS '
            opts = ['%02d%03d%s'%(x['icon'], vcount.get(i, 0), x['name']) for i, x in enumerate(vote_data['options'])]
            port.write('$OPTIONS ' + '|'.join(opts) + '\r\n')
        val = {'S':0, 'M':0, 'P':0}
        if port.rocket.id in rocket_db:
            val = rocket_db[port.rocket.id]
        else:
            rocket_db[port.rocket.id] = val
        print("Rocket parsed:", chr(port.rocket.role), port.rocket.id, port.rocket.name, hex(port.rocket.unlocks), val)
    except Exception as e:
        log_exception("parse_rocket", e)
        print("Error parsing ID: ")
        print(line)

def parse_game(line, port):
    global modified
    if not port or port.rocket is None:
        return

    try:
        #$GAME %5s%5s %5d %2d 
        if len(line) < 26:
            return
        verify_hash(line, port.rocket.id)
        rocket_id = line[6:11]
        if len(line) < 26:
            return
        game_id = line[11:16]
        score = int(line[17:22], 10)
        
        if rocket_id in rocket_db:
            rocket_db[rocket_id]['S'] += score
            rocket_db[rocket_id]['M'] += 1
        else:
            rocket_db[rocket_id] = {'S':score, 'M':1, 'P':0}

        tscore = rocket_db[rocket_id]['S']
        if tscore > highroller['score']:
            highroller['name'] = port.rocket.name
            highroller['score'] = tscore
            highroller['class'] = port.rocket.role

        crewdata = line[26:-5]
        crew = chunks = [crewdata[i:i + 5] for i in range(0, len(crewdata), 5)]
        for c in crew:
            if c == rocket_id:
                continue
            if c in rocket_db:
                rocket_db[c]['S'] += score // 5
                rocket_db[c]['P'] += 1
            else:
                rocket_db[c] = {'S':score // 5, 'M':0, 'P':1}

        if rocket_id not in update_db:
            update_db[rocket_id] = {'games':{}}
        rocket_entry = update_db[rocket_id]
        rocket_entry['name'] = port.rocket.name
        rocket_entry['unlocks'] = port.rocket.unlocks
        rocket_entry['games'][game_id] = {'score': score, 'crew': crew}
        print("Game parsed:", rocket_id, game_id, score, crew)

        modified = True
        port.write(line[0:16]+ b'\r\n')
    except Exception as e:
        log_exception("parse_game", e)
        print("Error parsing Game: ")
        print(line)

def parse_vote(line, port):
    try:
        if len(line) < 14:
            return
        verify_hash(line, port.rocket.id)
        rocket_id = line[6:11]
        vid = int(line[12:14], 10)
        vote_db[rocket_id] = vid
        modified = True
    except Exception as e:
        log_exception("parse_vote", e)
        print("Error parsing Vote: ")
        print(line)

def parse_eol(line, port):
    try:
        if not port or port.rocket is None:
            return
        data = rocket_db.get(port.rocket.id)
        if data is None:
            data = {'S':0, 'M':0, 'P':0}
        port.write(b'$EOL %7d %3d %3d\r\n' % (data['S'], data['M'], data['P']))
    except Exception as e:
        log_exception("parse_eol", e)
        print("Error parsing EOL: ")
        print(line)

def update_leds(ports, pixels):
    for index in range(pixels.n):
        if index < len(ports):
            pixels[index] = (0, 128, 0) if ports[index].is_connected() else (16, 0, 0)
        else:
            pixels[index] = (0, 0, 8)
    pixels.write()

def get_station_line():
    names = {
        'Test Alpha': 1,
        'Test Beta': 2,
        'Test Gamma': 3,
        'Test Delta': 4
    }
    return b"$STATION %d|%c%d|%s|%s\r\n" % (
        names.get(StationName, 1), 
        highroller['class'], 
        highroller['score'],
        highroller['name'], 
        motd
    )

async def send_post():
    global update_db
    try:
        if update_db is None:
            return

        # Ensure network is up before attempting POST. If reconnect fails,
        if not ensure_network():
            print('Skipping POST: no network')
            return

        voteinfo = {'version':1, 'results' : summerize_votes()}
        update_temp = {'games' : update_db, 'votes': voteinfo}
        headers = {'Content-Type': 'application/json', 'X-API-Key': api_key}
        url = urlbase + str(StationName).replace(' ','')
        print("Sending POST")
        response = requests.post(url, headers=headers, data=json.dumps(update_temp), timeout=10.0)
        print(response.status_code)
        if response.status_code == 200:
            rjson = response.json()
            if 'vote' in rjson and (voteinfo is None or rjson['vote']['version'] != voteinfo['version']):
                global vote_data, vote_db, motd
                vote_db = {}
                vote_data = rjson['vote']
                motd = vote_data['message']
                print("Vote data updated:", vote_data)
            update_db = {}
        try:
            response.close()
        except Exception as e:
            print("Error sending update", e)
    except Exception as e:
        print("Error sending update", e)

def summerize_votes():
    value_counts = {}
    for value in vote_db.values():
        value_counts[value] = value_counts.get(value, 0) + 1
    return value_counts

def sync_data():
    global modified, update_db
    print("Saving data", modified)
    try:
        if modified == True:
            with open('/data/rockets.json', "w") as f:
                json.dump(rocket_db, f)
            with open('/data/votes.json', "w") as f:
                json.dump(vote_db, f)
            savedname = ''
            try:
                with open('/data/leader.txt', 'r') as f:
                    savedname = f.read()
            except Exception as e:
                print("error reading leader", e)

            if savedname != highroller['name']:
                with open('/data/leader.txt', 'w') as f:
                    f.write(highroller['name'])

        if update_db:
            asyncio.create_task(send_post())
    except Exception as e:
        log_exception("sync_data", e)

    modified = False

async def main():
    print("Starting docking station")
    ports = build_ports(UART_PORTS)
    pixels = neopixel.NeoPixel(wspin, WS2812_COUNT)
    pixels.timing = (300, 800, 800, 300) 
    pixels.fill((0, 0, 0, 0))
    pixels.write()

    last_crew_update = time.ticks_ms()

    last_web_sync = 0
    asyncio.create_task(send_post())

    while True:
        try:
            active_count = 0
            crew = b'$CREW '
            for port in ports:
                try:
                    if port.connected:
                        active_count += 1
                    if port.rocket:
                        crew += port.rocket.get_id_str()
                    while True:
                        line = port.read()
                        if line is None:
                            break
                        #print("[{}] RX: {}".format(port.name, format_bytes(line)))
                        safe_parse_line(port, line)
                except Exception as exc:
                    log_exception("port loop ({})".format(getattr(port, 'name', 'unknown')), exc)

            update_leds(ports, pixels)

            crew += b'\r\n'
            now = time.ticks_ms()
            if (now - last_crew_update) > 1000:
                for port in ports:
                    try:
                        if port.connected:
                            if port.rocket == None:
                                print("Port {} has no rocket, sending station line".format(port.name))
                                port.write(get_station_line())
                            else:
                                port.write(crew)
                        else:
                            if port.rocket:
                                port.rocket = None
                    except Exception as exc:
                        log_exception("port heartbeat ({})".format(getattr(port, 'name', 'unknown')), exc)
                last_crew_update = now

            if (now - last_web_sync) > (1000 * 60):
                sync_data()
                last_web_sync = now

            await asyncio.sleep_ms(POLL_MS)
            pin.value(not pin.value())
        except KeyboardInterrupt:
            raise
        except Exception as exc:
            log_exception("main_loop", exc)
            await asyncio.sleep_ms(1000)


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("Shutdown requested")
    except Exception as exc:
        log_exception("main_entry", exc)
        while True:
            try:
                time.sleep(1)
            except KeyboardInterrupt:
                raise
