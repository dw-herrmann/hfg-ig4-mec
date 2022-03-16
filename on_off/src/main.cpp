#include <Arduino.h>
int motor = 8;
int relay = 10;
int direction = false;

void setup()
{
  pinMode(motor, OUTPUT);
  pinMode(relay, OUTPUT);
  // test
}

void loop()
{
  // anschalten
  digitalWrite(motor, HIGH);

  // 3000 ms
  delay(3000);

  // ausschalten
  digitalWrite(motor, LOW);

  // 100 ms delay
  delay(500);

  // direction umschalten und relay ansprechen
  direction = !direction;
  digitalWrite(relay, direction);
}