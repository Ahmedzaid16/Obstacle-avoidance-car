#include <Servo.h> // disable pwm ~ on 10 11 
#include <SoftwareSerial.h> // Import SoftwareSerial library
#define ECHO_PIN 4// Define ulrasonic echo
#define TRIG_PIN 10 // Define ultrasonic trig
#define servo_pin 11//define servo pin

// Motor A Pins // Left Motor Pins
#define ENA 3 // Connect ENA to pin 3
#define IN1 9 // Connect IN1 to pin 9
#define IN2 8 // Connect IN2 to pin 8

// Motor B Pins // Right Motor Pins
#define ENB 5 // Connect ENB to pin 5
#define IN3 7 // Connect IN3 to pin 7
#define IN4 6 // Connect IN4 to pin 6

Servo myservo;

int SpeedRR = 200; // Variable to store the car speed (PWM)
int SpeedLR = 200;
int SpeedL = 100;
int SpeedR = 130;

long t; // Variable to hold the time
int distance; // Variable to hold the distance
int right_distance; // Variable to hold the distance
int left_distance; // Variable to hold the distance             
                  
 void Motors (char d){
  switch(d){             
    
    case 'f': // Motor A // Move Left Motor
              digitalWrite(IN1, HIGH); // Set IN1 to HIGH
              digitalWrite(IN2, LOW); // Set IN2 to LOW
              analogWrite(ENA, SpeedL); // Set motor A speed
              
              // Motor B // Move Right Motor
              digitalWrite(IN3, HIGH); // Set IN3 to HIGH
              digitalWrite(IN4, LOW); // Set IN4 to LOW
              analogWrite(ENB, SpeedR); // Set motor B speed
              break;
    case 'r': // Motor A // Move Left Motor
              digitalWrite(IN1, HIGH); // Set IN1 to HIGH
              digitalWrite(IN2, LOW); // Set IN2 to LOW
              analogWrite(ENA, SpeedL); // Set motor A speed
              
              // Motor B // Stop Right Motor
              digitalWrite(IN3, LOW); // Set IN3 to LOW
              digitalWrite(IN4, LOW); // Set IN4 to LOW
              analogWrite(ENB, 0); // Set motor B speed to 0
              break;                                 
    case 'l': // Motor A // Stop Left Motor
              digitalWrite(IN1, LOW); // Set IN1 to LOW
              digitalWrite(IN2, LOW); // Set IN2 to LOW
              analogWrite(ENA, 0); // Set motor A speed to 0
              
              // Motor B // Move Right Motor
              digitalWrite(IN3, HIGH); // Set IN3 to HIGH
              digitalWrite(IN4, LOW); // Set IN4 to LOW
              analogWrite(ENB, SpeedR); // Set motor B speed
    case 's': // Motor A // Stop Left Motor
              digitalWrite(IN1, LOW); // Set IN1 to LOW
              digitalWrite(IN2, LOW); // Set IN2 to LOW
              analogWrite(ENA, 0); // Set motor A speed to 0
              
              // Motor B // Stop Right Motor
              digitalWrite(IN3, LOW); // Set IN3 to LOW
              digitalWrite(IN4, LOW); // Set IN4 to LOW
              analogWrite(ENB, 0); // Set motor B speed to 0              
             break;                 
    case 'b': // Motor A // Move Left Motor in Reverse
              digitalWrite(IN1, LOW); // Set IN1 to LOW
              digitalWrite(IN2, HIGH); // Set IN2 to HIGH
              analogWrite(ENA, SpeedL); // Set motor A speed
              
              // Motor B // Move Right Motor in Reverse
              digitalWrite(IN3, LOW); // Set IN3 to LOW
              digitalWrite(IN4, HIGH); // Set IN4 to HIGH
              analogWrite(ENB, SpeedR); // Set motor B speed
              break;     
    case 'L': // it means back left
              
              break;
    case 'R': // it means back right
                
              break;
    case 't': digitalWrite(IN1, LOW); // Set IN1 to LOW 
              digitalWrite(IN2, HIGH); // Set IN2 to HIGH
              analogWrite(ENA, SpeedLR); // Set motor A speed
              // Motor B // Move Right Motor
              digitalWrite(IN3, HIGH); // Set IN3 to HIGH
              digitalWrite(IN4, LOW); // Set IN4 to LOW
              analogWrite(ENB, SpeedRR); // Set motor B speed  
              break;   
    case 'm': // Motor A // Move Right Motor
              digitalWrite(IN1, HIGH); // Set IN3 to HIGH
              digitalWrite(IN2, LOW); // Set IN4 to LOW
              analogWrite(ENA, SpeedLR); // Set motor B speed
              // Motor B // Move Right Motor
              digitalWrite(IN3, LOW); // Set IN3 to HIGH
              digitalWrite(IN4, HIGH); // Set IN4 to LOW
              analogWrite(ENB, SpeedRR); // Set motor B speed  
              break;                       
  }
 }
 void setup(){
  Serial.begin(9600); // Start PC serial at 9600bps
  // attaches the servo on pin 10 to the servo object
  myservo.attach(servo_pin);
  myservo.write(90);
  pinMode(TRIG_PIN, OUTPUT); // Set TRIG_PIN as an output
  pinMode(ECHO_PIN, INPUT); // Set ECHO_PIN as an input
  pinMode(ENA, OUTPUT); // Set ENA pin as output
  pinMode(ENB, OUTPUT); // Set ENB pin as output
  pinMode(IN1, OUTPUT); // Set IN1 pin as output
  pinMode(IN2, OUTPUT); // Set IN2 pin as output
  pinMode(IN3, OUTPUT); // Set IN3 pin as output
  pinMode(IN4, OUTPUT); // Set IN4 pin as output
 }

 
 void loop(){
  //myservo.write(90);
  //delay(600);
  distance = calculate_distance(); // Calculate the distance
  Serial.println(distance); // Print the distance
  while(distance >=40)
  {
    Motors('b');
    distance = calculate_distance();
    Serial.println(distance);
  }
  Motors('s');
  delay(100);
  myservo.write(0);
  delay(400);
  right_distance = calculate_distance();
  Serial.println("right :");
  Serial.println(right_distance);
  myservo.write(180);
  delay(400);
  left_distance = calculate_distance();
  Serial.println("left :");
  Serial.println(left_distance);
  myservo.write(90);
  delay(15);
  //to go right
  if(left_distance<=right_distance)
  {
    // rotate r
    Motors('m');
    delay(200);
    myservo.write(180);
    Motors('s');
    delay(500);
    distance = calculate_distance();
    Serial.println(distance);
    Motors('b');
    delay(300);
    while(distance<50 )
    {
      Motors('b');
      distance = calculate_distance();
      Serial.println(distance);
    }
    myservo.write(90);
    Motors('s');
    delay(500);
    Motors('t');
    delay(220);
  }
  //to go left
  else 
  {
    Motors('t');
    delay(220);
    myservo.write(0);
    Motors('s');
    delay(500);
    distance = calculate_distance();
    Serial.println(distance);
    Motors('b');
    delay(300);
    while(distance<50)
    {
      Motors('b');
      distance = calculate_distance();
      Serial.println(distance);
    }
    myservo.write(90);
    Motors('s');
    delay(500);
    Motors('m');
    delay(200);
  }
 }

 int calculate_distance(){
  digitalWrite(TRIG_PIN, LOW); // Make sure that TRIG_PIN is LOW
  delayMicroseconds(2); // for just 2 microseconds
  digitalWrite(TRIG_PIN, HIGH); // Set the TRIG_PIN to HIGH
  delayMicroseconds(10); // for 10 microseconds
  digitalWrite(TRIG_PIN, LOW); // Set the TRIG_PIN to LOW
  t = pulseIn(ECHO_PIN, HIGH); // Return the length of pulse in microseconds
  return (0.5 * t * 0.0343); // Return the distance (D = 0.5T * S)
}
