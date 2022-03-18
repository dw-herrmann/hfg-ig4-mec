#include <Arduino.h>
int motor = 8;
bool power = false;
int relay = 10;
bool direction = false;
bool left = true;
bool right = false;
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

  // ---- ---- --- ---- ----- //
  // -- Richtung festlegen -- //
  // ---- ---- --- ---- ----- //
  if (abs(difference) > 15)
  { // Schwellwert erreicht

    if (LDRLeft > LDRRight)
    { // links ist heller
      // Switch an, richtung links
      Serial.print("toL");
      direction = left;
    }
    else
    { // rechts ist heller
      // Switch aus, richtung rechts
      Serial.print("toR");
      direction = right;
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

  // ---- ---- ---- ---- //
  // -- Grüner Bereich - //
  // ---- ---- ---- ---- //
  if (endLeft + 20 < sensorValue && sensorValue < endRight - 20)
  {
    // passt alles
  }
  // ---- ---- ---- ---- //
  // -- Gelber Bereich - //
  // ---- ---- ---- ---- //
  else if (endLeft < sensorValue && sensorValue < endRight) // falls in Wertebereich left
  {
    if (sensorValue < endLeft + 20)
    {
      Serial.print("toFarL");

      if (direction == right) // nach rechts (true) starten
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
      if (direction == left) // nach links (false) starten
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
    digitalWrite(relay, direction);
    delay(100);
    digitalWrite(motor, power);
    dirChange = power;
  }
}
