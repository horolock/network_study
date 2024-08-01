#include <stdio.h>
#include <string.h>
#include <WinSock2.h>

void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!");

    {
        char* address = "127.212.124.78";
        unsigned long conv_address = inet_addr(address);
        if (conv_address == INADDR_NONE)
            printf("Error occured!\n");
        else
            printf("Network ordered integer addr: %#1x\n", conv_address);
    }

    {
        struct sockaddr_in address;

        char* str;
        char strArr[20];

        address.sin_addr.s_addr = htonl(0x1020304);
        str = inet_ntoa(address.sin_addr);
        strcpy(strArr, str);

        printf("Dotted-Decimal notation3 %s\n", strArr);
    }

    WSACleanup();

    return 0;
}

void ErrorHandling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);

    exit(1);
}