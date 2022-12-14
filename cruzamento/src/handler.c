#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <sys/time.h>
#include "../includes/variables.h"
#include "../includes/message.h"

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
            if (estado == 3) {TEMP_ATUAL = delayMin[3];}
        }
        else if (digitalRead(BOTAO_PEDESTRE_2)) {
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
                if (estado != 3 && estado != 4) count_passagem_aux_vermelho++;
                else ++count_passagem1_auxiliar;

            }
            else {
                if (estado == 0) {
                    TEMP_ATUAL = delayMin[0];
                }
            } 
            passagem1_aux_state = !passagem1_aux_state;        
        } 
        else if (digitalRead(SENSOR_PASSAGEM_2) != passagem2_aux_state) {
            if (passagem2_aux_state) {
                if (estado != 3 && estado != 4) count_passagem_aux_vermelho++;
                else ++count_passagem2_auxiliar;
            }
            else {
                if (estado == 0) {
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
                TEMP_ATUAL = delayMin[3];
            }
            count_prin1++;
        }
        else {
            gettimeofday(&second_sensor_time1, NULL);

            float ms_difference = (second_sensor_time1.tv_usec - first_sensor_time1.tv_usec)/1000;
            float velocity;
            if (ms_difference >= 30.0) {
                velocity = (3.6/(ms_difference)) * 1000;
                buildNormalVelocityMessage(velocity);
                velocitySum += velocity;
            }

            if (estado > 2) { 
                count_prin_verm++;
                buildInfringementMessage();
            }
            else if (velocity > 60.0) {count_prin_velo++; buildVelocityMessage(velocity);}
            else ++count_prin1;
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
                TEMP_ATUAL = delayMin[3];
            }
            count_prin2++;
        }
        else {
            gettimeofday(&second_sensor_time2, NULL);

            float ms_difference = (second_sensor_time2.tv_usec - first_sensor_time2.tv_usec)/1000;
            float velocity;
            if (ms_difference >= 30.0) {
                velocity = (3.6/(ms_difference)) * 1000;
                buildVelocityMessage(velocity);
                velocitySum += velocity;
            }
            if (estado > 2) { 
                count_prin_verm++;
                buildInfringementMessage();
            }
            else if (velocity > 60.0) {count_prin_velo++; buildVelocityMessage(velocity);}
            else count_prin2++;
        }
        stop2_prin_state = 1;
    }
    last_changeStopPrin2 = now;
}