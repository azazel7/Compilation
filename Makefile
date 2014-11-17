#SRCDIR=src/
#OBJDIR=obj/
#EXEC=gazl

CC=g++
DEBUGFLAG=-O2 -Os 
LINK=
OPTION=-std=c++11
WARNINGFLAG=

ifeq ($(DEBUG),1)
DEBUGFLAG=-g3 -O0
endif

ifeq ($(WARNING),1)
WARNINGFLAG=-Wall -Wextra
endif
FILE=flex_scanner.o bison_grammar.o 

gazl: $(FILE) 
	$(CC) $(OPTION) $(FILE) -o $@ $(LINK) $(DEBUGFLAG) $(WARNINGFLAG)

flex_scanner.o: flex_scanner.l bison_grammar.o
	flex -o flex_scanner.cpp flex_scanner.l
	g++ flex_scanner.cpp -c -o flex_scanner.o

bison_grammar.o: bison_grammar.y
	bison --defines=bison_grammar.h --output=bison_grammar.cpp bison_grammar.y
	g++ bison_grammar.cpp -c -o bison_grammar.o

%.o : %.cpp
	$(CC) $(OPTION) -c $< -o $@ $(DEBUGFLAG) $(WARNINGFLAG)

clean:
	rm -f flex_scanner.cpp bison_grammar.cpp *.o $(EXEC)

