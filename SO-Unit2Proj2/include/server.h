/**
 * @file 	server.h
 * @brief 	A header that defines a SERVER CLASS to sockets API
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	19.11.2017
 * @data 	
 * @sa 		server.h
 */

#ifndef _SERVER_H_
#define _SERVER_H_

#include <iostream>
	using std::cout;
	using std::cin;

#include <string>
	using std::string;
	using std::to_string;

#include <vector>
	using std::vector;


#include "menu.h"
#include "File.h"
#include "Image.h"
#include "ManageImage.h"

#include "sockets.h"
/**
	* @class A class that defines a high-level server 
*/
class Server{
protected:
	int port; /** <- Port used by this server */
	int sockfd; /** <- Socket used by this server */
	int num_conections; /** <- Maximun number of permited connections */
	bool running = false; /** <- A flag that says if server is running */
	struct sockaddr_in serv_addr; /** <- Struct to low-level server */

	vector<int> v_cli_addr_sock; /** <- Vector to save clients sockets */
	vector<sockaddr_in> v_cli_addr_info; /** <- Vector to save clients informations */

	Datagram dt; /** <- Datagram used in this server */
	IPVersion ipv; /** <- IPVersion used in this server */

	/**
	* @fn void waitConnections()
	* @brief A function that wait for connections to this server. NOTE: If this server is based on TCP, must stayed stopped here waiting connections, else none will happens 
	* @throws SocketError: Failed to accept connection
	*/
	void waitConnections(){
		ssize_t newsockfd;
		struct sockaddr_in cli_addr;

		switch(dt){
			case Datagram::TCP:
				newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &SOCK_LEN);
				if(newsockfd == SOCKET_ERROR) throw SocketError("Failed to accept connection");

				v_cli_addr_sock.push_back(newsockfd);
				v_cli_addr_info.push_back(cli_addr);
				break;
			case Datagram::UDP:
				//none
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
				read_return = read(v_cli_addr_sock.back(), &buffer, MINIMUN_DATAGRAM_LEN);
				if(read_return == SOCKET_ERROR) throw SocketError("Failed to read from socket");
				
				messageLenghtToReceive = stoull(buffer);

				for(unsigned long long int i=0; i<messageLenghtToReceive; i+=DATAGRAM_LEN){

					read_return = read(v_cli_addr_sock.back(),&buffer,DATAGRAM_LEN);
					if(read_return == SOCKET_ERROR) throw SocketError("Failed to read from socket");

					message+=buffer;
					//cout << "i = " << i << " and messageLen = " << message.size() << endl;
				}
				break;
			case Datagram::UDP:
				read_return = recvfrom(sockfd, &buffer, MINIMUN_DATAGRAM_LEN, 0, (struct sockaddr *) &cli_addr, (socklen_t*) &SOCK_LEN);
				if(read_return == SOCKET_ERROR) throw SocketError("Failed to read from socket");
				
				messageLenghtToReceive = stoull(buffer);

				for(unsigned long long int i=0; i<messageLenghtToReceive; i+=DATAGRAM_LEN){
					read_return = recvfrom(sockfd, &buffer, DATAGRAM_LEN, 0, (struct sockaddr *) &cli_addr, (socklen_t*) &SOCK_LEN);
					if(read_return == SOCKET_ERROR) throw SocketError("Failed to read from socket");

					message+=buffer;
				}
				v_cli_addr_info.push_back(cli_addr);
				break;
		}
		return message;
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
				send_return = write(v_cli_addr_sock.back(), messageLen.c_str(), MINIMUN_DATAGRAM_LEN);
				if(send_return == SOCKET_ERROR) throw SocketError("Failed to write to socket");

				for(unsigned long long int i=0; i<message.size(); i+=DATAGRAM_LEN){
					send_return = write(v_cli_addr_sock.back(), message.c_str(), DATAGRAM_LEN);
					if(send_return == SOCKET_ERROR) throw SocketError("Failed to write to socket");
				}
				close(v_cli_addr_sock.back()); //close conection here?
				break;
			case Datagram::UDP:
				send_return = sendto(sockfd, messageLen.c_str(), MINIMUN_DATAGRAM_LEN, 0, (struct sockaddr *) &v_cli_addr_info.back(), SOCK_LEN);
				if(send_return == SOCKET_ERROR) throw SocketError("Failed to send info");

