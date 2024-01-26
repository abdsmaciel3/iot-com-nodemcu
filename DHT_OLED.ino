#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LARGURA_OLED 128
#define ALTURA_OLED 64
 
#define RESET_OLED -1
 
Adafruit_SSD1306 display(LARGURA_OLED, ALTURA_OLED, &Wire, RESET_OLED);

//--- DHT ---
#include <DHT.h>
#define DHTPIN D3
#define DHTTYPE DHT11    // selecionar o tipo de sensor DHT11, 22 ...
DHT dht(DHTPIN ,DHTTYPE);
int umidade;
int temperatura;

// --- DISPLAY ---
//#include <Adafruit_SSD1306.h> //Carrega a biblioteca oled
//#define OLED_RESET LED_BUILTIN
//Adafruit_SSD1306 display(OLED_RESET);


// --- SETUP ---
void setup() {
  Serial.begin(115200);
  configurarDisplay();
}

// --- LOOP ---
void loop() {
  medirTemperaturaUmidade();
  mostrarTempeturaUmidade ();
}

// --- FUNÇÕES AUXILIARES ---

// --- CONFIGURAR DISPLAY ---
void configurarDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Inicializa 0x3C
  display.setTextColor(WHITE);
  display.clearDisplay();
}

// --- MEDIÇÃO DE TEMPERATURA E UMIDADE ---
void medirTemperaturaUmidade() {
  umidade = dht.readHumidity(); //Le o valor da umidade
  temperatura = dht.readTemperature(false); //Le o valor da temperatura
  Serial.print("Temperatura : ");
  Serial.print(temperatura);
  Serial.print(" *C");
  Serial.print("    ");
  Serial.print("Umidade: ");
  Serial.println(umidade);
  Serial.print(" %");
  delay(2000);
}
// --- EXIBE TEMPERATURA E UMIDADE NO DISPLAY ---
void mostrarMensagemNoDisplay(const char* texto1, int medicao, const char* texto2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(texto1);
  display.setTextSize(5);
  display.setCursor(20, 20);
  display.print(medicao);
  display.setTextSize(2);
  display.print(texto2);
  display.display();
  delay(2000);

}

// --- MOSTRA TEMPERATURA E UMIDADE ---
void mostrarTempeturaUmidade () {
  mostrarMensagemNoDisplay("Temperatura", (temperatura), " C");
  mostrarMensagemNoDisplay("Umidade", (umidade), " %");

}
