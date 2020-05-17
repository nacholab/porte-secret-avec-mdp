#include <Servo.h>

Servo myServo;
const int piezo = A0;
const int switchPin = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int redLed = 5;

int knockVal;
int switchVal;


const int quietKnock = 3;
const int loudKnock = 50;

boolean locked = false;
int numbersOfKnocks = 0;

void setup() {
    myServo.attach(9);
    pinMode(yellowLed,OUTPUT);
    pinMode(greenLed,OUTPUT);
    pinMode(redLed,OUTPUT);
    pinMode(switchPin,INPUT);
    Serial.begin(9600);
    digitalWrite(greenLed, HIGH);
    myServo.write(0);
    Serial.println("La porte est ouverte");
}

void loop() {
    if(locked == false)
    {
        switchVal = digitalRead(switchPin);
        if(switchVal == HIGH)
        {
            locked = true;
            digitalWrite(greenLed, LOW);
            digitalWrite(redLed, HIGH);
            myServo.write(90);
            Serial.println("La porte est fermée");
            numbersOfKnocks=0;
            delay(1000);
        }
    }
    if(locked == true)
    {
        knockVal = analogRead(piezo);
        if(numbersOfKnocks < 3 && knockVal > 0)
        {
            if(checkForKnock(knockVal)== true)
            {
                numbersOfKnocks++;
            }
            Serial.print(3-numbersOfKnocks);
            Serial.println("coup restant ");
        }

        if(numbersOfKnocks >= 3)
        {
            locked = false;
            myServo.write(0);
            delay(20);
            digitalWrite(greenLed, HIGH);
            digitalWrite(redLed, HIGH);
            Serial.println("La boite est ouvert !");
        }
    }
}
boolean checkForKnock(int value){
    if(value > quietKnock && value < loudKnock)
    {
        digitalWrite(yellowLed, HIGH);
        delay(50);
        digitalWrite(yellowLed, LOW);
        Serial.print("Coup valid de valeur ");
        Serial.println(value);
        return true;
    }else
    {
        Serial.print("Mauvaise valeur de coup ");
        Serial.println(value);
        return false;    
    }
    
}
