#include "Logger.h"
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <stdarg.h>

Logger::Logger(const std::string&) {}

Logger::~Logger() {}

void Logger::write(const std::string& prefix, const std::string& msg) {
    std::lock_guard<std::mutex> lock(mtx);
    std::string full = prefix + msg;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (prefix == "[+] ") SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    else if (prefix == "[-] ") SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    else if (prefix == "[>] ") SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    std::cout << full << std::endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    logs.push_back(full);
}

void Logger::info(const std::string& msg) {
    write("[+] ", msg);
}

void Logger::error(const std::string& msg) {
    write("[-] ", msg);
}

void Logger::debug(const std::string& msg) {
    write("[>] ", msg);
}

void Logger::debug_fmt(const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf_s(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    write("[>] ", buffer);
}