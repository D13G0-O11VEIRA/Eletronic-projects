// C++ code

// PARAMETROS
int pin_led1 = 2;
int pin_led2 = 3;
int pin_led3 = 4;
int pin_led4 = 5;
int pin_led5 = 6;
int pin_led6 = 7;
int pin_led7 = 8;
int pin_led8 = 9;

int pin_bt1 = 10;
int pin_bt2 = 11;
int pin_bt3 = 12;

// VARIAVEIS
int leitura_bt1 = 0; // Seq.
int leitura_bt2 = 0; // Temp+
int leitura_bt3 = 0; // Temp-

int status_led = 0;
int seq_atual = 1;
int tempo = 500;

// CONFIG. PINOS ARDUINO
void setup()
{
	pinMode(pin_led1, OUTPUT);
  	pinMode(pin_led2, OUTPUT);
	pinMode(pin_led3, OUTPUT);
	pinMode(pin_led4, OUTPUT);
	pinMode(pin_led5, OUTPUT);
	pinMode(pin_led6, OUTPUT);
	pinMode(pin_led7, OUTPUT);
	pinMode(pin_led8, OUTPUT);
	pinMode(pin_bt1, INPUT);
  	pinMode(pin_bt2, INPUT);
  	pinMode(pin_bt3, INPUT);
  	Serial.begin(9600);
}

// LOOP DE ACIONAMENTO
void loop()
{
	leitura_bt1 = digitalRead(pin_bt1); //VALOR DO BOTÃO SEQ.
  	leitura_bt2 = digitalRead(pin_bt2); //VALOR DO BOTÃO +
   	leitura_bt3 = digitalRead(pin_bt3); //VALOR DO BOTÃO -
	
	if (leitura_bt1 == 1) // INCREMENTO AO ACIONAR O BOTÃO
    {
    	seq_atual = seq_atual + 1;
      	if (seq_atual > 3) // RESET NA CONTAGEM
    	{
    		seq_atual = 1;
    	}
  	}  
  	
  	Serial.println(seq_atual);	
}
