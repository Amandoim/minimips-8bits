#include <stdio.h>

#define NUM_REGS 8 // numeros de registradores (R0 a R7)

int regs[NUM_REGS]; // banco de registradores
int clock = 0; // sinal de clock (comportamento do meu processador)


//  Inicialização 
void init_regs() {
    for (int i = 0; i < NUM_REGS; i++) { // estamos percorrendo todos os registradores
        regs[i] = 0; //  colocandon valor 0 em cada registrador

    }
}


// Leitura (2 portas/ leituras)
void read_regs(int rs, int rt, int *out1, int *out2) {
    *out1 = regs[rs]; // valores são retornados atraves do ponteiro 
    *out2 = regs[rt];
}


//  Escrita (1 porta, sincronizada)
void write_reg(int reg_dest, int value, int RegWrite) { // onde escreve, valor a guardar e o sinal de controle
    if (clock == 1 && RegWrite && reg_dest != 0) {
        regs[reg_dest] = value; // gravando o valor no registrador de destino
    }
}


//  Clock
void clock_pulse() {
    clock = 1;  // subida
    clock = 0;  // descida
}


// Imprime o estado dos registradores
void print_regs() {
    printf("\n REGISTRADORES \n");
    for (int i = 0; i < NUM_REGS; i++) { // percorrendo os registradores para imprimir seus valores
        printf("R%d = %d\n", i, regs[i]);
    }
}
