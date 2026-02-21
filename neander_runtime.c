#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//Registradores
int8_t AC = 0; //acumulador
uint8_t PC = 0; //program counter
int Z = 0;      //flag zero
int N = 0;      //flag negativo

//Memória: 256 posições de 8bits
uint8_t MEMORIA[256];

void atualizar_flags(){
    if(AC == 0){
        Z = 1;
    } else {
        Z = 0;
    }

    if(AC < 0){
        N = 1;
    } else {
        N = 0;
    }
}

void carregar_arquivo(char *caminho){
    FILE *arquivo = fopen(caminho, "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Lê os 2 bytes do header
    uint8_t header[4];
    fread(header, 1, 4, arquivo);

    // Valida o header
    if(header[0] != 0x03 || header[1] != 0x4E){
        printf("Arquivo inválido!\n");
        fclose(arquivo);
        return;
    }

    // Lê as 256 posições de memória
    for(int i = 0; i < 256; i++){
        uint8_t par[2];
        fread(par, 1, 2, arquivo);
        MEMORIA[i] = par[0];
    }

    printf("Arquivo carregado com sucesso!\n");
    fclose(arquivo);
}

int main(){
    
    carregar_arquivo("programa.mem");

    PC = 0;

    int executando = 1;

    while(executando){
        uint8_t instrucao = MEMORIA[PC];
        PC++;

        if(instrucao == 0x20){  //LDA
            uint8_t endereco = MEMORIA[PC];
            PC++;
            AC = MEMORIA[endereco];
            atualizar_flags();
        } 

        else if(instrucao == 0x30){ //ADD
            uint8_t endereco = MEMORIA[PC];
            PC++;
            AC = AC + MEMORIA[endereco];
            atualizar_flags();
        }

        else if(instrucao == 0x10){ //STA, pega o valor o do acumulador e guarda em um endereço de memória
            uint8_t endereco = MEMORIA[PC];
            PC++;
            MEMORIA[endereco] = AC;
        }

        else if(instrucao == 0x80){ //JMP, pula para o HLT
            uint8_t endereco = MEMORIA[PC];
            PC++;
            PC = endereco;
        }

        else if(instrucao == 0xA0){ //JZ, pula para o HLT se AC = 0
            uint8_t endereco = MEMORIA[PC];
            PC++;
            if(Z == 1){
                PC = endereco;
            }
        }

        else if(instrucao == 0x90){ //JN, pula para HLT se AC < 0
            uint8_t endereco = MEMORIA[PC];
            PC++;
            if(N == 1){
                PC = endereco;
            }
        }

        else if(instrucao == 0x50){ //AND
            uint8_t endereco = MEMORIA[PC];
            PC++;
            AC = AC & MEMORIA[endereco];
            atualizar_flags();
        }

        else if(instrucao == 0x40){ //OR
            uint8_t endereco = MEMORIA[PC];
            PC++;
            AC = AC | MEMORIA[endereco];
            atualizar_flags();
        }

        else if(instrucao == 0x60){ //NOT não usa operando (não lê endereço da memória)
            AC = ~AC;
            atualizar_flags();
        }

        else if(instrucao == 0x00){ //NOP
            //não faz nada
        }

        else if (instrucao == 0xF0){ //HLT
            executando = 0;
        } 

        else {
            printf("Instrução inválida: 0x%02X no endereço %d\n", instrucao, PC - 1);
            executando = 0;
        }

    }

    printf("\n=== Valor final dos registradores ===\n");
    printf("AC = %d\n", AC);
    printf("PC = %d\n", PC);
    printf("Z = %d\n", Z);
    printf("N = %d\n", N);

    printf("\n=== Mapa de Memória (0-255) ===\n");
    for(int i = 0; i < 256; i++){
        printf("MEMORIA[%3d] = %3d (0x%02X)\n", i, MEMORIA[i], MEMORIA[i]);

    }

    return 0;
}