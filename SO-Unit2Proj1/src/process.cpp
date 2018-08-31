/**
 * @file 	process.cpp
 * @brief 	Arquivo responsável por implementar os métodos da classe Process
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	02.11.2017
 * @data 	
 * @sa 		process.h
 */

#include <iostream>
	using std::cout;
	using std::endl;

#include <ctime>

#include <string>
	using std::string;
	using std::to_string;

#include <memory>
	using std::shared_ptr;

#include <stdexcept>
	using std::runtime_error;

#include <array>
	using std::array;

#include "process.h"

/**
 * @brief Construtor do process.
 * @param programName O caminho para o executável.
 */
Process::Process(string programName){
	setProcess(programName);
	setID(-1);
	setQuantum(-1);

	srand(time(NULL));
	int priorRand = rand() %10;
	setPriority(priorRand);
}

/** 
* @brief Método de acesso ao PID. 
* @return O PID.
*/
int Process::getID(){
	return pid;
}

/** 
* @brief Método de acesso à prioridade. 
* @return A prioridade.
*/
int Process::getPriority(){
	return priority;
}

/** 
* @brief Método de acesso ao quantum. 
* @return O quantum.
*/
int Process::getQuantum(){
	return quantum;
}

/** 
* @brief Método de acesso ao processo. 
* @return O processo.
*/
string Process::getProcess(){
	return toProcess;
}

/** 
* @brief Método modificador do processo. 
* @param processName O novo processo.
*/
void Process::setProcess(string processName){
	toProcess = processName;
}

/** 
* @brief Método modificador do PID. 
* @param identifier O novo PID.
*/
void Process::setID(int identifier){
	pid = identifier;
}

/** 
* @brief Método modificador da prioridade. 
* @param p A nova prioridade.
*/
void Process::setPriority(int p){
	priority = p;
}

/** 
* @brief Método modificador do quantum. 
* @param q O novo quantum.
*/
void Process::setQuantum(int q){
	quantum = q;
}

/** 
* @brief Cria o processo no sistema e retorna seu PID 
* @brief cmd O comando para executar o processo
* @return Retorna o PID em formato de string
*/
string Process::exec(const char* cmd) {
    array<char, 128> buffer;
    string result="";
    shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr){
            result += buffer.data();
        	return result;
        }
    }
    return result;
}

/** 
* @brief Prepara o processo para a execução 
* @return Retorna o PID em formato inteiro
*/
int Process::execute(){
	string aux = getProcess()+" "+to_string((rand() % 15) +1);
	pid_t retorno = 0;
	retorno = atoi(exec(aux.c_str()).c_str());
	setID(retorno);
	return getID();
}