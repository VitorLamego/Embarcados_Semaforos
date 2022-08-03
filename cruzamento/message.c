#include <stdio.h>
#include "includes/variables.h"
#include "includes/cliente.h"

void buildPassMessage() {
    char mensagem[1000];

    sprintf(mensagem, "--- Cruzamento %d ---\nPrincipal para direita: %d\nPrincipal para a esquerda: %d\nAuxiliar para baixo: %d\nAuxiliar para cima: %d\n", 3, count_prin1, count_prin2, count_passagem1_auxiliar, count_passagem2_auxiliar);
    sendMessage(mensagem);
}