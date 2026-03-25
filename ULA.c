#include <stdio.h>

// 1. BANCO DE REGISTRADORES 
// Criamos 8 espaços e colocamos valores de exemplo (R0=0, R1=10, R2=20...)
int regs[8] = {0, 10, 20, 30, 40, 50, 60, 70};

// 2. FUNÇÃO DA ULA (O motor de cálculo)
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

// 3. FUNÇÃO PRINCIPAL (Onde o programa começa)
int main() {
    printf("--- SIMULADOR DE ULA MIPS ---\n\n");

    // TESTE 1: Somar Registrador 1 (10) + Registrador 2 (20) -> Tipo R (ADD, funct 0)
    int res1 = executar_ula(regs[1], regs[2], 0, 'R');
    printf("Teste ADD: R1(%d) + R2(%d) = %d\n", regs[1], regs[2], res1);

    // TESTE 2: Somar Registrador 3 (30) + Valor Imediato 5 -> Tipo I (ADDi, opcode 4)
    int res2 = executar_ula(regs[3], 5, 4, 'I');
    printf("Teste ADDi: R3(%d) + Imm(5) = %d\n", regs[3], res2);

    // TESTE 3: Comparar se R4 (40) é igual a R5 (50) -> Tipo I (BEQ, opcode 8)
    int res3 = executar_ula(regs[4], regs[5], 8, 'I');
    printf("Teste BEQ: R4(%d) == R5(%d) ? %s\n", regs[4], regs[5], res3 ? "SIM" : "NAO");

    return 0;
}
