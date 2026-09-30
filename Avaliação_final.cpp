// C++ code
//MENU = 0 - POT UN
//	   ==> STATUS: ON / OFF
//	   ==> VALOR POT (UND) : 0 - 1023
//
//MENU = 1 - POT V1
//	   ==> STATUS: ON / OFF
//	   ==> VALOR POT : 0 - 5V
//
//MENU = 2 - VEL PWM
//	   ==> STATUS: ON / OFF
//	   ==> VEL PWM : 0 - 255
//
//MENU = 3 - VEL%
//	   ==> STATUS: ON / OFF
//	   ==> VEL % : 0 - 100%
//
//BOTÃO START STOP
//POTENCIOMETRO - VELOCIDADE

#include <LiquidCrystal.h>

int pin_pt = A0;        // Potenciômetro
int pin_led = 3;		// Led motor ligado
int pin_tip120 = 5;		// Transistor
int pin_bt1 = 6;		// Botão start stop
int pin_bt2 = 7;		// Botão Menu Up Down
int pin_RS = 8;			// LCD Seleçao de registro
int pin_E = 9;			// LCD Ativar
int pin_db4 = 10;		// LCD DB4
int pin_db5 = 11;		// LCD DB5
int pin_db6 = 12;		// LCD DB6
int pin_db7 = 13;		// LCD DB7

LiquidCrystal lcd(pin_RS, pin_E, pin_db4 , pin_db5 , pin_db6 , pin_db7);
int lei_bt1 = 0;      	// Leitura do botão de velocidade
int lei_bt2 = 0;      	// Leitura do botão de menu
int lei_pt = 0;         // Leitura do potenciômetro
float ten = 0;          // Tensão em Volts
int vel_mt_pwm = 0;     // Valor alvo de PWM para o motor
float vel_mt_per = 0;   // Percentual de velocidade do motor
int pwm_atual = 0;		// Velocidade atual aplicada durante a rampa
int menu = 0;			// menu do display

void setup(){
  	pinMode(pin_led, OUTPUT);
  	pinMode(pin_tip120, OUTPUT);
	pinMode(pin_bt1, INPUT);
	pinMode(pin_bt2, INPUT);
   	
  	lcd.begin(16, 2);
	Serial.begin(9600);
}

void loop(){
	// Leitura do Potenciômetro e cálculo da tensão e porcentagem
	lei_pt = analogRead(pin_pt);   
	ten = (lei_pt * 5.0) / 1023.0;    
	// Mapeia os valores analógicos para o PWM e %
	vel_mt_pwm = map(lei_pt, 0, 1023, 0, 255);
	vel_mt_per = (lei_pt / 1023.0) * 100.0;
	// Leitura dos botões
	lei_bt1 = digitalRead(pin_bt1);
  	lei_bt2 = digitalRead(pin_bt2);
	if (lei_bt1 == HIGH){ // start stop
		
      
      	analogWrite(pin_tip120, vel_mt_pwm);
		pwm_atual = vel_mt_pwm;
	}
  
  
  	if (lei_bt2 == HIGH) { // menu
		menu++;
    	if(menu > 3){
    		menu = 0;
    	}
	}
    
  	if (menu == 0){
  		lcd.clear();
    	lcd.setCursor(0, 0);
    	lcd.print("Menu: ");
    	lcd.setCursor(7, 0);
    	lcd.print(menu);    	 
    }    
  	if (menu == 1){
  		lcd.clear();
    	lcd.setCursor(0, 0);
    	lcd.print("Menu: ");
    	lcd.setCursor(7, 0);
    	lcd.print(menu);   	
    }     
  	if (menu == 2){
  		lcd.clear();
    	lcd.setCursor(0, 0);
      	lcd.print("Menu: ");
    	lcd.setCursor(7, 0);
    	lcd.print(menu);
    }
    if (menu == 3){
  		lcd.clear();
    	lcd.setCursor(0, 0);
    	lcd.print("Menu: ");
    	lcd.setCursor(7, 0);
    	lcd.print(menu);
    }
  
  
	// Saída para o cmd serial
	Serial.print("Valor do potenciometro = ");
	Serial.println(lei_pt);
	Serial.print("Valor da tensao = ");
	Serial.print(ten);
	Serial.println("V");
	Serial.print("Velocidade em PWM = ");
	Serial.println(vel_mt_pwm); 
	Serial.print("Velocidade em porcentagem = ");
	Serial.print(vel_mt_per);
	Serial.println("%");  
		
	Serial.println("===================================");
	delay(300);
}
