#include <stdio.h>
#include "../includes/variables.h"

void printMenu() {
    while (1) {
        printf("\n--- Servidor Central ---\n");
        printf("1. Verificar reportes normais\n");
        printf("2. Verificar reportes de velocidade / infraçao\n");
        printf("3. Comando ( Não implementado )\n");

        printf("Escolha a sua opcao: \n");

        int escolha;

        while (scanf(" %d", &escolha) != 1 && (escolha > 3 || escolha < 1)) {}

        printf("\nImportante: Para voltar ao menu digite a mesma opcao selecionada");

        if (escolha == 1) {REPORTES_NORMAIS = 1;}
        if (escolha == 2) {REPORTES_SERIOS = 1;}
        if (escolha == 3) printf("Comandos selecionado\n");
        
        char retorno[1];
        while(scanf(" %s", retorno) != 1) {}

        REPORTES_NORMAIS = 0;
        REPORTES_SERIOS = 0;
    }

}