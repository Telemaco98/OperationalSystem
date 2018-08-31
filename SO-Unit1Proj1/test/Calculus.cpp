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
 * @fn 		float desvioPadrao(float *vetorTempo, int n)
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
