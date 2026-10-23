# Prompts dos cartuchos (geração de imagem)

Prompts usados para gerar as etiquetas conceito dos cartuchos do BMO no Gemini. A ideia é
que cada cartucho pareça um **jogo de videogame antigo**: etiqueta em pixel art, com um
**nome que funciona como título de jogo** e codifica a função do cartucho (nada de logo de
marca). Todos mantêm a mesma família visual: carcaça **teal**, borda de **contatos dourados**
(card edge) embaixo, foto de produto com fundo off-white.

Visão geral e especificação técnica do cartucho estão no [README](../README.md#especificação-do-cartucho-card-edge).

| Cartucho | Função | Nome (título de jogo) | Imagem |
|---|---|---|---|
| LoRa | Rádio de longo alcance, 915 MHz (comunicação entre dois BMOs) | WAVE RIDER | [`cartucho-wave-rider.jpg`](img/cartucho-wave-rider.jpg) |
| Câmera | Visão para o modo agente (um "corpo para o Claude" via API) | EAGLE EYE | [`cartucho-eagle-eye.jpg`](img/cartucho-eagle-eye.jpg) |

> Dica: para manter a família idêntica, anexe no Gemini uma das imagens já geradas como
> referência de estilo, junto com o prompt.

---

## WAVE RIDER — cartucho LoRa (915 MHz)

```
Fotografia de produto de um cartucho de videogame retrô feito em casa, membro de uma
família de cartuchos. Corpo em plástico impresso em 3D (FDM), com as linhas de camada
visíveis, na cor TEAL (verde-água), formato de retângulo com cantos arredondados, do
tamanho aproximado de um cartucho de Game Boy. Na borda INFERIOR, uma fileira de
contatos dourados tipo "card edge" (gold fingers), como a borda de uma placa de
circuito. No TOPO do cartucho, uma pequena ANTENA HELICOIDAL de mola, preta.

A frente do cartucho tem uma ETIQUETA brilhante que imita a CAPA de um JOGO antigo de
8/16 bits, em PIXEL ART. NÃO use o logotipo "LoRa" nem logos de marca. A etiqueta é a
capa de um jogo fictício chamado "WAVE RIDER", com o título em letras grandes de pixel
art, com contorno e sombra, estilo fliperama dos anos 80/90. A cena em pixel art mostra
um herói pequeno surfando sobre ONDAS DE RÁDIO concêntricas que viajam ao longe entre
duas torres/colinas distantes, sugerindo comunicação de longo alcance. No canto, um
pequeno selo de pixel art escrito "915 MHz" como se fosse o nível ou a fase do jogo, e
dois coraçõezinhos de vida. Paleta colorida e alegre (céu azul, nuvens, verde),
coerente com um jogo de plataforma retrô.

Luz de estúdio suave, fundo liso off-white neutro, leve sombra de contato, foco nítido,
estilo de foto de catálogo de produto. Proporção paisagem.
```

Nota técnica: a etiqueta diz 915 MHz porque é a faixa ISM do LoRa no Brasil (Anatel), e não
433 MHz. "LoRa" é marca da Semtech — uso conceitual apenas, por isso a etiqueta é de jogo e
não traz o logo.

---

## EAGLE EYE — cartucho câmera (visão para o modo agente)

Lente de câmera real no **centro da frente**, apontada para a frente (para quem o BMO olha).
O módulo (ex. OV2640) fica virado para fora, no lado oposto aos contatos, e a carcaça do
cartucho precisa de um furo redondo para a lente na face frontal.

```
Fotografia de produto de um cartucho de videogame retrô feito em casa, membro da mesma
família de cartuchos (mesma identidade visual). Corpo em plástico impresso em 3D (FDM),
com linhas de camada visíveis, na cor TEAL (verde-água), retângulo de cantos
arredondados, tamanho de cartucho de Game Boy. Na borda INFERIOR, uma fileira de
contatos dourados tipo "card edge" (gold fingers).

No CENTRO da FRENTE do cartucho, embutida na própria etiqueta, há uma LENTE DE CÂMERA
redonda real, apontada PARA A FRENTE (de frente para quem olha a foto), como o olho de
uma webcam ou de uma câmera de celular, com reflexo de vidro escuro. A lente fica
integrada à arte, como se fosse o "olho" do personagem do jogo.

A frente tem uma ETIQUETA brilhante que imita a CAPA de um JOGO antigo de 8/16 bits em
PIXEL ART, emoldurando a lente. NÃO use logos de marca. É a capa de um jogo fictício
chamado "EAGLE EYE", com o título em letras grandes de pixel art, contorno e sombra,
estilo capa de jogo retrô. A arte em pixel art em volta da lente mostra um robozinho
fofo cujo rosto se funde com a lente central (a lente é o olho dele), com um feixe de
visão/varredura saindo em direção ao observador e pequenos ícones de "reconhecido"
(checks em pixel) e alvos ao redor, sugerindo visão de máquina / uma IA que enxerga.
No canto, um selo de pixel art escrito "VISION" como se fosse o modo do jogo, e dois
coraçõezinhos de vida. Paleta colorida e alegre, coerente com um jogo de plataforma retrô.

Luz de estúdio suave, fundo liso off-white neutro, leve sombra de contato, foco nítido,
estilo foto de catálogo de produto. Proporção paisagem.
```
