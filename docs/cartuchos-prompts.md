# Prompts dos cartuchos (geração de imagem)

Prompts usados para gerar as etiquetas conceito dos cartuchos do d-BMO no Gemini. A ideia é
que cada cartucho pareça um **jogo de videogame antigo**: etiqueta em pixel art, com um
**título de jogo inspirado em distopias clássicas da literatura**, que codifica a função do
cartucho (nada de logo de marca). Todos mantêm a mesma família visual: carcaça **prata**
impressa em 3D, borda de **contatos dourados** (card edge) embaixo, foto de produto com fundo
off-white.

Visão geral e especificação técnica do cartucho estão no [README](../README.md#especificação-do-cartucho-card-edge).

| Cartucho | Função | Nome (título de jogo) | Imagem |
|---|---|---|---|
| LoRa | Rádio de longo alcance, 915 MHz (comunicação entre dois d-BMOs) | BRAVE NEW WORLD | [`cartucho-brave-new-world.jpg`](img/cartucho-brave-new-world.jpg) |
| Câmera | Visão para o modo agente (um "corpo para o Claude" via API) | BIG BROTHER | [`cartucho-big-brother.jpg`](img/cartucho-big-brother.jpg) |

Os nomes trocaram em 02/11/2026: o LoRa era WAVE RIDER e a câmera era EAGLE EYE, ambos no
visual teal antigo. Os prompts abaixo descrevem as imagens atuais; o Gemini não reproduz uma
imagem exatamente a partir do texto.

> Dica: para manter a família idêntica, anexe no Gemini uma das imagens já geradas como
> referência de estilo, junto com o prompt.

---

## BRAVE NEW WORLD — cartucho LoRa (915 MHz)

```
Fotografia de produto de um cartucho de videogame retrô feito em casa, membro de uma
família de cartuchos. Corpo em plástico PRATA impresso em 3D (FDM), com as linhas de
camada visíveis, formato de retângulo com cantos arredondados, com 52 × 52 mm. Na borda
INFERIOR, uma fileira de contatos dourados tipo "card edge" (gold fingers), como a borda
de uma placa de circuito. No TOPO do cartucho, uma pequena ANTENA HELICOIDAL de mola,
preta.

A frente do cartucho tem uma ETIQUETA brilhante que imita a CAPA de um JOGO antigo de
8/16 bits, em PIXEL ART. NÃO use o logotipo "LoRa" nem logos de marca. A etiqueta é a
capa de um jogo fictício chamado "BRAVE NEW WORLD", com o título em letras grandes de
pixel art laranja e amarelo, com contorno e sombra, estilo fliperama dos anos 80/90. A
cena em pixel art mostra uma floresta com ruínas antigas, onde um herói pequeno com arco
e flecha enfrenta robôs cinzentos de olhos vermelhos. No canto inferior, um pequeno selo
de pixel art escrito "915 MHz" como se fosse o nível ou a fase do jogo, e dois
coraçõezinhos de vida.

Luz de estúdio suave, fundo liso off-white neutro, leve sombra de contato, foco nítido,
estilo de foto de catálogo de produto. Proporção paisagem.
```

Nota técnica: a etiqueta diz 915 MHz porque é a faixa ISM do LoRa no Brasil (Anatel), e não
433 MHz. "LoRa" é marca da Semtech — uso conceitual apenas, por isso a etiqueta é de jogo e
não traz o logo.

---

## BIG BROTHER — cartucho câmera (visão para o modo agente)

Lente de câmera real no **centro da frente**, apontada para a frente (para quem o d-BMO olha).
O módulo (ex. OV2640) fica virado para fora, no lado oposto aos contatos, e a carcaça do
cartucho precisa de um furo redondo para a lente na face frontal.

```
Fotografia de produto de um cartucho de videogame retrô feito em casa, membro da mesma
família de cartuchos (mesma identidade visual). Corpo em plástico PRATA impresso em 3D
(FDM), com linhas de camada visíveis, retângulo de cantos arredondados, com 52 × 52 mm.
Na borda INFERIOR, uma fileira de contatos dourados tipo "card edge" (gold fingers).

No CENTRO da FRENTE do cartucho, embutida na própria etiqueta, há uma LENTE DE CÂMERA
redonda real, apontada PARA A FRENTE (de frente para quem olha a foto), como o olho de
uma webcam, com reflexo de vidro escuro. A lente fica integrada à arte, como se fosse o
"olho" do personagem do jogo.

A frente tem uma ETIQUETA brilhante que imita a CAPA de um JOGO antigo de 8/16 bits em
PIXEL ART, emoldurando a lente. NÃO use logos de marca. É a capa de um jogo fictício
chamado "BIG BROTHER", com o título em letras grandes de pixel art amarelo e laranja,
contorno e sombra, e o ano "1984" em pixel art acima do título e abaixo da lente. Paleta
quente de vermelho, laranja e amarelo sobre fundo escuro. A arte em volta da lente mostra
um robozinho cujo rosto se funde com a lente central (a lente é o olho dele), com um
feixe de visão saindo em direção ao observador, pequenos ícones de "reconhecido" (checks
em pixel) e um alvo ao redor, sugerindo vigilância e visão de máquina. No canto, um selo
de pixel art escrito "VISION" como se fosse o modo do jogo, e dois coraçõezinhos de vida.

Luz de estúdio suave, fundo liso off-white neutro, leve sombra de contato, foco nítido,
estilo foto de catálogo de produto. Proporção paisagem.
```
