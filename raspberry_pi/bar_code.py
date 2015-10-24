import sys
import serial
import array

valves_ser = serial.Serial('/dev/ttyACM0', 9600)
stepper_ser = serial.Serial('/dev/ttyACM1', 9600)

# The maximum valve time in millis
MAX_VALVE_TIME = 10000

# Definition of drinks by valve numbers
RUM = 0
VODKA = 1
WHISKEY = 2
SPRITE = 3
COKE = 4
ORANGE_JUICE = 5

# drink recipes in millis
DRINKS = {
    "rum_and_coke": [(RUM, 2000), (COKE, 5000)],
    "vodka_and_sprite": [(VODKA, 2000), (SPRITE, 5000)],
    "screwdriver": [(VODKA, 2000), (ORANGE_JUICE, 5000)],
    "jack_and_coke": [(WHISKEY, 2000), (COKE, 5000)]
}

def make_drink(name):
    # Reset the stepper motor
    rotate(0)

    instructions = DRINKS[name]
    for instruction in instructions:
        rotate(instruction[0])
        set_valves([instruction])

def make_drinks(drinks):
    # Takes a list of tuples, (drink_name, location (0-5))
    # Reset the stepper motor
    rotate(0)
        
    valves = [[], [], [], [], [], []]
    for drink in drinks: 
        insts = DRINKS[drink[0]]
        for inst in insts:
            valves[(inst[0]-drink[1])%6].append(inst)

    print valves

    for loc in range(6):
        rotate(loc)
        set_valves(valves[loc])

    #stepper_ser.write( chr(7) )
    rotate(0)

def set_valves(times):
    # takes a list of tuples, (valve, millis)
    valves_ser.write(b'\x01')
    valves = [2, 2, 2, 2, 2, 2]
    for time in times:
        valves[time[0]] = int((float(time[1]) / float(MAX_VALVE_TIME)) * 127);
        if (valves[time[0]] < 2):
            valves[time[0]] = 2
    print valves
    for v in valves:
        valves_ser.write(chr(v)) 

    resp = valves_ser.read()
    print resp
    
def rotate(position):
    # Takes a positon 0-5
    stepper_ser.write( str(position+1) )
    resp = stepper_ser.read()
    print resp

def main():
    # For now, try making one drink
    #make_drink( "rum_and_coke" )
    make_drinks([("rum_and_coke", 0), ("vodka_and_sprite", 1), ("screwdriver", 2)]) 
    #set_valves( [(0, 2000), (2, 3500), (4, 5000)] )
    
if __name__ == "__main__":
    main()
