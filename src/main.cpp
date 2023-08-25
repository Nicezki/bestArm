#include <Servo.h>
#include <Arduino.h>


void servoControl(int ServoNo, int degree);
void serialMorniHandle();
void resetServo();
void smoothServoControl(int ServoNo, int degree, int interpolate, int delayTime);
unsigned long currentMillis = millis();

//Define the Servo 5,6,9,10,11
#define SERVO_01_PIN 3
#define SERVO_02_PIN 5
#define SERVO_03_PIN 6
#define SERVO_04_PIN 9
#define SERVO_05_PIN 10
#define SERVO_06_PIN 11

Servo servo[6];

int servoPins[6] = {3, 5, 6, 9, 10, 11};


int sAngle[] = {0, 0, 0, 0, 0, 0};

int servoNumber = 0, servoAngle = 90, mode = 0;
unsigned long previousMillis = 0;

Servo myservo; // Declare Servo object
char inputBuffer[10]; // Buffer to store serial input
int bufferIndex = 0; // Index for input buffer

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(servoPins[i], OUTPUT);
  }
  // Attach servo to pin
  for (int i = 0; i < 5; i++) {
    servo[i].attach(servoPins[i], 500, 2500);
  }

  Serial.begin(9600);
  resetServo();
  Serial.println("Ready!");
}

void loop() {
  serialMorniHandle();
}










void serialMorniHandle() {
  
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read input from serial
    
    if (input.startsWith("S")) {
      mode = 0; // Set mode to select servo
      Serial.println("Selecting Servo, Type your servo number (0-5)");
    }
    else if (input.startsWith("D")) {
      mode = 1; // Set mode to set angle
      Serial.print("Selecting Degree, Enter your degree for servo ");
      Serial.println(servoNumber);
    }
    else if (input.startsWith("E")) {
      mode = 2; // Set mode to set angle
      Serial.print("[Force] Selecting Degree, Enter your degree for servo ");
      Serial.println(servoNumber);
    }    
    else if (input.startsWith("G")) {
      // Get servo angle
      Serial.print("Servo ");
      Serial.print(servoNumber);
      Serial.print(" | Angle: ");
      Serial.println(servoAngle);
    }
    else if (input.startsWith("R")) {
      // Get servo angle
      Serial.println("Reset All Servo ");
      resetServo();

    }

    else {
      // Parse input
      int value = input.toInt();
      if (mode == 0) {
        // Set servo number
        servoNumber = value;
        Serial.print("[Select] Now controlling servo ");
        Serial.println(servoNumber);
      }
      else if (mode == 1) {
        // Set servo angle
        servoAngle = value;
        Serial.print("[Set] Servo ");
        Serial.print(servoNumber);
        Serial.print(" is now set to ");
        Serial.println(servoAngle);
        smoothServoControl(servoNumber, servoAngle, 1, 25);
        
      }
      else if (mode == 2) {
        // Set servo angle
        servoAngle = value;
        Serial.print("[Force] Servo ");
        Serial.print(servoNumber);
        Serial.print(" is now set to ");
        Serial.println(servoAngle);
        servoControl(servoNumber, servoAngle);
      }
    }
  }
}
void servoControl(int ServoNo, int degree){
  if (degree > 180){
    degree = 180;
  }
  if (degree > 110 && ServoNo == 3) {
    degree = 110;
  }
  servo[ServoNo].write(degree);
  Serial.print("S ");
  Serial.print(ServoNo);
  Serial.print(" at: ");
  Serial.println(servo[ServoNo].read());

}

void smoothServoControl(int ServoNo, int targetDegree, int step = 1, int delayTime = 10) {
  int currentDegree = servo[ServoNo].read();

  if (targetDegree > 180) {
    targetDegree = 180;
  }

  if (targetDegree > 110 && ServoNo == 3) {
    targetDegree = 110;
  }

  if (currentDegree == targetDegree) {
    return;  // No need to move if already at the target degree
  }

  int direction = (currentDegree < targetDegree) ? 1 : -1;

  unsigned long previousMillis = millis();
  
  while (currentDegree != targetDegree) {
    if (millis() - previousMillis >= delayTime) {
      currentDegree += step * direction;
      
      if ((direction == 1 && currentDegree > targetDegree) || (direction == -1 && currentDegree < targetDegree)) {
        currentDegree = targetDegree;
      }

      servo[ServoNo].write(currentDegree);
        Serial.print("S ");
        Serial.print(ServoNo);
        Serial.print(" at: ");
        Serial.println(servo[ServoNo].read());
      
      previousMillis = millis();
    }
  }

}


void resetServo(){


  // servoControl(0, 0);
  // delay(500);
  // servoControl(1, 90);
  // delay(500);
  // servoControl(2, 180);
  // delay(500);
  // servoControl(3, 90);
  // delay(500);
  // servoControl(4, 0);
  // delay(500);
  // servoControl(5, 0);
  // delay(750);


  // servoControl(0, 0);
  // delay(500);
  // servoControl(1, 50);
  // delay(500);
  // servoControl(2, 180);
  // delay(500);
  // servoControl(3, 90);
  // delay(500);
  // servoControl(4, 90);
  // delay(500);
  // servoControl(5, 0);
  // delay(1000);



  smoothServoControl(0, 0);
  // delay(500);
  smoothServoControl(1, 145);
  // delay(1500);
  smoothServoControl(2, 40);
  // delay(500);
  smoothServoControl(3, 110); ///ตัวอวศา gripper
  // delay(500);
  smoothServoControl(4, 0);  ///เอียง gripper
  smoothServoControl(4, 90); ///เอียง gripper
  smoothServoControl(4, 0);   ///เอียง gripper
  smoothServoControl(4, 90);  ///เอียง gripper
  // delay(500);
  smoothServoControl(5, 0);
  // delay(5000);

  
}