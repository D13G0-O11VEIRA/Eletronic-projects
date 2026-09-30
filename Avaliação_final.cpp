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

int lei_pt = 0;         // Leitura do potenciômetro
float ten = 0;          // Tensão em Volts
int vel_mt_pwm = 0;     // Valor alvo de PWM para o motor
float vel_mt_per = 0;   // Percentual de velocidade do motor
int pwm_atual = 0;		// Velocidade atual aplicada durante a rampa

void setup()
{
  	pinMode(pin_led, OUTPUT);
  	pinMode(pin_tip120, OUTPUT);
	pinMode(pin_bt1, INPUT);
	pinMode(pin_bt2, INPUT);
   	
  	lcd.begin(16, 2);
	Serial.begin(9600);}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}
