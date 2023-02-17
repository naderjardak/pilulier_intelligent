#define BLYNK_PRINT Serial
#define BLYNK_MAX_SENDBYTES 128

// biblioteque de temp...

//biblioteque de module wifi...
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

//biblioteque d'affichur LCD(16*2)...
#include <LiquidCrystal.h>

//declaration des de LCD 
LiquidCrystal lcd(9, 8, 5, 4, 3, 7);

//library de capteur de tmperature..
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHT22);

BlynkTimer timer;


char auth[] = "Oz1eaMcQmnxrftOZFrs-6Qlbe0c81Kwl";
char ssid[] = "TOPNET_9C38";
char pass[] = "jrnader1999";


const int temp=0, al=6,led1=10,led2=11,led3=12,led4=13,con=22,decon=24;

int h40,h41,h42,h30,h31,h32,h20,h21,h22,h10,h11,h12,s1,s2,s3,s4,H;

int m1=1,m2=1,m3=1,m4=1;
String medic1;
String medic2;
String medic3;
String medic4;

// En raport avec esp(Wifi)
#define EspSerial Serial3
// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);


// predure de l'interuption :

              void med1()
              {
                m1=-1;
              }
              
              void med2()
              {
                m2=-1;
              }
              
              void med3()
              {
                m3=-1;
              }
              
              void med4()
              {
                m4=-1;
              }

// inportation de nom de medicament de l'application

            BLYNK_WRITE(V1) {          
               medic1 = param.asStr(); 
              
            }
            
            BLYNK_WRITE(V2) {
               medic2 = param.asStr(); 
              
            }
            
            BLYNK_WRITE(V3) { 
               medic3 = param.asStr();
              
            }
            
            BLYNK_WRITE(V4) { 
               medic4 = param.asStr(); 
              
            }

// fin de l'importation des nom





 BLYNK_WRITE(V10) {          
               h10 = param.asInt(); 
              
            }
            
            BLYNK_WRITE(V11) {
              h11 = param.asInt(); 
              
            }
            
            BLYNK_WRITE(V12) { 
                h12 = param.asInt();
              
            }
            
            BLYNK_WRITE(V13) { 
                h20 = param.asInt();
              
            }
            
 BLYNK_WRITE(V14) {          
                h21 = param.asInt(); 
              
            }
            
            BLYNK_WRITE(V15) {
               h22 = param.asInt();
              
            }
            
            BLYNK_WRITE(V16) { 
                h30 = param.asInt();
              
            }
            
            BLYNK_WRITE(V17) { 
                h31 = param.asInt();
              
            }
                        
            BLYNK_WRITE(V18) { 
                h32 = param.asInt();
              
            }
            
            BLYNK_WRITE(V19) { 
                h40 = param.asInt();
              
            }
            
 BLYNK_WRITE(V20) {          
               h41 = param.asInt();
              
              
            }
            
            BLYNK_WRITE(V21) {
               h42 = param.asInt();
              
              
            }
           

WidgetRTC rtc;
// Digital clock display of the time
void clockDisplay()
{

  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  lcd.setCursor(0, 0);
  lcd.print("time: ");
  lcd.print(String(hour()) + ":" + minute());
  lcd.print(" ");

}
BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();
}



void temperature()
{
 float t = dht.readTemperature();  //variable de temperature...
 lcd.setCursor(0, 1);
 lcd.print(t);
 Blynk.virtualWrite(V0,t);
   while(t>30)
          {
            lcd.setCursor(0, 0);
            lcd.print("Alarm temperature");
            tone(al,440,2000);
            noTone(al);
          } 
}


  
 
  
void setup()
{
      // Debug console
      Serial.begin(115200);
    
    // Set ESP8266 baud rate
        EspSerial.begin(ESP8266_BAUD);
        delay(10);
      
    // connection au resau wifi and access to page host...
           Blynk.begin(auth, wifi, ssid, pass, "192.168.1.14", 8080);
    
    // des interreption a l'ouverture de boite de medic1
          attachInterrupt(digitalPinToInterrupt(18), med1, RISING);
    // des interreption a l'ouverture de boite de medic2
          attachInterrupt(digitalPinToInterrupt(19), med2, RISING);
    // des interreption a l'ouverture de boite de medic3
          attachInterrupt(digitalPinToInterrupt(20), med3, RISING);
    // des interreption a l'ouverture de boite de medic4
          attachInterrupt(digitalPinToInterrupt(21), med4, RISING);
    
    // lencement d'afficheur lcd(16*2).
       lcd.begin(16,2);
    //lncement de capteur de temperature..
       dht.begin();
       
    // declaration de pin...
       pinMode(con, OUTPUT);
       pinMode(decon, OUTPUT);
       pinMode(al, OUTPUT);
       pinMode(led1, OUTPUT);
       pinMode(led2, OUTPUT);
       pinMode(12, OUTPUT);
       pinMode(led4, OUTPUT);
       pinMode(2, INPUT_PULLUP);
       pinMode(18, INPUT_PULLUP);
       pinMode(19, INPUT_PULLUP);
       pinMode(20, INPUT_PULLUP);
       pinMode(21, INPUT_PULLUP);


  setSyncInterval(10 * 60); // Sync interval in seconds (10 minutes)

  // Display digital clock every 10 seconds
  timer.setInterval(10000L, clockDisplay);
  timer.setInterval(10000L, temperature);
}

