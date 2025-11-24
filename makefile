# Nome do projeto
PROJ_NAME_P1=simulacao_filas_p1
PROJ_FILE_P1=./main/parte1.c

PROJ_NAME_P2=simulacao_filas_p2
PROJ_FILE_P2=./main/parte2.c

PROJ_NAME_P3=simulacao_filas_p3
PROJ_FILE_P3=./main/parte3.c

# Projeto que será executado com o run
PROJ_NAME=$(PROJ_NAME_P3)

# Nome do arquivo de Debug
DEBUG_NAME=$(PROJ_NAME)_debug

# Arquivos .c
C_SOURCE=$(wildcard ./src/*.c)

# Arquivos .h
H_SOURCE=$(wildcard ./hdr/*.h)

# Arquivos objeto
OBJ=$(subst .c,.o,$(subst src,objects,$(C_SOURCE)))

FLAG=${1..10}

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

simulate:
	@for i in $$(seq 1 50); do \
	    echo "Execução $$i"; \
	    $(MAKE) run1; \
	    $(MAKE) run2; \
	    $(MAKE) run3; \
	    mv "./exe/relatorios/Parte 1/relatorio_80.csv" "./exe/relatorios/Parte 1/relatorio_80__$$i.csv"; \
	    mv "./exe/relatorios/Parte 1/relatorio_90.csv" "./exe/relatorios/Parte 1/relatorio_90__$$i.csv"; \
	    mv "./exe/relatorios/Parte 1/relatorio_95.csv" "./exe/relatorios/Parte 1/relatorio_95__$$i.csv"; \
	    mv "./exe/relatorios/Parte 1/relatorio_99_9.csv" "./exe/relatorios/Parte 1/relatorio_99_9__$$i.csv"; \
	    mv "./exe/relatorios/Parte 2/relatorio_80.csv" "./exe/relatorios/Parte 2/relatorio_80__$$i.csv"; \
	    mv "./exe/relatorios/Parte 2/relatorio_90.csv" "./exe/relatorios/Parte 2/relatorio_90__$$i.csv"; \
	    mv "./exe/relatorios/Parte 2/relatorio_95.csv" "./exe/relatorios/Parte 2/relatorio_95__$$i.csv"; \
	    mv "./exe/relatorios/Parte 2/relatorio_99_9.csv" "./exe/relatorios/Parte 2/relatorio_99_9__$$i.csv"; \
	    mv "./exe/relatorios/Parte 3/relatorio_80.csv" "./exe/relatorios/Parte 3/relatorio_80__$$i.csv"; \
	    mv "./exe/relatorios/Parte 3/relatorio_90.csv" "./exe/relatorios/Parte 3/relatorio_90__$$i.csv"; \
	    mv "./exe/relatorios/Parte 3/relatorio_95.csv" "./exe/relatorios/Parte 3/relatorio_95__$$i.csv"; \
	    mv "./exe/relatorios/Parte 3/relatorio_99_9.csv" "./exe/relatorios/Parte 3/relatorio_99_9__$$i.csv"; \
	done; \
	\
	echo "Compactando relatórios por ocupação..."; \
	for parte in "Parte 1" "Parte 2" "Parte 3"; do \
	    cd "./exe/relatorios/$$parte" && \
        zip -j "relatorios_80.zip"    relatorio_80__*.csv; \
        zip -j "relatorios_90.zip"    relatorio_90__*.csv; \
        zip -j "relatorios_95.zip"    relatorio_95__*.csv; \
        zip -j "relatorios_99_9.zip"  relatorio_99_9__*.csv; \
		zip -j "relatorios_$$parte.zip" relatorios_*.zip; \
		\
		python3 ../../../gerar_medias.py "relatorios_$$parte.zip" .; \
		zip -j "relatorios_media_$$parte.zip" relatorios_*_media.csv; \
		\
        rm -f relatorio_80__*.csv; \
        rm -f relatorio_90__*.csv; \
        rm -f relatorio_95__*.csv; \
        rm -f relatorio_99_9__*.csv; \
		rm -f relatorios_80*; \
        rm -f relatorios_90*; \
        rm -f relatorios_95*; \
        rm -f relatorios_99_9*; \
        \
	    cd - >/dev/null; \
	done; \
	zip -j "./exe/relatorios/Relatorios.zip" ./exe/relatorios/Parte\ 1/relatorios*.zip ./exe/relatorios/Parte\ 2/relatorios*.zip ./exe/relatorios/Parte\ 3/relatorios*.zip


run1: objFolder exeFolder $(PROJ_NAME_P1)
	@ clear
	@ ./exe/$(PROJ_NAME_P1) Parte\ 1/relatorio_80.csv 0.5 0.1091
	@ ./exe/$(PROJ_NAME_P1) Parte\ 1/relatorio_90.csv 0.5 0.1227
	@ ./exe/$(PROJ_NAME_P1) Parte\ 1/relatorio_95.csv 0.5 0.1295
	@ ./exe/$(PROJ_NAME_P1) Parte\ 1/relatorio_99_9.csv 0.5 0.1362

run2: objFolder exeFolder $(PROJ_NAME_P2)
	@ clear
	@ ./exe/$(PROJ_NAME_P2) Parte\ 2/relatorio_80.csv 0.5 0.1091
	@ ./exe/$(PROJ_NAME_P2) Parte\ 2/relatorio_90.csv 0.5 0.1227
	@ ./exe/$(PROJ_NAME_P2) Parte\ 2/relatorio_95.csv 0.5 0.1295
	@ ./exe/$(PROJ_NAME_P2) Parte\ 2/relatorio_99_9.csv 0.5 0.1362

run3: objFolder exeFolder $(PROJ_NAME_P3)
	@ clear
	@ ./exe/$(PROJ_NAME_P3) Parte\ 3/relatorio_80.csv 0.5 0.1091
	@ ./exe/$(PROJ_NAME_P3) Parte\ 3/relatorio_90.csv 0.5 0.1227
	@ ./exe/$(PROJ_NAME_P3) Parte\ 3/relatorio_95.csv 0.5 0.1295
	@ ./exe/$(PROJ_NAME_P3) Parte\ 3/relatorio_99_9.csv 0.5 0.1362

run: objFolder exeFolder $(PROJ_NAME_P3)
	@ clear
# 	@ ./exe/$(PROJ_NAME_P3) Parte\ 3/relatorio_80.csv 0.5 0.1091
# 	@ ./exe/$(PROJ_NAME_P3) Parte\ 3/relatorio_90.csv 0.5 0.1227
# 	@ ./exe/$(PROJ_NAME_P3) Parte\ 3/relatorio_95.csv 0.5 0.1295
	@ ./exe/$(PROJ_NAME_P3) Parte\ 3/relatorio_99_9.csv 0.5 0.1362

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

$(PROJ_NAME_P3): $(OBJ)
	@ echo 'Construindo o binário usando o linker GCC: $@'
	$(CC) $(PROJ_FILE_P3) $^ -o ./exe/$@ -lm
	@ echo 'Binário pronto: $@'
	@ echo ' '

./objects/%.o: ./src/%.c ./hdr/%.h
	@ echo 'Construindo target usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p objects

exeFolder:
	@ mkdir -p exe exe/relatorios exe/relatorios/Parte\ 1 exe/relatorios/Parte\ 2 exe/relatorios/Parte\ 3

clean:
	@ $(RM) ./objects ./exe *~

.PHONY: all clean debug test run objFolder exeFolder
# Se existir algum arquivo com o mesmo nome que uma tag, como clean.c ou all.c, ele ignora