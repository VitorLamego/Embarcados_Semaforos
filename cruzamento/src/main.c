#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "../includes/handler.h"
#include "../includes/buttons_config.h"
#include "../includes/variables.h"
#include "../includes/message.h"
#include "../includes/cliente.h"
#include "../includes/listenConnection.h"
#include "../includes/semaforos.h"

void* send2SecMessage () {
    while (1) {
        delay(2000);
        buildPassMessage();
    }
}

void* setInfoMinute () {
    while (1) {
        delay(60000);
        minutes++;
        float fluxo = (count_prin1 + count_prin2) / minutes;
        float velocidadeMedia = velocitySum / (count_prin1 + count_prin2);
        buildReportMessage(fluxo, velocidadeMedia);
    }
}

int main(int argc, char** argv) {
    // Cruzamento 1

    wiringPiSetup();
    setVariables(argv[1]);

    setPinModeSemaforos(semaforo1);
    setPinModeSemaforos(semaforo2);

    setButtons();

    pthread_t messagemPassagem2s;
    pthread_t semaforos;
    pthread_t infoMinuto;
    pthread_t socketServer;
    pthread_t specialModes;
	int res0, res1, res2, res3, res4;

    res1 = pthread_create(&semaforos, NULL, semaforoController, NULL);
	res0 = pthread_create(&messagemPassagem2s, NULL, send2SecMessage, NULL);
    res2 = pthread_create(&infoMinuto, NULL, setInfoMinute, NULL);
    res3 = pthread_create(&socketServer, NULL, create_socket, NULL);
    res4 = pthread_create(&specialModes, NULL, special_observer, NULL);

    while(1){}

    return 0;
}
