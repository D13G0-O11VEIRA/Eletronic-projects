// Parametros
const int pinoA = 2;
const int pinoB = 3;
const int pinoC = 4;
const int pinoD = 5;
const int pinoE = 6;
const int pinoF = 7;
const int pinoG = 8;

const int pinoBotaoSobe = 9;   // Botão para aumentar
const int pinoBotaoDesce = 10; // Botão para diminuir

// Variaveis
int numeroAtual = 0;
bool ultimoEstadoSobe = HIGH;
bool ultimoEstadoDesce = HIGH;

// Tipo de display
enum TipoDisplay { CATODO_COMUM, ANODO_COMUM };
const TipoDisplay TIPO_DISPLAY = CATODO_COMUM;

// Matriz de mapeamento
const byte digitos[16][7] = 
{
 	{1, 1, 1, 1, 1, 1, 0}, // 0
 	{0, 1, 1, 0, 0, 0, 0}, // 1
 	{1, 1, 0, 1, 1, 0, 1}, // 2
 	{1, 1, 1, 1, 0, 0, 1}, // 3
 	{0, 1, 1, 0, 0, 1, 1}, // 4
 	{1, 0, 1, 1, 0, 1, 1}, // 5
 	{1, 0, 1, 1, 1, 1, 1}, // 6
 	{1, 1, 1, 0, 0, 0, 0}, // 7
 	{1, 1, 1, 1, 1, 1, 1}, // 8
 	{1, 1, 1, 1, 0, 1, 1}, // 9
 	{1, 1, 1, 0, 1, 1, 1}, // A
 	{0, 0, 1, 1, 1, 1, 1}, // b
 	{1, 0, 0, 1, 1, 1, 0}, // C
 	{0, 1, 1, 1, 1, 0, 1}, // d
 	{1, 0, 0, 1, 1, 1, 1}, // E
 	{1, 0, 0, 0, 1, 1, 1}  // F
};

const int pinosSegmentos[7] = {pinoA, pinoB, pinoC, pinoD, pinoE, pinoF, pinoG};

void setup()
{
	for (int i = 0; i < 7; i++) // Configura todos os pinos dos segmentos como saída
	{
		pinMode(pinosSegmentos[i], OUTPUT);
	}
	pinMode(pinoBotaoSobe, INPUT_PULLUP);
	pinMode(pinoBotaoDesce, INPUT_PULLUP);
	exibirNumero(numeroAtual); 
}

void loop() 
{
	// Lê o estado atual dos botões
	bool estadoSobe = digitalRead(pinoBotaoSobe);
  	bool estadoDesce = digitalRead(pinoBotaoDesce);

  	// Verifica se o botão de SUBIR foi pressionado
  	if (estadoSobe == LOW && ultimoEstadoSobe == HIGH) 
    {
   		numeroAtual++;
    	if (numeroAtual > 15) numeroAtual = 0; // Reseta contagem
    	exibirNumero(numeroAtual);
    	delay(50); // Debounce
  	}
  	ultimoEstadoSobe = estadoSobe;

  	// Verifica se o botão de DESCER foi pressionado
  	if (estadoDesce == LOW && ultimoEstadoDesce == HIGH) {
    	numeroAtual--;
    	if (numeroAtual < 0) numeroAtual = 15; // Reseta contagem
    	exibirNumero(numeroAtual);
    	delay(50); // Debounce
  	}
  	ultimoEstadoDesce = estadoDesce;
}

// Acionamento dos segmentos de número/letra
void exibirNumero(int numero) {
  	for (int i = 0; i < 7; i++) 
    {
    	byte estadoSegmento = digitos[numero][i];

    	// Inverte o sinal caso o display seja de anodo comum
    	if (TIPO_DISPLAY == ANODO_COMUM) 
        {
      		estadoSegmento = !estadoSegmento;
    	}
    digitalWrite(pinosSegmentos[i], estadoSegmento);
  	}
}
