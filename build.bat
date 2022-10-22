@if exist debug_logging.a (
    @del debug_logging.a
)
@if exist debug_logging.o (
    @del debug_logging.o
)
@gcc -o debug_logging.o -c  debug_logging.c
@ar rcs debug_logging.a debug_logging.o
@del *.o