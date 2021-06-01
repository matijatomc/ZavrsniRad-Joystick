// Potrebne bibilioteke za program
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Oderđivanje na kojim se pinovima nalazi CE i CSN pinovi modula
RF24 radio1(7, 8); 
RF24 radio2(7, 8); 
// Određivanje kanala preko kojeg će moduli komunicirat
const byte address1[6] = {"00001"}; 
const byte address2[6] = {"00002"}; 

// Void koji će se odvrtiti samo jednom nakon pokretanja Arduina
void setup() {
  Serial.begin(9600);
  radio1.begin(); // Započinjanje radio veze
  radio2.begin();
  // Postavljanje adrese od kanala za odašiljač preko kojeg če komunicirat
  radio1.openWritingPipe(address1); 
  radio2.openWritingPipe(address2);
  //Postavljanje maksimalne razine pojačanja snage
  radio1.setPALevel(RF24_PA_MAX); 
  radio2.setPALevel(RF24_PA_MAX); 
}

// Void koji će se vrtiti cijelo vrijeme dok Arduino radi
void loop() {
  radio1.stopListening(); // Postavljanje modula kao odašiljač
  radio2.stopListening();

  // Čitanje vrijednmosti potenciometra na analognom pinu 1
  int potBrzine = analogRead(A1); 
  // Mapitanje vrijednosti potenciometra u vrijednost kojoj radi motor
  int vrijednostBrzine = map(potBrzine, 0, 1023, 0, 180) ;

  // Čitanje vrijednmosti joystica na analognom pinu 0
  int potSkretanje = analogRead(A0); 
  // Mapitanje vrijednosti joytica u vrijednost kojoj radi servo
  int kutSkretanja = map(potSkretanje, 0, 1023, 0, 180); 

  // Slanje vrijednost za sevo
  Serial.print("Skretanje: "); Serial.println(kutSkretanja);
  radio1.write(&kutSkretanja, sizeof(kutSkretanja)); 
  // Slanje vrijednosti za motor
  Serial.print("Brzin: "); Serial.println(vrijednostBrzine);
  radio2.write(&vrijednostBrzine, sizeof(vrijednostBrzine)); 
  //delay(500);
}
