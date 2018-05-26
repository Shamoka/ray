EXEC = ray
IDIR = includes
CC = g++
CFLAGS = -Wall -Werror -ggdb -I$(IDIR)
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = sources/main.cpp			\
      sources/vec3f.cpp			\
      sources/color.cpp 		\
      sources/primitive.cpp 		\
      sources/ray.cpp 			\
      sources/sphere.cpp		\
      sources/plane.cpp 		\
      sources/cylindre.cpp 		\
      sources/simpleScene.cpp		\
      sources/rayTracer.cpp		\
      sources/light.cpp


OBJ = $(SRC:.cpp=.o)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(EXEC)

%.o:	%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(EXEC)

all:	$(EXEC)

re:	fclean all

.PHONY:	clean fclean re
