# Neander Runtime

Interpretador do computador didático **Neander**, desenvolvido em C. Lê um arquivo binário `.mem` gerado pelo simulador Neander, executa as instruções e imprime o estado final da CPU e o mapa de memória.

---

## Como compilar e rodar

### Pré-requisitos
- GCC instalado
- Arquivo `.mem` gerado pelo simulador Neander

### Compilar
```bash
gcc neander_runtime.c -o neander
```

### Rodar
```bash
./neander <arquivo.mem> <decimal|hex>
```

### Exemplos
```bash
./neander programa.mem decimal
./neander programa.mem hex
```

---

## Como gerar o arquivo `.mem` no Neander

1. Abra o simulador Neander
2. Insira os valores na memória conforme o programa desejado
3. Salve o arquivo como `programa.mem`
4. Coloque o arquivo na mesma pasta do código C

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

### Formato decimal
```
Arquivo carregado com sucesso!

=== Mapa de Memória ANTES da execução (0-255) ===
MEMORIA[  0] =  32
MEMORIA[  1] = 128
...
MEMORIA[128] =   5
MEMORIA[129] =   3
MEMORIA[130] =   0
...

=== Valor final dos registradores ===
AC = 8
PC = 7
Flag N = 0
Flag Z = 0
Acessos à memória = 10
Instruções lidas e executadas = 4

=== Mapa de Memória DEPOIS da execução (0-255) ===
MEMORIA[  0] =  32
MEMORIA[  1] = 128
...
MEMORIA[128] =   5
MEMORIA[129] =   3
MEMORIA[130] =   8
...
```

### Formato hexadecimal
```
Arquivo carregado com sucesso!

=== Mapa de Memória ANTES da execução (0-255) ===
MEMORIA[0x00] = 0x20
MEMORIA[0x01] = 0x80
...
MEMORIA[0x80] = 0x05
MEMORIA[0x81] = 0x03
MEMORIA[0x82] = 0x00
...

=== Valor final dos registradores ===
AC = 0x08
PC = 0x07
Flag N = 0x00
Flag Z = 0x00
Acessos à memória = 10
Instruções lidas e executadas = 4

=== Mapa de Memória DEPOIS da execução (0-255) ===
MEMORIA[0x00] = 0x20
MEMORIA[0x01] = 0x80
...
MEMORIA[0x80] = 0x05
MEMORIA[0x81] = 0x03
MEMORIA[0x82] = 0x08
...
```
