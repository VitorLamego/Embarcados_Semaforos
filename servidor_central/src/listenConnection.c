#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include "../includes/variables.h"

// Servidor Central Recebendo Mensagem dos Distribuídos

void TrataClienteTCP(int socketCliente) {
	char buffer[1000] = "";
	int tamanhoRecebido;

	if((tamanhoRecebido = recv(socketCliente, buffer, 1000, 0)) < 0)
		printf("Erro no recv()\n");
	if ((tamanhoRecebido < 70 || tamanhoRecebido > 125) && REPORTES_SERIOS) printf("%s\n", buffer);
	else if ((tamanhoRecebido > 70 && tamanhoRecebido < 130) && REPORTES_NORMAIS) printf("%s\n", buffer);
	else {}
	while (tamanhoRecebido > 0) {
		if(send(socketCliente, "", tamanhoRecebido, 0) != tamanhoRecebido)
			printf("Erro no envio - send()\n");
		
		if((tamanhoRecebido = recv(socketCliente, buffer, 1000, 0)) < 0)
			printf("Erro no recv()\n");
	}
}

void* create_socket (void) {
	int servidorSocket;
	int socketCliente;
	struct sockaddr_in servidorAddr;
	struct sockaddr_in clienteAddr;
	unsigned short servidorPorta;
	unsigned int clienteLength;

	servidorPorta = atoi("10351");

	if((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("falha no socker do Servidor\n");

	memset(&servidorAddr, 0, sizeof(servidorAddr));
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorAddr.sin_port = htons(servidorPorta);

	if(bind(servidorSocket, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0)
		printf("Falha no Bind\n");

	if(listen(servidorSocket, 10) < 0)
		printf("Falha no Listen\n");		

	while(1) {
		clienteLength = sizeof(clienteAddr);
		if((socketCliente = accept(servidorSocket, 
			                      (struct sockaddr *) &clienteAddr, 
			                      &clienteLength)) < 0)
			printf("Falha no Accept\n");
		
		TrataClienteTCP(socketCliente);
	}
}