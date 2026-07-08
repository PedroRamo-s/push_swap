*This project has been created as part of the 42 curriculum by aantela-, pgois-wa.*

# push_swap

Projeto da escola 42 (42 Porto) que consiste em ordenar uma pilha de números inteiros usando **duas stacks** (`a` e `b`) e um conjunto restrito de operações, com o menor número de operações possível.

Esta implementação vai além do mínimo pedido: inclui **múltiplas estratégias de ordenação** (para pilhas pequenas, médias e grandes), um **modo de benchmark** com contagem de operações e cálculo de desordem da pilha, e um **modo adaptativo** que escolhe automaticamente a melhor estratégia consoante o tamanho/desordem do input.

## Índice

- [Description](#description)
- [Instructions](#instructions)
- [Operações permitidas](#operações-permitidas)
- [Estratégias de ordenação e justificação](#estratégias-de-ordenação-e-justificação)
- [Modo bench](#modo-bench)
- [Estrutura do código](#estrutura-do-código)
- [Testar / Checker](#testar--checker)
- [Contribuições](#contribuições)
- [Resources](#resources)

## Description

O programa recebe uma lista de inteiros como argumentos (todos diferentes, sem duplicados), coloca-os na stack `a` e imprime na saída padrão a sequência de instruções necessárias para ordenar a stack `a` por ordem crescente, usando apenas a stack `b` como espaço auxiliar.

O objetivo do projeto é explorar complexidade algorítmica de forma prática: implementar quatro estratégias distintas (`Simple` O(n²), `Medium` O(n√n), `Complex` O(n log n) e `Adaptive`), medir a **desordem** de cada input (via contagem de inversões) e escolher automaticamente a estratégia mais eficiente consoante esse valor.

Regras gerais:
- Não pode haver números duplicados.
- Só são aceites inteiros válidos (dentro do intervalo de `int`).
- Se a pilha já estiver ordenada, o programa não imprime nada.
- Em caso de erro (input inválido, duplicado, overflow, etc.) o programa imprime `Error` para `stderr` e termina com código de saída `1`.

## Instructions

### Compilação

```bash
make        # compila push_swap (e a libft_printf interna)
make clean  # remove os .o
make fclean # remove os .o e o binário
make re     # fclean + all
```

O `Makefile` compila com `-Wall -Wextra -Werror` e depende internamente de `ft_printf` (incluída no repositório em `ft_printf/`), compilada automaticamente como biblioteca estática antes de linkar o executável.

### Utilização

```bash
./push_swap [flags] arg1 arg2 arg3 ...
```

Os argumentos podem ser passados como vários argumentos separados por espaço ou como uma única string com números separados por espaços (ambos os formatos são suportados, graças ao parsing com `ft_split`):

```bash
./push_swap 2 1 3 6 5 8
./push_swap "2 1 3 6 5 8"
```

### Flags opcionais

| Flag         | Efeito                                                                 |
|--------------|-------------------------------------------------------------------------|
| `--bench`    | Ativa o modo de benchmark: imprime estatísticas para `stderr` no final  |
| `--simple`   | Força a estratégia "Simple" (ótima para stacks pequenas)                |
| `--medium`   | Força a estratégia "Medium"                                             |
| `--complex`  | Força a estratégia "Complex"                                            |
| `--adaptive` | Força o modo adaptativo (comportamento por omissão)                    |

As flags podem ser colocadas antes ou depois dos números, e apenas uma estratégia pode ser escolhida por execução.

Exemplo:

```bash
./push_swap --bench --complex 5 4 3 2 1
./push_swap 5 4 3 2 1 --bench --complex
```

## Operações permitidas

| Operação | Descrição                                              |
|----------|---------------------------------------------------------|
| `sa`     | Troca os 2 primeiros elementos do topo de `a`            |
| `sb`     | Troca os 2 primeiros elementos do topo de `b`            |
| `ss`     | `sa` e `sb` simultaneamente                              |
| `pa`     | Retira o topo de `b` e coloca no topo de `a`             |
| `pb`     | Retira o topo de `a` e coloca no topo de `b`             |
| `ra`     | Rotaciona `a` para cima (o primeiro elemento vai para o fim) |
| `rb`     | Rotaciona `b` para cima                                  |
| `rr`     | `ra` e `rb` simultaneamente                               |
| `rra`    | Rotaciona `a` para baixo (o último elemento vai para o topo) |
| `rrb`    | Rotaciona `b` para baixo                                  |
| `rrr`    | `rra` e `rrb` simultaneamente                             |

## Estratégias de ordenação e justificação

O programa escolhe automaticamente a estratégia mais adequada (modo `adaptive`, por omissão), com base no tamanho da stack e num índice de **desordem** calculado através de contagem de inversões (merge sort), medido **antes** de qualquer operação, conforme exigido pelo subject.

| Estratégia | Complexidade  | Quando é usada (modo adaptativo)           |
|------------|---------------|--------------------------------------------|
| Simple     | O(n²)         | Stacks pequenas / baixa desordem (< 20%)   |
| Medium     | O(n·√n)       | Desordem intermédia (20% – 49%)            |
| Complex    | O(n log n)    | Alta desordem (≥ 50%) ou stacks grandes    |

Para pilhas com menos de 6 elementos é sempre usado um algoritmo dedicado (`sort_five`), otimizado para casos de 3 e 5 elementos.

Qualquer uma destas estratégias pode ser forçada manualmente através das flags `--simple`, `--medium` ou `--complex`, o que é útil para comparar desempenho no modo bench.

### Justificação técnica dos thresholds

Os limiares de 20% e 50% de desordem foram escolhidos porque refletem o ponto em que o custo de "posicionar" cada elemento na stack auxiliar `b` deixa de compensar face ao custo de estratégias com maior overhead de estrutura (partição/merge), mas menor custo assintótico por elemento. Com baixa desordem, a maioria dos elementos já está perto da posição final, pelo que uma inserção simples baseada em custo (O(n²) no pior caso) tem overhead reduzido na prática. Com desordem intermédia, dividir a stack em ⌈√n⌉ blocos por intervalo de valor reduz o número médio de rotações necessárias por elemento. Com desordem elevada, o custo de manter a stack "quase ordenada" durante a inserção deixa de compensar, e uma abordagem tipo *partição* recursiva (aproximação a quicksort/mergesort sobre stacks) domina em número de operações.

#### Simple — O(n²)

**Autoria: parse de `simple_sort.c` desenvolvido em colaboração — pgois-wa (base) + aantela- (revisão/integração).**

Empurra todos os elementos de `a` para `b` calculando, para cada um, o custo de rotação necessário para o inserir na posição correta relativa aos já presentes em `b` (`calculate_insertion_plan` + `plan_executor`), e depois traz tudo de volta para `a` já ordenado. Cada inserção custa O(n) no pior caso (procurar posição + rotacionar), para n elementos → O(n²) operações no pior caso. Espaço: O(n) para as duas stacks.

#### Medium — O(n·√n)

**Autoria: parse de `medium_sort.c` desenvolvido em colaboração — pgois-wa (base) + aantela- (revisão/integração).**

Divide os valores da stack em ⌈√n⌉ "chunks" por intervalo de valor (`push_chunks_b`) e empurra-os para `b` mantendo cada chunk parcialmente ordenado (`push_and_sort_b`, que faz `sb` sempre que a ordem local se inverte). Na fase de drenagem, seleciona repetidamente o valor máximo em `b` (`max_selector_b`), roda-o até ao topo pelo caminho mais curto (`rotate_to_top_b`) e empurra para `a`. Cada seleção/rotação custa O(√n) em média (por causa da estrutura em chunks), repetida n vezes → O(n·√n). Espaço: O(n).

#### Complex — O(n log n)

**Autoria: desenvolvido por aantela- (implementação principal de `complex_sort.c`, `push_swap_utils.c`, lógica de custos e rotação).**

Empurra todos os elementos exceto os 3 últimos para `b` (`push_all_to_b`), ordena os 3 restantes em `a` com um caso dedicado (`sort_three`), e depois traz cada elemento de `b` de volta para `a` pela posição de menor custo combinado (`move_cheapest`, que calcula custo de rotação em `a` e em `b` simultaneamente e escolhe o menor). Por fim, alinha o mínimo de `a` ao topo (`rotate_min_to_top`). O uso de custo combinado (menor entre rotação em `a` e em `b`, incluindo `rr`/`rrr`) é o que aproxima o número de operações a O(n log n) — análogo à ideia de particionamento eficiente usada em quicksort/mergesort adaptados a duas stacks. Espaço: O(n).

#### Adaptive (custom, learner's design)

**Autoria: lógica de seleção (cálculo de desordem + escolha de estratégia) desenvolvida por aantela-, integrando as três estratégias acima.**

Mede a desordem da stack de entrada por contagem de inversões via merge sort (O(n log n), medido antes de qualquer operação) e seleciona a estratégia cujo regime de complexidade é adequado ao nível de desordem observado, conforme a tabela acima. Isto garante que o número de operações geradas respeita os targets pedidos pelo subject (< 0.2 → O(n²); 0.2–0.5 → O(n√n); ≥ 0.5 → O(n log n)).

## Modo bench

Ao ativar `--bench`, o programa executa a ordenação normalmente (imprimindo as operações em `stdout`, como habitual) e adicionalmente escreve para `stderr` um resumo com:

- **disorder**: percentagem de desordem da pilha de entrada (baseada em contagem de inversões via merge sort);
- **strategy**: estratégia usada (e, no modo adaptativo, também a estratégia efetivamente escolhida) e a sua classe de complexidade;
- **total_ops**: número total de operações executadas;
- Contagem individual de cada operação (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`).

Exemplo de saída (`stderr`) para 500 números aleatórios:

```
[bench] disorder:  49.93%
[bench] strategy:  Adaptive / O(n√n)
[bench] total_ops: 7997
[bench] sa: 0 sb: 0 ss: 0 pa: 500 pb: 500
[bench] ra: 4840 rb: 1098 rr: 0 rra: 0 rrb: 1059 rrr: 0
```

## Estrutura do código

```
.
├── main_novo.c                # ponto de entrada, parsing de argumentos e fluxo geral
├── parse_args.c               # validação de inteiros, duplicados, is_sorted
├── parse_args_utils.c         # parsing das flags (--bench, --simple, --medium, ...)
├── push_swap_utils.c          # criação/manipulação da stack (t_list / t_node)
├── push_swap_utils_medium.c   # utilitários para a estratégia medium
├── push.c / swap.c / rotate.c / reverse_rotate.c
│                               # implementação das 11 operações (pa, pb, sa, sb, ss, ra, rb, rr, rra, rrb, rrr)
├── simple_sort*.c              # estratégia Simple + sort_three
├── sort_five*.c                 # algoritmo dedicado para pilhas < 6 elementos
├── medium_sort*.c              # estratégia Medium (O(n·√n))
├── complex_sort*.c              # estratégia Complex (O(n log n))
├── bench*.c                     # cálculo de desordem (merge sort) e impressão do relatório de bench
├── erro_handler.c              # tratamento de erros e libertação de memória
├── utils*.c                     # ft_strcmp, ft_split, rotate_to_top, ft_sqrt, etc.
├── push_swap.h                  # structs (t_node, t_list, t_program, t_bench...) e protótipos
├── ft_printf/                    # implementação própria de printf, usada internamente
└── checker_linux                # binário checker fornecido pela 42 para validar a ordenação
```

Principais estruturas de dados (`push_swap.h`):

- `t_node` / `t_list`: lista duplamente ligada que representa cada stack;
- `t_program`: agrega as duas stacks (`a`, `b`), estratégia escolhida, estado de bench e desordem calculada;
- `t_bench`: contador de cada operação, passado explicitamente pela cadeia de chamadas (sem variáveis globais);
- `t_move_plan` / `t_range`: estruturas auxiliares para planeamento de custos de inserção nos algoritmos Simple/Medium.

O código segue a **norminette** da 42 (funções com no máximo 25 linhas, no máximo 4 parâmetros, sem `for`, entre outras regras), pelo que a lógica é frequentemente dividida em pequenas funções auxiliares e utiliza `while` em vez de `for`.

## Testar / Checker

O repositório inclui um `checker_linux` (fornecido pela 42) que recebe a mesma lista de números e as instruções geradas por `push_swap` via `stdin`, e confirma se a stack fica corretamente ordenada:

```bash
ARGS="2 1 3 6 5 8"
./push_swap $ARGS | ./checker_linux $ARGS
# OK  -> stack ficou ordenada com as operações usadas
# KO  -> erro de ordenação ou operação inválida
```

Também é possível gerar inputs aleatórios grandes para testar performance e correção:

```bash
ARGS=$(python3 -c "import random; a=list(range(500)); random.shuffle(a); print(' '.join(map(str,a)))")
./push_swap $ARGS | ./checker_linux $ARGS
./push_swap --bench $ARGS > /dev/null   # ver estatísticas em stderr
```

## Contribuições

Este projeto foi desenvolvido em par, conforme exigido pelo subject (grupo de exatamente 2 learners). Ambos compreendem a totalidade do código e são capazes de o explicar/defender integralmente.

- **[aantela-](https://github.com/ArturVazOsorio)** (42 Porto):
  - Parsing de argumentos e flags (`parse_args.c`, `parse_args_utils.c`), tratamento de erros (`erro_handler.c`).
  - Implementação principal da estratégia **Complex** (O(n log n)): `complex_sort.c`, cálculo de custo combinado (`move_cheapest`), `sort_three`, alinhamento final (`rotate_min_to_top`).
  - Lógica de seleção adaptativa (cálculo de desordem via merge sort e escolha de estratégia por threshold).
  - Sistema de benchmark (`t_bench`, contagem de operações, `print_bench`).
  - Compliance com norminette (extração de structs como `t_range`, eliminação de ternários, divisão de ficheiros).

- **[pgois-wa](https://github.com/PedroRamo-s)** (42 Porto):
  - Base das estratégias **Simple** (O(n²)) e **Medium** (O(n·√n)): `simple_sort.c`, `medium_sort.c`, planeamento de custo de inserção (`t_move_plan`), lógica de chunking por valor.
  - Revisão conjunta e ajustes finais de ambos os ficheiros feitos com aantela-.

## Resources

### Referências

- [42's push_swap subject (documentação oficial do projeto)](https://github.com/42School)
- Cormen, Leiserson, Rivest, Stein — *Introduction to Algorithms* (secções sobre merge sort, inversões e análise de complexidade amortizada)
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/) — para validação das classes de complexidade reivindicadas
- Documentação da norminette 42 (regras de formatação e limites de funções)

### Uso de Inteligência Artificial

A IA (Claude, Anthropic) foi utilizada como apoio pontual nas seguintes tarefas, sempre revistas e compreendidas por ambos os autores antes de integração:

- **Debugging**: identificação de bugs relacionados com pressupostos incorretos entre lógica de rotação circular vs. linear no cálculo de custos de push.
- **Norminette compliance**: sugestões para divisão de ficheiros, extração de helpers, e refatorização para eliminar ternários e reduzir número de parâmetros por função (ex: introdução do struct `t_range`).
- **Geração de README**: estruturação e redação deste ficheiro a partir do repositório e do subject, incluindo a formatação exigida no capítulo VII.
- **Revisão de nomenclatura**: sugestões de nomes de funções em inglês mais descritivos, para maior legibilidade durante a defesa.

Nenhum código de lógica de ordenação central (algoritmos Simple, Medium, Complex) foi gerado diretamente por IA sem implementação e compreensão próprias dos autores — a IA serviu como ferramenta de revisão, não de autoria.
