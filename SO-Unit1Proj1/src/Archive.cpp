#include <fstream>
using std::ofstream;

#include <cstring>
using std::to_string;
using std::string;

#include <cstdlib>
using std::srand;

#include <ctime>

#include "Archive.h"

void getLinhasEColunas(int* lin, int* col, ifstream* entrada){
	string aux;
	
	getline(*entrada, aux, ' ');
	*lin = atoi(aux.c_str());
	
	getline(*entrada, aux);
	*col = atoi(aux.c_str());
}

/**
 * @fn 		void cleanArchive(string nameArchive)
 * @brief 	Função para limpar o arquivo de saída
 * @param 	string nameArchive Nome do arquivo de saída
 * @return 	A função não irá retornar nada.
 */
void cleanArchive(string nameArchive){
	ofstream myFile;
	myFile.open(nameArchive.c_str());
	myFile.clear();
	myFile.close();
}

/**
 * @fn 		void outArchives (string lyric) 
 * @brief 	Função para gerar as matrizes de dimensões 1x1, 2x2, 3x3, 4x4,
 * 		5x5, 6x6, 8x8, 10x10, 20x20, 30x30, 40x40, 50x50, 75x75 e 100x100
 * 		randomicamente e colocalas em um arquivo.
 * @param 	string lyric
 */
void outArchives (string lyric) {
	cout << " Gerando arquivos de saída...." << endl;

	int size[14] = {1, 2, 3, 4, 5, 6, 8, 10, 20, 30, 40, 50, 75, 100};

	for(int i = 0; i < 14; i++){
		string way = "./data/input/", n = to_string(size[i]);
		string nameArchive = way + lyric + n + "x" + n + ".txt";
		ofstream saida; 
		saida.open(nameArchive.c_str());
		saida.clear();

		saida << size[i] << " " << size[i] << endl;


		for(int j = 0; j < size[i]; j++) {
			for(int k = 0; k < size[i]; k++) {
				int aux = rand() % (size[i]+ 1);// - ((int)size[i]/2);
				saida << aux << " ";
			}
			saida << endl;
		}
		saida.close();
	}
}