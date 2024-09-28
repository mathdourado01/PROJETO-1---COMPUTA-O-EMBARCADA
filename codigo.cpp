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

// Perguntas e Respostas
const int qtdePerguntas = 10; 
String perguntas[qtdePerguntas] = {
  "Palmeiras tem mundial ?", // NAO
  "CC tem 10 semestres ?", // NAO
  "A Fei tem 10 cursos ?", // NAO
  "FEI é melhor que MAUA ?", // SIM
  "Futebol melhor que volei ?", // SIM
  "Libertadores > Champions ? ", // NAO
  "Lebron eh Goat ?", // SIM
  "Messi eh Goat ?", // SIM
  "Mbappe 2022 melhor prime ?", // SIM
  "Palmeiras > Cassio ?" // NAO
};
bool respostas[qtdePerguntas] = {false, false, false, true, true, false, true, true, true, false};

// Sequência do jogo
int sequencia[10]; 
int respostaJogador[10]; 
int posicaoAtual = 0; 

// Variável de controle
int perguntasSelecionadas[5];
int perguntaAtual = 0; 
bool jogoMemoria = false;
bool botaoPressionado = false;
bool jogoEncerrado = false;
bool fasePerguntas = false; 

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(botao1, INPUT_PULLUP); 
  pinMode(botao2, INPUT_PULLUP); 
  pinMode(botaoStart, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  
  lcd_1.begin(16, 2);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Seja bem vindo");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Pressione inicia");

  randomSeed(analogRead(0));
}

void loop() {
  // Verificar se o botão Start foi pressionado
  if (digitalRead(botaoStart) == LOW && !botaoPressionado) {
    delay(50);
    if (digitalRead(botaoStart) == LOW) {
      if (!jogoMemoria) {
        iniciarJogo(); 
      } else {
        encerrarJogo(); 
      }
      botaoPressionado = true; // Marca o botão como pressionado
    }
  }

  if (digitalRead(botaoStart) == HIGH) {
    botaoPressionado = false; 
  }

  if (jogoMemoria && !jogoEncerrado) {
    if (!fasePerguntas) {
      verificarEntradaJogador(); 
    } else {
      verificarRespostaPergunta();
    }
  }
}

void iniciarJogo() {
  jogoMemoria = true;
  posicaoAtual = 0;
  fasePerguntas = false; 
  perguntaAtual = 0;
  jogoEncerrado = false;
  
  // Seleciona perguntas aleatórias diferentes
  for (int i = 0; i < 5; i++) {
    int indice;
    bool jaUsada;
    do {
      indice = random(0, qtdePerguntas);
      jaUsada = false;
      for (int j = 0; j < i; j++) {
        if (perguntasSelecionadas[j] == indice) {
          jaUsada = true;
          break;
        }
      }
    } while (jaUsada);
    perguntasSelecionadas[i] = indice;
  }
  
  for (int i = 0; i < 10; i++) {
    sequencia[i] = random(0, 2); // 0 para LED1, 1 para LED2
  }

  // Exibir a sequência para o jogador
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Memorize as");
  lcd_1.setCursor(0, 1);
  lcd_1.print("cores dos leds");

  for (int i = 0; i < 10; i++) {
    if (sequencia[i] == 0) {
      digitalWrite(led1, HIGH);
    } else {
      digitalWrite(led2, HIGH);
    }
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(750); // Pausa entre os flashes
  }

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Agora repita");
  lcd_1.setCursor(0, 1);
  lcd_1.print("a sequencia");
  delay(500);
}

void verificarEntradaJogador() {
  if (digitalRead(botao1) == LOW) { // Jogador pressiona botão 1 (LED1)
    respostaJogador[posicaoAtual] = 0;
    mostrarTentativa(0); 
    registrarResposta();
  } else if (digitalRead(botao2) == LOW) { // Jogador pressiona botão 2 (LED2)
    respostaJogador[posicaoAtual] = 1;
    mostrarTentativa(1);
    registrarResposta();
  }
}

