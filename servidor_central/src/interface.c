#include <stdio.h>
#include "../includes/variables.h"
#include "../includes/cliente.h"

void printMenu() {
    while (1) {
        printf("\n--- Servidor Central ---\n");
        printf("1. Verificar reportes normais\n");
        printf("2. Verificar reportes de velocidade / infraçao\n");
        printf("3. Modo de Emergencia\n");
        printf("4. Modo noturno\n");

        printf("Escolha a sua opcao: \n");

        int escolha;

        while (scanf(" %d", &escolha) != 1 && (escolha > 4 || escolha < 1)) {}

        printf("\nImportante: Para voltar ao menu digite a mesma opcao selecionada\n");

        if (escolha == 1) {REPORTES_NORMAIS = 1;}
        else if (escolha == 2) {REPORTES_SERIOS = 1;}
        else if (escolha == 3) {sendForAllDistributed("Modo de Emergencia"); printf("Modo de Emergencia ativado!\n");}
        else if (escolha == 4) {sendForAllDistributed("Modo Noturno"); printf("Modo Noturno ativado! \n");}
        
        char retorno[1];
        while(scanf(" %s", retorno) != 1) {}
        
        if (escolha == 3) {sendForAllDistributed("Modo de Emergencia"); printf("Modo de Emergencia desativado!\n");}
        else if (escolha == 4) {sendForAllDistributed("Modo Noturno"); printf("Modo Noturno desativado! \n");}
        REPORTES_NORMAIS = 0;
        REPORTES_SERIOS = 0;
    }

}