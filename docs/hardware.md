# Hardware

Lista de componentes, arquitetura dos barramentos, pinagem, alimentação e configurações críticas do BMO v1 (ESP32-S3). Visão geral do projeto no [README](../README.md).

## Índice

- [Lista de componentes (BOM)](#lista-de-componentes-bom)
- [Arquitetura](#arquitetura)
- [Pinagem (ESP32-S3 N16R8)](#pinagem-esp32-s3-n16r8)
- [Alimentação](#alimentação)
- [Configurações críticas](#configurações-críticas)

---

## Lista de componentes (BOM)

Preços e links do AliExpress variam e expiram, então a tabela usa **termos de busca**. No NFC, IR e áudio, confira sempre o chip (não o título genérico do anúncio).

| Item | Qtd | Termo de busca | Observação |
|---|---:|---|---|
| ESP32-S3 DevKitC-1 N16R8 | 1 | `ESP32-S3 DevKitC-1 N16R8` | 16MB flash, 8MB PSRAM, 2x USB-C, pré-soldado |
| TFT 3,2" ILI9341 320×240 SPI | 1 | `3.2 ILI9341 320x240 SPI no touch` | sem touch (SKU MSP3217). Tela única: rosto do BMO + menu + status |
| CC1101 433 MHz + antena SMA | 1 | `CC1101 433MHz module SMA antenna` | sub-GHz |
| PN532 V3 NFC | 1 | `PN532 NFC module V3` | DIP switch em I²C (0x24) |
| Par IR KY-022 + KY-005 | 1 | `KY-022 KY-005` | RX + TX |
| MAX98357A (amp I²S) | 1 | `MAX98357A I2S amplifier` | alimentar em 5V |
| Alto-falante 8 Ω 2 W mini | 1 | `speaker 8 ohm 2W mini` | ~28 mm |
| Mic INMP441 (I²S) | 1 | `INMP441 I2S microphone` | captação de voz |
| Módulo MicroSD SPI (mini 3,3V) | 1 | `Micro SD card module SPI` | variante mini |
| Cartão microSD 32 GB | 1 | marca (SanDisk/Samsung/ADATA) | formatar FAT32 |
| Bateria LiPo 3,7V 1S ~2000 mAh | 1 | `LiPo 3.7V 2000mAh 1S protection` | comprar por último, ~6 mm de espessura |
| Carga + proteção USB-C | 1 | `TP4056 Type-C with protection DW01` | com saída OUT separada |
| MT3608 boost ajustável | 1 | `MT3608 step up module` | regular 5,0V antes de ligar |
| Botões tácteis 6×6 | vários | `tactile button 6x6 kit` | D-pad + ação (entrada do v1) |
| Chave SPST slide mini | 1 | `SPST slide switch mini` | liga/desliga |
| Resistores 4,7k / 100k / 1k | kit | `resistor kit 4.7k 100k 1k` | pull-up I²C, divisor de bateria |
| Capacitores 100nF (104) | ~5 | `100nF ceramic capacitor 104` | desacoplamento |
| Perfboard | 1 a 2 | `perfboard double side` | cortar no tamanho |
| Jumpers Dupont (M-M e M-F) | kit | `Dupont jumper wire kit` | protoboard |
| Fio fino 30 AWG | 1 | `30 AWG silicone wire` | fiação fina |

**Removido do v1**: teclado Rii i8, 2× MCP23017 e soquetes DIP (foram para o Projeto 2); OLED 1,3" secundário (a tela única faz rosto + menu + status).

---

## Arquitetura

```text
ESP32-S3 N16R8 (WiFi + BT nativo)
├── SPI (SCK/MOSI/MISO compartilhados, um CS por dispositivo)
│   ├── Display ILI9341 (3,2")
│   ├── CC1101
│   └── MicroSD
├── I²C (SDA/SCL)
│   └── PN532 (0x24)
├── I²S
│   ├── MAX98357A (saída, alimentado em 5V)
│   └── INMP441 (entrada, mic)
├── GPIO direto
│   ├── Botões + D-pad
│   ├── IR RX/TX
│   └── Leitura de bateria
└── USB (gravação e BadUSB)
```

- **SPI** (SCK/MOSI/MISO compartilhados, cada um com seu CS): Display, CC1101, MicroSD.
- **I²C** (SDA/SCL): PN532 (0x24). Tela única; sem OLED.
- **I²S**: MAX98357A (saída) + INMP441 (entrada), mesmo barramento.
- **GPIO direto**: IR RX/TX, botões/D-pad, leitura de bateria.

---

## Pinagem (ESP32-S3 N16R8)

Proposta de referência. Conferir contra a serigrafia da placa; o Bruce permite setar pino a pino.

| Função | GPIO | Nota |
|---|---:|---|
| I²C SDA | 8 | pull-up 4,7k |
| I²C SCL | 9 | pull-up 4,7k |
| SPI SCK | 12 | compartilhado |
| SPI MOSI | 11 | compartilhado |
| SPI MISO | 13 | compartilhado |
| CS Display | 10 | |
| CS CC1101 | 14 | |
| CS MicroSD | 21 | |
| Display DC | 17 | |
| Display RES | 18 | |
| Display BLK | 16 | backlight (3,3V fixo ou PWM) |
| CC1101 GDO0 | 15 | interrupção RF |
| IR RX (KY-022) | 4 | |
| IR TX (KY-005) | 5 | |
| I²S BCLK | 40 | áudio |
| I²S LRC | 41 | áudio |
| I²S DOUT (speaker) | 42 | amp em 5V |
| I²S SD IN (mic) | 6 | mic em 3,3V, L/R no GND |
| VBAT sense | 1 | divisor 100k/100k, ×2 no firmware |
| Botão BOOT/power | 0 | strapping |
| Botões / D-pad (gaming) | 38, 39, 47, 48, … | GPIO livres (o teclado saiu, sobram muitos) |

**Não usar:** GPIO 26 a 37 (flash/PSRAM octal), 19/20 (USB nativo), 43/44 (UART0). Cuidado com strapping: 3, 45, 46.

---

## Alimentação

```text
LiPo → B+ / B- da placa de carga + proteção (USB-C carrega a bateria)
OUT da placa → [chave SPST] → VIN do MT3608
VOUT do MT3608 (5,0V) → pino 5V do ESP32-S3 → regulador onboard → 3V3 → VCC dos módulos
VOUT do MT3608 (5,0V) → MAX98357A (alimentado em 5V)
```

- Regular o **MT3608 em 5,0V** com multímetro **antes** de ligar no ESP32.
- A carga puxa pelo **OUT** da placa de proteção (senão a proteção de sobredescarga não atua).
- Nunca expor a bateria crua.

---

## Configurações críticas

| Item | Configuração |
|---|---|
| MT3608 | Ajustar para 5,0V com multímetro **antes** de conectar ao ESP32 |
| PN532 | DIP switches em I²C (0x24). Plano B: HSU (serial) se instável |
| I²C | Pull-ups de 4,7k em SDA e SCL. O scan deve achar `0x24` (PN532) |
| microSD | Formatar em FAT32 |

Configurações de IDE e drivers (PSRAM, flash, ILI9341) estão em [firmware.md](firmware.md#configuração-da-placa).
