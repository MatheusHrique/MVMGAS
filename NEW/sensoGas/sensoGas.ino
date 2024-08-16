#include <ESP8266WiFi.h>
#include <ThingESP.h>
// #include <ThingerESP8266.h>

ThingESP8266 thing("LoMatheussssssssssz", "Connect8266", "123456789123456789");

unsigned long previousMillis = 0;
const long INTERVAL = 6000;

int gas;

const int vermelho = 2;  // D4 no ESP8266
const int amarelo = 0;   // D3 no ESP8266
const int verde = 4;     // D2 no ESP8266
const int alarme = 5;    // D1 no ESP8266

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);
  thing.SetWiFi("matheus", "1234567890");

  WiFi.mode(WIFI_STA);
  //WiFi.disconnect();
  delay(100);
  WiFi.begin("matheus", "1234567890");
  thing.initDevice();

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("Conectado ao Wi-Fi");

  // thing["sendMessage"] >> {
  //   out = "Olá, esta é uma mensagem!";
  // };

  // Configura os pinos como saída
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(alarme, OUTPUT);
}

String HandleResponse(String query) {
  if (query == "qual o valor do gas atual?") {
    //digitalWrite(LED, 0);
    return "Nivel do gás: " + String(gas);
  }

  if (gas >= 960) {
    return "Perigo! Nivel de gás está em: " + String(gas);
  }

  if (query == "qual o status atual?") {
    if (gas < 930) {
      return "Está em um nível seguro.";
    }
    if (gas >= 930 && gas < 960) {
      return "Está em um nível de cuidado.";
    }
    if (gas >= 960) {
      return "Está em um nível perigoso! Atenção!";
    }
  }

  return "Seu query não foi reconhecido.";
  //return "Erro! Algo deu de errado.";

  
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
  }
  if (gas >= 930 && gas < 960) {
    // Nível de cuidado
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, HIGH);
    digitalWrite(vermelho, LOW);
    noTone(alarme);
    Serial.println("Cuidado");
  }
  if (gas >= 960) {
    // Nível de perigo
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, HIGH);
    tone(alarme, 440);
    delay(500);  // Mantém o alarme ligado por 0,5 segundos
    noTone(alarme);
    delay(300);  // Pausa antes de verificar novamente
    Serial.println("Perigo");
    // sendMessage();
    // thing.sendMessage("Perigo! Nivel de gás está em: " + String(gas));
  }

  delay(500);  // Aguarda 0,5 segundos antes de ler novamente
}

// void sendMessage() {
//   pson payload;
//   payload = "Perigo! Nivel de gás está em: " + String(gas);
//   thing.write_resource("sendMessage", payload);
//   Serial.println("Mensagem enviada: " + String(payload));
// }