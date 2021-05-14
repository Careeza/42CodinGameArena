NAME	= arena

SRCS	= arena.cpp simulation.cpp

PL_CPP = $(wildcard compilePlayer/*.cpp)
PL_OBJ = $(wildcard playerObject/*.o)

PL_NEW_OBJ = $(patsubst compilePlayer/%.cpp, playerObject/%.o, $(PL_CPP))
PL_EXEC = $(patsubst playerObject/%.o, player/%, $(PL_OBJ))

CC		= clang++

CFLAGS	= -Ofast -std=c++11

OBJS	= ${SRCS:.cpp=.o}

.cpp.o:
	${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

player/%: playerObject/%.o
		${CC} ${CFLAGS} -arch x86_64 -o $@ $<

playerObject/%.o: compilePlayer/%.cpp 
		${CC} ${CFLAGS} -c -arch x86_64 -o $@ $<

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all: ${PL_NEW_OBJ} ${PL_EXEC} ${NAME}


clean:
	rm -rf ${PL_EXEC}
	rm -rf ${OBJS}

fclean:	clean
	rm -rf ${NAME}

re: 	fclean all
