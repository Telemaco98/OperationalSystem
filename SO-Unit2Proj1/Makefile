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
INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./build
BIN_DIR=./bin
DOC_DIR=./doc
TEST_DIR=./test

# Opcoes de compilacao
CFLAGS=-Wall -pedantic -ansi -std=c++11 -I. -I$(INC_DIR)

# Garante que os alvos desta lista nao sejam confundidos com arquivos de mesmo nome
.PHONY: all clean doxy debug doc

# Define o alvo (target) para a compilacao completa.
# Ao final da compilacao, remove os arquivos objeto.
all: init projeto3SO program
debug: CFLAGS += -g -O0
debug: projeto3SO



# Alvo (target) para a criaço da estrutura de diretorios
# necessaria para a geracao dos arquivos objeto 
init: 
	@mkdir -p $(BIN_DIR)/
	@mkdir -p $(OBJ_DIR)/

# Alvo (target) para a construcao do executavel
# Define os arquivos main.o, menu.o, process.o e scheduler.o como dependencias
projeto3SO: $(OBJ_DIR)/main.o $(OBJ_DIR)/menu.o $(OBJ_DIR)/process.o $(OBJ_DIR)/scheduler.o
	@echo "============="
	@echo "Ligando o alvo $@"
	@echo "============="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executavel 'projeto3SO' criado em $(BIN_DIR)] +++"
	@echo "============="

# Alvo (target) para a construcao do objeto Main.o
# Define os arquivos main.cpp, scheduler.cpp, scheduler.h, process.cpp, process.h, menu.cpp e menu.h como dependencias.
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/scheduler.cpp $(INC_DIR)/scheduler.h $(SRC_DIR)/process.cpp $(INC_DIR)/process.h $(SRC_DIR)/menu.cpp $(INC_DIR)/menu.h
	$(CC) -c $(CFLAGS) -o $@ $<	

# Alvo (target) para a construcao do objeto Calculus.o
# Define os arquivos menu.cpp e menu.h como dependencias.
$(OBJ_DIR)/menu.o: $(SRC_DIR)/menu.cpp $(INC_DIR)/menu.h 
	$(CC) -c $(CFLAGS) -o $@ $<	


# Alvo (target) para a construcao do objeto Calculus.o
# Define os arquivos process.cpp e process.h como dependencias.
$(OBJ_DIR)/process.o: $(SRC_DIR)/process.cpp $(INC_DIR)/process.h 
	$(CC) -c $(CFLAGS) -o $@ $<	

# Alvo (target) para a construcao do objeto Archive.o
# Define os arquivos scheduler.cpp, scheduler.h, process.cpp e process.h como dependencias.
$(OBJ_DIR)/scheduler.o: $(SRC_DIR)/scheduler.cpp $(INC_DIR)/scheduler.h $(SRC_DIR)/process.cpp $(INC_DIR)/process.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do executavel
# Define os arquivos program.o como dependencias
program: $(OBJ_DIR)/program.o 
	@echo "============="
	@echo "Ligando o alvo $@"
	@echo "============="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executavel 'program' criado em $(BIN_DIR)] +++"
	@echo "============="


# Alvo (target) para a construcao do objeto Main.o
# Define os arquivos program.cpp como dependencias.
$(OBJ_DIR)/program.o: $(SRC_DIR)/program.cpp
	$(CC) -c $(CFLAGS) -o $@ $<	

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