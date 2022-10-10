CC=g++
CCFLAG=-Wall -g -c
LDLIB=-I./utils/ -I./ui/

utils:
	$(CC)  $(CCFLAG) $(LDLIB) utils/constaint.cpp -o constaint.o

# all: utils.o 
	

clean:
	rm build/*.o 
# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile