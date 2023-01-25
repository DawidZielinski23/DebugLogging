#include"debug_logging.h"

static DEBUG_LOG_LEVEL Global_Level = 0;
static DEBUG_LOG_FILE* Global_DebugLogFileHandle = NULL;
static struct tm       Global_Date;
static bool            Global_DebugFileOpened = false;

char DebugLogLevelStrings[NUMBER_OF_LEVELS][LEVEL_STRING_SIZE] =
{
    "Info",
    "Warning",
    "Error",
    "Critical"
};

void OpenDebugFile()
{
    char Name[DEBUG_FILE_NAME_LENGTH];
    time_t Time = time(NULL);
    int Result;

    do
    {
        if(Global_DebugFileOpened == true)
        {
            break;
        }

        Global_Date = *localtime(&Time);

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

        Global_DebugLogFileHandle = fopen(Name, WRITE_FILE);
        if(Global_DebugLogFileHandle == NULL)
        {
            printf("Failed to open file");
        }
        else
        {
            Global_DebugFileOpened = true;
        }
    } while(0);
}

void CloseDebugFile()
{
    if((Global_DebugLogFileHandle != NULL) && (Global_DebugFileOpened == true))
    {
        fclose(Global_DebugLogFileHandle);
        Global_DebugLogFileHandle = NULL;
    }
}

void SetGlobalDebugLevel(DEBUG_LOG_LEVEL Level)
{
    if(Level > 0 && Level <= MAX_DEBUG_LOG_LEVEL)
    {
        Global_Level = Level;
    }
    else
    {
        Global_Level = 0;
    }
}

void WriteDebugLog(DEBUG_LOG_LEVEL Level, const char* Input, ...)
{
    char Log[MAX_DEBUG_LOG_SIZE] = {"\0"};
    time_t Time = time(NULL);
    struct tm Date = *localtime(&Time);
    int Index = 0;
    int Result = 0;
    va_list args;

    do
    {
        if(Input == NULL)
        {
            break;
        }

        if((Level != DEBUG_LOGGING_INFO_LEVEL)    &&
           (Level != DEBUG_LOGGING_WARNING_LEVEL) &&
           (Level != DEBUG_LOGGING_ERROR_LEVEL)   &&
           (Level != DEBUG_LOGGING_CRITICAL_LEVEL))
        {
            break;
        }

        if((Global_Level & Level) == 0)
        {
            break;
        }

        if(Global_DebugLogFileHandle == NULL)
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
            }
        }

        fprintf(Global_DebugLogFileHandle,
                "%02dh:%02dmin:%02ds; %10s; %s\n",
                Date.tm_hour - Global_Date.tm_hour,
                Date.tm_min - Global_Date.tm_min,
                Date.tm_sec - Global_Date.tm_sec,
                DebugLogLevelStrings[Index],
                Log);

        va_end(args);
    } while(0);
}

bool IsDebugLogFileOpen()
{
    return Global_DebugFileOpened;
}