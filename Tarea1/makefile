CC=g++
STD=-std=c++17
CFLAGS=-Wall
INC_PATH=-I"./libs/"
SRC=$(shell find src -name "*.cpp")
LFLAGS=-L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3
EXEC=intro

# Regla para compilar el proyecto
build:
	$(CC) $(CFLAGS) $(STD) $(INC_PATH) $(SRC) $(LFLAGS) -o $(EXEC)

# Regla para ejecutar el proyecto
run:
	./$(EXEC)

# Regla para limpiar los archivos generados
clean:
	rm $(EXEC)