int millisecondes=60000;    // 1 minute en millisecondes
int a1,a2,a3,a4,alM1,alM2,alM3,alM4;
int Te=60;

void programm() 
{ 
    int dtime;                        // delay time ...


// alarme de mdicamant...  
//V10..V12 (variabl vertuelle de declanchemant d'alarme pour mdic 1)...
H=hour();
 s1=0 ;
 s2=0 ;
 s3=0 ;
 s4=0 ;

                while((h10==H ||h11==H ||h12==H) and m1>0)              
                    {s1=1;
                    lcd.setCursor(0, 0);
                    lcd.print(medic1);
                    digitalWrite(led1, HIGH);
                    WidgetLED led1(V101);
                    led1.off();
                    led1.on();
                    
                        tone(al,440,2000);
                        noTone(al);
                        
                            a1++;//compter les millisecondes...
                            
                                if (a1>millisecondes)
                                {
                                alM1++;//compter les minutes...
                                a1=0;
                                }
                                lcd.clear();
                     }
                     
                  
           m1=1;
           digitalWrite(led1, LOW);
         
//V20..V22 (variabl vertuelle de declanchemant d'alarme pour mdic 2).


                 while((h20==H|| h21==H || h21==H)and(m2>0))
                  {
                    
                  s2=1;
                    lcd.setCursor(0, 0);
                    lcd.print(medic2);
                    digitalWrite(led2, HIGH);
                    WidgetLED led2(V102);
                    led2.off();
                    led2.on();
                  
                          tone(al,440,2000);
                          noTone(al);
                          
                                a2++;//compter les millisecondes...
                              
                                if (a2>millisecondes)
                                {
                                alM2++;//compter les minutes...
                                a2=0;
                                }
                    
                    lcd.clear();
                  }
            m2=1;
            digitalWrite(led2, LOW);
         
//V30..V32 (variabl vertuelle de declanchemant d'alarme pour mdic 3).


                  while((h30==H|| h31==H || h32==H)and m3>0)
                    {s3=1;
                    lcd.setCursor(0, 0);
                    lcd.print(medic3);
                    digitalWrite(led3, HIGH);
                    WidgetLED led3(V103);
                    led3.off();
                    led3.on();
              
                        tone(al,440,2000);
                        noTone(al);
                        
                                a3++;//compter les millisecondes...
                            
                                if (a3>millisecondes)
                                {
                                alM3++;//compter les minutes...
                                a3=0;
                                }
                 
                    lcd.clear();
                  }
            m3=1;
            digitalWrite(led3, LOW);
    
//V40..V42 (variabl vertuelle de declanchemant d'alarme pour mdic 4).
                  

                  if(((h40==H|| h42==H) || h41==H)and m4>0)
                  { 
                    s4=1;
                    lcd.setCursor(0, 0);
                    lcd.print(medic4);
                    digitalWrite(led4, HIGH);
                    WidgetLED led4(V104);
                    led4.off();
                    led4.on();
                   
                        tone(al,440,2000);
                        noTone(al);
                        
                              a4++;//compter les millisecondes...
                            
                              if (a4>millisecondes)
                              {
                              alM4++;//compter les minutes...
                              a4=0;
                              }
                  
                  }
                   
            
            m4=1;
            digitalWrite(led1, LOW); 

      

// si le pation n'a pas prix son medicament.. 
// en declenche un msg pour la famille...


          if(alM1==Te || alM2==Te || alM3==Te || alM4==Te)
          {
            Blynk.email("naderjardak5@gmail.com","medicamant"," le patient n'as pas pris ses medicamnt");// send message d'alarme gmail...
          }

          alM1=0;
          alM2=0;
          alM3=0;
          alM4=0;
          
         
         while (((s1==1 || s2==1) || (s3==1 || s4==1))and H==hour())
         {
                  temperature();
                  clockDisplay();
         }

       
}  




void loop()
{
   timer.run();  
   
      if (Blynk.connected()) {  
              Blynk.run();
              digitalWrite(con, HIGH);
              digitalWrite(decon, LOW);
      } else {
              digitalWrite(con, LOW);
              digitalWrite(decon, HIGH);
              Blynk.connect(); 
      } 
      
      
  programm();
  
}
