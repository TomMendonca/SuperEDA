#include <iostream>
#include <locale>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "SuperMercado.h"
#include "Ficheiros.h"

using namespace std;

int main() {

	//Necessario para usar a rand()
	locale::global(locale(""));
	srand(time(NULL));

	//Cria��o dos arrays est�ticos para os produtos, areas e fornecedores
	string* produtos = new string[contaLinhas("nome.txt")];
	string* areas = new string[contaLinhas("areas.txt")];
	string* fornecedores = new string[contaLinhas("fornecedores.txt")];
	leFicheiro("nome.txt", produtos);
	leFicheiro("areas.txt", areas);
	leFicheiro("fornecedores.txt", fornecedores);

	//Cria��o dos setores
	int numSetores = rand() % 5 + 8; //entre 8 e 12
	//Iniciar a Lista de Setores
	nodeSetor *setoresHead = NULL;
	cout << "Tamanho do SuperEDA: " << numSetores << endl;
	char id = 'A';
	for (int i = 0; i < numSetores; i++) {//insere setores na lista ligada de setores
		insereSetor(setoresHead, criaNodoSetor(areas, id));
		id++;
	}


	// Array apenas com as areas dos setores, usado para criar nodeProdutos
	int n_areas = numSetores;
	string* areasSetores = new string[n_areas];
	int i = 0;
	nodeSetor* iterator = setoresHead;
	while (iterator != NULL) {
		areasSetores[i] = iterator->area;
		iterator = iterator->next;
		i++;
	}

	//Cria��o da lista ligada do armaz�m 
	//Lista Ligada do armaz�m
	nodeProduto *armazemHead = NULL;
	//Inicializa��o da Lista Ligada armaz�m
	for (int i = 0; i < 50; i++) {//Inserir os 50 produtos
		insereProduto(armazemHead, criaNodeProduto(produtos, fornecedores, areasSetores, n_areas));
	}


	//Funcionamento dos menus!
	bool sair, voltar;
	sair = false;
	voltar = false;
	char opcao;


	do {
		//Visualizar o Supermercado!
		imprimeSetor(setoresHead, numSetores);//Impress�o dos Setores
		imprimeArmazem(armazemHead);//Impress�o do armaz�m

		cout << endl;
		cout << " (s)eguinte -------- (g)est�o -------- sai(r) " << endl << " Selecione uma op��o: ";
		cin >> opcao;
		cout << endl;
		switch (opcao)
		{
		case 's': //Simula��o do funcionamento do Supermercado
			
			//Vende os produtos do supermercado
			vender(setoresHead);
			//Funciona com algums bugs!
				
			//Tentar inserir 10 produtos nos setores que est�o no armaz�m
			for (int i = 0; i < 10; i++) {
				insereProdutoNoSetor(armazemHead, setoresHead);
			}

			//Adiciona 10 produtos ao armazem 
			for (int i = 0; i < 10; i++) {
				insereProduto(armazemHead, criaNodeProduto(produtos, fornecedores, areasSetores, n_areas));
			}


			break;
			
		case 'g': //Menu Gestor
			cout << "********* BEM-VINDO GESTOR *********" << endl;
			do {
				cout << endl << "(1).Remover produto" << endl;
				cout << "(2).Atualizar pre�o" << endl;
				cout << "(3).Iniciar campanha" << endl;
				cout << "(4).Gravar supermercado" << endl;
				cout << "(5).Carregar supermercado" << endl;
				cout << "(6).Imprimir produtos" << endl;
				cout << "(7).Criar nova �rea" << endl;
				cout << "(8).Mostrar registo de vendas" << endl;
				cout << "(0).Voltar" << endl;
				cout << "Selecione uma op��o: ";
				cin >> opcao;
				cout << endl;
				switch (opcao)
				{

				case'1': //Remover produto
					cin.ignore(); //Comer \n
					removeProdutoSuperMercado(armazemHead, setoresHead);
					//Apenas remove o produto do armazem e n�o dos setores

					break;
				case'2': //Atualizar pre�o
					cin.ignore(); //Comer \n
					atualizarPreco(armazemHead);

					break;
				case'3': //Iniciar campanha
					cout << "Funcionalidade n�o implementada\n ";
					break;

				case'4': //Gravar supermercado
					gravaSetores(setoresHead);//Grava cont�udo dos setores
					gravaArmazem(armazemHead);//Grava cont�udo do armazem
					break;

				case'5': //Carregar supermercado
					//carregaSetores(setoresHead);//N�o conseguimos colocar a funcionar
					carregaArmazem(armazemHead);//Carrega o conte�do do armazem
					break;

				case'6': //Imprimir produtos
					imprimirProdutos(armazemHead,  setoresHead, numSetores);
					break;
				case'7': //Criar nova �rea
					areasSetores = criaArea(areasSetores, n_areas);
					n_areas++;
					break;

				case'8': //Mostrar registo de vendas
					cout << "Funcionalidade n�o implementada\n ";
					break;


				case '0': //Voltar ao menu anterior
					voltar = true;
					break;

					{
				default:cout << "Escolha uma op��o v�lida!" << endl;
					}
				}
			} while (!voltar);
			voltar = false;
			break;

		case 'r': //Sair do programa "Fechar"
			sair = true;
			break;


		default:cout << "Escolha uma op��o v�lida!" << endl;

		}

	} while (!sair);

	return 0;
}