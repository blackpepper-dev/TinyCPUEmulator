#include "include/Logger.h"


AppLogger Logger;

void AppLogger::Init()
{

    if(LogToFile)
    {
        int directory = CreateLogDir();
        if( directory == 0)
            LogError("Error init, can't create Logs directory!");
        
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm* local = std::localtime(&time);

        std::ostringstream oss;
        oss << std::put_time(local, "%d-%m-%Y");   
        
        LogName = oss.str().append(".txt");   

        LogFile.open("Logs/" + LogName, std::ios::out | std::ios::app);

        if(!LogFile.is_open())
            LogError("Error while oppening log file!");
    }

}

void AppLogger::Dispose()
{
    LogFile.close();
}

void AppLogger::LogInfo(const std::string &msg) 
{
    Log(LogType::Info,msg);
}

void AppLogger::LogWarning(const std::string &msg) 
{
    Log(LogType::Warning,msg);
}

void AppLogger::LogError(const std::string &msg) 
{
    Log(LogType::Error,msg);
}

void AppLogger::LogDebug(const std::string& msg) 
{
    Log(LogType::Debug,msg);
}
void AppLogger::LogOther(const std::string& msg) 
{
    Log(LogType::Other,msg);
}

void AppLogger::Log(LogType type, const std::string& msg)
{
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return;
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    #endif

    if (!LogFile.is_open() && LogToFile) {
        std::cerr << "[LOGGER ERROR] Log file is not open!" << std::endl;
        return;
    }

    if (LogFile.tellp() > MAX_LOG_FILE_SIZE) {
        Dispose();
        Init();
    }

    //Form message
    std::ostringstream oss;
    oss << getDateTime();

    std::string colorStart, colorEnd = COLOR_RESET;
    std::string tag;

    switch (type) {
        case Success: colorStart = COLOR_GREEN; tag = "[SUCCESS]"; break;
        case Warning: colorStart = COLOR_YELLOW; tag = "[WARNING]"; break;
        case Error:   colorStart = COLOR_RED;    tag = "[ERROR]";   break;
        case Info:    colorStart = COLOR_CYAN;   tag = "[INFO]";    break;
        case Debug:   colorStart = std::string(BG_WHITE) + COLOR_MAGENTA; tag = "[DEBUG]"; break;
        case Other:   colorStart = COLOR_BLUE;   tag = "[OTHER]";   break;
        default:      colorStart = std::string(BG_WHITE) + STYLE_UNDERLINE + COLOR_BLACK; tag = "[UNKNOWN] Invalid log level"; break;
    }

    oss << tag << " " << msg;

    //Output
    if (LogToConsole)
        std::cout << colorStart << oss.str() << colorEnd << std::endl;

    if (LogToFile)
        LogFile << oss.str() << std::endl;
}

