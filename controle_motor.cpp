// C++ code

int pin_bt_h = 2;
int pin_bt_a = 3;
int pin_mt_h = 5;
int pin_mt_a = 6;
int pin_pt = A0;

int lei_bt_h = 0;
int lei_bt_a = 0;
int lei_pt = 0;
float ten = 0;
int vel_mt_pwm = 0;
float vel_mt_per = 0;
int sen_gir = 0;

void setup(){
	pinMode(pin_bt_h, INPUT);
	pinMode(pin_bt_a, INPUT);
	pinMode(pin_mt_h, OUTPUT);
	pinMode(pin_mt_a, OUTPUT);
	Serial.begin(9600);
}

void loop(){
	lei_pt = analogRead(pin_pt);
  	ten = (lei_pt*5.0)/1023.0;
    
	Serial.print("Valor do potenciometro = ");
	Serial.print(lei_pt);
  	Serial.println("");
  	Serial.print("Valor da tensao = ");
	Serial.print(ten);
  	Serial.print("V");
  	Serial.println("");
  	Serial.println("=============================");
    delay(1000);
}
