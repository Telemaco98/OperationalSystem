/**
 * @file 	client.h
 * @brief 	A header that defines a CLIENT CLASS to sockets API
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	19.11.2017
 * @data 	
 * @sa 		client.h
 */

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <string>
	using std::string;
	using std::to_string;

#include <vector>
	using std::vector;

#include "sockets.h"

/**
*	@class A class that defines a high-level client
*/
class Client{
protected:
	int sockfd; /** <- Used socket in this client */
	bool connected = false; /** <- A flag that says if this client is connected to someone */
	struct sockaddr_in serv_addr; /** <- A struct to low-level to a server*/
	
	Datagram dt; /** <- Datagram used in this client */
	IPVersion ipv; /** <- IPVersion used in this client */

	/**
	* @fn int createSocket()
	* @brief A function that creates a socket
	* @throws SocketError: Failed to create socket
	*/
	int createSocket(){
		int datagram, ip_version, flag;

		switch(dt){
			case Datagram::TCP:
				datagram = SOCK_STREAM;
				flag = 0;
				break;
			case Datagram::UDP:
				datagram = SOCK_DGRAM;
				flag = IPPROTO_UDP;
				break;
		}
		ip_version = getIPVersion(ipv);
		return socket(ip_version, datagram, flag);
	}

public:

	/**
	* @fn Client(Datagram dt, IPVersion ipv)
	* @brief Standard contructor
	* @param dt The type of Datagram protocol (TCP or UDP)
	* @param ipv The type of IPVersion used (IPV4 or IPV6)
	* @throws SocketError: Failed to create socket
	*/
	Client(Datagram dt, IPVersion ipv){
		this->dt = dt;
		this->ipv = ipv;
	
		sockfd = createSocket();
		if(sockfd == SOCKET_ERROR) throw SocketError("Failed to create socket");
	}

	/**
	* @brief Standard destructor
	*/
	~Client(){
		close(sockfd);
	}

	/**
	* @fn void connectTo(string serverIP, int serverPort)
	* @brief Prepare a connection to a server
	* @param serverIP The server IP that this client must connect
	* @param serverPort The port used by the server
	* @throws SocketError: Failed to connect
	*/
	void connectTo(string serverIP, int serverPort){
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = getIPVersion(ipv);
	    serv_addr.sin_addr.s_addr=inet_addr(serverIP.c_str());
	    serv_addr.sin_port = htons(serverPort);

		ssize_t connect_return;
		switch(dt){
			case Datagram::TCP:
				connect_return = connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
		    	if(connect_return == SOCKET_ERROR) throw SocketError("Failed to connect");
		    	break;
		    case Datagram::UDP:
		    	//none
		    	break;
		}
	}

	/**
	* @fn void send(string message)
	* @brief A function that sends a message to last connected client
	* @param message The message to send
	* @throws SocketError: Failed to send data
	*/
	void send(string message){
		ssize_t send_return;
		string messageLen = to_string((unsigned long long int)message.size());

		switch(dt){
			case Datagram::TCP:
				send_return = write(sockfd, messageLen.c_str(), MINIMUN_DATAGRAM_LEN);
				if(send_return == SOCKET_ERROR) throw SocketError("Failed to write to socket");
				//cout << "2" << endl;
				for(unsigned long long int i=0; i<message.size(); i+=DATAGRAM_LEN){
					send_return = write(sockfd,message.c_str(),DATAGRAM_LEN);
					//cout << "3" << endl;
					if(send_return == SOCKET_ERROR) throw SocketError("Failed to write to socket");
				}
				//cout << "2" << endl;
				break;
			case Datagram::UDP:
				send_return = sendto(sockfd, messageLen.c_str(), MINIMUN_DATAGRAM_LEN , 0 , (struct sockaddr *) &serv_addr, SOCK_LEN);
				if(send_return == SOCKET_ERROR) throw SocketError("Failed to send info to socket");

				for(unsigned long long int i=0; i<message.size(); i+=DATAGRAM_LEN){
					send_return = sendto(sockfd, message.c_str(), DATAGRAM_LEN , 0 , (struct sockaddr *) &serv_addr, SOCK_LEN);
					if(send_return == SOCKET_ERROR) throw SocketError("Failed to send info to socket");
				}
				break;
		}
	}

	/**
	* @fn string receive()
	* @brief A function that receives a message
	* @return The message received
	* @throws SocketError: Failed to receive data
	*/
	string receive(){
		string message = "";
		unsigned long long int messageLenghtToReceive;

		char buffer[DATAGRAM_LEN];
		bzero(buffer, DATAGRAM_LEN);

		ssize_t read_return;
		struct sockaddr_in cli_addr;

		switch(dt){
			case Datagram::TCP:
				read_return = read(sockfd, &buffer, MINIMUN_DATAGRAM_LEN);
				if(read_return == SOCKET_ERROR) throw SocketError("Failed to read from socket");

				messageLenghtToReceive = stoull(buffer);

				for(unsigned long long int i=0; i<messageLenghtToReceive; i+=DATAGRAM_LEN){
					read_return = read(sockfd,&buffer,DATAGRAM_LEN);
					if(read_return == SOCKET_ERROR) throw SocketError("Failed to read from socket");

					message+=buffer;
				}
				break;
			case Datagram::UDP:
				read_return = recvfrom(sockfd, &buffer, MINIMUN_DATAGRAM_LEN, 0, (struct sockaddr *) &cli_addr, (socklen_t*)&SOCK_LEN);
				if(read_return == SOCKET_ERROR) throw SocketError("Failed to read from socket");

				messageLenghtToReceive = stoull(buffer);

				for(unsigned long long int i=0; i<messageLenghtToReceive; i+=DATAGRAM_LEN){
					read_return = recvfrom(sockfd, &buffer, DATAGRAM_LEN, 0, (struct sockaddr *) &cli_addr, (socklen_t*)&SOCK_LEN);
					if(read_return == SOCKET_ERROR) throw SocketError("Failed to read from socket");

					message+=buffer;
				}
				break;
		}
		return message;
	}
};

#endif