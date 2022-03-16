#include <Arduino.h>
int motor = 8;
int relay = 10;
int direction = false;
int EndlageL = false;
int EndlageR = false;
int counter = 0;
int sensorValue = analogRead(A0);

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
  Serial.println(sensorValue);

  // Motor betätigen
  digitalWrite(motor, HIGH);

  // 1. stoppen, 2.umdrehen und 3. wieder starten
  if (sensorValue >= 670 || sensorValue <= 414)
  {
    // 1. stoppen
    digitalWrite(motor, false);

    // 2. umdrehen
    direction = !direction;
    digitalWrite(relay, direction);
    delay(500);

    // 3. wieder starten
    digitalWrite(motor, true);
    delay(500);
  }
}