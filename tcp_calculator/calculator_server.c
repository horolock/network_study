#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#define BUFFER_SIZE     1024
#define OPSZ            4

void ErrorHandling(char* message);
int calculate(int opnum, int opnds[], char operator);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET hServerSocket, hClientSocket;
    char opinfo[BUFFER_SIZE];
    int result, operandCount, i;
    int receiveCount, receiveLength;
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
        operandCount = 0;
        hClientSocket = accept(hServerSocket, (SOCKADDR*)&hClientSocket, &clientAddressSize);
        recv(hClientSocket, &operandCount, 1, 0);

        receiveLength = 0;

        while ((operandCount * OPSZ + 1) > receiveLength)
        {
            receiveCount = recv(hClientSocket, &opinfo[receiveLength], BUFFER_SIZE - 1, 0);
            receiveLength += receiveCount;
        }
        result = calculate(operandCount, (int*)opinfo, opinfo[receiveLength - 1]);
        send(hClientSocket, (char*)&result, sizeof(result), 0);
        closesocket(hClientSocket);
    }

    closesocket(hServerSocket);
    WSACleanup();

    return 0;
}

int calculate(int opnum, int opnds[], char operator)
{
    int result = opnds[0], i;

    switch(operator)
    {
        case '+':
            for (i = 1; i < opnum; ++i) result += opnds[i];
            break;
        case '-':
            for (i = 1; i < opnum; ++i) result -= opnds[i];
            break;
        case '*':
            for (i = 1; i < opnum; ++i) result *= opnds[i];
            break;
        default:
            break;
    }
    return result;
}

void ErrorHandling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);

    exit(1);
}