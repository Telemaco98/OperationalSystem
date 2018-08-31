/**
 * @file 	menu.h
 * @brief 	Arquivo responsável por declarar a classe que representa um processo.
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	02.11.2017
 * @data 	
 */

#ifndef _PROCESSO_H_
#define _PROCESSO_H_

#include <string>
using std::string;

/**
 * @class Scheduler
 */
class Process {
	private:
		string toProcess; /** < Arquivo que deve ser executado em forma de processo **/	
		int pid; /** < ID do processo criado **/	
		int priority; /** < Prioridade do processo criado **/
		int quantum; /** < Quantum calculado pela política de escalonamento atual do escalonador **/

	public:
		/** @brief Construtor do processo */
		Process(string functionName);

		/** @brief Método de acesso ao processo */
		string getProcess();
		
		/** @brief Método de acesso ao PID */
		int getID();

		/** @brief Método de acesso à prioridade */
		int getPriority();

		/** @brief Método de acesso ao quantum de execução */
		int getQuantum();

		/** @brief Método modificador do processo */
		void setProcess(string f);

		/** @brief Método modificador do PID */
		void setID(int identifier);

		/** @brief Método modificador da prioridade */
		void setPriority(int p);

		/** @brief Método modificador do quantum */
		void setQuantum(int q);

		/** @brief Prepara o processo para a execução */
		int execute();

	private:
		/** @brief Cria o processo no sistema e retorna seu PID */
		string exec(const char* cmd);
};

#endif