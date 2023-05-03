#include <Servo.h>
#include <BlynkSimpleStream.h>
#define BLYNK_TEMPLATE_ID "TMPL3IeaEjEsM"
#define BLYNK_TEMPLATE_NAME "new device"
#define BLYNK_AUTH_TOKEN "2zJ49EUrvWQ1Xa3GNf11L9xlodHDMjz_"
const int ir_entrance = 2;
const int ir_exit = 3;
const int servo_pin = 9;
const int num_slots = 4;
int ir_slots[num_slots] = { 4, 5, 6 ,7};

Servo gate;

void setup() {
  Serial.begin(9600);
  pinMode(ir_entrance, INPUT);
  pinMode(ir_exit, INPUT);
  for (int i = 0; i < num_slots; i++) {
    pinMode(ir_slots[i], INPUT);
  }
  gate.attach(servo_pin);
}

void loop() {
  int available_slots = 0;
  
  if (digitalRead(ir_entrance) == HIGH) {
    for (int i = 0; i < num_slots; i++) {
      if (digitalRead(ir_slots[i]) == HIGH) {
        available_slots++;
      }
    }
    
    if (available_slots > 0) {
      Serial.print(available_slots);
      Serial.println(" slots are available");
      gate.write(90);
      delay(3000);
      gate.write(0);

  if (digitalRead(ir_exit) == LOW) {
    delay(3000);
    gate.write(90);
  }
    } else {
      Serial.println("Parking is full.....");
      gate.write(90);
    }
  }

}
