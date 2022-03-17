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

  // Werte vergleichen
  difference = LDRLeft - LDRRight;

  Serial.print(sensorValue);

  Serial.print(" L=");
  Serial.print(analogRead(A1));
  Serial.print("  \t// R=");
  Serial.print(analogRead(A2));

  Serial.print("  \t// D=");

  // ---- ---- ---- ---- //
  // -- Grüner Bereich - //
  // ---- ---- ---- ---- //
  if (sensorValue > endLeft + 20 && sensorValue < endLeft - 20)
  {

    if (abs(difference) > 5)
    { // Schwellwert erreicht

      if (LDRLeft > LDRRight)
      { // links ist heller
        // Switch an, richtung links
        Serial.print("toL");
        direction = true;
      }
      else
      { // rechts ist heller
        // Switch aus, richtung rechts
        Serial.print("toR");
        direction = false;
      }

      digitalWrite(relay, direction);

      // Motor betätigen
      digitalWrite(motor, true);
    }
    else
    // guckt schon auf hellsten Punkt
    {
      digitalWrite(motor, false);
      Serial.print("static");
    }
  }
  // ---- ---- ---- ---- //
  // -- Gelber Bereich - //
  // ---- ---- ---- ---- //
  else if (sensorValue > endLeft && sensorValue < endLeft) // falls in Wertebereich left
  {
    if (sensorValue < endLeft + 20)
    {
      Serial.print("toFarL");

      if (direction == true) // nach rechts (true) starten
      {
        // digitalWrite(motor, true);
      }
      else // ansonsten anhalten
      {
        // digitalWrite(motor, false);
      }
    }
    else if (sensorValue > endLeft - 20)
    {
      Serial.print("toFarR");
      if (direction == false) // nach links (false) starten
      {
        // digitalWrite(motor, true);
      }
      else // ansonsten anhalten
      {
        // digitalWrite(motor, false);
      }
    }
  }
  // ---- ---- ---- ---- //
  // -- Roter Bereich - //
  // ---- ---- ---- ---- //
  else
  {
    // digitalWrite(motor, false);
    Serial.print("dead");
  }
  Serial.println();
}
