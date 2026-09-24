// C++ code

int pin_bt_h = 2;		// Botão Horário
int pin_bt_a = 3;		// Botão Anti-horário
int pin_mt_h = 5; 		// Saída PWM para Ponte H (Horário)
int pin_mt_a = 6;		// Saída PWM para Ponte H (Anti-horário)
int pin_pt = A0; 		// Potenciômetro

int lei_bt_h = 0;		// Leitura do botão Horario
int lei_bt_a = 0;		// Leitura do botão Anti-horario
int lei_pt = 0;			// Tensão de saida do potenciômetro
float ten = 0;			// Tensão em Volts
int vel_mt_pwm = 0; 	// Valor de saida para o motor
float vel_mt_per = 0;	// Perventual de Velocidade do motor
int sen_gir = 0;		// Sentido de giro do motor

void setup(){
	pinMode(pin_bt_h, INPUT);
	pinMode(pin_bt_a, INPUT);
	pinMode(pin_mt_h, OUTPUT);
	pinMode(pin_mt_a, OUTPUT);
	Serial.begin(9600);
}

void loop(){
	// Leitura do Potenciômetro e cálculo da tensão e porcentagem
  	lei_pt = analogRead(pin_pt); 	
  	ten = (lei_pt*5.0)/1023.0;		
  
  	// Mapeia os valores analógicos para o PWM e %
  	vel_mt_pwm = map(lei_pt, 0, 1023, 0, 255);
  	vel_mt_per = (lei_pt / 1023.0) * 100.0;
  
  	// Defição do sentido de giro
  	lei_bt_h = digitalRead(pin_bt_h);
  	lei_bt_a = digitalRead(pin_bt_a);

  	if (lei_bt_h == HIGH) {
    	sen_gir = 0;	// Sentido Horário
  	} else if (lei_bt_a == HIGH) {
    	sen_gir = 1;	// Sentido Anti-horário
  	}
  
  	// Controle da Ponte H
	if (sen_gir == 0) {
		analogWrite(pin_mt_h, vel_mt_pwm);
		analogWrite(pin_mt_a, 0);
	} else if (sen_gir == 1) {
		analogWrite(pin_mt_h, 0);
		analogWrite(pin_mt_a, vel_mt_pwm);
	}
  
  	// Saida para o cmd
	Serial.print("Valor do potenciometro = ");
	Serial.print(lei_pt);
  	Serial.println("");
  
  	Serial.print("Valor da tensao = ");
	Serial.print(ten);
  	Serial.print("V");
  	Serial.println("");
  
  	Serial.print("Velocidade em PWM = ");
  	Serial.print(vel_mt_pwm);
  	Serial.println("");
  
  	Serial.print("Velocidade em porcentagem = ");
  	Serial.print(vel_mt_per);
  	Serial.print("%");
  	Serial.println("");
  
  	Serial.print("Sentido de Giro: ");
  	if (sen_gir == 0) {
  		Serial.println("Anti-horario");
    } else if (sen_gir == 1){
    	Serial.println("Horario");
    }
  
  	Serial.println("===================================");
    delay(1000);
}
