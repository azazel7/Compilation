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

gazl: flex_scanner.c bison_grammar.c Function.o
	$(CC) $(OPTION) $? -o $@ $(LINK) $(DEBUGFLAG) $(WARNINGFLAG)

lex_scanner.c: flex_scanner.l
	flex -o flex_scanner.c flex_scanner.l

bison_grammar.c: bison_grammar.y
	bison --defines=bison_grammar.h --output=bison_grammar.c bison_grammar.y

%.o : %.cpp
	$(CC) $(OPTION) -c $< -o $@ $(DEBUGFLAG) $(WARNINGFLAG)

clean:
	rm -f flex_scanner.c bison_grammar.c *.o

