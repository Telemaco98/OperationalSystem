/**
 * @file 	main.cpp
 * @brief   Arquivo com a função pricaipal para fazer os calculos referentes à avaliação 
 * 			empíricas dos algorítmos de multiplicação de matrizes usando processos e 
 * 			normalmente
 * 			
 * @author 	Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @since  	09/09/2017
 * @date   	12/09/2017
 * @sa 	   	Calculus.h
 */

#include <iostream>
using std::cout;
using std::endl;

//Para comunicacao entre processos
#include <unistd.h>

#include <cstdlib>

#include "Calculus.h"

int main (int argc, char * argv[]){
	
	srand(time(NULL));
	outArchives("A"); // chama para criar as matrizes
	outArchives("B"); // chama para criar as matrizes

	cout << endl << "Iniciando análise empírica!" << endl;
	cout << "Cada multiplicação é realizada 20 vezes para reduzir oscilações de tempos através de um desvio padrão." << endl;
	cout << "Pode ser que não haja memória suficiente para as multiplicações de matrizes enormes, isso não afetará os dados gerados anteriomente" << endl;
	cout << "Ao final do processo, gere os gráficos digitando \'$ make gnuplot\' por linha de comando." <<endl;
	cout << "Por favor, espere até que as multiplicações finalizem." << endl << endl;
	
	analiseEmpirica();

	cout << endl << endl << "Digite \'$ make gnuplot\' no terminal para gerar os gráficos com os dados obtidos. " << endl;

	// System("ipcrm -m <num>");
	// shmctl(key, IPC_RMID, NULL);
	// shmctl(50, IPC_RMID, NULL);
	
	
	return 0;
}

/*TODO
- Ler duas matrizes pela linha de comando (Try/Cathc too)
- Ler duas matrizes por leitura de arquivo
- Ver checagem do tamanho das matrizes para a multiplicação (Try/catch too)
- Criar função para multiplicar matrizes usando processos
- Criar memoria compartilhada para armazenar as matrizes
- Criar função para imprimir na tela ou no arquivo
- Criar menu de interação? (y)
*/ 