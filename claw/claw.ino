#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

int HandSpeed = 250;


void Hand_close()
{
  Hand.run(HandSpeed);
}
void Hand_open()
{
  Hand.run(-HandSpeed);
}
