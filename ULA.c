#include <stdio.h>

{
// FUNÇÃO DA ULA 
int executar_ula(int v1, int v2, int controle, char tipo) {
    if (tipo == 'R') { // Baseado no FUNCT
        switch(controle) {
            case 0: return v1 + v2; // ADD
            case 2: return v1 - v2; // SUB
            case 4: return v1 & v2; // AND
            case 5: return v1 | v2; // OR
            default: return 0;
        }
    } else { // Baseado no OPCODE (Tipo I)
        switch(controle) {
            case 4:  return v1 + v2; // ADDi
            case 8:  return (v1 == v2); // BEQ (1 se igual, 0 se não)
            case 11: 
            case 15: return v1 + v2; // Cálculo de endereço (LW/SW)
            default: return 0;
        }
    }
}


return 0;
}
