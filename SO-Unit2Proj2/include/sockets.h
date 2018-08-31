/**
 * @file 	sockets.h
 * @brief 	A header that defines important functions to sockets API work fit
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	19.11.2017
 * @data 	
 * @sa 		sockets.h
 */

#ifndef _SOCKETS_H_
#define _SOCKETS_H_

#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <netdb.h>  //gethostbyname()

#include <string>
	using std::stoull;

#include <exception>
	using std::exception;

//defines bzero function
#define bzero(p, size)     (void)memset((p), 0, (size))

//const declaration
socklen_t SOCK_LEN = sizeof(sockaddr_in);
const int DATAGRAM_LEN = 65536;
const int MINIMUN_DATAGRAM_LEN = 8;
const int SOCKET_ERROR = -1;

/** @enum Datagram */
enum class Datagram{
	TCP=0, 
	UDP=1
};

/**@enum IPVersion */
enum class IPVersion{
	IPV4=0,
	IPV6=1
};

/** @class SocketError
*	@brief A class that defines standard errors to socket API
*/
class SocketError : public exception {
	private:
		string message;

	public:
		SocketError(string message){
			this->message = message;
		}

		const char * what() const throw(){
			return ("SocketError: "+message).c_str();
		}
};

/**
* 	@fn int getIPVersion(IPVersion ipv)
*	@brief Function that returns AF_INET flag acording to IPVersion
* 	@param ipv An IPVersion param
* 	@return Returns AF_INET flag
* 	@throws SocketError: No IPVersion recognized
*/
int getIPVersion(IPVersion ipv){
	switch(ipv){
		case IPVersion::IPV4:
			return AF_INET;
			break;
		case IPVersion::IPV6:
			return AF_INET6;
			break;
	}
	throw SocketError("No IPVersion recognized");
}

#endif