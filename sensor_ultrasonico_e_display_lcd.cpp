// C++ code

#include <LiquidCrystal.h>

int pin_trig = 2;
int pin_echo = 3;
int pin_RS = 4;
int pin_E = 5;
int pin_4 = 6;
int pin_5 = 7;
int pin_6 = 8;
int pin_7 = 9;
int pin_bt = 10;

LiquidCrystal lcd(pin_RS, pin_E, pin_4 , pin_5 , pin_6 , pin_7);
unsigned long tempo = 0;	// tempo
float dis = 0;				// distancia
float v_som = 0.0343218; 	// velocidade do som em cm/µs
int lei_bt = 0;				// leitura do botão
int menu = 0;				// menu do display

void setup(){
	pinMode(pin_trig, OUTPUT);
    pinMode(pin_echo, INPUT);
  	pinMode(pin_bt, INPUT);  
  
  	Serial.begin(9600);
  	lcd.begin(16, 2);
}

void loop(){
  	lei_bt = digitalRead(pin_bt);
  	if (lei_bt == HIGH){
  		menu++;
    	if(menu > 1){
    		menu = 0;
    	}
    }
  	if (menu == 0){
  		lcd.clear();
    	lcd.setCursor(0, 0);
    	lcd.print("Menu: ");
    	lcd.setCursor(7, 0);
    	lcd.print(menu);
      
    	lcd.setCursor(0, 1);
		lcd.print("Dist: ");
    	lcd.setCursor(6, 1);
		lcd.print(dis);
    	lcd.setCursor(12, 1);
		lcd.print("cm");  
    }    
  	if (menu == 1){
  		lcd.clear();
    	lcd.setCursor(0, 0);
    	lcd.print("Menu: ");
    	lcd.setCursor(7, 0);
    	lcd.print(menu);
      
    	lcd.setCursor(0, 1);
		lcd.print("Dist: ");
    	lcd.setCursor(6, 1);
		lcd.print(dis/100.00);
    	lcd.setCursor(12, 1);
		lcd.print("m");  
    }     
  	
	digitalWrite(pin_trig, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(pin_trig, LOW);
  	tempo = pulseIn(pin_echo, HIGH);
  	dis = (tempo*v_som)/2;
  
  	Serial.print("Tempo ida e volta = ");
    Serial.print(tempo);
  	Serial.println("us");
  	Serial.print("Distancia = ");
    Serial.print(dis);
  	Serial.println("cm");
  	Serial.println("=========================");
  	delay(1000);
}
