#include <iostream>
#include <locale>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "SuperMercado.h"
#include "Ficheiros.h"

using namespace std;


int main(){
	
	//Necessario para usar a rand()
	locale::global(locale(""));
	srand(time(NULL));

	//Cria��o dos arrays est�ticos para os produtos, areas e fornecedores
	string* produtos = new string[contaLinhas("nome.txt")];
	string* areas = new string[contaLinhas("areas.txt")];
	string* fornecedores = new string[contaLinhas("fornecedores.txt")];
	leFicheiro("nome.txt",produtos);
	leFicheiro("areas.txt", areas);
	leFicheiro("fornecedores.txt", fornecedores);


	//Cria��o dos setores
	int numSetores = rand() % 5 + 8;
	setor* setores = new setor[numSetores];
	cout << "Tamanho do SuperEDA: " << numSetores << endl;
	char id = 'A';
	for (int i = 0;i < numSetores;i++) {
		setores[i] = criaSetor(areas, id);
		id++;
	}
	 

	// Array apenas com as areas dos setores
	int n_areas = numSetores;
	string* areasSetores = new string[n_areas];
	for (int i = 0;i < n_areas; i++) {
		areasSetores[i] = setores[i].area;
	}

	
	//Cria��o do armaz�m
	int tam_armazem = 200;
	int n_produtosArmazem =0;
	produto* armazem = new produto[tam_armazem];
	for (int i = 0;i < 50;i++) {
		if (n_produtosArmazem < tam_armazem) {
			armazem[i] = criaProduto(produtos, fornecedores, areasSetores, numSetores);
			n_produtosArmazem++;
		}
	}



	bool sair, voltar;
	sair = false;
	voltar = false;
	char opcao;
	int ciclos=0;
	int ciclos_camp=0;


	do {

		cout << endl;
		imprimeSetor(numSetores, setores);
		imprimeArmazem(armazem, n_produtosArmazem);


		cout << endl;
		cout << " (s)eguinte -------- (g)est�o -------- sai(r) " << endl << " Selecione uma op��o: ";
		cin >> opcao;
		cout << endl;
		switch (opcao)
		{
		
		case 's': //Simula��o do funcionamento do Supermercado

			//Vende ou n�o os produtos de cada setor
			vender(setores, numSetores);
			
		
			//Adiciona 10 produtos ao armazem se tiver espa�o a partir da ultima posi��o ocupada(numero de produtos da array naquele momento).
			for (int i = 0; i < 10; i++) {
				if (n_produtosArmazem < tam_armazem) {
					armazem[n_produtosArmazem] = criaProduto(produtos, fornecedores, areasSetores, n_areas);
					n_produtosArmazem++;
				}
			}
		
			// Adiciona 10 produtos do armazem nos setores por prioridades e se tiver espa�o.
			for (int i = 0;i < 10;i++) {
				if (addProduto(armazem, setores, numSetores, n_produtosArmazem) == true) {
					n_produtosArmazem--;
				}
			}

			//Aumenta os ciclos
			ciclos++; 

			//Verifica se tem Campanhas ativas, se existirem e j� tiverem acabado reverte o pre�o
			if (ciclos == ciclos_camp) {
				for (int i = 0;i < numSetores;i++) {
					for (int j = 0; j < setores[i].num_produtos;j++) {
						if (setores[i].produtos[j].campanha == true) {
							setores[i].produtos[j].preco = setores[i].produtos[j].preco / (1 - setores->desconto);

						}
					}

				}
			}
		
			
		break;

		case 'g': //Menu Gestor
			cout << "********* BEM-VINDO GESTOR *********" << endl;
			do {
				cout << endl <<"(1).Remover produto" << endl;
				cout << "(2).Atualizar pre�o" << endl;
				cout << "(3).Iniciar campanha" << endl;
				cout << "(4).Gravar supermercado" << endl;
				cout << "(5).Carregar supermercado" << endl;
				cout << "(6).Imprimir produtos" << endl;
				cout << "(7).Criar nova �rea" << endl;
				cout << "(8).Mostrar registo de vendas" << endl;
				cout << "(9).Alterar �rea" << endl;
				cout << "(0).Voltar" << endl;
				cout << "Selecione uma op��o: ";
				cin >> opcao;
				cout << endl;
				switch (opcao)
				{

				case'1': //Remover produto

					cin.ignore(); //Comer \n
					n_produtosArmazem= n_produtosArmazem-remove_produto_por_nome(setores, numSetores, armazem, n_produtosArmazem);
					
					break;

				case'2': //Atualizar pre�o
					cin.ignore(); //Comer \n
					armazem = atualizaPreco(armazem, tam_armazem);
				
					break;

				case'3': //Iniciar campanha
					
					cout << "Introduza o n�mero de ciclos em que a campanha estar� ativa: ";
					cin >> ciclos_camp;
					setores=campanha(setores, numSetores);
					ciclos_camp = ciclos + ciclos_camp;
					break;

				case'4': //Gravar supermercado
					gravaSetores(setores, numSetores);
					gravaArmazem(armazem, n_produtosArmazem);
					break;

				case'5': //Carregar supermercado

					setores = carregaSetores();
					numSetores = contaLinhas("InfoSet.txt");
					n_areas = numSetores;
					for (int i = 0;i < n_areas; i++) {
						areasSetores[i] = setores[i].area;
					}
				
					armazem=carregaArmazem(tam_armazem);
					//Tamanho do armazem ser� o numero de linhas do ficheiro a dividir por 4 (nome, fornecedor, pre�o, area)
					n_produtosArmazem = contaLinhas("Armazem.txt") / 3; 		
					break;

				case'6': //Imprimir produtos

					cout << "(1).Imprimir produtos por ordem alfab�tica" << endl;
					cout << "(2).Ordenar produtos por pre�o" << endl;
					cin >> opcao;

					switch (opcao) {
					case '1': //Ordem Alfab�tica
						imprimeProdutoAlf (armazem,setores, n_produtosArmazem, numSetores);
						break;

					case '2': //Ordem Crescente de Pre�o
						imprimeProdutoPreco(armazem,setores,n_produtosArmazem,numSetores);
						break;
					default:cout << "Escolha uma op��o v�lida!" << endl;
					}
					break;
				 
				case'7': //Criar nova �rea
					areasSetores=criaArea(areasSetores, n_areas);
					n_areas++;
					
					break;

				case'8': //Mostrar registo de vendas

					cout << "--------------------------------------------- REGISTO DE VENDAS ---------------------------------------------" << endl << endl;
					
					for (int i = 0; i < numSetores; i++) {
						cout << " Setor " << setores[i].identificador << " | " << "Respons�vel : " << setores[i].responsavel << endl << endl;
						for (int j = 0; j <setores[i].n_produtos_registo;j++) {

							cout << " Produto: " << setores[i].registo[j].nome << " | " << "Pre�o: " << setores[i].registo[j].preco << " $" << endl;

						}
						cout << "----------------------------------------------------------------------------------------------------" << endl << endl;
					}
				
					break;

				case'9': //Alterar �rea
					setores = alteraArea(setores, numSetores, areasSetores, n_areas);
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

	}while (!sair);

	return 0;
}
