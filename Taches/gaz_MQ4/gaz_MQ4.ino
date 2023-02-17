void setup() {
  // put your setup code here, to run once:

}

// declaration de pin A0 pour l capteur de GAZ MQ4
int smokeA0 = A0;

void loop() {
  
int limit = analogRead(smokeA0);

// affichage dans le moniteur serie "Limit: valeur" ... 
Serial.print("\nLimit: ");
Serial.print(limit);
}
