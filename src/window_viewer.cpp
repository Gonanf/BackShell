#include <iostream>
#include "connections.hpp"
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define port 23112
unsigned int frame_number = 0;


bool try_to_get_image(std::vector<char> buffer)
{

    int width, height, channels;
    unsigned char* img_data = stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(buffer.data()), buffer.size(), &width, &height, &channels, 0);
    if (!img_data)
    {
        std::cout << "FALLADO" << std::endl;
        return false;
    }
    std::ofstream file;
    std::string path = "image" + std::to_string(frame_number++) +".jpg";
    stbi_write_png(path.c_str(), width, height, channels, img_data, 0);

    std::cout << width << "/" << height << std::endl;

    stbi_image_free(img_data);
    return true;
}

bool get_header(int socket, std::uint64_t *var)
{

    size_t offset = 0;
    char *buffer = reinterpret_cast<char *>(var);
    while (true)
    {
        int r = recv(socket, buffer + offset, sizeof(var) - offset, 0);
        std::cout << r << std::endl;
        if (r < 0)
        {
            if (errno == EINTR)
                continue;
            else
                error("no se pudo leer", WSAGetLastError());
        }
        else if (r == 0)
        {
            error("se corto la conexion", WSAGetLastError());
        }
        else if (offset + r == sizeof(var))
        {
            return true;
        }
        offset += r;
    }
    return false;
}

int main()
{
    std::cout << "############################\n";
    std::cout << "##      WINDOW VIEWER     ##\n";
    std::cout << "############################\n";
    SOCKET victim = connect_to_client(port);
    int r = 0;
    while (true)
    {
        size_t size;
        char size_buffer[8];
        if (recv(victim, size_buffer, 8, MSG_WAITALL) < 0)
        {
            error("no se pudo obtener el header", WSAGetLastError());
        };
        memcpy(&size, size_buffer, 8);
        std::cout << "SIZE: " << size << std::endl;
        std::vector<char> buffer(size);
        r = recv(victim, buffer.data(), buffer.size(), MSG_WAITALL);
        if (r < 0)
        {
            error("no se pudo obtener la imagen", WSAGetLastError());
        }
        if (!try_to_get_image(buffer))
        {
            error("no se pudo interpretar los datos", -1);
        }
    }

    return 0;
}
