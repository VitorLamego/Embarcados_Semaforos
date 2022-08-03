#include <stdio.h>
#include <wiringPi.h>

void setPinModeSemaforos (int semaforo[3]) {
    for (int i = 0; i < 3; i++) pinMode(semaforo[i], OUTPUT);
}


int main(void) {

    // Cruzamento 1
    int semaforo1[3] = {31, 25, 29}; // Verde-Amarelo-Vermelho
    int semaforo2[3] = {28, 27, 26};
    int estados[4][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 1}};

    wiringPiSetup();

    setPinModeSemaforos(semaforo1);
    setPinModeSemaforos(semaforo2);

    while(1)
    {
        int estado2;
        for (int estado1 = 0; estado1 < 4; estado1++) {
            estado2 = (estado1 + 2) % 4;
            for (int i = 0; i < 3; i++) {
                digitalWrite(semaforo1[i], LOW);
                digitalWrite(semaforo2[i], LOW);
            }
        }
    }

    return 0;
}