#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "../includes/variables.h"

void sendMessage(char *message, char *IP_Servidor, unsigned short servidorPorta) {
	int clienteSocket;
	struct sockaddr_in servidorAddr;
	char *mensagem;
	char buffer[1000] = "";
	unsigned int tamanhoMensagem;

	int bytesRecebidos;
	int totalBytesRecebidos;

	mensagem = message;

	// Criar Socket
	if((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Erro no socket()\n");

	// Construir struct sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
	servidorAddr.sin_port = htons(servidorPorta);

	// Connect
	if(connect(clienteSocket, (struct sockaddr *) &servidorAddr, 
							sizeof(servidorAddr)) < 0)
		printf("Erro no connect()\n");

	tamanhoMensagem = strlen(mensagem);
	int i = 0;
	if(send(clienteSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
		printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

	totalBytesRecebidos = 0;
	close(clienteSocket);
}

void sendForAllDistributed(char *message) {
    sendMessage(message, "164.41.98.17", 10352);
    sendMessage(message, "164.41.98.17", 10353);
    sendMessage(message, "164.41.98.26", 10354);
    sendMessage(message, "164.41.98.26", 10355);
}
