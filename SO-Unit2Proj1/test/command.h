/**
 * @file 	command.h
 * @brief 	Arquivo responsável fazer o a criação do struct Command
 * 			e a declaração das funções referentes a essa struct.
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	30.10.2017
 * @data 	
 * @sa 		process.h
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
using std::string;

#include "process.h"

enum Command {
	stop = 0,
	kill = 1,
	start = 2
};

/**
 * @fn 		void verifyCommand (Command command, Process process);
 * @brief	Function that do the system calls according with the command
 * @param 	command 	The command
 * @param	process 	The process
 */
void verifyCommand (Command command, Process process);

#endif