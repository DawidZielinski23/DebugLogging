TARGET = debug_logging.a

$(TARGET): debug_logging.o
	@ar rcs $@ $^
	@del $^

debug_logging.o: debug_logging.c debug_logging.h
	@gcc -c $< -o $@
 
clean:
	@del -f *.o *.a
