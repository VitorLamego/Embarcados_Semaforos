#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <sys/time.h>
#include "variables.h"

struct timeval last_changePeople;
struct timeval last_changePassAux;
struct timeval last_changePassPrin;
struct timeval last_changeStopPrin;
struct timeval last_changeStopPrin2;

struct timeval first_sensor_time1;
struct timeval second_sensor_time1;

struct timeval first_sensor_time2;
struct timeval second_sensor_time2;

static volatile int passagem1_aux_state = 0;
static volatile int passagem2_aux_state = 0;

static volatile int stop1_prin_state = 1;
static volatile int stop2_prin_state = 1;

void handlePassPeopleButton(void) {
	struct timeval now;
	unsigned long diff;

	gettimeofday(&now, NULL);

	diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_changePeople.tv_sec * 1000000 + last_changePeople.tv_usec);

	if (diff > 10000) {
        if (digitalRead(BOTAO_PEDESTRE_1)) {
            printf("Botão 1 pressionado!\n");     
            if (estado == 3) {TEMP_ATUAL = delayMin[3];}
        }
        else if (digitalRead(BOTAO_PEDESTRE_2)) {
            printf("Botão 2 pressionado \n");
		    if (estado == 0) {TEMP_ATUAL = delayMin[0];}
        }
	}

	last_changePeople = now;
}

void handleCarSensorAuxiliar(void) {
    struct timeval now;
	unsigned long diff;

	gettimeofday(&now, NULL);

	diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_changePassAux.tv_sec * 1000000 + last_changePassAux.tv_usec);
	if (diff > 10000) {
        if (digitalRead(SENSOR_PASSAGEM_1) != passagem1_aux_state) {
            if (passagem1_aux_state) {
                printf("Auxiliar descendo %d\n", ++count_passagem1_auxiliar);
                if (estado != 3 && estado != 4) printf("Ultrapassagem pelo vermelho\n");
            }
            else {
                if (estado == 0) {
                    printf("Reduzindo semáforo da principal\n"); 
                    TEMP_ATUAL = delayMin[0];
                }
            } 
            passagem1_aux_state = !passagem1_aux_state;        
        } 
        else if (digitalRead(SENSOR_PASSAGEM_2) != passagem2_aux_state) {
            if (passagem2_aux_state) {
                printf("Auxiliar subindo %d\n", ++count_passagem2_auxiliar);
                if (estado != 3 && estado != 4) printf("Ultrapassagem pelo vermelho\n");
            }
            else {
                if (estado == 0) {
                    printf("Reduzindo semáforo da principal\n"); 
                    TEMP_ATUAL = delayMin[0];
                }
            }
            passagem2_aux_state = !passagem2_aux_state;
        }
    }
	last_changePassAux = now;
}

void handlePassPrincipal(void) {
	struct timeval now;
	unsigned long diff;

	gettimeofday(&now, NULL);

	diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_changePassPrin.tv_sec * 1000000 + last_changePassPrin.tv_usec);

	if (diff > 10000) {
        
       gettimeofday(&first_sensor_time1, NULL); 
       stop1_prin_state = 0;
	}

	last_changePassPrin = now;
}

void handlePassPrincipal2(void) {
	struct timeval now;
	unsigned long diff;

	gettimeofday(&now, NULL);

	diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_changePassPrin.tv_sec * 1000000 + last_changePassPrin.tv_usec);

	if (diff > 10000) {
       gettimeofday(&first_sensor_time2, NULL);
       stop2_prin_state = 0;
	}

	last_changePassPrin = now;
}

void handleStopPrincipal(void) {
	struct timeval now;
	unsigned long diff;

	gettimeofday(&now, NULL);

	diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_changeStopPrin.tv_sec * 1000000 + last_changeStopPrin.tv_usec);
	if (diff > 10000) {
        if (stop1_prin_state) {   
            if (estado == 3) {
                printf("Reduzindo tempo da auxiliar\n");
                TEMP_ATUAL = delayMin[3];
            }
            count_prin1++;
        }
        // else if (stop1_prin_state && !digitalRead(SENSOR_VELOCIDADE_1_A)) {
        //     printf("Principal direita: %d\n", ++count_prin1);
        //     if (estado > 2) printf("Ultrapassagem no vermelho - Principal Direita\n");
        // }
        else {
            gettimeofday(&second_sensor_time1, NULL);

            printf("Principal direita: %d\n", ++count_prin1);
            if (estado > 2) printf("Ultrapassagem no vermelho\n");

            float ms_difference = (second_sensor_time1.tv_usec - first_sensor_time1.tv_usec)/1000;
            if (ms_difference >= 30.0) {
                float velocity = (3.6/(ms_difference)) * 1000;
                printf("Velocidade: %.1f km/h\n", velocity);

                if (velocity > 60.0) printf("Limite de velocidade ultrapassado\n");
            }
        }
        stop1_prin_state = 1;    
	}
	last_changeStopPrin = now;    
}

void handleStopPrincipal2 (void) {
    struct timeval now;
	unsigned long diff;

	gettimeofday(&now, NULL);

	diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_changeStopPrin2.tv_sec * 1000000 + last_changeStopPrin2.tv_usec);
	if (diff > 10000) {
        if (stop2_prin_state) {
            if (estado == 3) {
                printf("Reduzindo tempo da auxiliar\n");
                TEMP_ATUAL = delayMin[3];
            }
            count_prin2++;
        }
        // else if (stop2_prin_state ) {
        //     printf("Principal esquerda: %d\n", ++count_prin2);
        //     if (estado > 2) printf("Ultrapassagem no vermelho - Principal Esquerda\n");
        // }
        else {
            gettimeofday(&second_sensor_time2, NULL);

            printf("Principal esquerda: %d\n", ++count_prin2);
            if (estado > 2) printf("Ultrapassagem no vermelho\n");

            float ms_difference = (second_sensor_time2.tv_usec - first_sensor_time2.tv_usec)/1000;
            if (ms_difference >= 30.0) {
                float velocity = (3.6/(ms_difference)) * 1000;
                printf("Velocidade: %.1f km/h\n", velocity);

                if (velocity > 60.0) printf("Limite de velocidade ultrapassado\n");
            }
        }
        stop2_prin_state = 1;
    }
    last_changeStopPrin2 = now;
}