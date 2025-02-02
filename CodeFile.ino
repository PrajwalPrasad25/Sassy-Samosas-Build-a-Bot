#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define SERVOMIN  150   
#define SERVOMAX  600  
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  // Default I2C address

int theta=0;
int phi=0;

void moveServo(uint8_t servoNum, int angle) {
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(servoNum, 0, pulse);
}

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Initializing PCA9685...");

//   Wire.begin(21, 22);  // Set ESP32 I2C pins
//   pwm.begin();
//   pwm.setPWMFreq(40);  // 40Hz originally 
  
//   //delay(500);

//   // Serial.begin(115200);
//   // Wire.begin(21, 22);  // Use correct I2C pins for ESP32
//     // Serial.begin(115200);
//     // Wire.begin();

//     if (!lox.begin()) {
//         Serial.println("Failed to initialize VL53L0X! Check connections.");
//         while (1);
//     }
//     Serial.println("VL53L0X Initialized.");
// }

double function()
{
  VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);

    if(Serial.available()){
      String command=Serial.readStringUntil('\n');
      Serial.println(command);
    }

    if (measure.RangeStatus != 4) { // Status 4 means no object detected
        //Serial.print(abs(measure.RangeMilliMeter-56.722));
        //Serial.println(" mm");
    } else {
        Serial.println("Out of range.");
    }

    return abs(measure.RangeMilliMeter-56.722);
    // delay(0.5);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing PCA9685...");

  Wire.begin(21, 22);  // Set ESP32 I2C pins
  pwm.begin();
  pwm.setPWMFreq(40);  // 40Hz originally 
  
  //delay(500);

  // Serial.begin(115200);
  // Wire.begin(21, 22);  // Use correct I2C pins for ESP32
    // Serial.begin(115200);
    // Wire.begin();

    if (!lox.begin()) {
        Serial.println("Failed to initialize VL53L0X! Check connections.");
        while (1);
    }
    Serial.println("VL53L0X Initialized.");


  double d=function();
  Serial.println("Moving Servos...");
  
  moveServo(0, 0);
  moveServo(3,0);
  delay(25);
  float bias=-45;
  // Move servos in sequence
  for (int angle = 0-bias; angle <= 190-bias; angle += 1) {
      theta=angle;
      double r=function();
      double x=r*sin(theta)*cos(phi);
      double y=r*sin(theta)*sin(phi);
      double z=r*cos(theta);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);
      moveServo(0, angle);  
      delay(135);
  }

  for (int angle = 0; angle <= 22.50; angle += 1) {
    phi=angle;
    double r=function();
      double x=r*sin(theta)*cos(phi);
      double y=r*sin(theta)*sin(phi);
      double z=r*cos(theta);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);
      moveServo(3, angle);  
      delay(25);
  }

  for (int angle  = 190-bias; angle >= 0-bias; angle -= 1) {
    theta=angle;
    double r=function();
      double x=r*sin(theta)*cos(phi);
      double y=r*sin(theta)*sin(phi);
      double z=r*cos(theta);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);
      moveServo(0, angle);  
      delay(135);
  }

  for (int angle = 22.50; angle <= 45; angle += 1) {
    phi=angle;
    double r=function();
      double x=r*sin(theta)*cos(phi);
      double y=r*sin(theta)*sin(phi);
      double z=r*cos(theta);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);
      moveServo(3, angle);  
      delay(25);
  }

  for (int angle = 0-bias; angle <= 190-bias; angle += 1) {
    theta=angle;
    double r=function();
      double x=r*sin(theta)*cos(phi);
      double y=r*sin(theta)*sin(phi);
      double z=r*cos(theta);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);
      moveServo(0, angle);  
      delay(135);
  }

  for (int angle = 45; angle <= 67.50; angle += 1) {
      phi=angle;
      double r=function();
      double x=r*sin(theta)*cos(phi);
      double y=r*sin(theta)*sin(phi);
      double z=r*cos(theta);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);
      moveServo(3, angle);  
      delay(25);
  }

  for (int angle = 190-bias; angle >= 0-bias; angle -= 1) {
      theta=angle;
      double r=function();
      double x=r*sin(theta)*cos(phi);
      double y=r*sin(theta)*sin(phi);
      double z=r*cos(theta);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);
      moveServo(0, angle);  
      delay(135);
  }

  for (int angle = 67.50; angle <= 90; angle += 1) {
    phi=angle;
      double r=function();
      double x=r*sin(theta)*cos(phi);
      double y=r*sin(theta)*sin(phi);
      double z=r*cos(theta);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);
      moveServo(3, angle);  
      delay(25);
  }

  for (int angle = 0-bias; angle <= 190-bias; angle += 1) {
    theta=angle;
      double r=function();
      double x=r*sin(theta)*cos(phi);
      double y=r*sin(theta)*sin(phi);
      double z=r*cos(theta);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);
      moveServo(0, angle);  
      delay(135);
  }

  for (int angle = 90; angle >= 0; angle -= 1) {
    phi=angle;
      double r=function();
      double x=r*sin(theta)*cos(phi);
      double y=r*sin(theta)*sin(phi);
      double z=r*cos(theta);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);
      moveServo(3, angle);  
      delay(25);
  }

  for (int angle = 190-bias; angle >= 0-bias; angle -= 1) {
    theta=angle;
      double r=function();
      double x=r*sin(theta)*cos(phi);
      double y=r*sin(theta)*sin(phi);
      double z=r*cos(theta);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);
      moveServo(0, angle);  
      delay(135);
  }

  
}

