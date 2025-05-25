# Definir el compilador, por defecto usará g++ pero se cambiará a clang++ para MSan
CC=g++
STD=-std=c++17
CFLAGS=-Wall
INC_PATH=-I"./libs/"
SRC=$(shell find src -name "*.cpp")
LFLAGS=-L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3
EXEC=game_engine.exe

# Regla para compilar el proyecto sin ASan o MSan
build:
	$(CC) $(CFLAGS) $(STD) $(INC_PATH) $(SRC) $(LFLAGS) -o $(EXEC)

# Regla para ejecutar el proyecto
run:
	./$(EXEC)

# Regla para limpiar los archivos generados
clean:
	rm $(EXEC)

# Regla para compilar con AddressSanitizer (ASan)
asan:
	$(CC) $(CFLAGS) -fsanitize=address $(STD) $(INC_PATH) $(SRC) $(LFLAGS) -o $(EXEC)

# Regla para compilar con MemorySanitizer (MSan), usando clang++ en lugar de g++
msan:
	make; valgrind --leak-check=full ./$(EXEC)
