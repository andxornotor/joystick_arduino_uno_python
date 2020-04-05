/*
 * Joystick com Arduino e Python
 * Autor: And "Xornotor" Paiva
 * Xornotor's Lab 
 */

//Definição de constantes dos pinos utilizados
#define AX A2                             //Entrada do eixo Y do joystick esq.
#define AY A3                             //Entrada do eixo X do joystick esq.
#define AS 3                              //Entrada do botão do joystick esq.
#define BX A0                             //Entrada do eixo Y do joystick esq.
#define BY A1                             //Entrada do eixo X do joystick esq.
#define BS 4                              //Entrada do botão do joystick dir.
#define IR_REC 2                          //Entrada do sensor infravermelho (IR)

//Definição de valores de deadzone
#define DEADZONE_INF 350                  //Limite de deadzone inferior
#define DEADZONE_SUP 650                  //Limite de deadzone inferior

//Bibliotecas utilizadas
#include <IRremote.h>                     //Biblioteca para tratamento de IR
#include <LiquidCrystal.h>                //Biblioteca para operação de display

//Definição de pino de IR e declaração de variáveis
IRrecv irrecv(IR_REC);                    //Instância de receptor IR
decode_results results;                   //Variável de armazenamento de decode IR
unsigned long int resultAnterior;         //Variável para guardar o último valor lido pela IR

//Inicialização de display LCD
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);  //Instância de display

void setup() {
  
  //Definição de pinos
  pinMode(AX, INPUT);
  pinMode(AY, INPUT);
  pinMode(BX, INPUT);
  pinMode(BY, INPUT);
  pinMode(AS, INPUT_PULLUP);
  pinMode(BS, INPUT_PULLUP);
  
  //Inicialização da conexão serial para comunicação com Python
  Serial.begin(9600);

  //Inicialização de IR
  irrecv.enableIRIn();

  //Exibição de caracteres fixos no display
  lcd.begin(16, 2);                       //Inicialização de display 16x2
  lcd.setCursor(0, 0);                    //Posicionamento do cursor em (0, 0)
  lcd.print("A: ");                       //Imprime "A: " no display
  lcd.setCursor(0, 1);                    //Posicionamento do cursor em (0, 1)
  lcd.print("B: ");                       //Imprime "B: " no display
}

void loop() {
  decodeIR();                             //Função de decodificação de IR
  analogCapture('A');                     //Leitura da posição e do botão do joystick esq.
  analogCapture('B');                     //Leitura da posição e do botão do joystick dir.
}
   
//Tratamento do infra-vermelho
void decodeIR(){
  if(irrecv.decode(&results)){            //Condição executada somente quando há algum botão apertado
    if(results.value != 0xFFFFFFFF){      //Condição executada somente se botão foi apertado pela primeira vez
      resultAnterior = results.value;     //Armazena valor decodificado pelo IR em resultAnterior
      lcd.setCursor(10, 0);               //Posicionamento do cursor em (10, 0)
      lcd.print(results.value, HEX);      //Imprime o código decodificado no display
      delay(50);                          //Delay para evitar reconhecimento de novo pressionamento muito rapidamente
    }
    Serial.println(resultAnterior, HEX);  //Envia para a serial o código decodificado do último botão apertado
    irrecv.resume();                      //Habilita o IR para receber novo comando
  }
}

//Tratamento dos analogs
void analogCapture(char c){
  int ox, oy;                             //Variáveis de captura (OX - Horizontal, OY - Vertical)
  if(c == 'A'){                           //Joystick esquerdo
    lcd.setCursor(3, 0);                  //Posiciona cursor para printar estado do joystick esq.
    ox = analogRead(AX);                  //Leitura horizontal do joystick esq.
    oy = analogRead(AY);                  //Leitura vertical do joystick esq.
    if(!digitalRead(AS))                  //Condição satisfeita se o botão do joy. esq. for apertado
      Serial.println("JASWSW");           //Manda código via serial para indicar que botão esq. foi apertado
    Serial.print("JA");                   //Manda via serial identificador de que o próximo comando corresponde ao joy. esq.
  }else if(c == 'B'){                     //Joystick direito
    lcd.setCursor(3, 1);                  //Posiciona cursor para printar estado do joystick dir.
    ox = analogRead(BX);                  //Leitura horizontal do joystick dir.
    oy = analogRead(BY);                  //Leitura vertical do joystick dir.
    if(!digitalRead(BS))                  //Condição satisfeita se o botão do joy. dir. for apertado
      Serial.println("JBSWSW");           //Manda código via serial para indicar que botão dir. foi apertado
    Serial.print("JB");                   //Manda via serial identificador de que o próximo comando corresponde ao joy. dir.
  }
  if(ox >= DEADZONE_SUP){                 //Condição satisfeita se o joystick for movimentado para a direita
    if(oy >= DEADZONE_SUP){               //Condição satisfeita se o joystick for movimentado para a cima
      lcd.print("UR");
      Serial.println("URUR");
    }else if(oy <= DEADZONE_INF){         //Condição satisfeita se o joystick for movimentado para a baixo
      lcd.print("DR");
      Serial.println("DRDR");
    }else{                                //Condição de joystick movimentado APENAS para a direita
      lcd.print("R ");
      Serial.println("RRRR");
    }
  }else if(ox <= DEADZONE_INF){           //Condição satisfeita se o joystick for movimentado para a esquerda
    if(oy >= DEADZONE_SUP){               //Condição satisfeita se o joystick for movimentado para a cima
      lcd.print("UL");
      Serial.println("ULUL");
    }else if(oy <= DEADZONE_INF){         //Condição satisfeita se o joystick for movimentado para a baixo
      lcd.print("DL");
      Serial.println("DLDL");
    }else{                                //Condição de joystick movimentado APENAS para a esquerda
      lcd.print("L ");
      Serial.println("LLLL");
    }
  }else if(oy >= DEADZONE_SUP){           //Condição de joystick movimentado APENAS para cima
    lcd.print("U ");
    Serial.println("UUUU");
  }else if(oy <= DEADZONE_INF){           //Condição de joystick movimentado APENAS para baixo
    lcd.print("D ");
    Serial.println("DDDD");
  }else{                                  //Condição de joystick NÃO movimentado
    lcd.print("  ");
    Serial.println("NNNN");
  }
}
