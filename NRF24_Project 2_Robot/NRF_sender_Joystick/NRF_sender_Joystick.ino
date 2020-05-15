#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}
char All_buffers[5];

void loop()
{
  int xValue = constrain(map(analogRead(A0), 0, 900, -5, 5), -5, 5);
  int yValue = map(analogRead(A1), 0, 1023, -5, 5);

  char buffer[2];
  dtostrf(xValue, 2, 0, buffer);
  copy( buffer, All_buffers , 2);
  dtostrf(yValue, 2, 0, buffer);
  copy( buffer, All_buffers + 2 , 2);

  radio.write(&All_buffers, sizeof(All_buffers));
  Serial.println(All_buffers);

  delay(100);
}


void copy(char* src, char* dst, int len) {
  memcpy(dst, src, sizeof(src[0])*len);
}
