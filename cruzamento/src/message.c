#include <stdio.h>
#include "../includes/variables.h"
#include "../includes/cliente.h"

void buildPassMessage() {
    char mensagem[1000];

    sprintf(mensagem, "--- Cruzamento %d ---\nPrincipal para direita: %d\nPrincipal para a esquerda: %d\nAuxiliar para baixo: %d\nAuxiliar para cima: %d\nInfração de ultrapassagem: %d\nInfração de velocidade: %d\n", cruzamento, count_prin1, count_prin2, count_passagem1_auxiliar, count_passagem2_auxiliar, count_prin_verm + count_passagem_aux_vermelho, count_prin_velo);
    sendMessage(mensagem);
}

void buildInfringementMessage() {
    char mensagem[1000];

    sprintf(mensagem, "--- Cruzamento %d ---\n Ultrapassagem pelo sinal vermelho!\n", cruzamento);
    sendMessage(mensagem);
}