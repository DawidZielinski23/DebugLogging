DEBUG LOGGING

Debug logging module made by Dawid Zielinski.

The library has functions which allow to collect logs from the code.
The module creates debug file which name contains the date and hour when the program was run.
There are 4 levels of logs:
- Information,
- Warning,
- Error,
- Critical
The user could adjust which logs are seen in the file by calling SetGlobalDebugLevel() function
with proper level value in range from 1 to 15.
The debug file is open by OpenDebugFile() fuction and closed by CloseDebugFile() function.
WriteDebugLog() function write an entry to debug file.
The library has macros with special usage:
- LOG_FUNCTION_NAME(s) - to put entry with information that given function started,
- LOG_FUNCTION_END(s) - to put entry with information that given function ended.