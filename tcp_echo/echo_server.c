#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#define BUFFER_SIZE     1024

void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET hServerSocket, hClientSocket;
    char message[BUFFER_SIZE];
    int strLength, i;

    SOCKADDR_IN serverAddress, clientAddress;
    int clientAddressSize;

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
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

    for (i = 0; i < 5; ++i)
    {
        hClientSocket = accept(hServerSocket, (SOCKADDR*)&clientAddress, &clientAddressSize);
        if (hClientSocket == -1)
            ErrorHandling("accept() error!");
        else
            printf("Connected client %d\n", i + 1);
        
        while ((strLength = recv(hClientSocket, message, BUFFER_SIZE, 0)) != 0)
            send(hClientSocket, message, strLength, 0);
        
        closesocket(hClientSocket);
    }

    closesocket(hServerSocket);
    WSACleanup();
    return 0;
}

void ErrorHandling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}