CXX = gcc
CXXFLAGS = -Wall -MMD

OBJECTS = main.o tictactoe.o board.o vector.o text-commands.o resize-string.o
EXEC = multi_dim_ttt

DEPENDS = ${OBJECTS}:.o=.d

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}