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

#include <stdexcept>
using std::exception;

#include <list>
using std::list;

#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
#include <cstdio>

#include "scheduler.h"
#include "process.h"

/**
 * @brief Construtor do escalonador
 * @param st O tipo de escalonamento do escalonador (FIFO, NORMAL, RR)
 */
Scheduler::Scheduler(SchedulerType st) {
	schedulerType = st;
	processes = new queue<Process*>();
}

/**
 * @brief Funçao que recupera a estrutura dentro do escalonador.
 * @param id O identificador da task desejada
 * @return uma referencia para a estrutura Process em caso de sucesso, NULL em caso de falha.
 */
Process* Scheduler::getProcess (int id) {

	return new Process("./bin/program");
}

/**
 * @brief Muda o tipo de escalonador usado para um dos tipos específicos (NORMAL, FIFO e RR).
 * @param type O tipo do escalonador desejado.
 */
void Scheduler::setSchedulerType(SchedulerType type) {
	schedulerType = type;
}

/**
* @brief Prepara e/ou executa um processo
* @param *process Apontador para o processo que será executado
*/
int Scheduler::execute(Process *process){
	bool startFlag = false;
	int status=-1;
	
	int pid = process->getID();
	if(pid == -1) {
		pid = process->execute(); 
	}
	else {
		startFlag = true;
	}

	int cont=0;
	int quantum = process->getQuantum();
	
	while(cont<quantum or quantum==-1){ //aqui será o tempo do quantum
		if(startFlag){
			processController(Command::START, process);
		}
		if(quantum != -1) cont++;
		if(processController(Command::NONE, process)<0) break;
		sleep(1); 
	} 
	
	processController(Command::STOP, process);//caso o quantum seja alcançado, pararemos o processo e daremos continuidade a outro
	waitpid(pid,&status,WSTOPPED or WEXITED or WCONTINUED); //esperamos pelo processo filho caso ele tenha finalizado, encerrado, parado, etc. existem várias flags
	cout << "\tPID do processo " << process->getProcess() << " eh " << process->getID() << endl; //pid do filho para usos futuros
	
	if(processController(Command::NONE, process)<0) return -1;
	else return pid;
}

/**
* @brief Controlador de processos, tem poder para executar, verificar, parar, matar, etc. um processo
* @param command O sinal que deverá ser enviado ao processo 
* @param *process Apontador para o processo
* @return Retorna -1 em caso de falha, 0 em casos de sucesso
*/
int Scheduler::processController (Command command, Process *process) {
	try {
		switch(command) {
			case Command::NONE:
				return kill(process->getID(), 0);

			case Command::KILL:
				return kill(process->getID(), 9);

			case Command::START:
				return kill(process->getID(), 18);

			case Command::STOP:
				return kill(process->getID(), 19);
		}
	} catch (exception e){
		cout << "Houve um erro ao enviar comandos para o processo. Nada a ser feito!" << endl;
	}
	return -1;
}

/** 
 * @brief Adiciona um processo à fila 
 * @param process 	O processo para adicionar à fila 
 */
void Scheduler::addProcess (Process *process) {
	processes->push(process);
}

/**
 * @brief Executa o escalonador 
 */
void Scheduler::execute () {
	// TODO Administração dos processos de acordo com a política de escalonamento
	
	switch(schedulerType){
		case SchedulerType::FIFO:
			if(!processes->empty()){
				processes->front()->setQuantum(-1);
				cout << "\tProcessando " << processes->front()->getProcess() 
					 << " ate o fim de sua execucao segundo a politica atual (FIFO)"<< endl;
				execute(processes->front());
				cout << "\tExecucao de " << processes->front()->getProcess() << " finalizada" << endl;
				processes->pop();
			}
			break;

		case SchedulerType::NORMAL:			
			executeNormal();
			break;

		case SchedulerType::RR:
			int num = processes->size();
			cout << "\tExistem " << num  << " processos para executar no momento " << endl;
			for(int i = 0; i<num; i++){
				processes->front()->setQuantum((num/processes->size())*2);
				cout << "\tProcessando " << processes->front()->getProcess() 
					 << " por " << processes->front()->getQuantum() 
					 << " segundos, de acordo com a politica atual (RR)" << endl;
				int pid = execute(processes->front());
				if(pid == -1) {
					cout << "\tExecucao de " << processes->front()->getProcess() << " finalizada" << endl;
					processes->pop();
				} else {
					processes->push(processes->front());
					processes->pop();
				}
				cout << endl;
			}
			break;
	}
}

bool Scheduler::haveProcess(){
	return !processes->empty();
}

/**
 * @brief 	Cria um novo processo
 * @return 	Um Processo
 */
Process* Scheduler::newProcess(){
	return new Process("./bin/program");
}

/** 
 * @brief 	Funcão para compara qual processo é maior que outro
 * @return 	true/false 
 */
bool compare(Process *p1, Process *p2) {
	/* Prioridades recebem valores entre 0 e 127 (quanto menor o valor numérico maior a prioridade) */
	if(p1->getPriority() < p2->getPriority()) return true;
	else return false;
}

/**
 * @brief Executa os processos de acordo com a política escalonamento normal 
 */
void Scheduler::executeNormal() {
	list<Process*> listaP;
	while (!processes->empty()) {
		Process *p = processes->front();
		listaP.push_back(p);
		processes->pop();
	}
	listaP.sort(compare);

	cout << "\tExistem " << listaP.size()  << " processos para executar no momento \n" << endl;
	while (!listaP.empty()) {
		Process *p = listaP.front();
		listaP.pop_front();
		p->setQuantum(11 - p->getPriority());
		cout << "\tProcessando " << p->getProcess() 
			 << " por " << p->getQuantum() 
			 << " segundos, de acordo com a politica atual (NORMAL)" << endl;
		cout << "\tPrioridade: " << p->getPriority() << endl;
		int pid = execute(p);
		if(pid == -1) {
			cout << "\tExecucao de " << p->getProcess() << " finalizada\n" << endl;
		} else {
			listaP.push_back(p);
		}
		cout << endl;
	}
}