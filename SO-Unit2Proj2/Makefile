# Alvo (target) para a construção do executável mdc
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
RM = rm -rf 

# Compilador
CC=g++ 

# Variaveis para os subdiretorios
LIB_DIR=./lib
SRC_DIR=./src
OBJ_DIR=./build
BIN_DIR=./bin
DOC_DIR=./doc
TEST_DIR=./test
INC_DIR=./include

# Opcoes de compilacao
CFLAGS=-Wall -pedantic -ansi -std=c++11 -I. -I$(INC_DIR)

# Garante que os alvos desta lista nao sejam confundidos com arquivos de mesmo nome
.PHONY: all clean doxy debug doc

# Define o alvo (target) para a compilacao completa.
# Ao final da compilacao, remove os arquivos objeto.
all: client server
debug: CFLAGS += -g -O0
debug: client server

#-----------------------------------------------------------------------------------------------------------------------------
# Alvo (target) para a construcao do executavel
# Define os arquivos clientMain.o, ManageImage.o, File.o Image.o e menu.o como dependencias
client: $(OBJ_DIR)/clientMain.o $(OBJ_DIR)/ManageImage.o $(OBJ_DIR)/File.o $(OBJ_DIR)/Image.o $(OBJ_DIR)/menu.o
	@echo "======================="
	@echo "Ligando o alvo $@"
	@echo "======================="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executavel 'client' criado em $(BIN_DIR)/] +++"
	@echo "======================="

# Alvo (target) para a construcao do objeto client.o
$(OBJ_DIR)/clientMain.o: $(SRC_DIR)/clientMain.cpp $(INC_DIR)/client.h $(INC_DIR)/menu.h $(INC_DIR)/File.h $(INC_DIR)/Image.h $(INC_DIR)/ManageImage.h $(INC_DIR)/sockets.h
	$(CC) -c $(CFLAGS) -o $@ $<	
	
# Alvo (target) para a construcao do objeto ManageImage.o
$(OBJ_DIR)/ManageImage.o: $(SRC_DIR)/ManageImage.cpp $(INC_DIR)/ManageImage.h $(INC_DIR)/Image.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto ManageImage.o
$(OBJ_DIR)/File.o: $(SRC_DIR)/File.cpp $(INC_DIR)/File.h $(INC_DIR)/Image.h
	$(CC) -c $(CFLAGS) -o $@ $<	
	
# Alvo (target) para a construcao do objeto Image.o
$(OBJ_DIR)/Image.o: $(SRC_DIR)/Image.cpp $(INC_DIR)/Image.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto menu.o
$(OBJ_DIR)/menu.o: $(SRC_DIR)/menu.cpp $(INC_DIR)/menu.h
	$(CC) -c $(CFLAGS) -o $@ $<

#--------------------------------------------------------------------------------------

# Define os arquivos calcula.o main.o como dependencias
server: $(OBJ_DIR)/serverMain.o $(OBJ_DIR)/ManageImage.o $(OBJ_DIR)/File.o $(OBJ_DIR)/Image.o $(OBJ_DIR)/menu.o
	@echo "=================="
	@echo "Ligando o alvo $@"
	@echo "=================="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executável 'server' criado em $(BIN_DIR)/] +++"
	@echo "=================="

# Alvo (target) para a constração do objeto funcao.o
$(OBJ_DIR)/serverMain.o: $(SRC_DIR)/serverMain.cpp $(INC_DIR)/server.h $(INC_DIR)/ManageImage.h $(INC_DIR)/File.h $(INC_DIR)/Image.h $(INC_DIR)/menu.h $(INC_DIR)/sockets.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto ManageImage.o
$(OBJ_DIR)/ManageImage.o: $(SRC_DIR)/ManageImage.cpp $(INC_DIR)/ManageImage.h $(INC_DIR)/Image.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto ManageImage.o
$(OBJ_DIR)/File.o: $(SRC_DIR)/File.cpp $(INC_DIR)/File.h $(INC_DIR)/Image.h
	$(CC) -c $(CFLAGS) -o $@ $<	
	
# Alvo (target) para a construcao do objeto Image.o
$(OBJ_DIR)/Image.o: $(SRC_DIR)/Image.cpp $(INC_DIR)/Image.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto menu.o
$(OBJ_DIR)/menu.o: $(SRC_DIR)/menu.cpp $(INC_DIR)/menu.h
	$(CC) -c $(CFLAGS) -o $@ $<

#--------------------------------------------------------------------------------------

# Alvo (target) para a geração automatica de documentacao usando o Doxygen.
# Sempre remove a documentacao anterior (caso exista) e gera uma nova.
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