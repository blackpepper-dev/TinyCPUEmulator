#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

struct AppLogger
{

    enum LogType 
    {
        Success = 1,
        Error = 2,
        Warning = 3,
        Info = 4,
        Debug = 5,
        Other = 6
    };

    //Text colors
    const char* COLOR_RESET   = "\033[0m";
    const char* COLOR_BLACK   = "\033[30m";
    const char* COLOR_RED     = "\033[31m";
    const char* COLOR_GREEN   = "\033[32m";
    const char* COLOR_YELLOW  = "\033[33m";
    const char* COLOR_BLUE    = "\033[34m";
    const char* COLOR_MAGENTA = "\033[35m";
    const char* COLOR_CYAN    = "\033[36m";
    const char* COLOR_WHITE   = "\033[37m";

    //Background colors
    const char* BG_BLACK      = "\033[40m";
    const char* BG_RED        = "\033[41m";
    const char* BG_GREEN      = "\033[42m";
    const char* BG_YELLOW     = "\033[43m";
    const char* BG_BLUE       = "\033[44m";
    const char* BG_MAGENTA    = "\033[45m";
    const char* BG_CYAN       = "\033[46m";
    const char* BG_WHITE      = "\033[47m";


    //Test styles
    const char* STYLE_BOLD      =  "\033[1m";
    const char* STYLE_UNDERLINE =  "\033[4m";
    const char* STYLE_INVERT    =  "\033[7m";

    const int MAX_LOG_FILE_SIZE = 3200;

    std::string LogName;
    std::ofstream LogFile;


    bool LogToConsole = false;
    bool LogToFile = false;

    std::string getDateTime() const 
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm* local = std::localtime(&time);

        std::ostringstream oss;
        oss << std::put_time(local, "[%d-%m-%Y %H:%M:%S]");

        return oss.str();
    };

    int CreateLogDir()
    {
        #ifdef _WIN32
            if (CreateDirectoryA("Logs", NULL))
                return 1;
            DWORD err = GetLastError();
            if (err == ERROR_ALREADY_EXISTS)
                return 2;
            return 0;
        #else
            if (mkdir("Logs", 0777) == 0)
                return 1;
            if (errno == EEXIST)
                return 2;
            return 0;
        #endif
    }
    
    void Init();
    void Dispose();
    void Log(LogType type, const std::string& msg) ;
    void LogInfo(const std::string& msg) ;
    void LogWarning(const std::string& msg) ;
    void LogError(const std::string& msg) ;
    void LogDebug(const std::string& msg) ;
    void LogOther(const std::string& msg) ;
};

extern AppLogger Logger;
