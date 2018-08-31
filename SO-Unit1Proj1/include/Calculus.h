#ifndef CALCULUS_H
#define CALCULUS_H

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
using std::to_string;

#include <fstream>
using std::ofstream;
using std::ios;

#include <chrono>
using namespace std::chrono;

#include <ctime> 
#include <cmath>

#include "Multiplica.h"
#include "Archive.h"
#include "SharedMem.h"

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

	T **matrizC;
	
	for(int i = 0; i < 20; i++) {	

		auto start_timeProc = high_resolution_clock::now();
		matrizC = multiplica<T>(matrizA, matrizB, aux, aux, aux); //ComProcesso
		auto end_timeProc = high_resolution_clock::now();
		vComProcesso[i] = duration_cast<microseconds>(end_timeProc - start_timeProc).count();

		deleteSharedMem(aux);

		auto start_timeNoProc = high_resolution_clock::now();
		matrizC = multiplicaSemProcesso<T>(matrizA, matrizB, aux, aux, aux);
		auto end_timeNoProc = high_resolution_clock::now();
		vSemProcesso[i] = duration_cast<microseconds>(end_timeNoProc - start_timeNoProc).count();
		
		//cout << "Debug " << i << " proc=" << vComProcesso[i] << " noProc=" << vSemProcesso[i] << " ms" << endl;
	}

	string way = "./data/output/";
	string nameOutput = way + "C" + to_string(*aux) + "x" + to_string(*aux) + ".txt"; 
	storeData<T>(nameOutput, aux, aux, matrizC);

	for(int i = 0; i < n; i++)  delete matrizC[i];
	delete [] matrizC;

	ofstream saida;
	saida.open(nomeArquivo.c_str(), ios::app);
	saida << n << " " << desvioPadrao(vComProcesso, 20) << " " << desvioPadrao(vSemProcesso, 20) << endl;
	saida.close();
}

/**
 * @fn 		void analiseEmpirica ()
 * @brief   Função para fazer a análise empírica entre os algoritmos de multiplicação
 *  			de matrizes. As matrizes em análizes são as de dimensões: 1x1, 2x2, 3x3,
 *  			4x4, 5x5, 6x6, 8x8, 10x10, 20x20, 30x30, 40x40, 50x50, 75x75 e 100x100
 */
void analiseEmpirica ();

#endif