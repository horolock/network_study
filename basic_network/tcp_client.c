#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN serverAddress;

    char message[30];
    int messageLength = 0;
    int index = 0;
    int readLength = 0;

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!");

    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (hSocket == INVALID_SOCKET)
        ErrorHandling("socket() error!");
    
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddress.sin_port = htons(atoi(argv[2]));

    if (connect(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
        ErrorHandling("connect() error!");

    while (readLength = recv(hSocket, &message[index++], 1, 0))
    {
        if (readLength == -1)
            ErrorHandling("recv() error!");
        messageLength += readLength;
    }

    printf("Message from server: %s\n", message);
    printf("Function read call count: %d\n", messageLength);

    closesocket(hSocket);
    WSACleanup();

    return 0;
}

void ErrorHandling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}