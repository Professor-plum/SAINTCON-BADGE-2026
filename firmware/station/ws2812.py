from machine import Pin
import rp2

@rp2.asm_pio(sideset_init=rp2.PIO.OUT_LOW, out_init=rp2.PIO.OUT_LOW,
            out_shiftdir=rp2.PIO.SHIFT_LEFT, autopull=True, pull_thresh=24)
def _ws2812():
    wrap_target()
    label("bitloop")
    out(x, 1)               .side(0) [2]  # High for 0, Low for 1 (T0H / T1H start)
    jmp(not_x, "do_zero")   .side(1) [4]  # Driven High for both bits here
    
    # --- Code for a ONE bit ---
    jmp("bitloop")          .side(1) [4]  # Keep High longer for '1', wrap back to side(0)
    
    # --- Code for a ZERO bit ---
    label("do_zero")
    nop()                   .side(0) [4]  # Drop Low early for '0', hold, wrap back
    wrap()



class WS2812:
    def __init__(self, pin, num_leds):
        self.num_leds = num_leds
        self.sm = rp2.StateMachine(7, _ws2812, freq=8_000_000, sideset_base=Pin(pin))
        self.sm.active(1)
        self.leds = [(0, 0, 0)] * num_leds

    def encode_color(self, color):
        r, g, b = color
        return (g << 16) | (r << 8) | b

    def show(self):
        for color in self.leds:
            self.sm.put(self.encode_color(color) << 8)

    def set_pixel(self, index, color):
        if 0 <= index < self.num_leds:
            self.leds[index] = color

    def fill(self, color):
        self.leds = [color] * self.num_leds

    def update_port_status(self, ports):
        for index in range(self.num_leds):
            if index < len(ports):
                self.leds[index] = (0, 128, 0) if ports[index].is_connected() else (16, 0, 0)
            else:
                self.leds[index] = (0, 0, 8)
        self.show()
