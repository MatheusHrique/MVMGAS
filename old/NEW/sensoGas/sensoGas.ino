#include <ESP8266WiFi.h>
#include <ThingESP.h>

ThingESP8266 thing("LoMatheussssssssssz", "Connect8266", "123456789123456789");

unsigned long previousMillis = 0;
const long INTERVAL = 6000;

int gas;

//const int vermelho = D4;
//const int amarelo = D3;
//const int verde = D2;
//const int alarme = D1;

const int vermelho = 2;  // D4 no ESP8266
const int amarelo = 0;   // D3 no ESP8266
const int verde = 4;     // D2 no ESP8266
const int alarme = 5;    // D1 no ESP8266

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);
  //thing.SetWiFi("Wi-fi_Matheus", "12345678901");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.begin("Wi-fi_Matheus", "12345678901");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("Conectado ao Wi-Fi");

  thing.initDevice();

  // Configura os pinos como saída
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(alarme, OUTPUT);
}

String HandleResponse(String query, int gas) {
  if (query == "Qual o status atual?") {
    if (gas < 930) {
      return "Está em um nível seguro.";
    } else if (gas >= 930 && gas < 960) {
      return "Está em um nível de cuidado.";
    } else if (gas >= 960) {
      return "Está em um nível perigoso! Atenção!";
    }
  } else if (query == "Tudo ok, chapa?") {
    return "Tudo ótimo, chapa!";
  } else if (query == "Qual o valor do sensor de gás?") {
    //digitalWrite(LED, 0);
    return "O valor é: " + String(gas);
  } else return "Seu query não foi reconhecido.";
  return "Erro! Algo deu de errado.";
}

void loop() {
  gas = analogRead(A0);  // Lê o valor do sensor de gás

  thing.Handle();

  if (gas < 930) {
    // Nível seguro
    digitalWrite(verde, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, LOW);
    noTone(alarme);
    Serial.println("Seguro");
  } else if (gas >= 930 && gas < 960) {
    // Nível de cuidado
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, HIGH);
    digitalWrite(vermelho, LOW);
    noTone(alarme);
    Serial.println("Cuidado");
  } else if (gas >= 960) {
    // Nível de perigo
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, HIGH);
    tone(alarme, 440);
    delay(500);  // Mantém o alarme ligado por 0,5 segundos
    noTone(alarme);
    delay(300);  // Pausa antes de verificar novamente
    Serial.println("Perigo");
  }

  delay(500);  // Aguarda 0,5 segundos antes de ler novamente
}