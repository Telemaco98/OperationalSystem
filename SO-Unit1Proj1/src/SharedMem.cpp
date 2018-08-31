#include <cstdlib>
using std::system;

#include <string>
using std::string;
using std::to_string;

#include "SharedMem.h"

void deleteMem(key_t key){
	system(("ipcrm -M "+to_string(key)).c_str());
}


//FIXME remover todas as memorias compartilhadas identificadas pelas keys com IPC_RMID (ISSO NAO ESTA FUNCIONANDO!)
void deleteSharedMem(int *lin){
	key_t key=20* (*lin);
	key_t starter = key;
	for(int i=0; i<*lin; i++){
		key++; //Key deve ser incrementado para que cada linha da matriz seja referenciada por uma chave unica
		deleteMem(key);
	}
	deleteMem(starter);
}