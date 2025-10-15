# Nome do projeto
PROJ_NAME=simulacao_filas_menor

# Nome do arquivo de Debug
DEBUG_NAME=$(PROJ_NAME)_debug

# Arquivos .c
C_SOURCE=$(wildcard ./src/*.c)

# Arquivos .h
H_SOURCE=$(wildcard ./hdr/*.h)

# Arquivos objeto
OBJ=$(subst .c,.o,$(subst src,objects,$(C_SOURCE) ./objects/main.c))

# Compilador
CC=gcc

# Flags (opções) para o compilador
CC_FLAGS=-c -W -Wall -pedantic

# Comando utilizado como target do clean
RM=rm -rf

#########################
# Compilação e linkagem #
#########################
all: objFolder exeFolder $(PROJ_NAME)
debug: objFolder exeFolder $(DEBUG_NAME)

run: all
	@ clear
	@ ./exe/${PROJ_NAME} relatorio_80.csv 0.5 0.15

$(DEBUG_NAME): $(OBJ)
	@ echo 'Construindo arquivo de Debug usando o linker GCC: $@'
	$(CC) $^ -o ./exe/$@ -g
	@ echo 'Arquivo de Debug pronto!: $@'
	@ echo ' '

$(PROJ_NAME): $(OBJ)
	@ echo 'Construindo o binário usando o linker GCC: $@'
	$(CC) $^ -o ./exe/$@ -lm
	@ echo 'Binário pronto: $@'
	@ echo ' '

./objects/%.o: ./src/%.c ./hdr/%.h
	@ echo 'Construindo target usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./objects/main.o: ./main/main.c $(H_SOURCE)
	@ echo 'Construindo main usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p objects

exeFolder:
	@ mkdir -p exe exe/relatorios

clean:
	@ $(RM) ./objects ./exe *~


.PHONY: all clean debug run
# Se existir algum arquivo com o mesmo nome que uma tag, como clean.c ou all.c, ele ignora