// Teste de bancada da tela ILI9341 3,2" (BMO v1).
// Pinagem: README > Pinagem. VCC da tela no 3V3; LED no 3V3 na bancada (o pino 16 vai
// em HIGH mesmo assim, para quando o backlight passar a ser controlado).
// Versão touch (MSP3218, 14 pinos): T_CLK, T_CS, T_DIN, T_DO e T_IRQ ficam sem ligação, e os SD_* do slot
// no verso também (o microSD do BMO é o módulo separado, na porta traseira).
// Biblioteca: "Adafruit ILI9341" (o gerenciador instala junto Adafruit GFX e BusIO).
// Arduino IDE: placa "ESP32S3 Dev Module", PSRAM "OPI PSRAM", Flash Size "16MB".
// Serial em 115200, pelo USB-C marcado UART/COM da DevKitC.
//
// O que conferir:
// - O ID no serial deve ser 0x9341. 0x0000 ou 0xFFFF = MISO solto (a tela pode
//   funcionar mesmo assim) ou chip diferente do anunciado.
// - As cores devem bater com o nome escrito. Vermelho saindo azul = ordem RGB/BGR
//   trocada, sinal de chip diferente do anunciado.
// - O texto fica sempre no canto de origem: serve para escolher a rotação da carcaça.
#include <SPI.h>
#include <Adafruit_ILI9341.h>

#define PIN_SCK  12
#define PIN_MOSI 11
#define PIN_MISO 13
#define PIN_CS   10
#define PIN_DC   17
#define PIN_RST  18
#define PIN_BLK  16
#define PIN_CS_CC1101 14  // os outros CS do barramento ficam em HIGH
#define PIN_CS_SD     21

// ponytail: 10 MHz por causa dos jumpers da protoboard; na PCB dá para subir até 40 MHz.
#define SPI_HZ 10000000

Adafruit_ILI9341 tft(&SPI, PIN_DC, PIN_CS, PIN_RST);

const uint16_t CORES[] = {ILI9341_RED, ILI9341_GREEN, ILI9341_BLUE, ILI9341_WHITE};
const char *NOMES[] = {"VERMELHO", "VERDE", "AZUL", "BRANCO"};

void setup() {
  Serial.begin(115200);
  for (int p : {PIN_CS_CC1101, PIN_CS_SD, PIN_BLK}) {
    pinMode(p, OUTPUT);
    digitalWrite(p, HIGH);
  }
  SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI);
  tft.begin(SPI_HZ);
}

void loop() {
  // Lido a cada ciclo para não se perder se o monitor serial abrir depois do boot.
  uint16_t id = (tft.readcommand8(0xD3, 2) << 8) | tft.readcommand8(0xD3, 3);
  Serial.printf("ID da tela: 0x%04X (esperado 0x9341)\n", id);

  for (uint8_t r = 0; r < 4; r++) {
    tft.setRotation(r);
    for (uint8_t i = 0; i < 4; i++) {
      tft.fillScreen(CORES[i]);
      tft.setCursor(8, 8);
      tft.setTextColor(ILI9341_BLACK);
      tft.setTextSize(3);
      tft.printf("%s\nrot %d %dx%d", NOMES[i], r, tft.width(), tft.height());
      delay(700);
    }
  }
}
