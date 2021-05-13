NAME	= arena

SRCS	= arena.cpp simulation.cpp

PL_OBJ = $(wildcard playerObject/*.o)

PL_EXEC = $(patsubst playerObject/%.o, player/%, $(PL_OBJ))

CC		= clang++

CFLAGS	= -Ofast -std=c++11

OBJS	= ${SRCS:.cpp=.o}

.cpp.o:
	${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

player/%: playerObject/%.o
		${CC} ${CFLAGS} -o $@ $<

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:	${NAME} ${PL_EXEC}

clean:
	rm -rf ${PL_EXEC}
	rm -rf ${OBJS}

fclean:	clean
	rm -rf ${NAME}

re: 	fclean all
