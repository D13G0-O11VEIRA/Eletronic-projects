// C++ code

//VARIAVEIS
int pin_led1 = 2;
int pin_bt1 = 3;
int leitura_bt1 = 0;
int status_led = 0;

//CONFIG. ENTRADAS ARDUINO
void setup()
{
	pinMode(pin_led1, OUTPUT);
	pinMode(pin_bt1, INPUT);
}

//LOOP DE ACIONAMENTO
void loop()
{
	leitura_bt1 = digitalRead(pin_bt1); //VALOR DO BOTÃO
	if (leitura_bt1 == 1)
    {
      	status_led = !status_led; // SELO DO BOTÃO
    }  
	
    digitalWrite(pin_led1, status_led); // ACIONAMENTO DO LED
}
