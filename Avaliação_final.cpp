//C++ code

#include <LiquidCrystal.h>

// PINOS
const int PIN_POT = A0;		// Potenciômetro
const int PIN_LED = 3;		// Led motor ligado
const int PIN_TIP120 = 5;	// Transistor
const int PIN_BT_START = 6;	// Botão start stop
const int PIN_BT_MENU = 7;	// Botão Menu Up Down
const int PIN_RS = 8;		// LCD Seleçao de registro
const int PIN_E = 9;		// LCD Ativar
const int PIN_DB4 = 10;		// LCD DB4
const int PIN_DB5 = 11;		// LCD DB5
const int PIN_DB6 = 12;		// LCD DB6
const int PIN_DB7 = 13;		// LCD DB7
LiquidCrystal lcd(PIN_RS, PIN_E, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

// VARIÁVEIS
int valorPot = 0; 
float tensao = 0.0;
float velocidadePercentual = 0.0;
int pwmAlvo = 0;
int pwmAtual = 0;
int menu = 0;
const int TOTAL_MENUS = 4;
bool motorLigado = false;

// CONFIGURAÇÕES DOS BOTÕES
const unsigned long DEBOUNCE = 50;
bool estadoAnteriorStart = HIGH;
bool estadoAnteriorMenu = HIGH;
unsigned long ultimoCliqueStart = 0;
unsigned long ultimoCliqueMenu = 0;

// CONFIGURAÇÕES DA RAMPA
const unsigned long INTERVALO_RAMPA = 20;
const int PASSO_ACELERACAO = 6;
const int PASSO_DESACELERACAO = 4;
unsigned long ultimaAtualizacaoRampa = 0;

// CONFIGURAÇÕES DO LCD E SERIAL
const unsigned long INTERVALO_LCD = 200;
const unsigned long INTERVALO_SERIAL = 500;
unsigned long ultimoLCD = 0;
unsigned long ultimoSerial = 0;

void setup() {
	pinMode(PIN_LED, OUTPUT);
  	pinMode(PIN_TIP120, OUTPUT);
  	pinMode(PIN_BT_START, INPUT_PULLUP);
  	pinMode(PIN_BT_MENU, INPUT_PULLUP);

  	lcd.begin(16, 2);
  	Serial.begin(9600);

  	analogWrite(PIN_TIP120, 0);
  	analogWrite(PIN_LED, 0);
  	lcd.clear();
  	lcd.setCursor(0, 0);
  	lcd.print("Controle Motor");
  	lcd.setCursor(0, 1);
  	lcd.print("Iniciando...");
  	delay(1000);
  	atualizarLCD();
}

//Loop principal
void loop() {
  	lerPotenciometro();
  	lerBotaoStart();
  	lerBotaoMenu();
  	controlarMotor();
  	atualizarLCDPeriodicamente();
  	enviarSerialPeriodicamente();
}

// LEITURA DO POTENCIÔMETRO
void lerPotenciometro() {
  	valorPot = analogRead(PIN_POT);
  	tensao = (valorPot * 5.0) / 1023.0;
  	pwmAlvo = map(valorPot, 0, 1023, 0, 255);
	velocidadePercentual = (valorPot * 100.0) / 1023.0;
}

// BOTÃO START / STOP
void lerBotaoStart() {
	bool estadoAtual = digitalRead(PIN_BT_START);
  	if (estadoAtual == LOW && estadoAnteriorStart == HIGH) {
	    if (millis() - ultimoCliqueStart > DEBOUNCE) {
      		motorLigado = !motorLigado;
      		ultimoCliqueStart = millis();
    	}
  	}
  	estadoAnteriorStart = estadoAtual;
}

// BOTÃO MENU
void lerBotaoMenu() {
  	bool estadoAtual = digitalRead(PIN_BT_MENU);
  	if (estadoAtual == LOW && estadoAnteriorMenu == HIGH) {
    	if (millis() - ultimoCliqueMenu > DEBOUNCE) {
	    	menu++;
			if (menu >= TOTAL_MENUS) {
        		menu = 0;
      		}
     	 	ultimoCliqueMenu = millis();
    	}
  	}
	estadoAnteriorMenu = estadoAtual;
}

// CONTROLE DO MOTOR + RAMPA
void controlarMotor() {
  	if (millis() - ultimaAtualizacaoRampa <	INTERVALO_RAMPA) {
  		return;
  	}
  	ultimaAtualizacaoRampa = millis();

  	// MOTOR LIGADO
	if (motorLigado) {
    	if (pwmAtual < pwmAlvo) {
      		pwmAtual += PASSO_ACELERACAO;
      		if (pwmAtual > pwmAlvo) {
        		pwmAtual = pwmAlvo;
      		}
    	} 
    	else if (pwmAtual > pwmAlvo) {
      		pwmAtual -= PASSO_DESACELERACAO;
			if (pwmAtual < pwmAlvo) {
        		pwmAtual = pwmAlvo;
      		}
    	}
	}
	// MOTOR DESLIGADO
	else {
    	if (pwmAtual > 0) {
      		pwmAtual -= PASSO_DESACELERACAO;
		    if (pwmAtual < 0) {
        		pwmAtual = 0;
      		}
    	}
  	}
  	// APLICA PWM AO TIP120
  	analogWrite(PIN_TIP120, pwmAtual);
  	// LED INDICADOR
  	if (pwmAtual > 0) {
  		analogWrite(PIN_LED, 255);
  	} 
  	else {
    	analogWrite(PIN_LED, 0);
  	}
}

// ATUALIZAÇÃO DO LCD
void atualizarLCDPeriodicamente() {
	if (millis() - ultimoLCD >= INTERVALO_LCD) {
		ultimoLCD = millis();
	    atualizarLCD();
  	}
}

// LCD
void atualizarLCD() {
	lcd.clear();
	switch (menu) {
    	// MENU 0 - POTENCIÔMETRO
    	case 0:
	    	lcd.setCursor(0, 0);
	    	lcd.print("POT UN: ");
	    	if (motorLigado) {
				lcd.print("ON ");
	    	} else {
	    		lcd.print("OFF");
	    	}
	    	lcd.setCursor(0, 1);
	    	lcd.print("Valor: ");
	    	lcd.print(valorPot);
	    	break;
	
	    // MENU 1 - TENSÃO
	    case 1:
	      	lcd.setCursor(0, 0);
	      	lcd.print("POT V1: ");
	      	if (motorLigado) {
	      		lcd.print("ON ");
	      	} else {
	      		lcd.print("OFF");
	      	}
	      	lcd.setCursor(0, 1);
	      	lcd.print("Tensao: ");
	      	lcd.print(tensao, 2);
	      	lcd.print("V");
	      	break;
	
	    // MENU 2 - PWM
	    case 2:
	      	lcd.setCursor(0, 0);
	      	lcd.print("VEL PWM: ");
	      	if (motorLigado) {
    	  		lcd.print("ON ");
    	  	} else {
    	  		lcd.print("OFF");
    	  	}
	      	lcd.setCursor(0, 1);
	      	lcd.print("PWM: ");
	      	lcd.print(pwmAtual);
	      	break;
		
	    // MENU 3 - VELOCIDADE %
	    case 3:
	      	lcd.setCursor(0, 0);
	      	lcd.print("VEL %: ");
	      	if (motorLigado) {
	      		lcd.print("ON ");
	      	} else {
	      		lcd.print("OFF");
	      	}
    	  	lcd.setCursor(0, 1);
	      	lcd.print("Vel: ");
	      	lcd.print(velocidadePercentual, 1);
	      	lcd.print("%");
	      	break;
	}
}

// SERIAL
void enviarSerialPeriodicamente() {
	if (millis() - ultimoSerial >= INTERVALO_SERIAL) {
    	ultimoSerial = millis();
    	Serial.println("==============================");
    	Serial.print("Potenciometro : ");
    	Serial.println(valorPot);
    	Serial.print("Tensao        : ");
    	Serial.print(tensao, 2);
    	Serial.println(" V");
    	Serial.print("PWM alvo      : ");
    	Serial.println(pwmAlvo);
    	Serial.print("PWM atual     : ");
    	Serial.println(pwmAtual);
    	Serial.print("Velocidade    : ");
    	Serial.print(velocidadePercentual, 1);
    	Serial.println(" %");
    	Serial.print("Motor         : ");
    	if (motorLigado) {
      		Serial.println("LIGADO");
    	} 
      	else {
      		Serial.println("DESLIGADO");
    	}
    	Serial.print("Menu          : ");
    	Serial.println(menu);
    	Serial.println("==============================");
  	}
}
