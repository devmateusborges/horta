
#include <LiquidCrystal.h> //Inclui a biblioteca
#include "dht.h" //INCLUSÃO DE BIBLIOTECA
 
const int pinoDHT11 = A3; //PINO ANALÓGICO UTILIZADO PELO DHT11
dht DHT; //VARIÁVEL DO TIPO DHT

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;//Pinos para ligar o display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);//Define os pinos que serão usados para ligar o display

// HUMIDADE TERRA
int soilPin = A1; // pino analógico conectado ao sensor de umidade do solo
int soilMoisture = 0; // valor de umidade do solo lido
float soilPercent = 0; // valor de umidade do solo em porcentagem


//--------
  int culer  = 3;
  int selanoide = 2;
  int bombadeagua = 11;

void setup() {

  lcd.begin(16, 2);//Define o número de colunas e linhas do display
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  Serial.begin(9600);

  pinMode(bombadeagua, OUTPUT);
  pinMode(selanoide, OUTPUT);
  pinMode(culer, OUTPUT);
}

//Função para botão select
void select() {
  lcd.clear();
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.print("desligando...");
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  lcd.print(">_<");
  digitalWrite(culer, HIGH);
      digitalWrite(bombadeagua, LOW);
    digitalWrite(selanoide, LOW);
}

//Função para botão left
void left() {
  lcd.clear();
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.print("Ligando Ventilação");
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  digitalWrite(culer, LOW);
  delay(5000);
  digitalWrite(culer, HIGH);
  lcd.print("Abilitando");
}

//Função para botão up
void up() {
  lcd.clear();
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.print("Ligando Irrigação");
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
    digitalWrite(bombadeagua, HIGH);
    digitalWrite(selanoide, HIGH);
    delay(2000);
    lcd.print("Pronto...");
}

//Função para botão down
void down() {
  lcd.clear();
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.print("Desligando IRRIGAÇÃO");
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
    digitalWrite(bombadeagua, LOW);
    digitalWrite(selanoide, LOW);
    delay(2000);
    lcd.print("Pronto...");
}

//Função para botão right
void right(int humidade) {
  lcd.clear();
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.print("UMIDADE DO SOLO");
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  lcd.print(soilPercent);
  lcd.print("%");
  delay(8000);
}

void loop() {
  soilMoisture = analogRead(soilPin);
  soilPercent = map(soilMoisture, 1023, 325, 0, 100); // calcular porcentagem de umidade do solo
  digitalWrite(culer, HIGH);
  // EXPO 
  lcd.clear();
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.print("EXPO FAFRAM");
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  lcd.print("AUTHOR: Mateus Borges");

  // VERIFICA
  if(soilMoisture < 600){
     digitalWrite(bombadeagua, LOW);
    digitalWrite(selanoide, LOW);
  }else if (soilMoisture > 600){
    digitalWrite(bombadeagua, HIGH);
    digitalWrite(selanoide, HIGH);      
  }
 
   
// Buttons Display
  if ((analogRead(0)) < 80) { //Se a leitura for menor que 80 chama a função right
    right(soilPercent);
  }
  else if ((analogRead(0)) < 200) {//Se a leitura for menor que 200 chama a função up
    up();
  }
  else if ((analogRead(0)) < 400) {//Se a leitura for menor que 400 chama a função down
    down();
  }
  else if ((analogRead(0)) < 600) {//Se a leitura for menor que 600 chama a função left
    left();
  }
  else if ((analogRead(0)) < 800) {//Se a leitura for menor que 800 chama a função left
    select();
  }
   
}
