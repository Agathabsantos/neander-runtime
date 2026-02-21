# Neander Runtime

Interpretador do computador didático **Neander**, desenvolvido em C. Lê um arquivo binário `.mem` gerado pelo simulador Neander, executa as instruções e imprime o estado final da CPU e o mapa de memória.

---

## Como compilar e rodar

### Pré-requisitos
- GCC instalado
- Arquivo `programa.mem` gerado pelo simulador Neander

### Compilar
```bash
gcc neander_runtime.c -o neander
```

### Rodar
```bash
./neander
```

---

## Como gerar o arquivo `.mem` no Neander

1. Abra o simulador Neander
2. Insira os valores na memória conforme o programa desejado
3. Salve o arquivo como `programa.mem`
4. Coloque o arquivo `programa.mem` na mesma pasta do código C

### Exemplo de programa (soma de dois números)

| Endereço | Valor | Instrução |
|---|---|---|
| 0 | 32 | LDA 128 |
| 1 | 128 | (operando) |
| 2 | 48 | ADD 129 |
| 3 | 129 | (operando) |
| 4 | 16 | STA 130 |
| 5 | 130 | (operando) |
| 6 | 240 | HLT |
| 128 | 5 | (dado: primeiro número) |
| 129 | 3 | (dado: segundo número) |

---

## Instruções suportadas

| Instrução | Opcode | Descrição |
|---|---|---|
| NOP | 0x00 | Não faz nada |
| STA | 0x10 | Guarda o valor do AC em um endereço de memória |
| LDA | 0x20 | Carrega um valor da memória no AC |
| ADD | 0x30 | Soma um valor da memória ao AC |
| OR  | 0x40 | Operação OR entre AC e um valor da memória |
| AND | 0x50 | Operação AND entre AC e um valor da memória |
| NOT | 0x60 | Inverte os bits do AC |
| JMP | 0x80 | Salta para um endereço incondicionalmente |
| JN  | 0x90 | Salta para um endereço se AC for negativo |
| JZ  | 0xA0 | Salta para um endereço se AC for zero |
| HLT | 0xF0 | Para a execução |

---

## Saída do programa

Ao rodar, o programa imprime o estado final da CPU e o mapa completo de memória:

```
Arquivo carregado com sucesso!
AC = 8
PC = 7
Z  = 0
N  = 0

=== Mapa de Memória (0-255) ===
MEMORIA[  0] =  32 (0x20)
MEMORIA[  1] = 128 (0x80)
...
MEMORIA[128] =   5 (0x05)
MEMORIA[129] =   3 (0x03)
MEMORIA[130] =   8 (0x08)
...
```
