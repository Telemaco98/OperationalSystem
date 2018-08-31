/**
 * @file 	scheduler.cpp
 * @brief 	
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	08.10.2017
 * @data 	
 */

#ifndef _PROCESSO_H_
#define _PROCESSO_H_

class Process {
	private:
		void (*func)(void*); /*funçao a ser executada em forma de processo*/	
		int id; /*id do processo criado*/	
		int priority; /*prioridade do processo que vai ser criado*/
		int quantum; /*quantum calculado pela política de escalonamento atual*/

	public:
		Process(void (*f)(void*), int identifier, int p, int q);

		int getID();
		int getPriority();
		int getQuantum();

		void setFunction(void (*f)(void*));
		void setID(int identifier);
		void setPriority(int p);
		void setQuantum(int q);
};


#endif