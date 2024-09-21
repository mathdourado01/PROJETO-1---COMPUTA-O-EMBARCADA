#include <LiquidCrystal.h>


LiquidCrystal lcd_1(12, 11, 7, 6, 5, 4);

// Definindo os LEDs e Botões
const int led1 = 9;
const int led2 = 10;
const int botao1 = 2; // Botão para SIM (representa o LED1)
const int botao2 = 3; // Botão para NAO (representa o LED2)
const int botaoStart = 8; // Botão para Iniciar/Desistir

// Buzzer
const int buzzer = 13;

// Sequência do jogo
int sequencia[10]; 
int respostaJogador[10]; 
int posicaoAtual = 0; 

// Variável de controle
bool jogoIniciado = false; 
bool botaoPressionado = false; 

void setup() {

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(botao1, INPUT_PULLUP); 
  pinMode(botao2, INPUT_PULLUP); 
  pinMode(botaoStart, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  
  lcd_1.begin(16, 2);
  lcd_1.print("Press Start");

  randomSeed(analogRead(0));
}

void loop() {
  // Verificar se o botão Start foi pressionado
  if (digitalRead(botaoStart) == LOW && !botaoPressionado) {
    delay(50);
    if (digitalRead(botaoStart) == LOW) {
      iniciarJogo();
      botaoPressionado = true; // Marca o botão como pressionado
    }
  }

  // Verifica se o botão não esta mais apertado
  if (digitalRead(botaoStart) == HIGH) {
    botaoPressionado = false; 
  }

  // Se o jogo estiver iniciado, verificar a entrada do jogador
  if (jogoIniciado) {
    verificarEntradaJogador();
  }
}

void iniciarJogo() {
  jogoIniciado = true;
  posicaoAtual = 0;


  for (int i = 0; i < 10; i++) {
    sequencia[i] = random(0, 2); // 0 para LED1, 1 para LED2
  }

  // Exibir a sequência para o jogador
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Memorize a seq!");

  for (int i = 0; i < 10; i++) {
    if (sequencia[i] == 0) {
      digitalWrite(led1, HIGH);
    } else {
      digitalWrite(led2, HIGH);
    }
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(500); // Pausa entre os flashes
  }

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Sua vez!");
  delay(500);
}

void verificarEntradaJogador() {
  if (digitalRead(botao1) == LOW) { // Jogador pressiona botão 1 (LED1)
    respostaJogador[posicaoAtual] = 0;
    registrarResposta();
  } else if (digitalRead(botao2) == LOW) { // Jogador pressiona botão 2 (LED2)
    respostaJogador[posicaoAtual] = 1;
    registrarResposta();
  }
}


void registrarResposta() {
  delay(200); 
  posicaoAtual++;
  
  // Verifica se o jogador completou todas as respostas
  if (posicaoAtual == 10) {
    verificarSequencia();
  }
}

void verificarSequencia() {
  bool acertou = true;
  for (int i = 0; i < 10; i++) {
    if (respostaJogador[i] != sequencia[i]) {
      acertou = false;
      break;
    }
  }

  if (acertou) {
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Voce Ganhou!");
    for (int i = 0; i < 3; i++) {
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
    }
  } else {
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Voce Perdeu!");
    for (int i = 0; i < 3; i++) {
      digitalWrite(buzzer, HIGH);
      delay(300);
      digitalWrite(buzzer, LOW);
      delay(300);
    }
  }

  delay(2000);
  lcd_1.clear();
  lcd_1.print("Press Start");
  jogoIniciado = false;
}
