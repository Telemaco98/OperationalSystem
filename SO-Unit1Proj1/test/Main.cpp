#include <iostream>
using std::cout;
using std::endl;

//Para comunicacao entre processos
#include <unistd.h>

#include "Archive.h"
#include "Multiplica.h"
#include "SharedMem.h"

int main (int argc, char * argv[]){
	outArchives("A"); // chama para criar as matrizes
	outArchives("B"); // chama para criar as matrizes
	cout << "Ola, estou de volta a essa lingua maravilhosa!" << endl;

	int *linA = new int[1], *colA = new int[1];
	int *linB = new int[1], *colB = new int[1];

	//int **matrizA = loadData<int>("../data/input/A16x16.txt", linA, colA);
	//int **matrizB = loadData<int>("../data/input/B16x16.txt", linB, colB);

	//imprimirMatriz(matrizA, linA, colA);
	//cout << endl;
	//imprimirMatriz(matrizB, linB, colB);
	cout << endl;
	//int linha = *lin;

	//FIXME Colocar condicional para colA e linB
	//int **matrizC = multiplica<T>(matrizA, matrizB, linA, linB, colB);

	//imprimirMatriz(matrizC, linA, colB);
	//cout << endl;
/*
	int *mC;
	key_t key = 10;
	
	mC = sharedMem<int>(10, key);


	//Teste de fork, processos e memoria compartilhada
	cout << "Sou o pai com o pid " << getpid() << ", se eu morrer os outros morrem\n" ;
	int originalProcess = getpid();
	fork();
	cout << "Sou o processo de pid " << getpid() << endl;

	if(getpid()==originalProcess){
		//cout << "Teste SHM: ";
		for (int i=0; i<10; i++){
			mC[i]=0;
			
		}
	//cout << endl;
	}
	else {
		sleep(2);
		cout << "SharedMem = [ ";
		for (int i=0; i<10; i++){
			cout << mC[i] << " ";
		}
		cout << "]"<< endl;
		return 0;
	}
	
	sleep(3);
	*/
	// System("ipcrm -m <num>");
	// shmctl(key, IPC_RMID, NULL);
	// shmctl(50, IPC_RMID, NULL);
	
	
	return 0;
}

/*TODO
- POO ou PEP?
- Ler duas matrizes pela linha de comando (Try/Cathc too)
- Ler duas matrizes por leitura de arquivo
- Ver checagem do tamanho das matrizes para a multiplicação (Try/catch too)
- Criar função para multiplicar matrizes usando processos
- Criar memoria compartilhada para armazenar as matrizes
- Criar função para imprimir na tela ou no arquivo
- Criar menu de interação? (y)
*/ 