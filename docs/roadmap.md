# Roadmap

Próximos passos, montagem e decisões do BMO v1. Visão geral no [README](../README.md).

## Índice

- [Roadmap](#roadmap-1)
- [Montagem passo a passo](#montagem-passo-a-passo)
- [Decisões de projeto](#decisões-de-projeto)

---

## Roadmap

- [ ] Fechar entrada (D-pad + botões vs analógico)
- [ ] Protoboard: ESP32 + tela + CC1101 rodando Bruce
- [ ] NFC (PN532) lendo tag
- [ ] IR TX/RX
- [ ] Áudio (speaker) + mic
- [ ] Rosto animado no OLED
- [ ] Retro-Go rodando um jogo
- [ ] Modelar carcaça no CAD
- [ ] Imprimir e montar
- [ ] (Futuro) Modo agente via WiFi/BLE
- [ ] (Futuro) Projeto 2: Raspberry Pi + Rii + Kali

---

## Montagem passo a passo

1. Confirmar entrada do v1: só D-pad + botões, ou com analógico (sticks do controle PS3 no ADC).
2. Montar o núcleo na protoboard: ESP32-S3 + tela + CC1101 (sem solda). Rodar Bruce / MicroPython.
3. Testar cada módulo isolado em MicroPython (NFC lê tag, tela acende, scan WiFi).
4. Somar NFC, IR, áudio, mic e OLED do rosto.
5. Ligar botões/D-pad no GPIO e integrar no firmware.
6. Programar o rosto animado do BMO no OLED.
7. Comprar a bateria pela medida; modelar e imprimir a carcaça.

---

## Decisões de projeto

Alternativas avaliadas e **descartadas** (documentadas para não repetir):

| Alternativa | Por que não |
|---|---|
| Raspberry Pi / Kali no lugar do ESP32 | Categoria errada (computador vs microcontrolador). Vira o Projeto 2 separado |
| M5Stick / Cardputer ADV | Sem sub-GHz, NFC nem IR-RX de fábrica |
| Placas ESP32 + tela integradas (Guition, JC3248) | Consomem quase todo o GPIO; algumas com 4MB flash matam o gaming |
| Displays e-ink | Refresh lento demais para UI interativa e jogos |
| Segundo ESP32 / placa de processamento acoplada | O "cérebro extra" é remoto por WiFi/BLE, não acoplado por fio |
| Teclado QWERTY no v1 | Removido de propósito; vai para o Projeto 2 (Pi/Kali) |
| Pendrive USB como armazenamento | O microSD já cobre |
