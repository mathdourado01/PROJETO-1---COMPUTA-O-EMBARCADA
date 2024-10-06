# PROJETO-1---COMPUTA-O-EMBARCADA

1. Introdução
Projeto: Jogo da Memória e Jogo de Perguntas

Este projeto visa desenvolver um jogo interativo da memória utilizando uma placa Arduino e componentes eletrônicos, onde o jogador deve memorizar uma sequência de LEDs piscando. Após acertar a sequência, o jogador passa para uma fase de perguntas aleatórias, onde terá um tempo limitado para responder corretamente. Se caso acertar, recebera uma pergunta final que decidira seu destino.

Objetivo do projeto:
- Criar um jogo da memória, onde o jogador deve acertar uma sequência de LEDs e responder perguntas aleatórias.
  
2. Metodologia

Materiais Utilizados:
Arduino Uno
2 LEDs(Vermelho/Verde)
3 Botões(Start/Sim/Não)
Buzzer
Display LCD 
2 Protoboard 
3 Resistores
Potenciometro

Métodos:

O desenvolvimento do projeto foi dividido em duas partes principais:

Desenvolvimento da sequência de memória:
- Geração de uma sequência aleatória de LEDs piscando.
- Exibição da sequência para o jogador, onde os LEDs piscam em uma ordem aleatória.
- Verificação da resposta do jogador.
- Mostrar a contagem de acertos e em qual resposta ele está.
- Se errar o jogo encerra, caso acertar vai para a fase de perguntas.

Fase de perguntas:

- As perguntas são exibidas no display LCD. O jogador precisa responder utilizando os botões SIM/NAO.
- O jogador tem um tempo limite de 10 segundos para responder cada pergunta, com o buzzer avisando quando o tempo estiver acabando.
- O jogo permite que o jogador pule apenas uma pergunta caso o tempo acabe.
- Se o jogador acertar cinco perguntas, uma pergunta final aleatória é selecionada para definir o resultado final do jogo.
- Se errar o jogo encerra por completo.

3. Experimentos
![image](https://github.com/user-attachments/assets/2b154474-d863-4df9-a653-b0bca4361e69)

4. Conclusão

A solução que encontramos para resolver o projeto foi a partir de criações de arrays para armazenar tanto a sequência do jogo da memória, quanto as perguntas da segunda fase.
Com isso, o código era capaz de receber os dados fornecidos pelas arrays e fazer as verificações necessárias, como verificar se a sequência de leds está correta e se a pergunta foi respondida corretamente.
Apesar disso, encontramos uma grande dificuldade no processo, que foi o uso da interrupção no botão de start para acabar o jogo, pelo fato da nossa falta de familiaridade com o uso da lógica de interrupção no código. 
Embora tenhamos tido essa dificuldade, de resto, o projeto atende a todos os outros requisitos.
