# Firmware

Opções de firmware do BMO v1 e plano de trabalho. Hardware e pinagem em [hardware.md](hardware.md). Visão geral no [README](../README.md).

## Índice

- [Opções de firmware](#opções-de-firmware)
- [Configuração da placa](#configuração-da-placa)
- [Plano de firmware](#plano-de-firmware)
- [Rosto do BMO (tela principal)](#rosto-do-bmo-tela-principal)

---

## Opções de firmware

Um firmware por vez (como "cartuchos de software"):

| Firmware | Uso |
|---|---|
| **Bruce** (C++) | Multitool pronto (RF, NFC, IR, WiFi/BLE). Base do projeto. Suporta ILI9341 |
| **MicroPython** | Escrever Python e testar cada módulo. Interativo, ótimo para aprender |
| **Retro-Go** | Jogos retrô. Roda bem NES, GB, GBC, Master System, Game Gear e PC Engine. SNES e Mega Drive: lento ou parcial. GBA: não roda |
| **Modo agente** (futuro) | BMO como corpo remoto de um agente de IA via WiFi/BLE (WebSocket), usando speaker, mic e tela. Só firmware, sem hardware novo |

A parte custom a escrever é a leitura dos botões/D-pad e a integração no input do Bruce/emulador.

---

## Configuração da placa

| Item | Configuração |
|---|---|
| ESP32-S3 N16R8 no Arduino IDE | `PSRAM: OPI PSRAM` e `Flash Size: 16MB` |
| Display | Driver ILI9341 (tela única) |

---

## Plano de firmware

1. Fechar a entrada do v1: só D-pad + botões, ou com analógico (sticks do controle PS3 no ADC).
2. Montar o núcleo na protoboard (ESP32-S3 + tela + CC1101, sem solda) e rodar Bruce / MicroPython.
3. Testar cada módulo isolado em MicroPython (NFC lê tag, tela acende, scan WiFi).
4. Somar NFC, IR, áudio e mic.
5. Ligar botões/D-pad no GPIO e integrar no input do Bruce/emulador.
6. Programar o rosto animado do BMO na tela principal.
7. Rodar um jogo no Retro-Go.
8. (Futuro) Modo agente via WiFi/BLE.

---

## Rosto do BMO (tela principal)

O BMO tem **uma tela só** (ILI9341 3,2" colorida). Ela mostra o **rosto animado do BMO** quando ocioso (olhos piscam, boca reage), o **menu/terminal** quando em uso e indicadores de **status** (bateria, sinal, atividade). Alterna conforme o estado do aparelho.

Recomendação de implementação: desenhar os rostos **por código** (ex. TFT_eSPI, com primitivas de círculo, retângulo e linha), não por bitmap, porque são formas geométricas simples e a animação fica leve e fluida.

Mapear cada expressão a um estado do aparelho: ocioso, escaneando, sucesso, erro e bateria baixa. Há um SVG com 30 rostos do personagem como referência visual.
