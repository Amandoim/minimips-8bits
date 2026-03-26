#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decodificar(char *binario) {
    // Pegamos os 4 primeiros bits para identificar a instrução (Exemplo Mini MIPS)
    // No seu caso, vamos comparar a string diretamente para ser "o mais simples possível"
    
    printf("%s -> ", binario);

    if (strncmp(binario, "1011", 4) == 0)      printf("LW\n");
    else if (strncmp(binario, "1111", 4) == 0) printf("SW\n");
    else if (strncmp(binario, "0100", 4) == 0) printf("ADDI\n");
    else if (strncmp(binario, "1000", 4) == 0) printf("BEQ\n");
    else if (strncmp(binario, "0010", 4) == 0) printf("J\n");
    else if (strncmp(binario, "0000", 4) == 0) {
        // Para Tipo R (0000), olhamos o final (funct)
        // ADD termina em 100000 (0x20) e SUB em 101010 (0x22) no MIPS padrão
        if (strstr(binario, "101010")) printf("SUB\n");
        else printf("ADD\n");
    } 
    else printf("Desconhecido\n");
}

int main() {
    FILE *file = fopen("arquivo.txt", "r");
    char linha[20];

    if (file == NULL) {
        printf("Erro ao abrir arquivo.txt\n");
        return 1;
    }

    while (fscanf(file, "%s", linha) != EOF) {
        decodificar(linha);
    }

    fclose(file);
    return 0;
}
