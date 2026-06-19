# Referências de Estudo — push_swap

> Organizado por tema, do mais fundamental ao mais específico.
> Foco em fontes que complementam o que estamos a implementar.

---

## C — Linguagem Base

### Livros
- **The C Programming Language** — Kernighan & Ritchie (K&R)  
  A referência definitiva. Capítulos essenciais: 5 (ponteiros), 6 (structs), 7 (I/O).
- **C Programming: A Modern Approach** — K.N. King  
  Mais acessível que K&R. Bom para solidificar bases.

### Referências Online
- https://en.cppreference.com/w/c — referência completa da linguagem e biblioteca standard
- https://www.iso-9899.info/wiki/The_Standard — o standard C11 anotado

### Páginas Man (correr no terminal)
```bash
man 3 malloc      # alocação de memória
man 3 free        # libertação de memória
man 2 write       # write para file descriptors
man 3 exit        # terminar processo
man 3 dprintf     # printf para fd (usado no debug.c)
```

---

## Listas Ligadas

### O que estamos a usar
Lista **duplamente ligada** com ponteiros `top`, `bottom` e campo `size` na struct da stack.

### Para estudar
- **K&R Capítulo 6.5** — estruturas auto-referenciadas  
- https://www.learn-c.org/en/Linked_lists — introdução prática  
- https://visualgo.net/en/list — visualização interativa de listas ligadas  

### Conceitos chave a dominar
```
Inserção no topo       →  O(1)
Inserção no fundo      →  O(1)  (temos ponteiro bottom)
Remoção do topo        →  O(1)
Traversal completo     →  O(n)
Acesso por índice      →  O(n)  (não temos, usamos traversal)
```

### Operações que implementámos
```c
node_builder(value)              // aloca e inicializa um nó
add_bottom(stack, value)         // insere no fundo — O(1)
push(src, dst)                   // move topo de src para topo de dst — O(1)
rotate(s)                        // topo vai para o fundo — O(1)
reverse_rotate(s)                // fundo vai para o topo — O(1)
```

---

## Enums em C

### O que estamos a usar
```c
typedef enum e_strategy
{
    STRAT_ADAPTIVE,   // vale 0
    STRAT_SIMPLE,     // vale 1
    STRAT_MEDIUM,     // vale 2
    STRAT_COMPLEX     // vale 3
}   t_strategy;
```

### Para estudar
- https://en.cppreference.com/w/c/language/enum  
- K&R Capítulo 2.3 — constantes  

### Porquê usar enum em vez de #define
```c
// Com #define — sem tipo, sem debug, sem scope
#define STRAT_SIMPLE 1

// Com enum — tem tipo, aparece no debugger, agrupa constantes relacionadas
typedef enum e_strategy { STRAT_SIMPLE } t_strategy;
```

---

## Gestão de Memória

### O que estamos a usar
```c
malloc(sizeof(t_node))   // alocar um nó
free(current)            // libertar um nó
```

### Para estudar
- K&R Capítulo 8.7 — storage allocator  
- https://www.cs.cornell.edu/courses/cs3110/2019sp/textbook/ads/memory.html  
- **Valgrind** — ferramenta essencial para detetar leaks:
```bash
valgrind --leak-check=full ./push_swap --simple 5 3 8 1 6
```

### Erros comuns
```
Use after free      →  aceder a memória depois de free()
Double free         →  chamar free() duas vezes no mesmo ponteiro
Memory leak         →  malloc() sem free() correspondente
Null dereference    →  desreferenciar ponteiro NULL (→ segfault)
```

### O nosso padrão de libertação
```c
void    free_stack(t_stack *stack)
{
    t_node *current;
    t_node *next_node;

    current = stack->top;
    while (current != NULL)
    {
        next_node = current->next;   // guardar next ANTES de free
        free(current);
        current = next_node;
    }
}
```

---

## Algoritmos de Ordenação

### O que estamos a implementar

#### sort_simple — Selection Sort adaptado — O(n²)
Encontra o mínimo, move-o para o topo, empurra para B. Repete até restar 3.
```
Melhor caso:   O(n)   — input quase ordenado (early exit)
Caso médio:    O(n²)
Pior caso:     O(n²)
```

#### sort_three — caso especial
Ordenar 3 elementos com no máximo 2 operações. Todos os casos possíveis:
```
1 2 3  →  já ordenado
1 3 2  →  sa
2 1 3  →  sa
2 3 1  →  rra → sa  ou  ra
3 1 2  →  ra  → sa  ou  rra
3 2 1  →  ra  → sa  ou  sa → rra
```

