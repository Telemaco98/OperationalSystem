# Makefile, separando os diferentes elementos da aplicacao
# como codigo (src), cabecalhos (include), executaveis (build), bibliotecas (lib), etc.
# Cada elemento e alocado em uma pasta especifica, organizando melhor seu codigo fonte.
#
# Algumas variaveis sao usadas com significado especial:
#
# $@ nome do alvo (target)
# $^ lista com os nomes de todos os pre-requisitos sem duplicatas
# $< nome do primeiro pre-requisito
#

# Comandos do sistema operacional
# Linux: rm -rf 
# Windows: cmd //C del 
RM = rm -rf 

# Compilador
CC=g++ 

# Variaveis para os subdiretorios
LIB_DIR=./lib
INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./build
BIN_DIR=./bin
DOC_DIR=./doc
TEST_DIR=./test
DAT_DIR=./data
IMG_DIR=./images

# Opcoes de compilacao
CFLAGS=-Wall -pedantic -ansi -std=c++11 -I. -I$(INC_DIR)

# Garante que os alvos desta lista nao sejam confundidos com arquivos de mesmo nome
.PHONY: all clean doxy debug doc

# Define o alvo (target) para a compilacao completa.
# Ao final da compilacao, remove os arquivos objeto.
all: init Projeto1SO
debug: CFLAGS += -g -O0
debug: Projeto1SO



# Alvo (target) para a criaço da estrutura de diretorios
# necessaria para a geracao dos arquivos objeto 
init: 

	@mkdir -p $(BIN_DIR)/
	@mkdir -p $(OBJ_DIR)/

# Alvo (target) para a construcao do executavel
# Define os arquivos main.o, vector.o, sort.o, mod.o e busca.o como dependencias
Projeto1SO: $(OBJ_DIR)/Main.o $(OBJ_DIR)/Calculus.o $(OBJ_DIR)/Archive.o $(OBJ_DIR)/ShMem.o

	@echo "============="
	@echo "Ligando o alvo $@"
	@echo "============="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executavel 'Projeto1SO' criado em $(BIN_DIR)] +++"
	@echo "============="


# Alvo (target) para a construcao do objeto Main.o
# Define os arquivos Main.cpp, Calculus.cpp e Calculus.h como dependencias.
$(OBJ_DIR)/Main.o: $(SRC_DIR)/Main.cpp $(SRC_DIR)/Calculus.cpp $(INC_DIR)/Calculus.h
	$(CC) -c $(CFLAGS) -o $@ $<	

# Alvo (target) para a construcao do objeto Calculus.o
# Define os arquivos calculaTempo.cpp, vector.cpp, sort.cpp, busca.cpp, calculaTempo.h, vector.h, sort.h, busca.h como dependencias.
$(OBJ_DIR)/Calculus.o: $(SRC_DIR)/Calculus.cpp $(SRC_DIR)/Archive.cpp $(INC_DIR)/Calculus.h $(INC_DIR)/Archive.h $(INC_DIR)/SharedMem.h
	$(CC) -c $(CFLAGS) -o $@ $<	

# Alvo (target) para a construcao do objeto Archive.o
# Define os arquivos Archive.cpp e Archive.h, como dependencias.
$(OBJ_DIR)/Archive.o: $(SRC_DIR)/Archive.cpp $(INC_DIR)/Archive.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto Archive.o
# Define os arquivos Archive.cpp e Archive.h, como dependencias.
$(OBJ_DIR)/ShMem.o: $(SRC_DIR)/SharedMem.cpp $(INC_DIR)/SharedMem.h
	$(CC) -c $(CFLAGS) -o $@ $<

gnuplot: 
	$(RM) $(IMG_DIR)/*
	@gnuplot -e "filename='$(DAT_DIR)/output/tempos.dat'" $(DAT_DIR)/output/settingsArchive.gnuplot

doxy:
	$(RM) $(DOC_DIR)/*

	doxygen -g

doc:

	doxygen

# Alvo (target) usado para limpar os arquivos temporarios (objeto)
# gerados durante a compilacao, assim como os arquivos binarios/executaveis.
clean:
	$(RM) $(BIN_DIR)/* 
	$(RM) $(OBJ_DIR)/*
	$(RM) $(DOC_DIR)/*
	$(RM) $(IMG_DIR)/*	
