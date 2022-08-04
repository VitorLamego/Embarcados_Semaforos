#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int cruzamento;
int TEMP_ATUAL = 0;
int delayMin[6] = {10, 3, 1, 5, 3, 1};
int delayMax[6] = {20, 3, 1, 10, 3, 1};
int estado = 0;
int count_passagem1_auxiliar = 0;
int count_passagem2_auxiliar = 0;
int count_prin1 = 0;
int count_prin2 = 0;

// Botoes de pedestre
int BOTAO_PEDESTRE_1;
int BOTAO_PEDESTRE_2;

// Via Auxiliar - Sensor Passagem
int SENSOR_PASSAGEM_1;
int SENSOR_PASSAGEM_2;

// Via Principal
int SENSOR_VELOCIDADE_1_A;
int SENSOR_VELOCIDADE_1_B;

int SENSOR_VELOCIDADE_2_A;
int SENSOR_VELOCIDADE_2_B;

// Semaforos LEDS
int semaforo1[3]; // VIA PRINCIPAL
int semaforo2[3]; // Verde-Amarelo-Vermelho

void setVariables(char *cruzamento1) {
    if (strcmp(cruzamento1, "1") == 0 || strcmp(cruzamento1, "3") == 0) {
        cruzamento = atoi(cruzamento1);
        // Botoes de pedestre
        BOTAO_PEDESTRE_1 = 10;
        BOTAO_PEDESTRE_2 = 11;

        // Via Auxiliar - Sensor Passagem
        SENSOR_PASSAGEM_1 = 15;
        SENSOR_PASSAGEM_2 = 16;

        // Via Principal
        SENSOR_VELOCIDADE_1_A = 1;
        SENSOR_VELOCIDADE_1_B = 4;

        SENSOR_VELOCIDADE_2_A = 5;
        SENSOR_VELOCIDADE_2_B = 6;

        semaforo1[0] = 28; semaforo1[1] = 27; semaforo1[2] = 26;
        semaforo2[0] = 31; semaforo2[1] = 25; semaforo2[2] = 29;
    }
    else {
        cruzamento = atoi(cruzamento1);
        // Botoes de pedestre
        BOTAO_PEDESTRE_1 = 12;
        BOTAO_PEDESTRE_2 = 13;

        // Via Auxiliar - Sensor Passagem
        SENSOR_PASSAGEM_1 = 7;
        SENSOR_PASSAGEM_2 = 0;

        // Via Principal
        SENSOR_VELOCIDADE_1_A = 2;
        SENSOR_VELOCIDADE_1_B = 3;

        SENSOR_VELOCIDADE_2_A = 23;
        SENSOR_VELOCIDADE_2_B = 24;

        // Semaforos LEDS
        semaforo1[0] = 30; semaforo1[1] = 21; semaforo1[2] = 22;
        semaforo2[0] = 8; semaforo2[1] = 9; semaforo2[2] = 14;
    }
}
