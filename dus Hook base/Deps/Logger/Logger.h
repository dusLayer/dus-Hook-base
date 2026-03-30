#pragma once
#include <string>
#include <vector>
#include <mutex>

class Logger
{
public:
    Logger(const std::string& filename = "");
    ~Logger();

    void info(const std::string& msg);
    void error(const std::string& msg);
    void debug(const std::string& msg);
    void debug_fmt(const char* fmt, ...);

    const std::vector<std::string>& getLogs() const { return logs; }
    void clearLogs() { logs.clear(); }

private:
    void write(const std::string& prefix, const std::string& msg);

    std::mutex mtx;
    std::vector<std::string> logs;
};