#include "../includes/handler.h"
#include "../includes/buttons_config.h"
#include "../includes/variables.h"
#include <wiringPi.h>

void* semaforoController () {
    int estados1[6][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}};
    int estados2[6][3] = {{0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    
    while(1) {
        if (!EMERGENCY_MODE && !NIGHT_MODE) {
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
                    delay(1000);
                    seconds++;
                }
            }
        }
    }
}

void emergencyMode() {
    while (EMERGENCY_MODE) {
        digitalWrite(semaforo1[0], HIGH); digitalWrite(semaforo1[1], LOW); digitalWrite(semaforo1[2], LOW);
        digitalWrite(semaforo2[0], LOW); digitalWrite(semaforo2[1], LOW); digitalWrite(semaforo2[2], HIGH);
    }
}

void nigthMode() {
    while (NIGHT_MODE) {
        digitalWrite(semaforo1[0], LOW); digitalWrite(semaforo1[1], HIGH); digitalWrite(semaforo1[2], LOW);
        digitalWrite(semaforo2[0], LOW); digitalWrite(semaforo2[1], HIGH); digitalWrite(semaforo2[2], LOW);
        delay(1000);
        digitalWrite(semaforo1[0], LOW); digitalWrite(semaforo1[1], LOW); digitalWrite(semaforo1[2], LOW);
        digitalWrite(semaforo2[0], LOW); digitalWrite(semaforo2[1], LOW); digitalWrite(semaforo2[2], LOW);
        delay(1000);
    }
}

void reset() {
    if (!EMERGENCY_MODE && !NIGHT_MODE) {
        digitalWrite(semaforo1[0], HIGH); digitalWrite(semaforo1[1], LOW); digitalWrite(semaforo1[2], LOW);
        digitalWrite(semaforo2[0], LOW); digitalWrite(semaforo2[1], LOW); digitalWrite(semaforo2[2], HIGH);
    }
    estado = 0;
}

void special_observer() {
    while (1) {
        emergencyMode();
        nigthMode();
    }
}

