# DBBS 1.0 — d-BMO-body Battery System

> Status: especificação preliminar. Arquitetura funcional definida; componentes, pinagem final, dimensões e layout de PCB ainda dependem de validação.
>
> Escopo: subsistema de bateria da variante d-BMO-body baseada em ESP32-P4 + ESP32-C6. Este documento não substitui nem altera a alimentação do BMO v1 legado baseado em ESP32-S3 descrito no README.

## 1. Decisões consolidadas

| Parâmetro | Decisão |
|---|---|
| Plataforma-alvo | Placa ESP32-P4 + ESP32-C6 (P4-C6) |
| Formato da bateria | Célula pouch plana Li-ion/Li-Po, removível |
| Capacidade desejada | 3.000–4.000 mAh (meta, não requisito de compra isolado) |
| Química inicial suportada | Li-ion/Li-Po 1S, tensão máxima de carga de 4,20 V |
| Carregamento | USB-C dedicado no próprio dispositivo |
| Saída para a placa | 5 V regulados, pelo conector de alimentação de 2 pinos SH1.0 da placa, sujeito à confirmação da revisão e pinagem |
| Troca a quente | Fora do escopo da revisão 1.0; aparelho desligado para substituir a bateria |
| Compatibilidade | Baterias de fabricantes diferentes somente por adaptadores mecânicos/elétricos DBI-1 verificados |

A capacidade de 3.000–4.000 mAh é uma meta de autonomia. Não comprovará compatibilidade física nem capacidade de descarga. Dimensões, corrente contínua/pico, tensão de carga, pinagem e circuito de proteção devem ser verificados por modelo.

## 2. Identificação da placa e alimentação

A descrição comercial recebida é compatível com a família Waveshare ESP32-P4-Module-DEV-KIT, mas a identificação ainda é provisória. Confirmar fabricante, modelo, revisão da PCB, serigrafia, esquema elétrico e pinagem antes de fabricar a DBBS.

Referências do fabricante para conferência:
- https://docs.waveshare.com/ESP32-P4-Module-DEV-KIT
- https://docs.waveshare.com/ESP32-P4-Module-DEV-KIT/Resources-And-Documents
- Esquema: https://files.waveshare.com/wiki/ESP32-P4-Module-DEV-KIT/ESP32-P4-Module-DEV-KIT.pdf

A arquitetura DBBS deve fornecer 5 V regulados à entrada dedicada de 5 V da placa, pelo conector SH1.0 de 2 pinos, após confirmar polaridade e revisão. Não aplicar a tensão bruta da célula (aprox. 3,0–4,2 V) como se fosse uma entrada de 5 V. Não injetar 3,3 V diretamente no barramento interno da placa.

O conector de bateria RTC da placa não é entrada para a bateria principal. Ele se destina à alimentação RTC compatível indicada pelo fabricante.

A placa possui seus próprios reguladores. A DBBS não deve contorná-los nem alimentar diretamente seus trilhos internos sem um projeto específico e validado.

## 3. Arquitetura funcional preliminar

```
USB-C dedicado (5 V)
        |
Proteção de entrada, CC1/CC2, ESD e limitação de corrente
        |
Carregador chaveado 1S com Power Path / gerenciamento de carga do sistema
        |                         |
        |                         +---- SYS
        |                                |
Bateria 1S removível                  Boost DC-DC 5 V
        |                                |
Proteção da célula (PCM)                Proteção contra retorno
        |                                / seleção de fonte
Interface DBI-1 -------------------------+
                                         |
                              Saída 5 V / GND
                                         |
                              SH1.0 2 pinos da P4-C6
```

O diagrama é funcional, não um esquema elétrico liberado para fabricação. A implementação deverá garantir que o caminho de carga, a alimentação do sistema e o boost operem simultaneamente sem instabilidade, sobrecorrente ou retorno entre fontes.

### Blocos obrigatórios

1. **Entrada USB-C:** porta dedicada à carga. Implementar corretamente os resistores de identificação CC (Rd) e proteção ESD. USB Power Delivery não é requisito inicial; dimensionar para uma fonte USB-C 5 V compatível com a corrente de entrada escolhida.
2. **Carregador:** CI chaveado para célula 1S, com Power Path/load sharing. Não selecionar apenas pelo valor máximo de corrente anunciado. Verificar tensão de entrada, corrente de carga, corrente do sistema, limites térmicos e perfil de terminação.
3. **Proteção da célula:** proteção contra sobretensão, subtensão, sobrecorrente e curto-circuito. Pode estar integrada à bateria ou ser implementada na DBBS, mas a presença e os limites devem ser documentados. Evitar empilhar proteções sem compreender seus limiares.
4. **Conversor boost:** elevar a faixa variável da célula/SYS para 5 V regulados. Meta inicial de projeto: 5 V / até 3 A, ainda sujeita a medição da carga real, análise térmica e validação do conversor, indutor, trilhas e conectores. Não tratar esse valor como consumo medido da placa.
5. **Seleção/islação de fontes:** impedir retorno de corrente entre boost, USB-C da DBBS e portas USB da placa. Se a placa for conectada a um computador para programação enquanto a DBBS alimenta a entrada de 5 V, validar a ausência de paralelismo indevido entre VBUS. Implementar power mux, ideal diode ou isolamento apropriado conforme o esquema final.
6. **Medição de carga:** fuel gauge dedicado, por exemplo MAX17048 como candidato, conectado por I²C. Fuel gauge não substitui PCM/BMS.
7. **Temperatura:** usar NTC somente quando a bateria realmente disponibilizar um terminal NTC e sua curva for conhecida. Não simular NTC com resistor fixo para contornar uma proteção.
8. **Saída:** 5 V e GND no conector correto da placa. Confirmar pinagem, corrente admissível e retenção mecânica do SH1.0 real antes do desenho da PCB.

