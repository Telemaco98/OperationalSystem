/**
 * @file 	command.cpp
 * @brief 	Arquivo responsável fazer o a criação do struct Command e analizá-lo
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	30.10.2017
 * @data 	
 * @sa 		process.h
 */

#include <sys/types.h>
#include <cstdlib>

#include "command.h"
#include "process.h"

/**
 * @fn 		void verifyCommand (Command command, Process process);
 * @brief	Function that do the system calls according with the command
 * @param 	command 	The command
 * @param	process 	The process
 */
void verifyCommand (Command command, Process process) {
	string c;
	switch(command) {
		case 0:
			c = "kill -19 -" + process.getID();
			System(c);
			break;

		case 1:
			c = "kill -9 -" + process.getID();
			System(c);
			break;

		case 2:
			c = "kill -18 -" + process.getID();
			System(c);
			break;
	}
}
// Sinal -18  = Continuar a execução, se interrompido
// Sinal -19 = para a 
// Sinal -9 = “mata” o processo, caso ele não respeite o que foi pedido pelo sinal 15 (anterior).