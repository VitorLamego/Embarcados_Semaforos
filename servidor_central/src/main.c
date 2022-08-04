#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include "../includes/listenConnection.h"
#include "../includes/interface.h"

int main (int argc, char** argv) {

	pthread_t socker_server;
	pthread_t interface;
	int res0, res1;

	res0 = pthread_create(&socker_server, NULL, create_socket, NULL);
	res1 = pthread_create(&interface, NULL, printMenu , NULL);
    pthread_join(socker_server, NULL); // Blocante


	puts("Terminou!");
	return 0;
}
