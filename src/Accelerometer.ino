const uint8_t LDR1 = A1;
const uint8_t LDR2 = A2;
const uint16_t threshold = 900; // Use checkLDRInt() for getting a good threshold in your circumstances
const float distance = 150.00; // in cm
float acceleration = 0;
uint32_t cycles = 0;
uint32_t startMillis = 0;
uint32_t endMillis = 0;
uint32_t squareTime = 0;
bool ready = false;

bool checkLDR(uint8_t pin) {
    return (analogRead(pin) > 900);
}

uint16_t checkLDRInt(uint8_t pin) {
    return analogRead(pin);
}

void setup() {
    pinMode(LDR1, INPUT);
    pinMode(LDR2, INPUT);
    Serial.begin(115200);
    Serial.println("Not yet ready for start");
}

void loop() {
   if (checkLDR(LDR1) && checkLDR(LDR2)) {
       if (!ready) {
           Serial.println("Ready for start");
           ready = true;
       }
       if (!checkLDR(LDR1)) {
           startMillis = millis();
           Serial.println("Time started");
           while (checkLDR(LDR2)) {
               cycles++;
           }
           endMillis = millis();
           Serial.println((String) cycles + " cycles in " + (endMillis-startMillis) + " milliseconds");
           Serial.println((String)"Such that" + ((float)(endMillis-startMillis)/cycles) + " milliseconds per cycle");
           squareTime = square(endMillis - startMillis);
           acceleration = 2*distance/squareTime/100.00*1000000; // in m/(s*s)
           Serial.println((String)"Acceleration is " + acceleration + " m/(s*s)");
           loop();
       }
    } else {
       if (ready) {
           Serial.println("Not yet ready for start");
           ready = false;
       }
    }
}
