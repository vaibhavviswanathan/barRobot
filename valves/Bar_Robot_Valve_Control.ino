char in_byte;
int valve_pins[6] = {1, 2, 3, 4, 5, 6};
int max_time = 30000;

void setup()
{
  Serial.begin(9600);
  for (int i=0; i<6; i++) {
   pinMode(valve_pins[i], OUTPUT); 
  }
  for (int i=0; i<6; i++) {
   digitalWrite(valve_pins[i], HIGH); 
  }
  Serial.print("Ready");
}

void loop()
{
  char valve_times[6];
  boolean reading = false;
  int current_byte=0;
  if (Serial.available() > 0) {
    in_byte= Serial.read();
    if (in_byte == 1 && !reading) {
      for (int i=0; i<6; ++i) {
        valve_times[0] = 0;
      }
      reading = true;
      current_byte=0;
    }
    if (reading) {
      valve_times[current_byte] = Serial.read();
      current_byte++;
      if (current_byte == 6) {
        reading = false;
        // Begin valve control
        
        // Initially turn on all valves
        for (int i=0; i<6; i++) {
          digitalWrite(valve_pins[i], LOW); 
        }
        for (int time=2; time<256; ++time) {
          for (int i=0; i<6; ++i) {
            if (valve_times[i] == time) {
              digitalWrite(valve_pins[i], HIGH); 
            }
          }
          delay(max_time / 256);
        }
      }
    }
  }
}


