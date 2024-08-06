#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include "errors.hpp"
#pragma comment(lib, "Ws2_32.lib")

// TODO: Añadir limpieza y to eso (WSACleanup y liberar variables)


SOCKET connect_to_client(u_short port_name){
    int r = 0;
    SOCKET listening_socket = INVALID_SOCKET;
    SOCKET victim_socket = INVALID_SOCKET;
    WSADATA init;

    if (WSAStartup(MAKEWORD(2, 2), &init) != 0) error("WSA no se inicio correctamente", WSAGetLastError());
    struct sockaddr_in  address_inf;
    ZeroMemory(&address_inf, sizeof(address_inf));
    address_inf.sin_family = AF_INET;
    address_inf.sin_addr.S_un.S_addr = INADDR_ANY;
    address_inf.sin_port = htons(port_name);
    


    listening_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listening_socket == INVALID_SOCKET) error("no se pudo conectar al socket listener", WSAGetLastError());

    r = bind(listening_socket, (sockaddr*)(&address_inf), sizeof(address_inf));
    if (r == SOCKET_ERROR) error("no se pudo conectar el listener con la ip", WSAGetLastError());


    r = listen(listening_socket, SOMAXCONN);
    if (r == SOCKET_ERROR) error("no se pudo escuchar en el socket listener", WSAGetLastError());
    
    victim_socket = accept(listening_socket, NULL, NULL);
    if (victim_socket == INVALID_SOCKET) error("no se pudo conectar al socket de la victima", WSAGetLastError());
    
    closesocket(listening_socket);
    std::cout << "To bien " << victim_socket << std::endl;
    return victim_socket;
}