				for(unsigned long long int i=0; i<message.size(); i+=DATAGRAM_LEN){
					
					send_return = sendto(sockfd, message.c_str(), DATAGRAM_LEN, 0, (struct sockaddr *) &v_cli_addr_info.back(), SOCK_LEN);
					if(send_return == SOCKET_ERROR) throw SocketError("Failed to send info");
				}
				break;
		}	
	}

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
	* @fn Server(int port, Datagram dt, IPVersion ipv, int num_conections = 1)
	* @brief Standard contructor
	* @param port The port that this server will use
	* @param dt The type of Datagram protocol (TCP or UDP)
	* @param ipv The type of IPVersion used (IPV4 or IPV6)
	* @param num_conections Maximun conection number permited. Defined as 1 by default 
	* @throws SocketError: Failed to open socket / Failed to bind socket 
	*/
	Server(int port, Datagram dt, IPVersion ipv, int num_conections = 1){
		this->dt = dt;
		this->ipv = ipv;
		this->port = port;
		this->num_conections = num_conections;
		
		sockfd = createSocket();
		if(sockfd == SOCKET_ERROR) throw SocketError("Failed openning socket");

		bzero((char *) &serv_addr, sizeof(serv_addr));	
		serv_addr.sin_family = getIPVersion(ipv);
		serv_addr.sin_port = htons(port);
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

		ssize_t bind_return = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
		if(bind_return == SOCKET_ERROR) throw SocketError("Failed to bind socket");

		if(dt==Datagram::TCP) listen(sockfd, num_conections);
	}

	/**
	* @brief Standard destructor
	*/
	~Server(){
		for(int i=0; i<(int)v_cli_addr_sock.size(); i++){
			close(v_cli_addr_sock[i]);
		}
		close(sockfd);
	}

	/**
	* @fn void run() 
	* @brief A function that runs the server
	* @throws SocketError
	*/
	void run(){
		running = true;
		int cont = 0;
		int opt;
		cout << "Starting to run" << endl;
		while(isRunning()){
			//wait for connections
			cout << "Starting to wait connections" << endl;
			waitConnections();

			//read from
			cout << "Starting to read" << endl;
			string filtro = receive();
			//cout << filtro << endl;
			opt = atoi(filtro.c_str());
			Image *img = from_string(receive());
			Image *imgAux;

			//cout << "Image: " << img->to_string() << endl;
			double emboss[3][3] = {
		        { -2, -1, 0 },
		        { -1,  1,  1 },
		        { 0, 1, 2 }
		    };
		    double boxblur[3][3] = {
				{ 0.0625, 0.125, 0.0625 },
				{ 0.125,  0.25,  0.125  },
				{ 0.0625, 0.125, 0.0625 }
			};
			string archiveN = "";
			Image* img2;

			switch(opt){
				case 1: //limiarizacao
					Pixel limiar;
				    limiar.rgb.R = 127;
				    limiar.rgb.G = 127;
				    limiar.rgb.B = 127;

				    imgAux = limiarization(img, limiar);
					break;
				case 2://conversao
					if(img->getType() == PixelType::RGB) imgAux = transform(img, PixelType::RGB, PixelType::YCbCr);
					else imgAux = transform(img, PixelType::YCbCr, PixelType::RGB);
					break;
				case 3://alpha
					cout << "Escreva o nome do arquivo da outra imagem: " ;
					cin >> archiveN;
					img2 = readImg(archiveN);
					imgAux = alphaTransform(img, img2);
					break;
				case 4://boxblur
					imgAux = filter(img, boxblur);
					break;
				case 5://emboss
    				imgAux = filter(img, emboss);
					break;
				default:
					cout << "Não há essa opção" << endl;
					break;
			}

			//write from
			cout << "Starting to write" << endl;
			send(imgAux->to_string());
			//send("I receive your message");

			if(++cont>=num_conections) break; 
			sleep(1);
		}
		running = false;
	}

	/**
	* @fn int getPort()
	* @brief Accessor
	* @return The used port
	*/
	int getPort(){
		return port;
	}

	/**
	* @fn int getNumConnections()
	* @brief Accessor
	* @return Maximun number of conections
	*/
	int getNumConnections(){
		return num_conections;
	}

	/**
	* @fn bool isRunning()
	* @brief Accessor
	* @return A flag that returns if the server is running or not
	*/
	bool isRunning(){
		return running;
	}
};
#endif