# Nome do projeto
PROJ_NAME_P1=simulacao_filas_p1
PROJ_FILE_P1=./main/parte1.c

PROJ_NAME_P2=simulacao_filas_p2
PROJ_FILE_P2=./main/parte2.c

# Projeto que será executado com o run
PROJ_NAME=$(PROJ_NAME_P2)

# Nome do arquivo de Debug
DEBUG_NAME=$(PROJ_NAME)_debug

# Arquivos .c
C_SOURCE=$(wildcard ./src/*.c)

# Arquivos .h
H_SOURCE=$(wildcard ./hdr/*.h)

# Arquivos objeto
OBJ=$(subst .c,.o,$(subst src,objects,$(C_SOURCE)))

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
	@ ./exe/$(PROJ_NAME) relatorio_95.csv 0.5 0.1295

test: all
	@ ./exe/$(PROJ_NAME) relatorio_80.csv 0.5 0.1091
	@ ./exe/$(PROJ_NAME) relatorio_90.csv 0.5 0.1227
	@ ./exe/$(PROJ_NAME) relatorio_95.csv 0.5 0.1295
	@ ./exe/$(PROJ_NAME) relatorio_99_9.csv 0.5 0.1362


$(DEBUG_NAME): $(OBJ)
	@ echo 'Construindo arquivo de Debug usando o linker GCC: $@'
	$(CC) $^ -o ./exe/$@ -g
	@ echo 'Arquivo de Debug pronto!: $@'
	@ echo ' '

$(PROJ_NAME_P1): $(OBJ)
	@ echo 'Construindo o binário usando o linker GCC: $@'
	$(CC) $(PROJ_FILE_P1) $^ -o ./exe/$@ -lm
	@ echo 'Binário pronto: $@'
	@ echo ' '

$(PROJ_NAME_P2): $(OBJ)
	@ echo 'Construindo o binário usando o linker GCC: $@'
	$(CC) $(PROJ_FILE_P2) $^ -o ./exe/$@ -lm
	@ echo 'Binário pronto: $@'
	@ echo ' '

./objects/%.o: ./src/%.c ./hdr/%.h
	@ echo 'Construindo target usando o compilador GCC: $<'
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