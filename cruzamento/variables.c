#include <unistd.h>
#include <sys/time.h>

int TEMP_ATUAL = 0;
int delayMin[6] = {10, 3, 1, 5, 3, 1};
int estado = 0;
int count_passagem1_auxiliar = 0;
int count_passagem2_auxiliar = 0;
int count_prin1 = 0;
int count_prin2 = 0;

// Botoes de pedestre
int BOTAO_PEDESTRE_1 = 10;
int BOTAO_PEDESTRE_2 = 11;

// Via Auxiliar - Sensor Passagem
int SENSOR_PASSAGEM_1 = 15;
int SENSOR_PASSAGEM_2 = 16;

// Via Principal
int SENSOR_VELOCIDADE_1_A = 1;
int SENSOR_VELOCIDADE_1_B = 4;

int SENSOR_VELOCIDADE_2_A = 5;
int SENSOR_VELOCIDADE_2_B = 6;
