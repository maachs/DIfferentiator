all: differentiator

flags = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

differentiator: main.o Constructor.o Dump.o Diff.o ReadExpression.o Simplifier.o
	g++ main.o Constructor.o Dump.o Diff.o ReadExpression.o Simplifier.o

main.o: ./src/main.cpp
	g++ -I ./include/ -c $(flags) ./src/main.cpp

Constructor.o: ./src/Constructor.cpp
	g++ -I ./include/ -c $(flags) ./src/Constructor.cpp

Dump.o: ./src/Dump.cpp
	g++ -I ./include/ -c $(flags) ./src/Dump.cpp

Diff.o: ./src/Diff.cpp
	g++ -I ./include/ -c $(flags) ./src/Diff.cpp

ReadExpression.o: ./src/ReadExpression.cpp
	g++ -I ./include/ -c $(flags) ./src/ReadExpression.cpp

Simplifier.o: ./src/Simplifier.cpp
	g++ -I ./include/ -c $(flags) ./src/Simplifier.cpp

clean:
	rm -rf *.o *.exe
