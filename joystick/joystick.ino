// Potrebne bibilioteke za program
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Oderđivanje na kojim se pinovima nalazi CE i CSN pinovi modula
RF24 radio(7, 8); 
// Određivanje kanala preko kojeg će moduli komunicirat
const byte address[6] = {"00001"}; 

// Void koji će se odvrtiti samo jednom nakon pokretanja Arduina
void setup() {
  Serial.begin(9600);
  radio.begin(); // Započinjanje radio veze
  // Postavljanje adrese od kanala za odašiljač preko kojeg če komunicirat
  radio.openWritingPipe(address); 
  //Postavljanje maksimalne razine pojačanja snage
  radio.setPALevel(RF24_PA_MAX); 
}

// Void koji će se vrtiti cijelo vrijeme dok Arduino radi
void loop() {
  radio.stopListening(); // Postavljanje modula kao odašiljač

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
  radio.write(&kutSkretanja, sizeof(kutSkretanja)); 
  // Slanje vrijednosti za motor
  Serial.print("Brzin: "); Serial.println(vrijednostBrzine);
  radio.write(&vrijednostBrzine, sizeof(vrijednostBrzine)); 
  //delay(500);
}
