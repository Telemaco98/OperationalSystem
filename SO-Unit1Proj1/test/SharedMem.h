#ifndef _SHARED_MEM_H_
#define _SHARED_MEM_H_

#include <iostream>
using std::cout;
using std::endl;

//Para memoria compartilhada
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

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

template <typename T>
T* sharedMem(int tam, key_t key){
	int shmid = createShMem<T>(tam, key);
	return attachShMem<T>(shmid);
}

/*
template <typename T>
T** alocarMatriz(int *lin, int *col){
	T **matriz = new T*[*lin]; 
	for(int i = 0; i < *lin; i++){
		matriz[i] = new T[*col];
	}
	return matriz;
}
*/

/*
	keys usadas:
	1, 10, 100, 50(2x2), 200(16x16), 1024(1024x1024)
*/

template <typename T>
//FIXME remover todas as memorias compartilhadas identificadas pelas keys com IPC_RMID (ISSO NAO ESTA FUNCIONANDO!)
T** alocarMatrizComShMEM(int *lin, int *col){
	T **matriz;
	key_t key = 200;
	matriz = sharedMem<T*>(*lin, key);
	for(int i=0; i<*lin; i++){
		key++; //Key deve ser incrementado para que cada linha da matriz seja referenciada por uma chave unica
		matriz[i] = sharedMem<T>(*col, key);
	}
	return matriz;
}

#endif