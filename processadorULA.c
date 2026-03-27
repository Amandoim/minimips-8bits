#include <stdio.h>


// Estrutura do processador 

typedef struct {

    unsigned int pc; // Program Counter (contador de programa)

    // Apenas 4 registradores (0 a 3)
    // → precisamos de apenas 2 bits para representá-los
    int registradores[4];

    // Memória de dados reduzida 
    int memoria_dados[256];

    // Memória de instruções (cada instrução tem 8 bits)
    int memoria_instr[256];

} MIPS_Core;



// Funcao da ULA 

int ULA(int A, int B, int op) {

    // A → primeiro operando
    // B → segundo operando
    // op → operação a ser realizada

    switch(op) {

        case 0:
            // Soma
            return A + B; //Add

        case 1:
            // Subtração  //sub
            return A - B;

        case 2:
            // Operação AND (bit a bit)
            return A & B;

        case 3:
            // Operação OR (bit a bit)
            return A | B;

        default:
            // Caso a operação não exista
            return 0;
    }
}
