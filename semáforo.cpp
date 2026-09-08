// C++ code

//CONF. SAIDA P/ PINOS 8, 9, 10
void setup()
{
	  pinMode(10, OUTPUT);
  	pinMode(9, OUTPUT);
  	pinMode(8, OUTPUT);
}

void loop()
{
	digitalWrite(8, HIGH); // LIGA PINO 8
 	digitalWrite(10, LOW); // DESLIGA PINO 10	 
	delay(4000); // ESPERA 4SEG.
	digitalWrite(9, HIGH); //LIGA PINO 9
	digitalWrite(8, LOW); // DESLIGA PINO 8
	delay(2000); // ESPERA 2SEG.
 	digitalWrite(10, HIGH); // LIGA PINO 10
 	digitalWrite(9, LOW); // DESLIGA PINO 9
	delay(3000); // ESPERA 3SEG.
}