## 4. DBI-1 — interface de bateria proposta

DBI-1 é uma convenção interna proposta para o projeto, não um padrão industrial existente.

| Sinal lógico | Função | Regra |
|---|---|---|
| BAT+ | Positivo da célula | Identificar por documentação e medição controlada |
| BAT− | Negativo da célula | Referência de retorno |
| NTC | Sensor térmico | Opcional; somente se existir e for caracterizado |
| ID | Identificação do modelo/adaptador | Opcional; nunca autoriza carga sem perfil validado |

O adaptador DBI-1 converte o contato físico específico de cada modelo de bateria para a interface lógica comum. A identificação por resistor ou EEPROM poderá informar o modelo, mas o firmware/circuito só deve habilitar a carga quando houver um perfil aprovado para aquela bateria.

### Critérios mínimos para aceitar uma bateria

- Célula única 1S, com tensão máxima de carga documentada de 4,20 V.
- Química e especificação do fabricante identificáveis.
- Pinagem dos contatos confirmada por documentação confiável e verificação elétrica.
- Dimensões e espessura compatíveis com o compartimento, sem pressão sobre a pouch.
- Corrente contínua e de pico compatíveis com o consumo do sistema, incluindo transientes.
- Proteção PCM/BMS presente e caracterizada, ou proteção equivalente implementada e validada na DBBS.
- Limite de corrente de carga permitido pelo fabricante conhecido.
- NTC e ID mapeados corretamente, quando existentes.
- Ausência de danos, inchaço, perfuração, deformação ou histórico desconhecido.

**Não aceitar automaticamente:** baterias 1S de alta tensão (4,35 V/4,40 V), células sem identificação, packs com múltiplas células em série, baterias com pinagem desconhecida ou células cuja corrente de descarga não esteja documentada. A compatibilidade física não implica compatibilidade elétrica.

## 5. Dimensionamento e autonomia

A meta de 3.000–4.000 mAh não define sozinha a autonomia. A energia nominal aproximada de uma célula 1S é:

`Wh ≈ capacidade (Ah) × tensão nominal (V)`

A autonomia real depende da potência média e dos picos da placa, display, áudio, Ethernet, microSD, periféricos e conversores, além de eficiência, temperatura, envelhecimento e limite de descarga.

Antes de fechar o conversor e a bateria:
- medir a corrente da P4-C6 em repouso, operação típica e carga máxima representativa;
- medir picos durante inicialização, Wi-Fi/Bluetooth, display, áudio, Ethernet e armazenamento;
- medir a eficiência do boost na faixa de tensão da célula;
- verificar a corrente exigida da bateria no menor estado de carga permitido;
- selecionar uma célula cuja corrente contínua e de pico exceda os valores medidos com margem documentada.

Uma meta de 5 V / 3 A equivale a até 15 W na saída. Em uma célula 1S, isso pode exigir vários ampères da bateria. Uma célula de 4.000 mAh com baixa capacidade de descarga pode ser inadequada. Não comprar apenas pelo número de mAh.

## 6. Requisitos mecânicos

- Compartimento para bateria pouch plana, com tampa traseira removível.
- Berço/trilho com polarização mecânica, retenção positiva e extração por lingueta.
- Contatos protegidos contra inversão, curto e contato acidental com objetos metálicos.
- Adaptadores DBI-1 específicos para cada modelo validado.
- Espaço para tolerância dimensional e eventual expansão da célula; não comprimir a pouch.
- Não perfurar, dobrar, prensar ou colar a célula de modo que danifique o invólucro.
- Troca somente com o aparelho desligado na revisão 1.0.
- Não congelar envelope universal antes de selecionar células reais de referência. A meta de 3–4 Ah pode não caber no volume mecânico inicialmente imaginado.

Hot-swap fica reservado a uma revisão futura, que exigirá power-path apropriado, energia de retenção (hold-up), detecção de remoção e testes de brownout. Não basta adicionar um capacitor isolado.

## 7. BOM preliminar por função

