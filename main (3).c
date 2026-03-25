/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEM_SIZE 256

// Estrutura para facilitar a explicação: cada campo da instrução é isolado
struct instrucao {
    char inst_bin[17]; 
    char nome[10];
    int opcode, rs, rt, rd, funct, imm, addr;
};

// 1. CONVERSÃO: O arquivo tem HEX (Base 16), mas o MIPS trabalha com BIN (Base 2)
void hex_para_bin(char *hex, char *bin) {
    long val = strtol(hex, NULL, 16);
    for (int i = 15; i >= 0; i--) {
        bin[i] = (val & 1) ? '1' : '0';
        val >>= 1;
    }
    bin[16] = '\0';
}

// 2. MAPEAMENTO: Traduz os códigos da tabela da imagem para nomes legíveis
void definir_nome(struct instrucao *inst) {
    if (inst->opcode == 0) { // Tipo R: O nome depende do campo FUNCT (últimos 3 bits)
        switch(inst->funct) {
            case 0: strcpy(inst->nome, "ADD"); break;
            case 2: strcpy(inst->nome, "SUB"); break;
            case 4: strcpy(inst->nome, "AND"); break;
            case 5: strcpy(inst->nome, "OR");  break;
            default: strcpy(inst->nome, "R_ERR");
        }
    } else { // Outros Tipos: O nome depende apenas do OPCODE
        switch(inst->opcode) {
            case 4:  strcpy(inst->nome, "ADDi"); break;
            case 11: strcpy(inst->nome, "LW");   break;
            case 15: strcpy(inst->nome, "SW");   break;
            case 8:  strcpy(inst->nome, "BEQ");  break;
            case 2:  strcpy(inst->nome, "J");    break;
            default: strcpy(inst->nome, "UNKN");
        }
    }
}

// 3. DECODIFICAÇÃO: "Fatiar" a string de bits conforme o formato da instrução
void decodificador(struct instrucao *inst) {
    char temp[13]; // Buffer para extrair partes da string
    
    // Opcode: Sempre os 4 bits iniciais [0-3]
    strncpy(temp, inst->inst_bin, 4); temp[4] = '\0';
    inst->opcode = (int)strtol(temp, NULL, 2);

    if (inst->opcode == 0) { // FORMATO TIPO R: [Op 4][rs 3][rt 3][rd 3][funct 3]
        strncpy(temp, inst->inst_bin + 4, 3); temp[3] = '\0'; inst->rs = (int)strtol(temp, NULL, 2);
        strncpy(temp, inst->inst_bin + 7, 3); temp[3] = '\0'; inst->rt = (int)strtol(temp, NULL, 2);
        strncpy(temp, inst->inst_bin + 10, 3); temp[3] = '\0'; inst->rd = (int)strtol(temp, NULL, 2);
        strncpy(temp, inst->inst_bin + 13, 3); temp[3] = '\0'; inst->funct = (int)strtol(temp, NULL, 2);
        
        definir_nome(inst);
        printf("HEX -> BIN: %s | %-5s $%d, $%d, $%d (Tipo R)\n", inst->inst_bin, inst->nome, inst->rd, inst->rs, inst->rt);
    } 
    else if (inst->opcode == 2) { // FORMATO TIPO J: [Op 4][address 12]
        strncpy(temp, inst->inst_bin + 4, 12); temp[12] = '\0';
        inst->addr = (int)strtol(temp, NULL, 2);
        
        definir_nome(inst);
        printf("HEX -> BIN: %s | %-5s %d (Tipo J)\n", inst->inst_bin, inst->nome, inst->addr);
    } 
    else { // FORMATO TIPO I: [Op 4][rs 3][rt 3][imm 6]
        strncpy(temp, inst->inst_bin + 4, 3); temp[3] = '\0'; inst->rs = (int)strtol(temp, NULL, 2);
        strncpy(temp, inst->inst_bin + 7, 3); temp[3] = '\0'; inst->rt = (int)strtol(temp, NULL, 2);
        strncpy(temp, inst->inst_bin + 10, 6); temp[6] = '\0'; inst->imm = (int)strtol(temp, NULL, 2);
        
        definir_nome(inst);
        printf("HEX -> BIN: %s | %-5s $%d, $%d, %d (Tipo I)\n", inst->inst_bin, inst->nome, inst->rt, inst->rs, inst->imm);
    }
}

int main() {
    struct instrucao memoria[MEM_SIZE];
    char hex_lido[10];
    FILE *file = fopen("entrada.txt", "r");

    if (!file) {
        printf("Erro: Crie um arquivo 'entrada.txt' com os valores hexadecimais.\n");
        return 1;
    }

    printf("PROCESSO DE DECODIFICACAO MIPS 16-BITS\n");
    printf("------------------------------------------------------------\n");

    int i = 0;
    while (fscanf(file, "%s", hex_lido) != EOF && i < MEM_SIZE) {
        hex_para_bin(hex_lido, memoria[i].inst_bin);
        decodificador(&memoria[i]);
        i++;
    }

    fclose(file);
    return 0;
}