void mostrarTentativa(int ledIndicado) {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Tentativa: ");
  lcd_1.print(posicaoAtual + 1);
  
  if (respostaJogador[posicaoAtual] == sequencia[posicaoAtual]) {
    lcd_1.setCursor(0, 1);
    lcd_1.print("Correto!");
  } else {
    lcd_1.setCursor(0, 1);
    lcd_1.print("Errado!");
    delay(1000);
    encerrarJogo();
  }
  delay(500);
}

void registrarResposta() {
  delay(200); 
  posicaoAtual++;
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
      tone(buzzer, 700, 200); 
      delay(300);
    }
    iniciarPerguntas();
  } else {
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Voce Perdeu!");
    for (int i = 0; i < 3; i++) {
      tone(buzzer, 400, 300); 
      delay(400);
    }
  }
}

void iniciarPerguntas() {
  fasePerguntas = true;
  perguntaAtual = 0;
  exibirPergunta();
}

void exibirPergunta() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Pergunta:");
  lcd_1.setCursor(0, 1);
  String pergunta = perguntas[perguntasSelecionadas[perguntaAtual]];

  int maxScroll = pergunta.length() - 15; // Calcular quanto deslocamento é necessário
  for (int i = 0; i <= maxScroll; i++) {
    lcd_1.setCursor(0, 1);
    lcd_1.print(pergunta.substring(i, i + 16)); // Mostra parte da pergunta
    delay(500); 
  }
}

void verificarRespostaPergunta() {
  if (digitalRead(botao1) == LOW) { 
    delay(200); 
    if (respostas[perguntasSelecionadas[perguntaAtual]]) {
      respostaCorreta();
    } else {
      respostaIncorreta();
    }
  } else if (digitalRead(botao2) == LOW) { 
    delay(200); 
    if (!respostas[perguntasSelecionadas[perguntaAtual]]) {
      respostaCorreta();
    } else {
      respostaIncorreta();
    }
  }
}

void respostaCorreta() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Correto!");
  tone(buzzer, 1000, 200); 
  delay(1000);

  perguntaAtual++;
  if (perguntaAtual < 5) {
    exibirPergunta(); // Próxima pergunta aleatória
  } else {
    exibirPerguntaFinal(); 
  }
}

void respostaIncorreta() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Incorreto!");
  tone(buzzer, 400, 500); 
  delay(2000);
  reiniciarJogo();
}

void exibirPerguntaFinal() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Pergunta Final:");
  lcd_1.setCursor(0, 1);
  lcd_1.print("CR7 maior atleta da história?");
  
  String perguntaFinal = "CR7 maior atleta da história?";
  int maxScroll = perguntaFinal.length() - 15; 
  for (int i = 0; i <= maxScroll; i++) {
    lcd_1.setCursor(0, 1);
    lcd_1.print(perguntaFinal.substring(i, i + 16));
    delay(500); 
  }
  
  verificarRespostaPerguntaFinal();
}

void verificarRespostaPerguntaFinal() {
  bool respostaFinalCorreta = true; 
  while (true) {
    if (digitalRead(botao1) == LOW) { 
      delay(200); 
      if (respostaFinalCorreta) {
        venceuJogo();
      } else {
        perdeuJogo();
      }
      break;
    } else if (digitalRead(botao2) == LOW) {
      delay(200);
      if (!respostaFinalCorreta) {
        venceuJogo();
      } else {
        perdeuJogo();
      }
      break;
    }
  }
}

void venceuJogo() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Parabens! Venceu!");
  for (int i = 0; i < 3; i++) {
    tone(buzzer, 1000, 300); 
    delay(300);
  }
  delay(2000);
  reiniciarJogo();
}

void perdeuJogo() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Voce Perdeu!");
  tone(buzzer, 400, 500); 
  delay(2000);
  reiniciarJogo();
}

void reiniciarJogo() {
  jogoMemoria = false;
  fasePerguntas = false;
  perguntaAtual = 0;
  mensagemInicial(); 
}

void encerrarJogo() {
  jogoMemoria = false;
  jogoEncerrado = true;
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Jogo Encerrado!");

  for (int i = 0; i < 3; i++) {
    tone(buzzer, 500, 200); 
    delay(300);
  }

  delay(2000);
  mensagemInicial(); 
}

void mensagemInicial() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Seja bem vindo");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Pressione inicia");
}
