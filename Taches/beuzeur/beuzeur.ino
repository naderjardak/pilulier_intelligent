
int al=6;

void setup() 
{
pinMode(al, OUTPUT);
}

void loop() 
{
  
      digitalWrite (al, HIGH); // le buzzer est actionné
      delay (500); // délai de 0.5 secondes
      digitalWrite (al, LOW); // le buzzer est à l'arrêt
      delay (500); // délai de 0.5 secondes
      
}
