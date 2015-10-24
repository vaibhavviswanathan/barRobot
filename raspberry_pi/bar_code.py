import sys
import serial

valves_ser = serial.Serial('/dev/ttyUSB0', 9600)
stepper_ser = serial.Serial('/dev/ttyUSB1', 9600)

# The maximum valve time in millis
MAX_VALVE_TIME = 30000

# Definition of drinks by valve numbers
RUM = 0
VODKA = 1
WHISKEY = 2
SPRITE = 3
COKE = 4
ORANGE_JUICE = 5

# drink recipes in millis
drinks = {
    "rum_and_coke": [(RUM, 2000), (COKE, 5000)],
    "vodka_and_sprite": [(VODKA, 2000), (SPRITE, 5000)],
    "screwdriver": [(VODKA, 2000), (ORANGE_JUICE, 5000)],
    "jack_and_coke": [(WHISKEY, 2000), (COKE, 5000)]
}

def make_drink(name):
    instructions = drinks[name]
    for instruction in instructions:

def set_valves(times):
    # takes a list of tuples, (valve, millis)
    valves_ser.write()

def main():
    # For now, try making one drink
    make_drink( "rum_and_coke" )
    
if __name__ == "__main__":
    main()
