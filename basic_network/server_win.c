#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

void ErrorHandling(char *message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET hServerSocket, hClientSocket;
    SOCKADDR_IN serverAddress, clientAddress;

    int clientAddressSize = 0;
    char message[] = "Hello World!";

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!");

    hServerSocket = socket(PF_INET, SOCK_STREAM, 0);

    if (hServerSocket == INVALID_SOCKET)
        ErrorHandling("socket() error!");
    
    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(atoi(argv[1]));

    if (bind(hServerSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
        ErrorHandling("bind() error!");
    
    if (listen(hServerSocket, 5) == SOCKET_ERROR)
        ErrorHandling("listen() error!");
    
    clientAddressSize = sizeof(clientAddress);
    hClientSocket = accept(hServerSocket, (SOCKADDR*)&clientAddress, &clientAddressSize);

    if (hClientSocket == INVALID_SOCKET)
        ErrorHandling("accept() error!");
    
    send(hClientSocket, message, sizeof(message), 0);

    closesocket(hClientSocket);
    closesocket(hServerSocket);
    WSACleanup();

    return 0;
}

void ErrorHandling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);

    exit(1);
}