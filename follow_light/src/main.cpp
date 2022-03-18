#include <Arduino.h>
int motor = 8;
bool power = false;
int relay = 10;
bool direction = false;
// left:  false
// right: true
bool dirChange = direction;
bool EndlageL = false;
bool EndlageR = false;
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

      // Motor betätigen
      power = true;
    }
    else
    // guckt schon auf hellsten Punkt
    {
      power = false;
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
        power = true;
      }
      else // ansonsten anhalten
      {
        power = false;
      }
    }
    else if (sensorValue > endLeft - 20)
    {
      Serial.print("toFarR");
      if (direction == false) // nach links (false) starten
      {
        power = true;
      }
      else // ansonsten anhalten
      {
        power = false;
      }
    }
  }
  // ---- ---- ---- ---- //
  // -- Roter Bereich - //
  // ---- ---- ---- ---- //
  else
  {
    power = false;
    Serial.print("dead");
  }
  Serial.println();

  // ---- ---- -- ---- ---- //
  // -- Motor Umschalten -- //
  // ---- ---- -- ---- ---- //

  if (dirChange != power) // Wenn direction umgedeht wird, pause einbauen
  {
    digitalWrite(motor, false);
    delay(100);
    digitalWrite(motor, power);
    delay(100);
    dirChange = power;
  }

  digitalWrite(relay, direction);
}
