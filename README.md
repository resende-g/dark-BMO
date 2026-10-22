# dark-bmo

> Multitool portátil DIY de estudo de segurança da informação, estilo Flipper Zero, caseiro.
> Baseado em ESP32-S3, com cara de BMO (Hora de Aventura). Jogos retrô + RF / NFC / IR.

![status](https://img.shields.io/badge/status-planejamento%20%2F%20montagem-yellow)
![plataforma](https://img.shields.io/badge/MCU-ESP32--S3-blue)
![licença](https://img.shields.io/badge/licen%C3%A7a-MIT-green)

---

## Sobre

O **dark-bmo** (ou só BMO) é um aparelho de mão feito do zero para estudar segurança da informação na prática: rádio sub-GHz, NFC, infravermelho, WiFi e Bluetooth. Nasceu do reaproveitamento de um mini teclado Rii i8 achado em casa e foi crescendo até virar um projeto completo de hardware + firmware.

O nome e o visual são **inspirados** no personagem BMO de Hora de Aventura (ver [Aviso legal](#aviso-legal)): corpo teal, carinha numa telinha, formato de computador-brinquedo.

É um projeto de aprendizado. O objetivo é tanto a ferramenta quanto o processo de montar, soldar, entender barramentos e escrever firmware.

> ⚠️ **Uso responsável.** As funções de RF, NFC e IR servem para estudar protocolos e testar no seu próprio equipamento, em laboratório ou em CTFs. Veja [Segurança e ética](#segurança-e-ética).

---

## Índice

- [Status](#status)
- [Versões do projeto](#versões-do-projeto)
- [Recursos](#recursos)
- [Documentação](#documentação)
- [Segurança e ética](#segurança-e-ética)
- [Aviso legal](#aviso-legal)
- [Licença](#licença)

---

## Status

**Planejado, parcialmente comprado, ainda não montado.** Fase atual: aguardar peças, montar na protoboard e começar o firmware.

---

## Versões do projeto

O projeto foi dividido em dois, cada um com o hardware certo para o seu propósito.

### BMO v1 (este repositório): ESP32-S3

Jogos retrô + RF / NFC / IR simples. **Sem teclado QWERTY.** Entrada por **botões tácteis + D-pad** (estilo controle de videogame), o que aproxima o visual do personagem (tela grande em cima, botões coloridos embaixo) e simplifica muito a montagem.

### Projeto 2 (futuro): Raspberry Pi + teclado Rii

Kali Linux de verdade para pentest sério. O teclado QWERTY do Rii i8 vai para cá, onde digitar comando faz sentido. Fora do escopo deste repositório por enquanto.

---

## Recursos

| Recurso | Hardware | Firmware base |
|---|---|---|
| Sub-GHz 433 MHz | CC1101 + antena SMA | Bruce |
| NFC 13,56 MHz | PN532 (I²C) | Bruce |
| Infravermelho (TX + RX) | par KY-022 / KY-005 | Bruce |
| WiFi + Bluetooth | nativo do ESP32-S3 | Bruce |
| Jogos retrô (NES, GB, GBC, SMS, GG, PCE) | ESP32-S3 + tela + SD | Retro-Go |
| Áudio (som + mic) | MAX98357A + speaker + INMP441 | |
| Rosto animado do BMO | OLED 1,3" SH1106 | custom |
| Scripts / testes | | MicroPython |

---

## Documentação

O detalhe técnico fica na pasta [docs/](docs/):

| Documento | Conteúdo |
|---|---|
| [docs/hardware.md](docs/hardware.md) | BOM, arquitetura dos barramentos, pinagem, alimentação e configurações críticas |
| [docs/firmware.md](docs/firmware.md) | Opções de firmware (Bruce, MicroPython, Retro-Go), configuração da placa, rosto do BMO e plano |
| [docs/carcaca.md](docs/carcaca.md) | Notas da carcaça 3D: layout, furos, fixação e dimensões |
| [docs/roadmap.md](docs/roadmap.md) | Roadmap, montagem passo a passo e decisões rejeitadas |

---

## Segurança e ética

Este é um projeto educacional de segurança da informação. As capacidades de RF (sub-GHz), NFC e IR existem para **aprender como os protocolos funcionam** e para testar em equipamento próprio, em laboratório ou em competições de captura de bandeira (CTF).

Não use para interferir, acessar ou clonar sistemas, cartões, controles ou dispositivos de terceiros sem autorização explícita. Rádio, NFC e IR são regulados; respeite a legislação local (no Brasil, Anatel e leis de crimes cibernéticos, entre outras). A responsabilidade pelo uso é de quem monta e opera.

---

## Aviso legal

BMO (Beemo) é um personagem de **Adventure Time**, propriedade da Cartoon Network / Warner Bros. Discovery. Este projeto é um trabalho de fã, **sem fins lucrativos**, apenas inspirado na estética do personagem. Não é afiliado, patrocinado nem endossado pelos detentores dos direitos. Não venda nem distribua comercialmente peças, carcaças ou imagens que reproduzam o personagem.

---

## Licença

Código sob [MIT](LICENSE). Documentação sob [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/) (não comercial, pelo aviso acima).

---

*Projeto pessoal de aprendizado. Feito com peças de ferro-velho, um teclado velho e muita pesquisa. Be more.*
