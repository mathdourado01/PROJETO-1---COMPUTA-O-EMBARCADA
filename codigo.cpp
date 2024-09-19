#include <LiquidCrystal.h>
LiquidCrystal lcd_1(12, 11, 7, 6, 5, 4);

int seconds = 0;
// Definindo os LEDs e Botões
const int led1 = 9;
const int led2 = 10;
const int botao1 = 2; // Botão para SIM
const int botao2 = 3; // Botão para NAO
const int botaoStart = 1; // Botão para Iniciar/Desistir
// Buzzer
const int buzzer = 13;

int sequencia[10];
int respostaJogador[10];

// Variável de controle
bool jogoIniciado = false;
void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(botao1, INPUT_PULLUP); 
  pinMode(botao2, INPUT_PULLUP); 
  pinMode(botaoStart, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  
  lcd_1.begin(16, 2);
  lcd_1.print("     Start:");

}

void loop()
{
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting
  // begins with 0):
  lcd_1.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd_1.print(seconds);
  delay(1000); // Wait for 1000 millisecond(s)
  seconds += 1;
}
