/**
 * @file 	scheduler.cpp
 * @brief 	Arquivo responsável por implementar os métodos da classe Scheduler
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	08.10.2017
 * @data 	
 * @sa 		scheduler.h
 * @sa 		process.h
 */

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include "scheduler.h"
#include "process.h"

void foo(void *){
	cout << "Do nothing" << endl;
}

/**
 * @brief Construtor do escalonador
 */
Scheduler::Scheduler(SchedulerType st){
	schedulerType = st;
}

/*
 * @brief Fuçao que inicializa uma tarefa (processo) específica.
 * @param task_ a tarefa a ser executada.
 * @return 0 em caso de sucesso, -1 em caso de falha.
 */
int Scheduler::startProcess (Process *process) {
	
	return 0;
}

/*
 * @brief Fuçao que recupera a estrutura dentro do escalonador.
 * @param id identificador da task desejada
 * @return uma referencia para a estrutura task em caso de sucesso, NULL em caso de falha.
 */
Process* Scheduler::getProcess (int id) {

	return new Process(&foo, 2, 2, 2);
}

/*
 * @brief Muda o tipo de escalonador usado para um dos tipos específicos (NORMAL, FIFO e RR).
 * @param sheduler tipo do escalonador desejado.
 * @return 0 em caso de sucesso, -1 em caso de falha.
 */
int Scheduler::setSchedulerType(SchedulerType type) {
	schedulerType = type;
	if(schedulerType == type) return 0;
	else return -1;
}