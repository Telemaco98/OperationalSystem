#ifndef _SHARED_MEM_H_
#define _SHARED_MEM_H_

#include <iostream>
using std::cout;
using std::endl;

//Para memoria compartilhada
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


/**
 * @fn 	  int createShMem(int tam, key_t key)
 * @brief Função para criar a memória compartilhada.
 *
 * @param tam   		int 	- O tamanho do bloco de memória que deve ser alocado
 * @param key   		key_t 	- A chave única para identificação da memória compatilhada
 * @return O shmid gerado pelo sistema operacional
 */
template <typename T>
int createShMem(int tam, key_t key){
	int shmid;
	if ((shmid = shmget(key, tam*sizeof(T), IPC_CREAT | 0666)) < 0) {
		perror("shmget");
		cout << "Erro ao criar memoria compartilhada! Saindo da execucao!" << endl;
		exit(1);
	}

	return shmid;
}


/**
 * @fn 	  T* attachShMem(int shmid)
 * @brief Função que anexa a memória compartilhada.
 *
 * @param shmid   		int 	- O identificador do bloco de memória compartilhada criada pelo sistema operacional
 * @return O bloco de memória gerado pelo sistema operacional
 */
template <typename T>
T* attachShMem(int shmid){
	T *shm;
	shm = (T*) shmat(shmid, NULL, 0);
	if (shm == (void*) -1) {
		perror("shmat");
		cout << "Erro ao anexar memoria compartilhada! Saindo da execucao!" << endl;
		exit(1);
	}
	return shm;
}

/**
 * @fn 	  T* sharedMem(int tam, key_t key)
 * @brief Função que invoca as funções de criação e anexo da memória compartilhada.
 *
 * @param tam   		int 	- O tamanho do bloco de memória que deve ser alocado
 * @param key   		key_t 	- A chave única para identificação da memória compatilhada
 * @return O bloco de memória gerado pelo sistema operacional
 */
template <typename T>
T* sharedMem(int tam, key_t key){
	int shmid = createShMem<T>(tam, key);
	return attachShMem<T>(shmid);
}


/**
 * @fn 	  T** alocarMatrizComShMEM(int *lin, int *col)
 * @brief Função que aloca memória compartilhada no formato de matriz.
 *
 * @param lin   		int* 	- A quantidade de linhas da matriz.
 * @param col   		int* 	- A quantidade de colunas da matriz.
 * @return O bloco de memória gerado pelo sistema operacional
 */
template <typename T>
T** alocarMatrizComShMEM(int *lin, int *col){
	T **matriz;
	key_t key=20* (*lin);

	matriz = sharedMem<T*>(*lin, key);
	for(int i=0; i<*lin; i++){
		key++; //Key deve ser incrementado para que cada linha da matriz seja referenciada por uma chave unica
		matriz[i] = sharedMem<T>(*col, key);
	}
	return matriz;
}


void deleteMem(key_t key);


//FIXME remover todas as memorias compartilhadas identificadas pelas keys com IPC_RMID (ISSO NAO ESTA FUNCIONANDO!)
void deleteSharedMem(int *lin);

#endif