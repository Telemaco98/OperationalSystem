/**
 * @file 	main.cpp
 * @brief 	
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	08.10.2017
 * @data 	
 * @sa 		scheduler.h
 * @sa 		menu.h
 */

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <ctime>

#include "scheduler.h"
#include "menu.h"

int main() {
	srand(time(NULL));
	Scheduler *e = new Scheduler(SchedulerType::FIFO);
	
	int choose;
	do{
		choose = menu();
		Process* foo;
		switch(choose){
			case 1:
				foo = e->newProcess();
				cout << "\tCriando novo processo: " << foo->getProcess() << endl;
				e->addProcess(foo);
				break;
			case 2:
				if(e->haveProcess()){
					cout << "\tProcessando mais uma rodada" << endl;
					cout << "---------------------------------------------------------------------------------"<< endl;
					e->execute();
					cout << "---------------------------------------------------------------------------------"<< endl;
					cout << "\tRodada de processos finalizada!" << endl;
				} else {
					cout << "\tNenhum processo executando no momento!" << endl;
				}
				break;
			case 3:
				int change = mudarPolitica();
				if(change>=0){
					SchedulerType politica = (SchedulerType) change;
					e->setSchedulerType(politica);
					cout << "\tMudanca realizada com sucesso! " << endl;
				} else {
					cout << "\tNenhuma mudanca foi realizada!" << endl;
				}
				break;
		}
	}while(choose!=0);

	return 0;
}


// política normal: ESQUECI
// política FIFO: executa todos os processos em ordem de chegada até o fim do programa
// política Round Robin: executa os programas com o tempo predetermiando