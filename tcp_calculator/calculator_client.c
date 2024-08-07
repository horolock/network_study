#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <WinSock2.h>

#define BUFFER_SIZE     1024
#define RLT_SIZE        4
#define OPSZ            4

void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET hSocket;
    char opmsg[BUFFER_SIZE];
    int result, operandCount, i;
    SOCKADDR_IN serverAddress;

    if (argc != 3)
    {
        printf("Usage: %s <IP> <port>\n", argv[0]);
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
    else
        puts("Connected ...... ");
    
    fputs("Operand count: ", stdout);
    scanf("%d", &operandCount);
    opmsg[0] = (char)operandCount;

    for (i = 0; i < operandCount; ++i)
    {
        printf("Operand %d: ", i + 1);
        scanf("%d", (int*)&opmsg[i * OPSZ + 1]);
    }

    fgetc(stdin);
    fputs("Operator: ", stdout);
    scanf("%c", &opmsg[operandCount * OPSZ + 1]);
    send(hSocket, opmsg, operandCount * OPSZ + 2, 0);
    recv(hSocket, &result, RLT_SIZE, 0);

    printf("Operation result: %d\n", result);
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