| Bloco | Componente / requisito | Estado |
|---|---|---|
| Conector de carga | USB-C receptáculo, CC1/CC2, ESD | A selecionar |
| Proteção de entrada | Fusível ou limitador, TVS/ESD conforme projeto | A dimensionar |
| Carregador | CI chaveado 1S com Power Path | A selecionar |
| Bateria | Li-ion/Li-Po 1S, 4,20 V máx., alvo 3.000–4.000 mAh | Modelos a validar |
| Proteção da célula | PCM/BMS 1S | Confirmar se integrado à célula |
| Fuel gauge | MAX17048 (candidato) | A validar |
| Boost | Conversor 1S para 5 V; meta preliminar até 3 A | A selecionar após medição |
| Isolamento/seleção | Ideal diode, power mux ou load switch apropriado | A dimensionar |
| Interface | Contatos e adaptadores DBI-1 | A projetar |
| Conector da placa | SH1.0 2 pinos | Confirmar peça, pinagem e corrente |

BQ24074 não está definido como componente final: é carregador linear e sua dissipação pode ser inadequada para a carga do sistema. Pode ser reavaliado apenas após análise térmica e de corrente. Não comprar carregador, boost ou BMS com base apenas em títulos de anúncio.

## 8. Termos de busca para aquisição

### Baterias (pesquisar por modelo e dimensões, não só capacidade)
- `3.7V 1S 4000mAh LiPo battery pouch protected`
- `3.7V 3500mAh lithium polymer battery 1S PCM`
- `3.7V 3000mAh Li-ion polymer battery flat pouch`
- `3.7V 4000mAh rechargeable battery 4.2V protection board`
- `1S 3.7V LiPo battery NTC 3 wire` (somente se o modelo realmente tiver NTC)
- `[modelo exato da bateria] datasheet pinout dimensions`

### Circuitos e componentes (para pesquisa técnica; não comprar sem validação)
- `1S switching Li-ion charger power path IC`
- `single cell buck boost charger power path 4.2V`
- `1S Li-ion battery fuel gauge MAX17048 module`
- `3.7V to 5V boost converter 3A continuous`
- `5V 3A synchronous boost converter 1S LiPo`
- `1S Li-ion battery protection PCM 10A` (a corrente deve ser escolhida pelo orçamento real, não pelo anúncio)
- `USB C 5V charging board power path 1S`
- `spring battery contacts 2 pin gold plated`
- `SH1.0 2 pin cable connector`

### Cuidados com anúncios
- Desconfiar de capacidades muito altas em dimensões pequenas ou sem marca/modelo rastreável.
- Solicitar foto da etiqueta real, dimensões com espessura, pinagem, datasheet, tensão máxima de carga, corrente máxima contínua/pico e especificação do PCM.
- Não inferir pinagem pela cor dos fios ou posição dos contatos.
- Não comprar células inchadas, recondicionadas, sem identificação ou com especificação contraditória.
- Não usar anúncio de bateria de controle/telefone como prova de que ela cabe ou suporta a corrente exigida.
- Confirmar política de transporte de baterias de lítio e condições de envio para o Brasil.

## 9. Plano de validação antes da fabricação

1. Fotografar a placa P4-C6 e registrar fabricante, modelo e revisão.
2. Baixar o esquema correspondente à revisão exata e confirmar o conector SH1.0, polaridade, entrada 5 V e possíveis caminhos de VBUS.
3. Selecionar pelo menos duas baterias candidatas de fabricantes/modelos distintos; obter datasheets e medir dimensões.
4. Validar pinagem, proteção, tensão de carga e corrente de descarga de cada modelo.
5. Medir consumo real da placa com o conjunto de periféricos previsto.
6. Dimensionar carregador, boost, power mux, trilhas, conectores e dissipação térmica.
7. Prototipar e testar carga simultânea com operação do sistema, transientes, temperatura, estabilidade dos 5 V e ausência de backfeed.
8. Testar proteção, polaridade, remoção/inserção com o aparelho desligado, autonomia e indicação de bateria.
9. Só então congelar BOM, esquema, PCB e envelope mecânico.

Ensaios de falha e curto-circuito devem ser feitos em bancada apropriada, com contenção e supervisão. Considerar IEC 62133-2 e UN 38.3 como referências de segurança/transporte; esta documentação não representa certificação do produto.

## 10. Itens explicitamente em aberto

- Confirmação de que a placa adquirida é a Waveshare ESP32-P4-Module-DEV-KIT ou uma variante/clonagem.
- Revisão exata e pinagem do conector de entrada 5 V.
- Corrente real da placa e dos periféricos.
- Modelos físicos de bateria que atendam ao envelope e à corrente.
- CI exato de carregamento chaveado com Power Path.
- CI exato do boost 5 V e do power mux.
- Estratégia de leitura de NTC/ID por modelo.
- Dimensões finais do compartimento e do adaptador DBI-1.

---

**Regra de engenharia:** nenhuma bateria ou circuito entra na BOM de fabricação como componente aprovado até que tensão, pinagem, dimensões, corrente, proteção e perfil de carga estejam documentados e testados.
