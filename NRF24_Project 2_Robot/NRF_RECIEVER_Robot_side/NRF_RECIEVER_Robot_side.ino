#define MA1 3
#define MA2 5
#define MB1 6
#define MB2 9

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  pinMode(MA1, 1);
  pinMode(MA2, 1);
  pinMode(MB1, 1);
  pinMode(MB2, 1);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  String s;
  char m1b, m1f, m2b, m2f;
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    
    if (text[0] == '-') {
      s= text[1];
      m1b = s.toInt();
      m1f = 0;
      
    } else {
       s= text[1];
      m1f = s.toInt();
      m1b = 0;
    }
    if (text[2] == '-' ) {
             s= text[3];
      m2b = s.toInt();
      m2f = 0;

    } else {
       s= text[3];
      m2f = s.toInt();
      m2b = 0;
    }



    analogWrite(MA1,  (m1f)*25);
    analogWrite(MA2, (m1b)*25);
    analogWrite(MB1, (m2f)*25);
    analogWrite(MB2, (m2b)*25);

        Serial.print(String(sizeof(text))+"     ");

    Serial.print((m1f));
    Serial.print( (m1b));
    Serial.print((m2f));
    Serial.print((m2b));
    Serial.println();

  }
}
