// C++ code

int pin_bt_h = 2;       // Botão Horário
int pin_bt_a = 3;       // Botão Anti-horário
int pin_mt_h = 5;       // Saída PWM para Ponte H (Horário)
int pin_mt_a = 6;       // Saída PWM para Ponte H (Anti-horário)
int pin_pt = A0;        // Potenciômetro

int lei_bt_h = 0;       // Leitura do botão Horário
int lei_bt_a = 0;       // Leitura do botão Anti-horário
int lei_pt = 0;         // Leitura do potenciômetro
float ten = 0;          // Tensão em Volts
int vel_mt_pwm = 0;     // Valor alvo de PWM para o motor
float vel_mt_per = 0;   // Percentual de velocidade do motor
int sen_gir = 0;       	// Sentido atual (0 = Anti-horário, 1 = Horário)
int pwm_atual = 0;		// Velocidade atual aplicada durante as rampas

void rampaTrocaSentido(int novo_sentido, int pwm_alvo) {
	// Rampa de Desaceleração
	for (int i = pwm_atual; i >= 0; i--) {
		if (sen_gir == 0) {
	 		analogWrite(pin_mt_h, 0);
	    	analogWrite(pin_mt_a, i);
	  	} else if (sen_gir == 1) {
	    	analogWrite(pin_mt_h, i);
	    	analogWrite(pin_mt_a, 0);
	  	}
	  	delay(10);
	}
	// Atualiza o sentido de giro
	sen_gir = novo_sentido;
	// Rampa de Aceleração
	for (int i = 0; i <= pwm_alvo; i++) {
		if (sen_gir == 0) {
	    	analogWrite(pin_mt_h, 0);
	    	analogWrite(pin_mt_a, i);
	  	} else if (sen_gir == 1) {
	    	analogWrite(pin_mt_h, i);
	    	analogWrite(pin_mt_a, 0);
	  	}
	  	delay(10); 
    }
}

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
	ten = (lei_pt * 5.0) / 1023.0;    
	// Mapeia os valores analógicos para o PWM e %
	vel_mt_pwm = map(lei_pt, 0, 1023, 0, 255);
	vel_mt_per = (lei_pt / 1023.0) * 100.0;
	// Leitura dos botões
	lei_bt_h = digitalRead(pin_bt_h);
	lei_bt_a = digitalRead(pin_bt_a);
	// Verificações dos botãos Horário e Anti-horário pressionados
	if (lei_bt_a == HIGH && sen_gir != 0) {
		rampaTrocaSentido(0, vel_mt_pwm);
	} else if (lei_bt_h == HIGH && sen_gir != 1) {
		rampaTrocaSentido(1, vel_mt_pwm);
	}
	// Atualiza o PWM do motor com base no potenciômetro 
	if (sen_gir == 0) {
		analogWrite(pin_mt_h, 0);
		analogWrite(pin_mt_a, vel_mt_pwm);
		pwm_atual = vel_mt_pwm;
	} else if (sen_gir == 1) {
		analogWrite(pin_mt_h, vel_mt_pwm);
		analogWrite(pin_mt_a, 0);
		pwm_atual = vel_mt_pwm;
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
	Serial.print("Sentido de Giro: ");
	if (sen_gir == 1) {
		Serial.println("Anti-horario");
	} else {
		Serial.println("Horario");
	} 
	Serial.println("===================================");
	delay(300);
}
