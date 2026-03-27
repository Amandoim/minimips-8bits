// Função responsável por decodificar uma instrução binária
void decodificador(struct instrucao *inst) {
    char temp[13]; // Buffer auxiliar para armazenar partes da instrução

    // Extrai o opcode (4 primeiros bits)
    strncpy(temp, inst->inst_bin, 4);
    temp[4] = '\0';
    inst->opcode = (int)strtol(temp, NULL, 2);

    // Verifica o tipo da instrução com base no opcode
    if (inst->opcode == 0) { // Tipo R: [opcode][rs][rt][rd][funct]

        // Extrai rs (3 bits)
        strncpy(temp, inst->inst_bin + 4, 3);
        temp[3] = '\0';
        inst->rs = (int)strtol(temp, NULL, 2);

        // Extrai rt (3 bits)
        strncpy(temp, inst->inst_bin + 7, 3);
        temp[3] = '\0';
        inst->rt = (int)strtol(temp, NULL, 2);

        // Extrai rd (3 bits)
        strncpy(temp, inst->inst_bin + 10, 3);
        temp[3] = '\0';
        inst->rd = (int)strtol(temp, NULL, 2);

        // Extrai funct (3 bits)
        strncpy(temp, inst->inst_bin + 13, 3);
        temp[3] = '\0';
        inst->funct = (int)strtol(temp, NULL, 2);
    } 
    else if (inst->opcode == 2) { // Tipo J: [opcode][address]

        // Extrai endereço (12 bits)
        strncpy(temp, inst->inst_bin + 4, 12);
        temp[12] = '\0';
        inst->addr = (int)strtol(temp, NULL, 2);
    } 
    else { // Tipo I: [opcode][rs][rt][imm]

        // Extrai rs (3 bits)
        strncpy(temp, inst->inst_bin + 4, 3);
        temp[3] = '\0';
        inst->rs = (int)strtol(temp, NULL, 2);

        // Extrai rt (3 bits)
        strncpy(temp, inst->inst_bin + 7, 3);
        temp[3] = '\0';
        inst->rt = (int)strtol(temp, NULL, 2);

        // Extrai imediato (6 bits)
        strncpy(temp, inst->inst_bin + 10, 6);
        temp[6] = '\0';
        inst->imm = (int)strtol(temp, NULL, 2);
    }
}