#include <iostream>
using std::cout;
using std::endl;

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char * argv[]){ //fazer try_catch
	int time = atoi(argv[1]);

	pid_t child_pid = fork(); //cria-se um processo filho que irá executar o quer que seja
 	if(child_pid==0){
		sleep(time);
		exit(0);//finaliza corretamente o filho
	}
	cout << child_pid << endl;
	return child_pid;
}
