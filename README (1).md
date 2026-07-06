# push_swap

Projeto da escola 42 (42 Porto) que consiste em ordenar uma pilha de números inteiros usando **duas stacks** (`a` e `b`) e um conjunto restrito de operações, com o menor número de operações possível.

Esta implementação vai além do mínimo pedido: inclui **múltiplas estratégias de ordenação** (para pilhas pequenas, médias e grandes), um **modo de benchmark** com contagem de operações e cálculo de desordem da pilha, e um **modo adaptativo** que escolhe automaticamente a melhor estratégia consoante o tamanho/desordem do input.

## Índice

- [Sobre o projeto](#sobre-o-projeto)
- [Operações permitidas](#operações-permitidas)
- [Compilação](#compilação)
- [Utilização](#utilização)
- [Estratégias de ordenação](#estratégias-de-ordenação)
- [Modo bench](#modo-bench)
- [Estrutura do código](#estrutura-do-código)
- [Testar / Checker](#testar--checker)
- [Autores](#autores)

## Sobre o projeto

O programa recebe uma lista de inteiros como argumentos (todos diferentes, sem duplicados), coloca-os na stack `a` e imprime na saída padrão a sequência de instruções necessárias para ordenar a stack `a` por ordem crescente, usando apenas a stack `b` como espaço auxiliar.

Regras gerais:
- Não pode haver números duplicados.
- Só são aceites inteiros válidos (dentro do intervalo de `int`).
- Se a pilha já estiver ordenada, o programa não imprime nada.
- Em caso de erro (input inválido, duplicado, overflow, etc.) o programa imprime `Error` para `stderr` e termina com código de saída `1`.

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

## Compilação

```bash
make        # compila push_swap (e a libft_printf interna)
make clean  # remove os .o
make fclean # remove os .o e o binário
make re     # fclean + all
```

O `Makefile` compila com `-Wall -Wextra -Werror` e depende internamente de `ft_printf` (incluída no repositório em `ft_printf/`), compilada automaticamente como biblioteca estática antes de linkar o executável.

## Utilização

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

## Estratégias de ordenação

O programa escolhe automaticamente a estratégia mais adequada (modo `adaptive`, por omissão), com base no tamanho da stack e num índice de desordem calculado através de contagem de inversões (merge sort):

| Estratégia | Complexidade  | Quando é usada (modo adaptativo)           |
|------------|---------------|--------------------------------------------|
| Simple     | O(n²)         | Stacks pequenas / baixa desordem (≤ 20%)   |
| Medium     | O(n·√n)       | Desordem intermédia (21% – 49%)            |
| Complex    | O(n log n)    | Alta desordem (> 50%) ou stacks grandes    |

Para pilhas com menos de 6 elementos é sempre usado um algoritmo dedicado (`sort_five`), otimizado para casos de 3 e 5 elementos.

Qualquer uma destas estratégias pode ser forçada manualmente através das flags `--simple`, `--medium` ou `--complex`, o que é útil para comparar desempenho no modo bench.

## Modo bench

Ao ativar `--bench`, o programa executa a ordenação normalmente (imprimindo as operações em `stdout`, como habitual) e adicionalmente escreve para `stderr` um resumo com:

- **Disorder**: percentagem de desordem da pilha de entrada (baseada em contagem de inversões via merge sort);
- **Strategy**: estratégia usada (e, no modo adaptativo, também a estratégia efetivamente escolhida);
- **Operations**: número total de operações executadas;
- Contagem individual de cada operação (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`).

Exemplo de saída (`stderr`) para 100 números aleatórios:

```
[bench] Disorder:  52.14%
[bench] Strategy:  Adaptive  / Complex [O(n log n)]
[bench] Operations:   567
[bench]    sa: 0   sb: 0   ss: 0
[bench]    pa: 97   pb: 97
[bench]    ra: 61   rb: 40   rr: 53
[bench]   rra: 147  rrb: 19  rrr: 53
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

## Autores

- [aantela-](https://github.com/ArturVazOsorio) — 42 Porto
- [pgois-wa](https://github.com/PedroRamo-s) — 42 Porto
