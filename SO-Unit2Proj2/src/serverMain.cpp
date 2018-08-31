#include <iostream>
	using std::cout;
	using std::cin;
	using std::endl;

#include "server.h"

int main (){
	Server *s = new Server(10000, Datagram::TCP, IPVersion::IPV4,100);
	s->run();

	return 0;
}