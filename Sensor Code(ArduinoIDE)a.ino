/* * PROJECT: ESP32 Rotating Radar Scanner
 * -----------------------------------------------------------
 * Developed by: Nayaab Rahman
 * * WHAT IT DOES: 
 * Uses an ultrasonic sensor and a servo motor to scan for 
 * objects in a 180-degree arc.
 * * FEATURES:
 * - Displays distance and angle on an OLED screen.
 * - Sounds an alarm (Buzzer+LED) if an object is within 14cm.
 * - Freezes movement when a target is detected.
 * -----------------------------------------------------------
 */

//Libraries for OLED screen
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//library for servo
#include <ESP32Servo.h>

Servo myServo;      // Created Servo object
int deg = 0;      // Variable to track position
int change = 1;       // How many degrees to move each time
// Define screen dimensions
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

//Defining trig, echo, buzzer, etc pins
#define trig 12
#define echo 13
#define led 4
#define buzzer 5
#define servo 14

// Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//function for returning distance in cm
float readDistanceCM() {
  // Trigger pulse for input and output
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Read echo (timeout after 30 ms)
  long duration = pulseIn(echo, HIGH, 30000);
  if (duration <= 0) {
    return -1.0; // we dont want a negative time value
  }

  // Distance in cm, the divison by 2 is because the distance is traveled twice, once from trig and back by echo
  float distance = (duration * 0.0343) / 2.0;
  return distance;
}



void setup() {
  //trig is the output, and echo is the input
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
   myServo.attach(servo); // 4. Initialize servo
  myServo.write(deg);     // Start at 0 degrees
   // Initialize with the I2C addr 0x3C (common for 128x64)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
//small delay for the code to begin(not needed but good to have)
  delay(100);

 display.clearDisplay();
 display.setTextSize(1);      // Normal 1:1 pixel scale
 display.setTextColor(SSD1306_WHITE);//set colour
 display.setCursor(0, 0);     // Start at top-left corner
 display.display(); // Push the initial clear to the screen
}

void loop() {

// 1. Clear the internal buffer
  display.clearDisplay();

  display.setTextSize(1);      
  display.setCursor(85, 0);
  display.print(deg);
  display.print((char)247); // Degree symbol code
  
  // 2. Set text properties
  display.setTextSize(1);      
  display.setCursor(0, 0);

double distance = readDistanceCM();//call the distance function created above


if(distance>=14 || distance<0)
{
  digitalWrite(led, LOW);
    noTone(buzzer);
    digitalWrite(buzzer, LOW);
    
    // Update the angle
    deg += change;
if(deg>=180||deg<=0)
{
change=-change;

}
myServo.write(deg);
}
else {
    // STOP and WARNING if something is too close
    display.setCursor(0, 50);
    display.print("!!! OBJECT DETECTED !!!");
    digitalWrite(led, HIGH);
 digitalWrite(buzzer, HIGH);
    // We don't update 'angle' here, so the servo stays still
  }


    if (distance < 0) {
      Serial.println("Distance: invalid");//we want positive distances, not negative
      display.setCursor(0, 20);
    display.print("Out of range");
    Serial.println("Distance: invalid");
    }
    else {
    // Large font for the actual number
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.print(distance, 2); // 2 decimal places
    display.print(" cm");
    }

//display distance in cm(4 decimal places)
Serial.print("Deg: ");
  Serial.print(deg);
  Serial.print(" | Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

display.display();
delay(15);
}
