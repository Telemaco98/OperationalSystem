/**
 * @file 	Calculus.cpp
 * @brief   Arquivo para fazer os calculos referentes à avaliação empíricas 
 * 			dos algorítmos de multiplicação de matrizes usando processos e 
 * 			normalmente
 * 			
 * @author 	Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @since  	09/09/2017
 * @date   	12/09/2017
 * @sa 	   	Calculus.h
 */

#include "Calculus.h"

/**
 * @fn 		float desvioPadrao(float *vetorTempo, int n
 * @brief 	Responsável por calcular e retornar o desvio padrão do tempo
 * @param 	vetorTempo 	float* 	- Vetor de com os tempos
 * @param 	n			int 	- Número inteiro com a quantidade de elementos do vetor
 * @return 	desvioP
 */
float desvioPadrao(float *vetorTempo, int n) {
 	float aux1, desvioP, media = 0;
	
	for(int ii = 0; ii < n; ii++){
		media += vetorTempo[ii];
	}
	
	media = media/n;
	
	for(int ii = 0; ii < n; ii++){
        aux1 = aux1 + pow(vetorTempo[ii] - media, 2);
    }

	desvioP = sqrt(( 1/ (float) n)*aux1);
	return desvioP;
}

/**
 * @fn 		void analiseEmpirica ()
 * @brief   Função para fazer a análise empírica entre os algoritmos de multiplicação
 *  			de matrizes. As matrizes em análizes são as de dimensões: 1x1, 2x2, 3x3,
 *  			4x4, 5x5, 6x6, 8x8, 10x10, 20x20, 30x30, 40x40, 50x50, 75x75 e 100x100
 */
void analiseEmpirica () {
	cout << " Fazendo os cálculos ... " << endl;
	string exitArchive = "./data/output/tempos.dat";

	cleanArchive(exitArchive);

	int size[14] = {1, 2, 3, 4, 5, 6, 8, 10, 20, 30, 40, 50, 75, 100};
	int *linA = new int[1], *colA = new int[1];
	int *linB = new int[1], *colB = new int[1];

	for(int i = 0; i < 14; i++){
		string way = "./data/input/", n = to_string(size[i]);
		
		string nameArchive = way + "A" + n + "x" + n + ".txt";
		int **matrizA = loadData<int>(nameArchive, linA, colA);

		nameArchive = way + "A" + n + "x" + n + ".txt";
		int **matrizB = loadData<int>(nameArchive, linB, colB);


		//chama a função que calcula o tempo
		calcularTempo(matrizA, matrizB, *linA, exitArchive);

		deleteMatriz<int>(matrizA, *linA);
		deleteMatriz<int>(matrizB, *linB);

		cout << " Cálculos para dimensão " << size[i] << "x" << size[i] << " efetuado com sucesso!" << endl;
	}

	delete [] linA;
	delete [] linB;
	delete [] colA;
	delete [] colB;

	cout << " ... Cálculos finalizados com sucesso!" << endl;
}