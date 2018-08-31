#include <iostream>
	using std::cout;
	using std::cin;
	using std::endl;

#include <string>
	using std::string;

#include <exception>
	using std::exception;

#include <vector>
	using std::vector;


#include "client.h"
#include "menu.h"
#include "File.h"
#include "Image.h"
#include "ManageImage.h"

#include "sockets.h"

int main (){
    Client *c = new Client(Datagram::TCP, IPVersion::IPV4);
    string serverIP = "127.0.0.1";
    int port = 10000;
    
    
    int result, filtro;
    Image* img = NULL;
    Image* imgAux;
    string path = "";
    do{
    	result = menu();
    	switch(result){
    		case 1:    			
    			cout << "Digite o nome da imagem na pasta image/: " << endl;
    			cin >> path;
    			/*i = path.find("\n", 0);
    			path = path.substr(0,i);*/
    			img = readImg (path);
    			break;
    		case 2:
    			cout << "Digite o nome de saida da imagem na pasta image/: " << endl;
    			cin >> path;
    			writeImg (img, path);
    			break;
    		case 3:
    		//filtrar
    			if(img != NULL){

	    			filtro = processar();
	    			
	    			c->connectTo(serverIP, port);
	    			
	    			c->send(std::to_string(filtro));
	    			
	    			c->send(img->to_string());
	    			
	    			imgAux = from_string(c->receive());
	    			img = imgAux;

	    			cout << img->to_string() << endl; 

	    			
	    		} else {
	    			cout << "So eh possivel aplicar filtros com uma imagem carregada do sistema!" << endl;
	    		}
    			break;
    	}
    	
    } while (result != 0);
    
    //string message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi porta leo metus, id varius dolor vestibulum id. Phasellus hendrerit lorem eu lorem ultricies fermentum. Phasellus congue, erat vel pretium dapibus, leo erat feugiat nulla, in convallis risus dolor sit amet justo. Nunc in arcu diam. Suspendisse id rutrum nunc, et rutrum leo. Ut id velit vitae nisi euismod molestie. Sed at lectus laoreet, aliquet purus eget, vulputate massa.\nVivamus scelerisque sapien augue. Pellentesque dictum, dolor et pharetra hendrerit, felis velit rhoncus dui, non cursus nulla nunc in turpis. Donec libero dolor, lacinia et posuere at, tristique scelerisque tortor. Vivamus orci quam, congue sed elit non, molestie eleifend sem. In purus enim, mollis ac arcu non, lobortis blandit est. Nunc at magna malesuada, euismod dui in, eleifend purus. Ut blandit quam neque, id tincidunt ex iaculis eu.\nInteger semper quis lacus vitae scelerisque. Nulla vitae leo porttitor, sodales turpis at, commodo est. Vestibulum vulputate diam non nulla semper, nec fermentum ex imperdiet. Integer ut pharetra risus. Cras dapibus nibh eu mauris blandit bibendum. Aenean sollicitudin sit amet enim eu tempus. Vestibulum nulla est, tempus eget porta vel, pellentesque id magna. Donec eu suscipit leo. Proin et finibus justo. Aliquam consectetur tristique interdum.\nQuisque eleifend nulla id velit auctor, eu dapibus libero tincidunt. Nullam in nulla congue, tincidunt mauris a, iaculis mauris. Maecenas leo turpis, iaculis sit amet tristique id, convallis ac odio. Mauris pretium tristique ex, quis placerat tellus cursus a. Aenean sollicitudin nunc vitae lacus sodales, nec laoreet nulla feugiat. Phasellus vulputate, velit vel aliquam faucibus, risus sem sollicitudin mi, sed consequat massa nisi sed urna. Quisque faucibus risus lacus, ut auctor nisl vestibulum ac. Integer convallis ligula velit, et luctus elit iaculis in. Sed tincidunt fringilla orci, sollicitudin tempor libero dapibus vitae. Suspendisse quis turpis eu turpis malesuada suscipit ac vitae orci. Morbi scelerisque velit eget ex efficitur, vel gravida dui lacinia. Nullam sit amet felis sed sem suscipit condimentum sed nec ligula. In id massa euismod, elementum nisi eget, fringilla diam. Donec interdum finibus commodo. Maecenas ullamcorper pharetra elit.\nMorbi consectetur nunc ac dolor auctor accumsan. Etiam lobortis diam orci, non ornare elit pellentesque id. Nullam tempor suscipit hendrerit. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Vestibulum hendrerit odio vitae neque finibus ultricies ac nec est. Curabitur fringilla risus at mi finibus mattis. Nullam placerat malesuada libero nec vehicula. Sed arcu metus, finibus in erat nec, faucibus tristique lacus. Donec dapibus scelerisque feugiat. Proin ac porta diam.";
    //c->send(message);
   // cout << c->receive() << endl;
   
    /*
	
    */

	return 0;
}
