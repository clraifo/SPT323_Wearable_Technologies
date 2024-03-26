/*

Casey L. Raiford
SPT323 Haptics - Final Project

This circuit and code is an MVP version of Light Alert, a
device designed to alert the user to the presence of 
light above a customizable level of brightness. 

The major components, aside from the Arduino Uno and 
the bread board are as follows:

Photoresistor - takes in light, puts out analog signal
Vibration motor - actuates in response to photoresistor output
Transistor - drives the vibration motor
Indicator LED - solely here to provide a better visual signal
that the motor is on, receives equivalent signal form the photoresistor 

To try the circuit and code out, hit "Start Simulation" ^^^
rth

*/

const int motorPin = 5; // Define pin for the motor
const int photoresistorPin = A0; // Define pin for the photoresistor
const int LEDPin = 11; // Define pin for the LED

void setup() {
  pinMode(motorPin, OUTPUT); // Set the motor pin as an output
  pinMode(LEDPin, OUTPUT); // Set the LED pin as an output
  Serial.begin(9600); // Start serial communication with a baud rate of 9600
}

void pulseMotor() {
  analogWrite(motorPin, 255); // Write a maximum speed to the motor pin to pulse the motor at full strength
  digitalWrite(LEDPin, HIGH); // Turn on the LED
  delay(1000); // Delay for 1000 milliseconds (1 second)
  analogWrite(motorPin, 0); // Write a minimum speed to the motor pin to stop the pulse
  digitalWrite(LEDPin, LOW); // Turn off the LED
  delay(1000); // Delay for 1000 milliseconds (1 second)
}

void loop() {
  int photoresistorValue = analogRead(photoresistorPin); // Read the value of the photoresistor
  if (photoresistorValue >= 679) { // If the photoresistor's maximum output is reached
    pulseMotor(); // Pulse the motor
  } else {
    int motorSpeed = map(photoresistorValue, 0, 1023, 100, 255); // Map the photoresistor value to a motor speed between 100 and 255
    analogWrite(motorPin, motorSpeed); // Write the motor speed to the motor pin to control the motor's vibration
    int LEDBrightness = map(motorSpeed, 100, 255, 0, 255); // Map the motor speed to a brightness level between 0 and 255
    analogWrite(LEDPin, LEDBrightness); // Write the LED brightness to the LED pin to control the LED's brightness
  }
  Serial.println(photoresistorValue); // Write the photoresistor value to the serial monitor
  delay(10); // Slow down the loop with a delay of 10 milliseconds
}
