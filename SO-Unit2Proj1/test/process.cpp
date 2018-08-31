/**
 * @file 	process.cpp
 * @brief 	
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	08.10.2017
 * @data 	
 * @sa 		process.h
 */

#include "process.h"

Process::Process(void (*f)(void*), int identifier, int p, int q){
	setFunction(*f);
	setID(identifier);
	setPriority(p);
	setQuantum(q);
}

int Process::getID(){
	return id;
}

int Process::getPriority(){
	return priority;
}

int Process::getQuantum(){
	return quantum;
}

void Process::setFunction(void (*f)(void*)){
	func = f;
}

void Process::setID(int identifier){
	id = identifier;
}

void Process::setPriority(int p){
	priority = p;
}

void Process::setQuantum(int q){
	quantum = q;
}