# Carcaça 3D

Notas de projeto da carcaça do BMO v1. Componentes e pinagem em [hardware.md](hardware.md). Visão geral no [README](../README.md).

## Conceito

- Corpo retangular **teal**, impresso em 3D (FDM), com duas perninhas (estilo BMO em pé).
- Ergonomia por chanfro e arredondamento das arestas inferiores, mantendo o corpo retangular.
- Detalhes mecânicos precisos (recorte de botões, heat-sets, bosses) saem do **CAD** (Fusion, Tinkercad ou FreeCAD), não de gerador de imagem.

## Layout v1

Aproxima o aparelho do personagem: tela grande colorida no **topo**; abaixo, controles de videogame coloridos (D-pad amarelo, botões azul, verde e vermelho). **Sem teclado.**

## Fixação

Parafusos na **traseira** com **heat-set inserts** (não na frente).

## Posição dos componentes

| Componente | Posição e observações |
|---|---|
| Tela principal (única) | topo; faz rosto + menu + status |
| Antena SMA | topo |
| Antena do PN532 | virada para fora, sem metal atrás |
| LED + receptor IR | frente |
| Speaker | grade no canto inferior |
| Microfone | furo no topo |
| 2× USB-C + chave | uma lateral |
| Slot microSD | outra lateral |

## Dimensões conhecidas

| Peça | Medida |
|---|---|
| Tela principal (placa) | 55 × 65 mm (área ativa 48,6 × 64,8 mm) |
| Bateria alvo | ~6 mm de espessura, 2000 mAh |

**A medir:** altura livre acima dos controles, que define a orientação da tela principal.
