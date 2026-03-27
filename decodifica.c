// Função responsável por decodificar uma instrução binária de 8 bits (string de '0' e '1')
void decodificador(struct instrucao *inst) {

    // Buffer auxiliar para armazenar partes da instrução
    // 8 bits + 1 para o caractere de fim '\0'
    char temp[9];

    // EXTRAÇÃO DO OPCODE

    // Copia os 2 primeiros bits (opcode)
    strncpy(temp, inst->inst_bin, 2);
    temp[2] = '\0'; // Finaliza a string

    // Converte de binário para inteiro
    inst->opcode = (int)strtol(temp, NULL, 2);


    
    // TIPO R (opcode == 0)
    // Formato: [opcode(2)][rs(2)][rt(2)][rd(2)]
    
    if (inst->opcode == 0) {

        // Extrai rs (bits 2 e 3)
        strncpy(temp, inst->inst_bin + 2, 2);
        temp[2] = '\0';
        inst->rs = (int)strtol(temp, NULL, 2);

        // Extrai rt (bits 4 e 5)
        strncpy(temp, inst->inst_bin + 4, 2);
        temp[2] = '\0';
        inst->rt = (int)strtol(temp, NULL, 2);

        // Extrai rd (bits 6 e 7)
        strncpy(temp, inst->inst_bin + 6, 2);
        temp[2] = '\0';
        inst->rd = (int)strtol(temp, NULL, 2);
    }


    
    // TIPO J (opcode == 2)
    // Formato: [opcode(2)][addr(6)]
    
    else if (inst->opcode == 2) {

        // Extrai endereço (bits 2 até 7 → 6 bits)
        strncpy(temp, inst->inst_bin + 2, 6);
        temp[6] = '\0';
        inst->addr = (int)strtol(temp, NULL, 2);
    }


    
    // TIPO I (outros opcodes)
    // Formato: [opcode(2)][rs(2)][rt(2)][imm(2)]
    
    else {

        // Extrai rs (bits 2 e 3)
        strncpy(temp, inst->inst_bin + 2, 2);
        temp[2] = '\0';
        inst->rs = (int)strtol(temp, NULL, 2);

        // Extrai rt (bits 4 e 5)
        strncpy(temp, inst->inst_bin + 4, 2);
        temp[2] = '\0';
        inst->rt = (int)strtol(temp, NULL, 2);

        // Extrai imediato (bits 6 e 7)
        strncpy(temp, inst->inst_bin + 6, 2);
        temp[2] = '\0';
        inst->imm = (int)strtol(temp, NULL, 2);
    }
}
