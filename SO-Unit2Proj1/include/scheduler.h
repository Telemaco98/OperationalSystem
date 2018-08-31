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

#include <queue>
using std::queue;

#include "process.h"

/** @enum SchedulerType */
enum class SchedulerType{
	NORMAL = 0, /** < Fair share scheduling */ 
	FIFO,	/** < First in, first out */
	RR 		/** < Round robin */
};

/** @enum Command */
enum Command {
	NONE = 0, /** < Comando zero (faz nada) */
	STOP, /** < Comando dezenove (para um processo) */
	KILL, /** < Comando nove (mata um processo) */
	START /** < Comando dezoito (inicia um processo) */
};

/**
 * @class Scheduler
 */
class Scheduler {
	private: 
		SchedulerType schedulerType; 	/** < Tipo do escalonador **/
		queue<Process*> *processes;		/** < Fila de processos **/
		int quantum;					/** < Quantum **/
		
		/** @brief Executa um processo */
		int execute(Process *process);
	
		void executeNormal();

	public:
		/** @brief Construtor do escalonador */
		Scheduler(SchedulerType st);

		/** @brief Fuçao que recupera a estrutura dentro do escalonador. */
		Process* getProcess (int id);

		/** @brief Muda o tipo de escalonador usado para um dos tipos específicos (NORMAL, FIFO e RR). */
		void setSchedulerType(SchedulerType type);

		/** @brief Controlador de processos */
		int processController (Command command, Process *process);

		/** @brief Adiciona um processo à fila **/
		void addProcess (Process *process);

		/** @brief Executa o escalonador **/
		void execute ();

		/** @brief Cria um novo processo **/
		Process* newProcess();
		
		/** @brief Verifica se há processo **/
		bool haveProcess();
};

#endif