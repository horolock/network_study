#undef UNICODE
#undef _UNICODE

#include <stdio.h>
#include <WinSock2.h>

int main(int argc, char* argv[])
{
    char* strAddress = "203.211.218.102:9190";
    char strAddressBuffer[50];

    SOCKADDR_IN serverAddress;
    int size;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    size = sizeof(serverAddress);

    WSAStringToAddress(strAddress, AF_INET, NULL, (SOCKADDR*)&serverAddress, &size);

    size = sizeof(strAddressBuffer);

    WSAAddressToString((SOCKADDR*)&serverAddress, sizeof(serverAddress), NULL, strAddressBuffer, &size);

    printf("Second conv result: %s\n", strAddressBuffer);

    WSACleanup();

    return 0;
}