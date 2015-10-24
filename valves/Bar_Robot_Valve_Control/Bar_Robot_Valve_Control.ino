char in_byte;
int valve_pins[6] = {3, 4, 5, 6, 7, 8};
int max_time = 10000;

void setup()
{
  Serial.begin(9600);
  for (int i=0; i<6; i++) {
   pinMode(valve_pins[i], OUTPUT); 
  }
  for (int i=0; i<6; i++) {
   digitalWrite(valve_pins[i], HIGH); 
  }
}

char valve_times[6];
boolean reading = false;
int current_byte=0;

void loop()
{
  if (Serial.available() > 0) {
    in_byte= Serial.read();
    if (reading) {
      valve_times[current_byte] = in_byte;
      current_byte++;
      if (current_byte == 6) {
        reading = false;
        // Begin valve control
        
        int done = 0;
        // Initially turn on all valves
        for (int i=0; i<6; i++) {
          digitalWrite(valve_pins[i], LOW); 
        }
        for (byte time=2; time<128; ++time) {
          for (int i=0; i<6; ++i) {
            if (valve_times[i] <= time) {
              digitalWrite(valve_pins[i], HIGH);
              done++; 
            }
          }
          if (done < 6) {
            delay(max_time / 128);
          }
        }
        Serial.print('A');
      }
    }
    if (in_byte == 1 && !reading) {
      for (int i=0; i<6; ++i) {
        valve_times[i] = 2;
      }
      reading = true;
      current_byte=0;
    }
  }
}
