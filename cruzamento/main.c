#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "includes/handler.h"
#include "includes/buttons_config.h"
#include "includes/variables.h"
#include "includes/message.h"
#include "includes/cliente.h"

void* send2SecMessage () {
    while (1) {
        delay(2000);
        buildPassMessage();
    }
}

int main(void) {
    // Cruzamento 1
    int semaforo1[3] = {28, 27, 26}; // VIA PRINCIPAL
    int semaforo2[3] = {31, 25, 29}; // Verde-Amarelo-Vermelho
    int estados1[6][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}};
    int estados2[6][3] = {{0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    int delayMax[6] = {20, 3, 1, 10, 3, 1};

    wiringPiSetup();

    setPinModeSemaforos(semaforo1);
    setPinModeSemaforos(semaforo2);

    setButtons();

    pthread_t messagemPassagem2s;
	int res0;

	res0 = pthread_create(&messagemPassagem2s, NULL, send2SecMessage, NULL);

    while(1) {
        for (estado = 0; estado < 6; estado++) {
            for (int i = 0; i < 3; i++) {
                if (estados1[estado][i]) {digitalWrite(semaforo1[i], HIGH);}
                else digitalWrite(semaforo1[i], LOW);
                if (estados2[estado][i]) {digitalWrite(semaforo2[i], HIGH);}
                else digitalWrite(semaforo2[i], LOW);
            }
            
            int seconds = 0;
            TEMP_ATUAL = delayMax[estado];
            while (seconds < TEMP_ATUAL) {
                sleep(1);
                seconds++;
            }
        }
    }

    return 0;
}
