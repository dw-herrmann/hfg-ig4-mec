#include <Arduino.h>
int motor = 8;
int relay = 10;
int direction = false;
// left = false
// right = true
int EndlageL = false;
int EndlageR = false;
int counter = 0;
int sensorValue = analogRead(A0);
int LDRLeft = analogRead(A1);
int LDRRight = analogRead(A2);
int endLeft = 414;
int endRight = 670;

int difference;

void setup()
{
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
  pinMode(relay, OUTPUT);
}

void loop()
{
  // Sensor auslesen
  sensorValue = analogRead(A0);
  LDRLeft = analogRead(A1);
  LDRRight = analogRead(A2);

  Serial.print(sensorValue);

  Serial.print("L=");
  Serial.print(analogRead(A1));
  Serial.print("  \t// R=");
  Serial.print(analogRead(A2));

  Serial.print("  \t// D=");
  // grüner bereich
  if (sensorValue >= endLeft + 20 || sensorValue <= endRight - 20)
  {
    // Werte vergleichen
    difference = LDRLeft - LDRRight;

    if (abs(difference) > 15)
    { // Schwellwert erreicht

      if (LDRLeft > LDRRight)
      { // links ist heller
        // Switch an, richtung links
        Serial.print("toL");
        direction = false;
      }
      else
      { // rechts ist heller
        // Switch aus, richtung rechts
        Serial.print("toR");
        direction = true;
      }

      digitalWrite(relay, direction);

      // Motor betätigen
      // digitalWrite(motor, true);
    }
    else
    // guckt schon auf hellsten Punkt
    {
      // digitalWrite(motor, false);
      Serial.print("static");
    }
  }
  // gelber Bereich
  else if (
      // falls in Wertebereich left
      sensorValue >= (endLeft + 20) && sensorValue <= (endLeft))
  {
    Serial.print("toFarL");
    if (direction == true) // richtung rechts (true), dann starten, ansonsten anhalten
    {
      // digitalWrite(motor, true);
    }
    else
    {
      // digitalWrite(motor, false);
    }
  }
  else if (
      // falls in Wertebereich right
      sensorValue >= (endRight - 20) && sensorValue <= (endRight))
  {
    Serial.print("toFarR");
    if (direction == false) // richtung links (false), dann starten, ansonsten anhalten
    {
      // digitalWrite(motor, true);
    }
    else
    {
      // digitalWrite(motor, false);
    }
  }
  // roter Bereich
  else
  {
    // digitalWrite(motor, false);
    Serial.print("dead");
  }
  Serial.println();
}
