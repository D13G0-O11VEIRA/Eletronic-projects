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

// Matriz de mapeamento dos segmentos para os dígitos de 0 a 9
const byte digitos[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

const int pinosSegmentos[7] = {pinoA, pinoB, pinoC, pinoD, pinoE, pinoF, pinoG};

void setup() {
  // Configura todos os pinos dos segmentos como saída
  for (int i = 0; i < 7; i++) {
    pinMode(pinosSegmentos[i], OUTPUT);
  }

  // Configura os botões com resistor interno de Pull-up
  // Quando o botão for pressionado, o Arduino lerá LOW (0V)
  pinMode(pinoBotaoSobe, INPUT_PULLUP);
  pinMode(pinoBotaoDesce, INPUT_PULLUP);

  // Exibe o número inicial (0)
  exibirNumero(numeroAtual);
}

void loop() {
  // Lê o estado atual dos botões
  bool estadoSobe = digitalRead(pinoBotaoSobe);
  bool estadoDesce = digitalRead(pinoBotaoDesce);

  // Verifica se o botão de SUBIR foi pressionado (transição de HIGH para LOW)
  if (estadoSobe == LOW && ultimoEstadoSobe == HIGH) {
    numeroAtual++;
    if (numeroAtual > 9) numeroAtual = 0; // Se passar de 9, volta para 0
    exibirNumero(numeroAtual);
    delay(50); // Debounce (evita leituras falsas causadas pelo clique mecânico)
  }
  ultimoEstadoSobe = estadoSobe;

  // Verifica se o botão de DESCER foi pressionado (transição de HIGH para LOW)
  if (estadoDesce == LOW && ultimoEstadoDesce == HIGH) {
    numeroAtual--;
    if (numeroAtual < 0) numeroAtual = 9; // Se for menor que 0, volta para 9
    exibirNumero(numeroAtual);
    delay(50); // Debounce
  }
  ultimoEstadoDesce = estadoDesce;
}

// Função responsável por acionar os segmentos correspondentes ao número
void exibirNumero(int numero) {
  for (int i = 0; i < 7; i++) {
    byte estadoSegmento = digitos[numero][i];

    // Inverte o sinal caso o display seja de anodo comum
    if (TIPO_DISPLAY == ANODO_COMUM) {
      estadoSegmento = !estadoSegmento;
    }

    digitalWrite(pinosSegmentos[i], estadoSegmento);
  }
}
