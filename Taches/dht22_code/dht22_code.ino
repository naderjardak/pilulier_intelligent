// biblio pour dht22
//{
#include <DHT.h>
#include <DHT_U.h>
//}


//declaration de pin et de reference de captur
DHT dht(2,DHT22);

void setup() {

  //lncement de capteur de temperature..
       dht.begin();
       
  //lencement de moniteur serie...
       Serial.begin(115200);
}

void loop() {
float t = dht.readTemperature();  //variable de temperature...
Serial.print(t); // afficher le valeur de tmperature sur le moniteur serie
}