void loop(){

}



// void loop() {
//   double d=function();
//   Serial.println("Moving Servos...");
  
//   moveServo(0, -90);
//   moveServo(3,0);
//   delay(25);
//   // Move servos in sequence
//   for (theta = 0; theta <= 180; theta += 1) {
//       double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(0, theta);  
//       delay(100);
//   }

//   for (phi = 0; phi <= 22.50; phi += 1) {
//     double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(3, phi);  
//       delay(25);
//   }

//   for (theta = 180; theta >= 0; theta -= 1) {
//     double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(0, theta);  
//       delay(100);
//   }

//   for (phi = 22.50; phi <= 45; phi += 1) {
//     double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(3, phi);  
//       delay(25);
//   }

//   for (theta = 0; theta <= 180; theta += 1) {
//     double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(0, theta);  
//       delay(100);
//   }

//   for (phi = 45; phi <= 67.50; phi += 1) {
//    double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(3, phi);  
//       delay(25);
//   }

//   for (theta = 180; theta >= 0; theta -= 1) {
//     double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(0, theta);  
//       delay(100);
//   }

//   for (phi = 67.50; phi <= 90; phi += 1) {
//     double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(3, phi);  
//       delay(25);
//   }

//   for (theta = 0; theta <= 180; theta += 1) {
//     double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(0, theta);  
//       delay(100);
//   }

//   for (int phi = 90; phi >= 0; phi -= 1) {
//     double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(3, phi);  
//       delay(25);
//   }

//   for (int theta = 180; theta >= 0; theta -= 1) {
//     double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(0, theta);  
//       delay(100);
//   }

  
// }

// void arm(int start, int end)
// {
//   moveServo(0, 0);
//   moveServo(3,0);
//   delay(25);
  
//   if(end>start){
//     for(theta=start; theta<=end; theta++)
//     {
//       double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(0, theta);  
//       delay(100);
//     }
//   }

//   else{
//     for(theta=start; theta>=end; theta--)
//     {
//       double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(0, theta);  
//       delay(100);
//     }
//   }
  
// }

// void base(int start, int end)
// {
//   if(end>start){
//     for(phi=start; phi<=end; phi++)
//     {
//       double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(3, phi);  
//       delay(25);
//     }
//   }

//   else{
//     for(phi=start; phi>=end; phi--)
//     {
//       double r=function();
//       double x=r*sin(theta)*cos(phi);
//       double y=r*sin(theta)*sin(phi);
//       double z=r*cos(theta);
//       Serial.print(x);
//       Serial.print(y);
//       Serial.println(z);
//       moveServo(3, phi);  
//       delay(25);
//     }
//   }
  
// }

// void loop(){
//   arm(0, 180);
//   base(0, 22.50);
//   arm(180, 0);
//   base(22.50, 45);
//   arm(0, 180);
//   base(45, 67.50);
//   arm(180, 0);
//   base(67.5, 90);
//   arm(0, 180);
//   arm(180, 0);
//   base(90,0);
// }


