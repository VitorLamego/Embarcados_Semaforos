#include <wiringPi.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include "../includes/variables.h"
#include "../includes/handler.h"

void setPinModeSemaforos (int semaforo[3]) {
    for (int i = 0; i < 3; i++) pinMode(semaforo[i], OUTPUT);
}

void setButtons() {
    pinMode(BOTAO_PEDESTRE_1, OUTPUT);
    pinMode(BOTAO_PEDESTRE_2, OUTPUT);
    gettimeofday(&last_changePeople, NULL);
    gettimeofday(&last_changePassAux, NULL);
    gettimeofday(&last_changeStopPrin, NULL);
    wiringPiISR(BOTAO_PEDESTRE_1, INT_EDGE_RISING, &handlePassPeopleButton);
	wiringPiISR(BOTAO_PEDESTRE_2, INT_EDGE_RISING, &handlePassPeopleButton);

    pinMode(SENSOR_PASSAGEM_1, OUTPUT);
    pinMode(SENSOR_PASSAGEM_2, OUTPUT);
    wiringPiISR(SENSOR_PASSAGEM_1, INT_EDGE_BOTH, &handleCarSensorAuxiliar);
	wiringPiISR(SENSOR_PASSAGEM_2, INT_EDGE_BOTH, &handleCarSensorAuxiliar);

    pinMode(SENSOR_VELOCIDADE_1_A, OUTPUT);
    pinMode(SENSOR_VELOCIDADE_1_B, OUTPUT);
    wiringPiISR(SENSOR_VELOCIDADE_1_A, INT_EDGE_BOTH, &handleStopPrincipal);
    wiringPiISR(SENSOR_VELOCIDADE_1_B, INT_EDGE_RISING, &handlePassPrincipal);

    pinMode(SENSOR_VELOCIDADE_2_A, OUTPUT);
    pinMode(SENSOR_VELOCIDADE_2_B, OUTPUT);
    wiringPiISR(SENSOR_VELOCIDADE_2_A, INT_EDGE_BOTH, &handleStopPrincipal2);
    wiringPiISR(SENSOR_VELOCIDADE_2_B, INT_EDGE_RISING, &handlePassPrincipal2);
}