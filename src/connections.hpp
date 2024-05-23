#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include "errors.hpp"
#pragma comment(lib, "Ws2_32.lib")

// TODO: Añadir limpieza y to eso (WSACleanup y liberar variables)


SOCKET connect_to_client(char* port_name){
    int r = 0;
    SOCKET listening_socket = INVALID_SOCKET;
    SOCKET victim_socket = INVALID_SOCKET;
    WSADATA init;

    if (WSAStartup(MAKEWORD(2, 2), &init) != 0) error("WSA no se inicio correctamente", WSAGetLastError());
    struct addrinfo address_inf;
    ZeroMemory(&address_inf, sizeof(address_inf));
    address_inf.ai_protocol = IPPROTO_TCP;
    address_inf.ai_family = AF_INET;
    address_inf.ai_socktype = SOCK_STREAM;
    address_inf.ai_flags = AI_PASSIVE;
    struct addrinfo *result = NULL;

    r = getaddrinfo(NULL, port_name, &address_inf, &result);
    if (r != 0) error("no se pudo obtener la informacion de direccion del server", WSAGetLastError());

    listening_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listening_socket == INVALID_SOCKET) error("no se pudo conectar al socket listener", WSAGetLastError());

    r = bind(listening_socket, result->ai_addr, (int)result->ai_addrlen);
    if (r == SOCKET_ERROR) error("no se pudo conectar el listener con la ip", WSAGetLastError());

    freeaddrinfo(result);

    r = listen(listening_socket, SOMAXCONN);
    if (r == SOCKET_ERROR) error("no se pudo escuchar en el socket listener", WSAGetLastError());
    
    victim_socket = accept(listening_socket, NULL, NULL);
    if (victim_socket == INVALID_SOCKET) error("no se pudo conectar al socket de la victima", WSAGetLastError());
    
    closesocket(listening_socket);
    std::cout << "To bien " << victim_socket << std::endl;
    return victim_socket;
}