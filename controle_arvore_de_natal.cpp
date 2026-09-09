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
	leitura_bt1 = digitalRead(pin_bt1);
  	leitura_bt2 = digitalRead(pin_bt2);
   	leitura_bt3 = digitalRead(pin_bt3);
	
	//BOTÃO SEQ.
  	if (leitura_bt1 == 1) // INCREMENTO AO ACIONAR O BOTÃO
    {
    	seq_atual = seq_atual + 1;
      	if (seq_atual > 3) // RESET NA CONTAGEM
    	{
    		seq_atual = 1;
    	}
  	}  
  	
  	//BOTÃO +
  	if (leitura_bt2 == 1) // INCREMENTO AO ACIONAR O BOTÃO
    {
    	tempo = tempo + 100;
  	}  
  
  	//BOTÃO -
  	if (leitura_bt3 == 1) // DECRESCIMO AO ACIONAR O BOTÃO
    {
    	tempo = tempo - 100;
  	}  
   
  	// PADRÕES DAS SEQUENCIAS
  	if (seq_atual == 1)
    {
    	digitalWrite(pin_led1, HIGH);
        delay(tempo);
        digitalWrite(pin_led2, HIGH);
        delay(tempo);
        digitalWrite(pin_led3, HIGH);
        delay(tempo);
        digitalWrite(pin_led4, HIGH);
        delay(tempo);
        digitalWrite(pin_led5, HIGH);
        delay(tempo);
        digitalWrite(pin_led5, HIGH);
        delay(tempo);
        digitalWrite(pin_led6, HIGH);
        delay(tempo);
        digitalWrite(pin_led7, HIGH);
        delay(tempo);
   		digitalWrite(pin_led8, HIGH);
        delay(tempo);
      
   		digitalWrite(pin_led8, LOW);
        delay(tempo);
        digitalWrite(pin_led7, LOW);
        delay(tempo);
        digitalWrite(pin_led6, LOW);
        delay(tempo);
        digitalWrite(pin_led5, LOW);
        delay(tempo);
        digitalWrite(pin_led4, LOW);
        delay(tempo);
        digitalWrite(pin_led3, LOW);
        delay(tempo);
        digitalWrite(pin_led2, LOW);
        delay(tempo);
        digitalWrite(pin_led1, LOW);
        delay(tempo);
    }
  
  	Serial.print("seq_atual = ");	
   	Serial.println(seq_atual);	
    Serial.print("tempo = ");	
  	Serial.println(tempo);	
  	Serial.println("");	
  
	delay(1000);
}
