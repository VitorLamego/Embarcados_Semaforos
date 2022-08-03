#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include "listenConnection.h"


int main (int argc, char** argv) {

	pthread_t t0;
	int res0;

	res0 = pthread_create(&t0, NULL, create_socket, (void *) argv[1]);
    pthread_join(t0, NULL); // Blocante


	puts("Terminou!");
	return 0;
}
