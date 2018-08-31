/**
 * @file 	Calculus.h
 * @brief   Arquivo para fazer os calculos referentes à avaliação empíricas 
 * 			dos algorítmos de multiplicação de matrizes usando processos e 
 * 			normalmente
 * 			
 * @author 	Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @since  	09/09/2017
 * @date   	12/09/2017
 * @sa 		Multiplica.h
 * @sa 	   	Archive.h
 */

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>
using std::string;

#include <fstream>
using std::ofstream;
using std::ios;

#include <chrono>
#include <ctime> 
#include <cmath>

#include "Multiplica.h"
#include "Archive.h"

/**
 * @fn 		float desvioPadrao(float *vetorTempo, int n)
 * @brief 	Responsável por calcular e retornar o desvio padrão do tempo
 * @param 	vetorTempo 	float* 	- Vetor de com os tempos
 * @param 	n			int 	- Número inteiro com a quantidade de elementos do vetor
 * @return 	desvioP
 */
float desvioPadrao(float *vetorTempo, int n);

/**
 * @fn 	  void calcularTempo (T **matrizA, T **matrizB, int linA, int colAlinB, int colB)
 * @brief Função para calcular a média de tempos para fazer a multiplicação de matrizes 
 * 				de tamanho 'n' utilizando processos e sem utilizá-los.
 *
 * @param matrizA   	T** 	- A matriz a
 * @param matrizB   	T** 	- A matriz b
 * @param n				int 	- Dimensão nxn das matrizes
 * @param nomeArquivo	String	- Nome do arquivo de saída
 */
template <typename T>
void calcularTempo (T **matrizA, T **matrizB, int n, string nomeArquivo) {
	float *vComProcesso = new float[20];
	float *vSemProcesso = new float[20];
	int *aux = &n;

	int **matrizC; 
	for(int i = 0; i < 20; i++) {	
		std::chrono::time_point<std::chrono::system_clock> start, end;
		std::chrono::duration<float> elapsed_seconds;

		start = std::chrono::system_clock::now();
		matrizC = multiplica<T>(matrizA, matrizB, aux, aux, aux);
		end = std::chrono::system_clock::now();
		elapsed_seconds = end-start;
		vComProcesso[i] = elapsed_seconds;


		start = std::chrono::system_clock::now();
		matrizC = multiplicaSemProcesso<T>(matrizA, matrizB, aux, aux, aux);
		end = std::chrono::system_clock::now();
		elapsed_seconds = end-start;
		vComProcesso[i] = elapsed_seconds;
	}

	for(int i = 0; i < n; i++)  delete matrizC[i];
	delete [] matrizC;
	
	float d1 =  desvioPadrao(vComProcesso, 20);
	float d2 = desvioPadrao(vComProcesso, 20);

	ofstream saida;
	saida.open(nomeArquivo.c_str(), ios::app);
	saida << d1 << " " << d2 << endl;
	saida.close();
}
