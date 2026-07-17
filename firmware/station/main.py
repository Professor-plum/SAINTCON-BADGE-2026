import time
import json
import os
import sys
from machine import Pin
from utime import sleep

pin = Pin("LED", Pin.OUT)

try:
    from station.uart_ports import build_ports
    from station.ws2812 import WS2812
except ImportError:
    from uart_ports import build_ports
    from ws2812 import WS2812

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
WS2812_COUNT = 8
LED_UPDATE_MS = 100
POLL_MS = 50

rocket_db = {}
vote_db = {}
update_db = {}

highroller = {'id':0, 'v':0}

try:
    if 'rockets.json' in os.listdir():
        with open('rockets.json', "r") as f:
            # JSON keys are always saved as strings, convert them back to ints
            raw_data = json.load(f)
            rocket_db = {k: int(v) for k, v in raw_data.items()}
            for k,v in rocket_db.items():
                if v > highroller['v']:
                    highroller["id"] = k
                    highroller["v"] = v
    else:
        rocket_db = {}
except Exception as e:
    print("Error loading rocket DB, starting fresh:", e)
    rocket_db = {}

try:
    if 'votes.json' in os.listdir():
        with open('votes.json', "r") as f:
            # JSON keys are always saved as strings, convert them back to ints
            raw_data = json.load(f)
            vote_db = {k: {'V':int(v['V']), 'S':int(v['S'])} for k, v in raw_data.items()}
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
        self.state = "started"
        self.str = idstr[4:]

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
        port.write(b'$DIALOG The station needs your vote for what to build next! Please vote for your favorite design!\r\n')
        port.write(b'$OPTIONS 1:Hull| 2:Laser| 3:Shield| 4:Missiles\r\n')
        port.write(b'$EOL\r\n')
        rocket_db[port.rocket.id] = {"str":port.rocket.str, "games":[]}
    except ValueError as e:
        sys.print_exception(e)
        print("Error parsing ID: ")
        print(line)

def parse_game(line, port):
    try:
        #$GAME %5s%5s %05d %02d 
        game_id = line[6:16]
        rocket_id = line[11:16]
        score = int(line[17:22], 10)
        if rocket_id in update_db:
            rocket_entry = update_db[rocket_id]
            if not 'games' in rocket_entry:
                rocket_entry['games'] = []
            rocket_entry['games'].append(line)
        if rocket_id in rocket_db:
            rocket_db[rocket_id] += score
        port.write(line[0:16]+ b'\r\n')
    except ValueError as e:
        print("Error parsing Game: ")
        print(line)

def parse_vote(line, port):
    try:
        rocket_id = line[6:11]
        vote = {'V':0, 'S':0}
        score = 0
        vote['V'] = int(line[15:16], 10)
        if rocket_id in vote_db:
            vote['S'] += vote_db[rocket_id]['S']
        vote_db[rocket_id] = vote
    except ValueError as e:
        print("Error parsing Vote: ")
        print(line)   


def main():
    print("Starting docking station")
    ports = build_ports(UART_PORTS)
    leds = WS2812(WS2812_PIN, WS2812_COUNT)
    leds.fill((0, 0, 0))
    leds.show()

    last_crew_update = time.ticks_ms()

    last_active_count = -1
    while True:
        active_count = 0
        crew = b'$CREW '
        for port in ports:
            if port.connected:
                active_count += 1
            if port.rocket:
                crew += port.rocket.get_id_str()
            while True:
                line = port.read()
                if line is None:
                    break
                print("[{}] RX: {}".format(port.name, format_bytes(line)))
                if line.startswith(b"$ID "):
                    parse_rocket(line, port)
                elif line.startswith(b'$GAME '):
                    parse_game(line, port)
                elif line.startswith(b'$VOTE '):
                    parse_vote(line, port)
                decoded = format_bytes(line)

        crew += b'\r\n'
        now = time.ticks_ms()
        if (now - last_crew_update) > 1000:
            for port in ports:
                if port.connected:
                    if port.rocket == None:
                        print("Sending Station beacon to", port.name)
                        port.write(b'$STATION test station 1|Welcome to the station!|Build progress 1/100|Current leader: Bobby Tables\r\n')
                    else:
                        print("Sending Crew update to", port.name)
                        port.write(crew)
                else:
                    if port.rocket:
                        port.rocket = None
            last_crew_update = now 

        if active_count != last_active_count:
            print("Active UART ports:", active_count, "/", len(ports))
            last_active_count = active_count

        leds.update_port_status(ports)
        time.sleep_ms(POLL_MS)
        pin.value(not pin.value())


if __name__ == "__main__":
    main()
