# dark-bmo

> Multitool portátil DIY de estudo de segurança da informação, estilo Flipper Zero, caseiro.
> Baseado em ESP32-S3, com cara de BMO (Hora de Aventura). Jogos retrô + RF / NFC / IR.

![status](https://img.shields.io/badge/status-planejamento%20%2F%20montagem-yellow)
![plataforma](https://img.shields.io/badge/MCU-ESP32--S3-blue)
![licença](https://img.shields.io/badge/licen%C3%A7a-MIT-green)

---

## Sobre

O **dark-bmo** (ou só BMO) é um aparelho de mão feito do zero para estudar segurança da
informação na prática: rádio sub-GHz, NFC, infravermelho, WiFi e Bluetooth. Nasceu do
reaproveitamento de um mini teclado Rii i8 achado em casa e foi crescendo até virar um
projeto completo de hardware + firmware.

O nome e o visual são **inspirados** no personagem BMO de Hora de Aventura (ver
[Aviso legal](#aviso-legal)): corpo teal, carinha fofa numa telinha, formato de
computador-brinquedo.

É um projeto de aprendizado. O objetivo é tanto a ferramenta quanto o processo de montar,
soldar, entender barramentos e escrever firmware.

> ⚠️ **Uso responsável.** As funções de RF, NFC e IR servem para estudar protocolos e
> testar no seu próprio equipamento, em laboratório ou em CTFs. Veja [Segurança e ética](#segurança-e-ética).

---

## Índice

- [Status](#status)
- [Pessoas do projeto](#pessoas-do-projeto)
- [Versões do projeto](#versões-do-projeto)
- [Recursos](#recursos)
- [Lista de componentes (BOM)](#lista-de-componentes-bom)
- [Arquitetura](#arquitetura)
- [Pinagem](#pinagem-esp32-s3-n16r8)
- [Alimentação](#alimentação)
- [Configurações críticas](#configurações-críticas)
- [Firmware](#firmware)
- [Rosto do BMO (tela principal)](#rosto-do-bmo-tela-principal)
- [Carcaça 3D](#carcaça-3d)
- [Montagem passo a passo](#montagem-passo-a-passo)
- [Roadmap](#roadmap)
- [Decisões de projeto (e alternativas rejeitadas)](#decisões-de-projeto)
- [Segurança e ética](#segurança-e-ética)
- [Aviso legal](#aviso-legal)
- [Licença](#licença)

---

## Status

**Planejado, parcialmente comprado, ainda não montado.** Fase atual: aguardar peças,
montar na protoboard e começar o firmware.

---

## Pessoas do projeto

| Pessoa | Papel |
|---|---|
| **Resende** (Gabriel) | Lead do projeto: arquitetura, firmware, compras, documentação |
| **Tiago Batista** | PCB caseira no laser (viabiliza o conector card edge e a migração perfboard → PCB) |
| **Tiago Efraim** | Impressão 3D da carcaça e montagem; monta um BMO em par (candidato ao cartucho LoRa p/ comunicação entre os dois) |

São dois Tiagos distintos: **Batista** cuida da PCB; **Efraim** imprime e monta junto.

## Versões do projeto

O projeto foi dividido em dois, cada um com o hardware certo para o seu propósito:

### BMO v1 (este repositório) — ESP32-S3
Jogos retrô + ataques simples de RF / NFC / IR. **Sem teclado QWERTY.** Entrada por
**botões tácteis + D-pad** (estilo controle de videogame), o que aproxima o visual do
personagem (tela grande em cima, botões coloridos embaixo) e simplifica muito a montagem.

### Projeto 2 (futuro) — Raspberry Pi + teclado Rii
Kali Linux de verdade para pentest sério. O teclado QWERTY do Rii i8 vai para cá, onde
digitar comando faz sentido. Fora do escopo deste repositório por enquanto.

---

## Recursos

| Recurso | Hardware | Firmware base |
|---|---|---|
| Sub-GHz 433 MHz | CC1101 + antena SMA | Bruce |
| NFC 13,56 MHz | PN532 (I²C) | Bruce |
| Infravermelho (TX + RX) | par KY-022 / KY-005 | Bruce |
| WiFi + Bluetooth | nativo do ESP32-S3 | Bruce |
| Jogos retrô (NES, GB, GBC, SMS, GG, PCE) | ESP32-S3 + tela + SD | Retro-Go |
| Áudio (som + mic) | MAX98357A + speaker + INMP441 | — |
| Rosto animado do BMO | tela principal ILI9341 | custom |
| Scripts / testes | — | MicroPython |

---

## Lista de componentes (BOM)

> Preços e links do AliExpress variam e expiram; use os **termos de busca** abaixo. No NFC,
> IR e áudio, confira sempre o chip (não o título genérico do anúncio).

| Item | Qtd | Termo de busca | Observação |
|---|---:|---|---|
| ESP32-S3 DevKitC-1 N16R8 | 1 | `ESP32-S3 DevKitC-1 N16R8` | 16MB flash, 8MB PSRAM, 2x USB-C, pré-soldado |
| TFT 3,2" ILI9341 320×240 SPI | 1 | `3.2 ILI9341 320x240 SPI no touch` | sem touch (MSP3217). Tela ÚNICA: rosto do BMO + menu + status |
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
| Perfboard | 1-2 | `perfboard double side` | cortar no tamanho |
| Jumpers Dupont (M-M e M-F) | kit | `Dupont jumper wire kit` | protoboard |
| Fio fino 30 AWG | 1 | `30 AWG silicone wire` | fiação fina |

**Removido do v1**: teclado Rii i8, 2× MCP23017 e soquetes DIP (foram para o Projeto 2); **OLED 1,3" secundário** (sem o teclado, uma tela só já faz rosto + menu + status).

---

## Arquitetura

```
                        ┌───────────────────┐
                        │   ESP32-S3 N16R8   │
                        │  (WiFi + BT nativo)│
                        └─────────┬─────────┘
           ┌──────────────┬───────┼────────┬──────────────┐
          SPI            I²C      I2S      GPIO          USB
      ┌────┴────┐     ┌───┴───┐  ┌─┴──┐  ┌──┴───┐      (grava/
   Display     CC1101 PN532       MAX  INMP  botões      BadUSB)
   ILI9341     MicroSD 0x24       98357 441  + D-pad
   (3,2")                          A(5V)(mic)  IR TX/RX
```

- **SPI** (SCK/MOSI/MISO compartilhados, cada um com seu CS): Display, CC1101, MicroSD.
- **I²C** (SDA/SCL): PN532 (0x24). (Tela única; sem OLED secundário.)
- **I²S**: MAX98357A (saída) + INMP441 (entrada), mesmo barramento.
- **GPIO direto**: IR RX/TX, botões/D-pad, leitura de bateria.

---

## Pinagem (ESP32-S3 N16R8)

Proposta de referência — conferir contra a serigrafia da placa; o Bruce permite setar pino a pino.

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

**Não usar:** GPIO 26–37 (flash/PSRAM octal), 19/20 (USB nativo), 43/44 (UART0).
Cuidado com strapping: 3, 45, 46.

---

## Alimentação

```
LiPo + → B+ ┐ placa carga+proteção (USB-C carrega)
LiPo - → B- ┘ → OUT → [chave SPST] → VIN do MT3608
                       VOUT = 5,0V → pino 5V do ESP32 → regulador onboard → 3,3V
3V3 → VCC dos módulos        MAX98357A → puxa 5V do MT3608
```

- Regular o **MT3608 em 5,0V** com multímetro **antes** de ligar no ESP32.
- A carga puxa pelo **OUT** da placa de proteção (senão a proteção de sobredescarga não atua).
- Nunca expor a bateria crua.

---

## Configurações críticas

- **MT3608**: ajustar 5,0V antes de conectar.
- **PN532**: DIP switches em I²C (0x24). Plano B: HSU (serial) se instável.
- **ESP32-S3 N16R8** no Arduino IDE: `PSRAM: OPI PSRAM` e `Flash Size: 16MB`.
- **Display**: driver ILI9341 (tela única).
- **I²C**: pull-ups 4,7k em SDA/SCL. Scan deve achar `0x24` e `0x3C`.
- **microSD**: formatar em FAT32.

---

## Firmware

Um firmware por vez (como "cartuchos de software"):

| Firmware | Uso |
|---|---|
| **Bruce** (C++) | multitool pronto (RF, NFC, IR, WiFi/BLE). Base do projeto. Suporta ILI9341 e SH1106 |
| **MicroPython** | escrever Python e testar cada módulo; interativo, ótimo pra aprender |
| **Retro-Go** | jogos retrô. Roda bem NES, GB, GBC, Master System, Game Gear, PC Engine. SNES/Mega Drive lento/parcial. GBA não |
| **Modo agente** (futuro) | BMO como corpo remoto de um agente de IA via WiFi/BLE (WebSocket), usando speaker/mic/telas. Só firmware, sem hardware novo |

A parte custom a escrever é a leitura dos botões/D-pad e a integração no input do Bruce/emulador.

---

## Rosto do BMO (tela principal)

O BMO tem **uma tela só** (ILI9341 3,2" colorida). Ela mostra o **rosto animado do BMO**
quando ocioso (olhos piscam, boca reage), o **menu/terminal** quando em uso, e indicadores
de **status** (bateria / sinal / atividade). Alterna conforme o estado do aparelho.

Recomendação de implementação: desenhar os rostos **por código** (ex. TFT_eSPI, com
primitivas de círculo/retângulo/linha), não por bitmap, porque são formas geométricas
simples e a animação fica leve e fluida. Mapear cada expressão a um estado do aparelho (ocioso,
escaneando, sucesso, erro, bateria baixa). Há um SVG com 30 rostos do personagem como
referência visual.

---

## Carcaça 3D

- Corpo retangular **teal**, impresso em 3D (FDM), com duas perninhas (estilo BMO em pé).
- **Layout v1** (aproxima do personagem): tela grande colorida no **topo**; abaixo, controles
  de videogame coloridos (D-pad amarelo, botões azul/verde/vermelho). **Sem teclado.**
- **Uma tela só** (ILI9341) no topo, grande, para rosto + menu + status.
- Faixa horizontal acima do D-pad: **conector de expansão** (I²C + 3V3 + GND + GPIO livre),
  com polyfuse/resistor em série na alimentação (protege o ESP32 de curto no módulo plugado).
  No desenho do personagem essa faixa é o slot/leitor do BMO, então um conector ali é fiel.
  - **Grove** ou **pin header**: funcionam em perfboard, prático. Grove dá acesso aos módulos
    prontos da M5Stack.
  - **Card edge** (borda da PCB vira contato, estilo cartucho): o visual de cartucho de verdade.
    Depende de ter PCB (ver nota de PCB caseira abaixo). **Alvo do v1: card edge COMPLETO**,
    expondo I²C + SPI + UART + 3V3 + 5V + GND + 2 GPIO (~13 a 15 contatos). A confirmar com o
    Tiago se a PCB no laser aguenta essa densidade com qualidade; se não, cai para o nível
    MÉDIO (I²C + UART + energia + 2 GPIO, ~9 a 10 contatos), que já cobre a maioria dos cartuchos.
    Proteção obrigatória: polyfuse na alimentação e CS dedicado para quem usar o SPI compartilhado.
  - Alternativa simples, se não quiser conector agora: barra de LEDs de status (power/RF/carga).
- Parafusos na **traseira** com **heat-set inserts** (não na frente).
- Ergonomia por chanfro/arredondamento das arestas inferiores, mantendo o corpo retangular.
- Antena SMA no topo; antena do PN532 virada para fora sem metal atrás; LED + receptor IR na
  frente; grade do speaker no canto inferior; furo do mic no topo; 2× USB-C + chave numa
  lateral; slot microSD na outra.
- Detalhes mecânicos precisos (recorte de botões, heat-sets, bosses) saem do **CAD**
  (Fusion / Tinkercad / FreeCAD), não de gerador de imagem.

### PCB caseira (em avaliação)

O colega **Tiago** faz **PCB caseira no laser** (grava a máscara e corrói o cobre, sem
depender de fábrica). Isso abre duas possibilidades para o BMO:

- **Conector card edge** (cartucho de verdade) na faixa acima do D-pad vira viável já no v1,
  não só numa v2 futura. É o acabamento mais fiel ao personagem.
- O próprio corpo do circuito pode migrar de **perfboard para PCB**, deixando a montagem bem
  mais limpa e robusta.

Limites a confirmar com ele antes de decidir: densidade de trilhas (o ESP32-S3 e os módulos
têm muitos pinos juntos), single vs double side, e quem desenha a PCB (KiCad/EasyEDA).
Reunião de alinhamento a marcar. Enquanto não fecha, o conector padrão é **Grove/pin header
no perfboard**.

### Cartuchos de expansão (o que o card edge permite)

O conector expõe sinais; o cartucho plugado decide a função. **Não** adiciona processamento
(o cérebro continua sendo o ESP32) nem é slot de armazenamento rápido. Com o nível completo,
os cartuchos possíveis:

- **Rádio/RF extra** (via SPI): segundo rádio em outra frequência (868, 315), LoRa, outro NFC/RFID.
- **GPS** (via UART/I²C): georreferenciar capturas.
- **Sensores e módulos** (via I²C): ambientais, telas pequenas, leitores, e os módulos prontos
  da M5Stack/Seeed.
- **Cartuchos temáticos**: cada cartucho como uma "ferramenta" ou "jogo" físico, no espírito do
  cartucho de videogame do BMO.

**Referências visuais (família de cartuchos):** dois conceitos, mesma carcaça teal e mesma
borda de contatos dourados, mudando só etiqueta e antena:
- Cartucho de jogo (etiqueta pixel art): `docs/img/cartucho-conceito.jpg`
- Cartucho LoRa (etiqueta técnica + antena de mola): `docs/img/cartucho-lora-conceito.jpg`

Servem de referência do card edge para a conversa com o Tiago e para o CAD. Decidir na PCB real
se os contatos ficam de um lado (single-side) ou dos dois lados (double-side, dobra os pinos no
mesmo espaço).

Nota técnica do LoRa: a etiqueta da imagem diz 433 MHz, mas no Brasil o LoRa opera na faixa ISM
de **915 MHz** (Anatel: 902-907,5 e 915-928). 433 MHz é a faixa do CC1101 comum. Ajustar para
915 se/quando o cartucho LoRa for feito de verdade. "LoRa" é marca da Semtech (uso conceitual
apenas, não comercial).

Limite honesto: o card edge não torna o BMO mais rápido nem roda IA local; para um "cérebro
extra" o cartucho precisaria do próprio processador (outro projeto). O uso mais valioso para o
propósito de segurança é o **cartucho de rádio/sensor extra**.

### Anatomia de um cartucho (importante)

O **card edge não vem pronto** em nenhum módulo. Um cartucho é montado de duas partes:

1. **Módulo da função** (comprado, ex. módulo LoRa SX1276/1278 do AliExpress): traz o chip e
   tem pinos normais (SPI, energia). Faz o trabalho (rádio, GPS, sensor), mas NÃO tem a borda
   de contatos.
2. **PCB-cartucho** (fabricada pelo Tiago Batista no laser): é a placa com o formato de
   cartucho e os **contatos card edge na borda**. O módulo da função é soldado em cima dela, e
   as trilhas ligam os pinos do módulo aos contatos certos da borda.

```
[Módulo LoRa comprado] --soldado em--> [PCB-cartucho c/ card edge] --encaixa no--> [conector do BMO]
```

Ou seja: **cartucho completo = módulo da função + PCB-cartucho com card edge**. O conector
fêmea (a fenda que recebe o cartucho) fica no corpo do BMO. Por isso a PCB do Batista é
essencial: o AliExpress dá o cérebro do rádio, o Batista dá o corpo do cartucho.

### Dimensões conhecidas
| Peça | Medida |
|---|---|
| Tela principal (placa) | 55 × 65 mm (área ativa 48,6 × 64,8 mm) |
| Bateria alvo | ~6 mm de espessura, 2000 mAh |

> A medir: altura livre acima dos controles, que define a orientação da tela principal.

---

## Montagem passo a passo

1. Confirmar entrada do v1: só D-pad + botões, ou com analógico (sticks do controle PS3 no ADC).
2. Montar o núcleo na protoboard: ESP32-S3 + tela + CC1101 (sem solda). Rodar Bruce / MicroPython.
3. Testar cada módulo isolado em MicroPython (NFC lê tag, tela acende, scan WiFi).
4. Somar NFC, IR, áudio e mic.
5. Ligar botões/D-pad no GPIO e integrar no firmware.
6. Programar o rosto animado do BMO na tela principal.
7. Comprar a bateria pela medida; modelar e imprimir a carcaça.

---

## Roadmap

- [ ] Fechar entrada (D-pad + botões vs analógico)
- [ ] Protoboard: ESP32 + tela + CC1101 rodando Bruce
- [ ] NFC (PN532) lendo tag
- [ ] IR TX/RX
- [ ] Áudio (speaker) + mic
- [ ] Rosto animado na tela principal
- [ ] Retro-Go rodando um jogo
- [ ] Alinhar PCB caseira com o Tiago (card edge vs perfboard)
- [ ] Modelar carcaça no CAD
- [ ] Imprimir e montar
- [ ] (Futuro) Modo agente via WiFi/BLE
- [ ] (Futuro) Projeto 2: Raspberry Pi + Rii + Kali

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
| Segunda tela (OLED de status) | Sem o teclado, a tela única ILI9341 faz rosto + menu + status |

---

## Segurança e ética

Este é um projeto educacional de segurança da informação. As capacidades de RF (sub-GHz),
NFC e IR existem para **aprender como os protocolos funcionam** e para testar em equipamento
próprio, em laboratório ou em competições de captura de bandeira (CTF).

Não use para interferir, acessar ou clonar sistemas, cartões, controles ou dispositivos de
terceiros sem autorização explícita. Rádio, NFC e IR são regulados; respeite a legislação
local (no Brasil, Anatel e leis de crimes cibernéticos, entre outras). A responsabilidade
pelo uso é de quem monta e opera.

---

## Aviso legal

BMO (Beemo) é um personagem de **Adventure Time**, propriedade da Cartoon Network / Warner
Bros. Discovery. Este projeto é um trabalho de fã, **sem fins lucrativos**, apenas inspirado
na estética do personagem. Não é afiliado, patrocinado nem endossado pelos detentores dos
direitos. Não venda nem distribua comercialmente peças, carcaças ou imagens que reproduzam
o personagem.

---

## Licença

Código sob [MIT](LICENSE). Documentação sob
[CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/) (não comercial, pelo aviso acima).

---

*Projeto pessoal de aprendizado. Feito com peças de ferro-velho, um teclado velho e muita
pesquisa. Be more.*
