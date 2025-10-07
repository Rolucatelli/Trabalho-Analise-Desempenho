# Nome do projeto
PROJ_NAME=heuristicas_3-partition

# Nome do arquivo de Debug
DEBUG_NAME=heuristicas_3-partition_debug

# Arquivos .c
C_SOURCE=$(wildcard ./src/*.c) $(wildcard ./src/algoritmos/*.c) $(wildcard ./src/estruturas/*.c)

# Arquivos .h
H_SOURCE=$(wildcard ./hdr/*.h) $(wildcard ./hdr/algoritmos/*.h) $(wildcard ./hdr/estruturas/*.h)

# Arquivos objeto
OBJ=$(subst .c,.o,$(subst src,objects,$(C_SOURCE) ./objects/main.c))

# Compilador
CC=gcc

# Flags (opções) para o compilador
CC_FLAGS=-c -W -Wall -pedantic

# Comando utilizado como target do clean
RM=rm -f

#########################
# Compilação e linkagem #
#########################
all: objFolder exeFolder $(PROJ_NAME)
debug: objFolder exeFolder $(DEBUG_NAME)

run: all
	@ ./exe/${PROJ_NAME}

$(DEBUG_NAME): $(OBJ)
	@ echo 'Construindo arquivo de Debug usando o linker GCC: $@'
	$(CC) $^ -o ./exe/$@ -g
	@ echo 'Arquivo de Debug pronto!: $@'
	@ echo ' '

$(PROJ_NAME): $(OBJ)
	@ echo 'Construindo o binário usando o linker GCC: $@'
	$(CC) $^ -o ./exe/$@
	@ echo 'Binário pronto: $@'
	@ echo ' '

./objects/%.o: ./src/%.c ./hdr/%.h
	@ echo 'Construindo target usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./objects/main.o: ./main/main.c $(H_SOURCE)
	@ echo 'Construindo target usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p objects

exeFolder:
	@ mkdir -p exe

clean:
	@ $(RM) ./objects/* ./exe/* *~


.PHONY: all clean debug run
# Se existir algum arquivo com o mesmo nome que uma tag, como clean.c ou all.c, ele ignora