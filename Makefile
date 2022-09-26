CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = main.o canvas.o toolbox.o verify.o gameplay.o terminal.o random.o
EXEC = escape

ifdef BORDERLESS
CFLAGS += -D BORDERLESS
BORDERLESS : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c canvas.h toolbox.h verify.h gameplay.h random.h
	$(CC) -c main.c $(CFLAGS)

canvas.o : canvas.c canvas.h
	$(CC) -c canvas.c $(CFLAGS)

toolbox.o : toolbox.c toolbox.h canvas.h
	$(CC) -c toolbox.c $(CFLAGS)

verify.o : verify.c verify.h gameplay.h canvas.h toolbox.h
	$(CC) -c verify.c $(CFLAGS)

gameplay.o : gameplay.c gameplay.h terminal.h verify.h canvas.h random.h toolbox.h
	$(CC) -c gameplay.c $(CFLAGS)

terminal.o : terminal.c terminal.h
	$(CC) -c terminal.c $(CFLAGS)

random.o : random.c random.h
	$(CC) -c random.c $(CFLAGS)

clean :
	rm -f $(EXEC) $(OBJ)

# make clean <- will always run (will never prompt "make: 'clean' up to date") 
# since there will be no file called "clean" be made as a result of this operation

#
# How to use Makefile
# -------------------
# make <- will look for the default file named Makefile, build the first target
# make Makefile <- can explicitely define the name of the Makefile
# 
# How to use Makefile to build targets individually
# --------------------------------------------------
# make <target>
# make escape <- build the target "escape"
# make main.o <- build the target "main.o" 
# make canvas.o <- build the target "canvas.o"
# make toolbox.o <- build the target "toolbox.o"
# make verify.o <- build the target "verify.o"
# make gameplay.o <- build the target "gameplay.o"
# make terminal.o <- build the target "terminal.o"
# make clean <- build the target "clean"
