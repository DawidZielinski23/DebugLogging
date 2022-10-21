#include"debug_logging.h"

STATIC DEBUG_LOG_LEVEL Global_Level = 0;
STATIC DEBUG_LOG_FILE* Global_DebugLofFileHandle = NULL;
struct tm Global_Date;


CHAR DebugLogLevelStrings[NUMBER_OF_LEVELS][LEVEL_STRING_SIZE] =
{
    "Info",
    "Warning",
    "Error",
    "Critical"
};

VOID OpenDebugFile()
{
    CHAR Name[DEBUG_FILE_NAME_LENGTH];
    time_t Time = time(NULL);
    Global_Date = *localtime(&Time);
    INT Result;

    do
    {
        Result = snprintf(Name,
                          DEBUG_FILE_NAME_LENGTH,
                          "debuglog_%02d_%02d-%02d_%02d.log",
                          Global_Date.tm_mday,
                          Global_Date.tm_mon + 1,
                          Global_Date.tm_hour,
                          Global_Date.tm_min);

        if(Result < 0)
        {
            printf("Failed to create debug file name");
            break;
        }

        Global_DebugLofFileHandle = fopen(Name, WRITE_FILE);
        if(Global_DebugLofFileHandle == NULL)
        {
            printf("Failed to open file");
        }
    } while(0);
}

VOID CloseDebugFile()
{
    if(Global_DebugLofFileHandle != NULL)
    {
        fclose(Global_DebugLofFileHandle);
    }
}

VOID SetGlobalDebugLevel(DEBUG_LOG_LEVEL Level)
{
    if(Level > 0 && Level < MAX_DEBUG_LOG_LEVEL)
    {
        Global_Level = Level;
    }
    else
    {
        Global_Level = 0;
    }
}

VOID WriteDebugLog(DEBUG_LOG_LEVEL Level, const CHAR* Input, ...)
{
    CHAR Log[MAX_DEBUG_LOG_SIZE] = {"\0"};
    time_t Time = time(NULL);
    struct tm Date = *localtime(&Time);
    INT Index = 0;
    INT Result = 0;
    va_list args;

    do
    {
        if(Input == NULL)
        {
            break;
        }

        if(Global_Level & Level == 0            &&
           Level != DEBUG_LOGGING_INFO_LEVEL    &&
           Level != DEBUG_LOGGING_WARNING_LEVEL &&
           Level != DEBUG_LOGGING_ERROR_LEVEL   &&
           Level != DEBUG_LOGGING_CRITICAL_LEVEL)
        {
            break;
        }

        if(Global_DebugLofFileHandle == NULL)
        {
            break;
        }

        va_start(args, Input);

        Result = vsprintf(Log, Input, args);

        if(Result < 0)
        {
            va_end(args);
            break;
        }

        for(Index = 0; Index < NUMBER_OF_LEVELS; Index++)
        {
            if(Level == BIT(Index))
            {
                break;
            };
        }
        printf("Index %d %s\n", Index, DebugLogLevelStrings[Index]);

        fprintf(Global_DebugLofFileHandle,
                "%02dh:%02dmin:%02ds; %10s; %s\n",
                Date.tm_hour - Global_Date.tm_hour,
                Date.tm_min - Global_Date.tm_min,
                Date.tm_sec - Global_Date.tm_sec,
                DebugLogLevelStrings[Index],
                Log);

        va_end(args);
    } while(0);
}
