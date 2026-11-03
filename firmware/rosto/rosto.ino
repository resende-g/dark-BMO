// Rosto do d-BMO na tela ILI9341 3,2" (bancada). Mostra os 10 estados da spec em blocos de
// pixel vermelho sobre fundo escuro; os desenhos ficam em rosto_faces.h.
// Pinagem e configuração do Arduino IDE iguais às do firmware/teste_tela (README > Pinagem):
// placa "ESP32S3 Dev Module", PSRAM "OPI PSRAM", Flash Size "16MB", USB CDC On Boot "Enabled".
// Biblioteca: "Adafruit ILI9341" (instala junto Adafruit GFX e BusIO).
//
// Como usar:
// - Botão OK (GPIO 2, ao GND) passa para o próximo estado.
// - No monitor serial (115200), digitar o número (0–9) ou o nome do estado (ex.: alert).
// - Sem nada, o rosto fica em IDLE, piscando.
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include "rosto_faces.h"

#define PIN_SCK  12
#define PIN_MOSI 11
#define PIN_MISO 13
#define PIN_CS   10
#define PIN_DC   17
#define PIN_RST  18
#define PIN_BLK  16
#define PIN_CS_CC1101 14  // os outros CS do barramento ficam em HIGH
#define PIN_CS_SD     21
#define PIN_OK   2

// ponytail: 10 MHz por causa dos jumpers da protoboard; na PCB dá para subir até 40 MHz.
#define SPI_HZ 10000000
// Tela na horizontal (320 × 240). Ajustar quando a orientação da carcaça estiver fechada.
#define ROTATION 1

// Cores da paleta do d-BMO em RGB565.
const uint16_t COR_FUNDO = 0x0841;  // #090A0C
const uint16_t COR_SINAL = 0xD906;  // #D92332
const uint16_t COR_ESCURO = 0x88A4; // #8F1722

Adafruit_ILI9341 tft(&SPI, PIN_DC, PIN_CS, PIN_RST);

int estado = 0, quadro = 0;
unsigned long trocaEm = 0;
char naTela[GRID_H][GRID_W];  // o que já está desenhado, para só redesenhar o que mudou
int bloco, origemX, origemY;

uint16_t cor(char c) {
  return c == '#' ? COR_SINAL : c == '+' ? COR_ESCURO : COR_FUNDO;
}

void desenha(const Frame &fr) {
  for (int y = 0; y < GRID_H; y++)
    for (int x = 0; x < GRID_W; x++) {
      char c = fr.rows[y][x];
      if (c == naTela[y][x]) continue;
      tft.fillRect(origemX + x * bloco, origemY + y * bloco, bloco, bloco, cor(c));
      naTela[y][x] = c;
    }
}

void mudaEstado(int novo) {
  estado = (novo + FACE_COUNT) % FACE_COUNT;
  quadro = 0;
  trocaEm = 0;  // desenha já no próximo loop
  Serial.printf("Estado %d: %s\n", estado, FACES[estado].name);
}

void leSerial() {
  static char buf[16];
  static int n = 0;
  while (Serial.available()) {
    char c = Serial.read();
    if (c != '\n' && c != '\r') {
      if (n < (int)sizeof(buf) - 1) buf[n++] = c;
      continue;
    }
    if (n == 0) continue;
    buf[n] = 0;
    n = 0;
    if (buf[0] >= '0' && buf[0] <= '9' && buf[1] == 0) {
      mudaEstado(buf[0] - '0');
      return;
    }
    for (int i = 0; i < FACE_COUNT; i++)
      if (strcasecmp(buf, FACES[i].name) == 0) {
        mudaEstado(i);
        return;
      }
    Serial.printf("Estado desconhecido: %s\n", buf);
  }
}

void leBotao() {
  static bool antes = HIGH;
  static unsigned long mudouEm = 0;
  bool agora = digitalRead(PIN_OK);
  if (agora != antes && millis() - mudouEm > 50) {  // debounce de 50 ms
    mudouEm = millis();
    antes = agora;
    if (agora == LOW) mudaEstado(estado + 1);
  }
}

void setup() {
  Serial.begin(115200);
  for (int p : {PIN_CS_CC1101, PIN_CS_SD, PIN_BLK}) {
    pinMode(p, OUTPUT);
    digitalWrite(p, HIGH);
  }
  pinMode(PIN_OK, INPUT_PULLUP);
  SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI);
  tft.begin(SPI_HZ);
  tft.setRotation(ROTATION);
  tft.fillScreen(COR_FUNDO);
  memset(naTela, '.', sizeof(naTela));

  // Maior bloco inteiro que cabe na tela, com o rosto centralizado.
  bloco = min(tft.width() / GRID_W, tft.height() / GRID_H);
  origemX = (tft.width() - bloco * GRID_W) / 2;
  origemY = (tft.height() - bloco * GRID_H) / 2;

  Serial.println("Rosto do d-BMO. Estados:");
  for (int i = 0; i < FACE_COUNT; i++) Serial.printf("  %d %s\n", i, FACES[i].name);
  mudaEstado(0);
}

void loop() {
  leSerial();
  leBotao();
  const Face &face = FACES[estado];
  if (millis() >= trocaEm) {
    desenha(face.frames[quadro]);
    trocaEm = millis() + face.frames[quadro].ms;
    quadro = (quadro + 1) % face.count;
  }
}
