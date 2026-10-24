// Teste de bancada do CC1101 (BMO v1): lê PARTNUM/VERSION por SPI e confere o fio do GDO0.
// Pinagem: README > Pinagem. VCC do módulo no 3V3, NUNCA no 5V.
// Sem biblioteca extra. Não transmite nada (dá para rodar sem antena).
// Arduino IDE: placa "ESP32S3 Dev Module", PSRAM "OPI PSRAM", Flash Size "16MB",
// USB CDC On Boot "Enabled" (Serial em 115200 pelo USB-C marcado USB). Repete a
// cada 3 s, então dá para mexer nos jumpers e ver o resultado mudar.
#include <SPI.h>

#define PIN_SCK  12
#define PIN_MOSI 11
#define PIN_MISO 13
#define PIN_CS   14
#define PIN_GDO0 15
#define PIN_CS_TELA 10  // os outros CS do barramento ficam em HIGH
#define PIN_CS_SD   21

#define CC1101_SRES    0x30  // strobe de reset
#define CC1101_PARTNUM 0x30  // registradores de status: leitura exige 0xC0 (read + burst)
#define CC1101_VERSION 0x31

SPISettings cfg(1000000, MSBFIRST, SPI_MODE0);

// Com o CS em LOW, o CC1101 segura o MISO em HIGH até o cristal estabilizar.
bool esperaPronto() {
  uint32_t t0 = millis();
  while (digitalRead(PIN_MISO)) {
    if (millis() - t0 > 100) return false;
  }
  return true;
}

// Manda um byte de comando; se 'le', devolve o byte seguinte. -1 = chip não ficou pronto.
int cc1101(uint8_t cmd, bool le) {
  SPI.beginTransaction(cfg);
  digitalWrite(PIN_CS, LOW);
  int v = -1;
  if (esperaPronto()) {
    SPI.transfer(cmd);
    v = le ? SPI.transfer(0) : 0;
  }
  digitalWrite(PIN_CS, HIGH);
  SPI.endTransaction();
  return v;
}

void setup() {
  Serial.begin(115200);
  for (int p : {PIN_CS, PIN_CS_TELA, PIN_CS_SD}) {
    pinMode(p, OUTPUT);
    digitalWrite(p, HIGH);
  }
  pinMode(PIN_GDO0, INPUT);
  SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI);
}

void loop() {
  Serial.println("--- CC1101 ---");

  // Reset manual do datasheet: pulso no CS, espera 40 us, strobe SRES.
  digitalWrite(PIN_CS, LOW);
  delayMicroseconds(10);
  digitalWrite(PIN_CS, HIGH);
  delayMicroseconds(40);
  if (cc1101(CC1101_SRES, false) < 0) {
    Serial.println("FALHA: MISO nunca baixou. Confira 3V3/GND do módulo, MISO (13) e CS (14).");
    delay(3000);
    return;
  }

  int part = cc1101(CC1101_PARTNUM | 0xC0, true);
  int ver = cc1101(CC1101_VERSION | 0xC0, true);
  Serial.printf("PARTNUM: 0x%02X (esperado 0x00)\n", part);
  Serial.printf("VERSION: 0x%02X (esperado 0x14; 0x04 em lote antigo)\n", ver);
  if (ver == 0x14 || ver == 0x04) Serial.println("OK: CC1101 respondendo no SPI.");
  else if (ver == 0x00) Serial.println("FALHA: leu 0x00. SCK (12)/MOSI (11) solto ou módulo sem energia.");
  else Serial.println("Valor inesperado: chip não é CC1101 ou jumper com mau contato.");

  // Depois do reset, o GDO0 sai com CLK_XOSC/192: 26 MHz / 192 ≈ 135 kHz.
  // ponytail: contagem por software perde algumas bordas; um pouco abaixo de 135 é normal.
  uint32_t bordas = 0, t0 = micros();
  int ultimo = digitalRead(PIN_GDO0);
  while (micros() - t0 < 10000) {  // janela de 10 ms
    int v = digitalRead(PIN_GDO0);
    bordas += v && !ultimo;
    ultimo = v;
  }
  Serial.printf("GDO0: ~%.0f kHz (esperado ~135)\n", bordas / 10.0);
  if (bordas == 0) Serial.println("FALHA: GDO0 parado. Fio do pino 15 solto.");

  delay(3000);
}
