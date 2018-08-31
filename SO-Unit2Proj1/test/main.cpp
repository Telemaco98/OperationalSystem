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

#include "scheduler.h"
#include "menu.h"

int main(){
	cout << "Oi!" << endl;

	SchedulerType s = SchedulerType::NORMAL;

	Scheduler *e = new Scheduler(s);
	Process* foo;
	foo = e->getProcess(1);
	cout << "Testando escalonador e processo: ID do processo criado: " << foo->getID() << endl;
	int choose;
	do{
		choose = menu();
		switch(choose){
			case 1:
				cout << "Escolheu 1" << endl;
			break;
			case 2:
				cout << "Escolheur 2" << endl;
			break;
			case 3:
				cout << "Escolheur 3" << endl;
			break;
		}
	}while(choose!=0);

	return 0;
}