### Para estudar
- https://visualgo.net/en/sorting — visualização de todos os algoritmos  
- https://www.bigocheatsheet.com — complexidades de referência rápida  
- **Selection Sort:** https://en.wikipedia.org/wiki/Selection_sort  
- **Insertion Sort:** https://en.wikipedia.org/wiki/Insertion_sort (útil para sort_medium)  

### Complexidades a conhecer
```
O(1)        →  constante     — acesso direto
O(log n)    →  logarítmico   — binary search
O(n)        →  linear        — traversal
O(n log n)  →  linearítmico  — merge sort, heap sort
O(n²)       →  quadrático    — selection sort, insertion sort
```

---

## Contagem de Inversões (Disorder)

### O que implementámos
```c
// Para cada par (i,j) onde i<j:
//   se a[i] > a[j]  →  é uma inversão
// disorder = inversões / total_pares * 100
```

### Para estudar
- https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)  
- O algoritmo eficiente (O(n log n)) usa merge sort — útil para benchmarks com inputs grandes:  
  https://www.geeksforgeeks.org/counting-inversions/  

### Relação com disorder
```
0 inversões    →  0.00%    →  já ordenado
n*(n-1)/2      →  100.00%  →  ordem inversa
```

---

## File Descriptors e I/O

### O que estamos a usar
```
fd 0  →  stdin   — entrada standard
fd 1  →  stdout  — saída standard  (moves: "ra\n", "pb\n", etc.)
fd 2  →  stderr  — erros standard  (debug e benchmark)
```

### Porquê separar stdout e stderr
O checker da 42 lê apenas o stdout para contar e validar moves.  
O debug/benchmark em stderr não interfere:
```bash
./push_swap --simple 5 3 8 1 6 | wc -l          # conta moves (stdout)
./push_swap --simple 5 3 8 1 6 2>/dev/null       # suprime debug (stderr)
./push_swap --bench --simple 5 3 8 1 6 2>&1      # vê tudo junto
```

### Para estudar
- `man 2 write`  
- `man 3 dprintf`  
- https://en.wikipedia.org/wiki/Standard_streams  

---

## Variadic Functions (`va_list`)

### Relevância
Usado no teu `ft_printf` que implementaste anteriormente.

### Para estudar
- `man 3 stdarg`  
- K&R Capítulo 7.3 — variable-length argument lists  
- https://en.cppreference.com/w/c/variadic  

---

## Norminette — Regras Relevantes

### Regras que afectaram decisões de design
```
Sem variáveis globais          →  razão para passar t_bench * por parâmetro
Máximo 25 linhas por função    →  razão para sort_three ser função separada
Máximo 4 parâmetros            →  atenção ao adicionar parâmetros
Sem declarações dentro de if   →  int value; fora do bloco
```

### Referência
- https://github.com/42School/norminette  
- Correr localmente: `norminette *.c *.h`  

---

## Ferramentas de Debug e Teste

### Valgrind
```bash
valgrind --leak-check=full --track-origins=yes ./push_swap --simple 5 3 8 1 6
```

### Testers conhecidos da comunidade
- https://github.com/gemartin99/Push-Swap-Tester  
- https://github.com/LeoFu9487/push_swap_tester  
- https://github.com/SimonCROS/push_swap_tester  

### Gerador de inputs aleatórios
```bash
# gerar 100 números aleatórios sem repetição
shuf -i 1-1000 -n 100 | tr '\n' ' '

# testar e contar moves
ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ')
./push_swap $ARG | wc -l
```

### Validar se o output está correto
```bash
ARG="5 3 8 1 6"
./push_swap $ARG | ./checker $ARG
# output esperado: OK
```

---

## Push Swap — Referências Específicas

- **Subject oficial 42:** no teu intra  
- https://medium.com/@jamierobertdawson/push-swap-the-least-number-of-moves-with-two-stacks-d1e76a71789a — explicação geral do problema  
- https://en.wikipedia.org/wiki/Sorting_algorithm — visão geral de algoritmos  

### Estratégias comuns na comunidade
```
≤ 3 elementos   →  sort_three direto
≤ 5 elementos   →  sort_simple
≤ 100 elementos →  insertion sort com B como buffer
≤ 500 elementos →  radix sort ou turkish algorithm
```

---

## Leitura Recomendada por Ordem

1. K&R Capítulo 5 — ponteiros e arrays
2. K&R Capítulo 6 — structs
3. https://visualgo.net/en/list — listas ligadas visual
4. https://visualgo.net/en/sorting — algoritmos de sort visual
5. https://www.bigocheatsheet.com — complexidades
6. `man 3 malloc` + `man 2 write`
7. Valgrind no teu código
