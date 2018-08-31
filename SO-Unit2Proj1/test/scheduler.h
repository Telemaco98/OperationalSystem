/**
 * @file 	scheduler.h
 * @brief 	Arquivo para criar a classe Scheduler que representa o escalonador.
 * 			O campo necessário para construir um objeto Scheduler é: schedulerType, 
 * 			o qual define qual tipo de escalonador ele representa.
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	08.10.2017
 * @data 	
 * @sa 		process.h
 */

#ifndef _ESCALONADOR_H_
#define _ESCALONADOR_H_

#include "process.h"

enum class SchedulerType{
	NORMAL, 
	FIFO,	//First in, first out
	RR 		//Round Robin
};

/**
 * @class Scheduler
 */
class Scheduler {
	private: 
		SchedulerType schedulerType; 	/** < Tipo do escalonador **/
	public:
		/** @brief Construtor do escalonador */
		Scheduler(SchedulerType st);

		/** @brief Fuçao que inicializa uma tarefa (processo) específica. */
		int startProcess (Process *process);

		/** @brief Fuçao que recupera a estrutura dentro do escalonador. */
		Process* getProcess (int id);

		/** @brief Muda o tipo de escalonador usado para um dos tipos específicos (NORMAL, FIFO e RR). */
		int setSchedulerType(SchedulerType type);
};

#endif