/**
 * @file 	menu.h
 * @brief 	Arquivo responsável por implmentar as funções 
 * 			responsáveis por exibir os menus.
 * 
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	08.10.2017
 * @data 	
 */

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include "menu.h"

/**
 * @fn 		int menu()
 * @brief 	Função responsável por imprimir o menu principal
 * @return 	result
 */
int menu(){
	int result;
	do{
		cout << " +-------------------------------------+ " << endl;
		cout << " |                M E N U              | " << endl;
		cout << " +-------------------------------------+ " << endl;
		cout << " | 1 - Carregar Imagem                 | " << endl;
		cout << " |-------------------------------------| " << endl;
		cout << " | 2 - Salvar Imagem                   | " << endl;
		cout << " |-------------------------------------| " << endl;
		cout << " | 3 - Processar Imagem                | " << endl;
		cout << " |-------------------------------------| " << endl;
		cout << " | 0 - Sair                            | " << endl;
		cout << " +-------------------------------------+ " << endl;
		cout << " \tOpcao: ";
		cin >> result;
		cout << endl;
		if(result<0 or result>3){
			cout << "Opcao invalida! Tente novamente" << endl;
		}
	}while(result<0 or result>3);
	return result;
}

/**
 * @fn 		int menu()
 * @brief 	Função responsável por imprimir o menu de políticas de escalonamento
 * @return 	result
 */
int processar() {
	int result;
	do {
		cout << " +----------------------------------+ " << endl;
		cout << " |    Processamento de Imagem       | " << endl;
		cout << " +----------------------------------+ " << endl;
		cout << " | 1 - Limiarizar                   | " << endl;
		cout << " |----------------------------------| " << endl;
		cout << " | 2 - Converter Imagem             | " << endl;
		cout << " |----------------------------------| " << endl;
		cout << " | 3 - AlphaTransform               | " << endl;
		cout << " |----------------------------------| " << endl;
		cout << " | 4 - Filtro BoxBlur               | " << endl;
		cout << " |----------------------------------| " << endl;
		cout << " | 5 - Filtro Emboss                | " << endl;
		cout << " |----------------------------------| " << endl;
		cout << " | 0 - Voltar                       | " << endl;
		cout << " +----------------------------------+ " << endl;
		cout << " \tOpção: ";
		cin >> result;
		cout << endl;
		if(result<0 or result>5){
			cout << "Opcao invalida! Tente novamente" << endl;
		}
 	} while (result < 0 or result > 5);
 	return result;
}