#ifndef DEBUG_LOGGING_H
#define DEBUG_LOGGING_H

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdarg.h>
#include<time.h>
#include<windows.h>

#define STATIC static

typedef FILE DEBUG_LOG_FILE;
typedef uint8_t DEBUG_LOG_LEVEL;
typedef char CHAR;
typedef int INT;

#define BIT(_i) 1u<<_i

#define WRITE_FILE "w"
#define MAX_DEBUG_LOG_LEVEL 0xF
#define NUMBER_OF_LEVELS 4
#define LEVEL_STRING_SIZE 10
#define DEBUG_FILE_NAME_LENGTH 30
#define MAX_DEBUG_LOG_SIZE 1024

#define DEBUG_LOGGING_INFO_LEVEL     BIT(0)
#define DEBUG_LOGGING_WARNING_LEVEL  BIT(1)
#define DEBUG_LOGGING_ERROR_LEVEL    BIT(2)
#define DEBUG_LOGGING_CRITICAL_LEVEL BIT(3)

#define LOG_FUNCTION_NAME WriteDebugLog(DEBUG_LOGGING_INFO_LEVEL, "Function %s", __func__)

VOID OpenDebugFile();

VOID CloseDebugFile();

VOID SetGlobalDebugLevel(DEBUG_LOG_LEVEL Level);

VOID WriteDebugLog(DEBUG_LOG_LEVEL Level, const CHAR* Input, ...);

#endif /*DEBUG_LOGGING_H*/