#include <iostream>
#include <string>
#include "SuperMercado.h"
#include "Ficheiros.h"


using namespace std;

//Cria um novo setor
setor criaSetor(string* areas, char id) {
	setor s;
	s.identificador = id;
	s.area = areas[rand() % contaLinhas("areas.txt")];
	s.capacidade = rand() % 6 + 5;
	s.num_produtos = 0;
	s.produtos = new produto[s.capacidade];
	s.registo = new produto[100];
	s.n_produtos_registo = 0;
	cout << "Introduza o respons�vel pelo setor " << s.identificador << " : ";
	getline(cin, s.responsavel);
	return s;
}
//Cria um novo produto
produto criaProduto(string* produtos, string* fornecedores, string* areasSetores, int n_areas) {
	int aux = 1;
	produto p;
	p.nome = produtos[rand() % contaLinhas("nome.txt")];
	p.fornecedor = fornecedores[rand() % contaLinhas("fornecedores.txt")];
	p.area = areasSetores[rand() % n_areas];
	p.campanha = false;

	while ((aux % 2) != 0) {
		aux = rand() % 80 + 1;
	}
	if ((aux % 2) == 0) {
		p.preco = aux;
	}
	return p;
}
//Fun��o para imprimir todos os produtos dos Setores
void imprimeSetor(int n,setor*setores) {
	cout << "--------------------------------------------- SuperEDA ---------------------------------------------" << endl << endl;

	for (int i = 0; i < n; i++) {
		cout << " Setor " << setores[i].identificador << " | " << "Respons�vel : " << setores[i].responsavel << " | " << "Capacidade : " << setores[i].capacidade << " | " << "Produtos : " << setores[i].num_produtos << " | " << "�rea : " << setores[i].area << endl << endl;
		for (int j = 0; j < setores[i].num_produtos;j++) {

			cout << " Produto: " << setores[i].produtos[j].nome << " | " << "Fornecedor: " << setores[i].produtos[j].fornecedor << " | " << "Pre�o: " << setores[i].produtos[j].preco << " $" << endl;

		}
		cout << "----------------------------------------------------------------------------------------------------" << endl << endl;
	}
}
//Imprime todos os produtos do armaz�m
void imprimeArmazem(produto* armazem, int n_produtos) {
	cout << endl << endl << "Armaz�m: " << endl << endl;
	for (int i = 0;i < n_produtos;i++) {
		cout << " " << "PRODUTO: " << armazem[i].nome << " | " << "FORNECEDOR: " << armazem[i].fornecedor << " | " << "PRE�O: " << armazem[i].preco << " $" << " | " << "�REA: " << armazem[i].area << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
	}
}

//Remove 1 produto 
void removeProduto(produto* lista,produto p, int n_produtos) {
	for (int i = 0; i < n_produtos; i++) {

		if (lista[i].preco == p.preco && lista[i].nome == p.nome && lista[i].fornecedor == p.fornecedor && lista[i].area == p.area ) {
			lista[i] = lista[i + 1];
			
			p = lista[i + 1];
		}
	}
}
//Remove o porduto por nome dos setores e armazem
int remove_produto_por_nome(setor* setores, int n_setores, produto* armazem, int n_produtos ) {

	bool remove_do_Setor = false;
	int remove_do_Armazem = 0;
	string nomeProduto;

	cout << "Insira o nome do produto que pretente remover: ";
	getline(cin, nomeProduto);
	cout << endl;

	for (int i = 0; i < n_setores; i++) {
		for (int j = 0; j < setores[i].num_produtos;j++)
			if (setores[i].produtos[j].nome == nomeProduto) {
				remove_do_Setor = true;
				removeProduto(setores[i].produtos, setores[i].produtos[j], setores[i].capacidade-1);
				setores[i].num_produtos--;
			}
	}
	if (remove_do_Setor == false)cout << "O produto " << nomeProduto << " n�o existe em nenhum setor! " << endl;
	else {cout << "O produto " << nomeProduto << " foi removido dos setores! " << endl;}

	for (int i = 0;i < n_produtos;i++) {
		if (armazem[i].nome == nomeProduto) {
			removeProduto(armazem, armazem[i], n_produtos);
			remove_do_Armazem++;
		}
	}
	if (remove_do_Armazem == NULL)cout << "O produto " << nomeProduto << " n�o existe no armaz�m! " << endl;
	else { cout << "O produto " << nomeProduto << " foi removido do armaz�m! " << endl; }
	return remove_do_Armazem;

}


//Percorre o armazem at� conseguir adicionar um produto no setor correspondente que tenha espa�o e remove-o do armazem. 
bool addProduto(produto* armazem, setor* setores, int numSetores, int n_produtos) {

	for (int i = 0; i < n_produtos; i++) {
		for (int j = 0;j < numSetores;j++) {

			if (armazem[i].area == setores[j].area && setores[j].num_produtos < setores[j].capacidade) {
				setores[j].produtos[setores[j].num_produtos] = armazem[i];
				setores[j].num_produtos++;
				removeProduto(armazem, armazem[i], n_produtos);
				return true;


			}
		}
	}
}

//Fun��o de simula a venda de produtos
void vender(setor* setores, int n_setores) {
	for (int i = 0; i < n_setores;i++) {
		for (int j = 0;j < setores[i].num_produtos; j++) {

			if (rand() % 4 + 1 == 1) {
				setores[i].registo[setores[i].n_produtos_registo]=setores[i].produtos[j];
				setores[i].n_produtos_registo++;
				removeProduto(setores[i].produtos, setores[i].produtos[j], setores[i].capacidade-1);
				setores[i].num_produtos--;

			}
		}
	}
	
}
//Cria uma nova area que o utilizador introduz
string* criaArea(string*areasSetores, int n_setores) {
	string* novasAreas = new string[n_setores + 1];
	string novaArea;
	cout << "Introduza uma nova �rea: ";
	cin.ignore();
	getline(cin, novaArea);
	cout << "A �rea " << novaArea << " foi criada." << endl;
	for (int i = 0;i < n_setores;i++) {
		novasAreas[i] = areasSetores[i];

	}
	novasAreas[n_setores] = novaArea;
	cout << novasAreas[n_setores] << endl;
	return novasAreas;
}
//Altera uma area existente por outrea introduzida pelo utilizador
setor* alteraArea(setor* setores, int numSetores,string*areas, int n_areas) {
	char id;
	string novaArea;
	bool identificador=false;
	bool area=false;
	int s;

	while (identificador == false) {
		cout << "Introduza a letra correspondente ao setor que pretende alterar: ";
		cin >> id;
		for (int i = 0;i < numSetores;i++) {
			if (setores[i].identificador == id) {
				identificador = true;
				s = i;
			}
		}
		if (identificador == false) {
			cout << "O setor " << id << " n�o existe!" << endl;
		}
	}
	cin.ignore();
	while (area == false) {
		cout << "Introduza a nova �rea deste setor: ";
		getline(cin,novaArea);
		for (int j = 0;j < n_areas;j++) {
			if (areas[j] == novaArea) {
				area = true;
			}
		}
		if (area == false) cout << "A �rea " << novaArea << " n�o existe!" << endl;
	}
	setores[s].area = novaArea;
	setores[s].num_produtos = 0;

	return setores;
	

}

//Fun��o para iniciar uma campanha
setor* campanha(setor*setores, int numSetores) {
	bool desconto=false;
	string area;
	int n_areas=0;
	while (desconto==false) {
		cout << "Introduza um n�mero entre 0 e 1 referente ao desconto: ";
		cin >> setores->desconto;
		if (setores->desconto > 0 && setores->desconto < 1) desconto = true;
	}
	cin.ignore();
	while (n_areas == NULL) {
		cout << "Introduza a �rea a aplicar desconto: ";
		getline(cin, area);
		for (int i = 0; i < numSetores; i++) {

			if (area==setores[i].area) {
				n_areas++;
				for (int j = 0;j < setores[i].num_produtos;j++) {
					setores[i].produtos[j].preco = setores[i].produtos[j].preco * (1 - setores->desconto);
					setores[i].produtos[j].campanha = true;
				}

			}

		}
		if (n_areas == NULL)cout << "A �rea " << area << " n�o existe em nenhum setor!" << endl;
	}

	return setores;


}

// Fun��o para alterar o pre�o de um produto no armaz�m
produto* atualizaPreco(produto* armazem, int n_produtosArmazem) {
	string nomeProd; //Nome to Produto para procurar
	int novoPreco; //Novo pre�o do porduto
	bool existeProduto = false; //Encontrou o produto no armaz�m
	bool precoValido = false;
	cout << "Introduza o nome do Produto que deseja modificar: " ;
	getline(cin, nomeProd);
	cout << "Introduza o novo pre�o: ";
	cin >> novoPreco;
	//Pre�o tem de ser v�lido PAR
	while (precoValido == false) {
		if (novoPreco % 2 == 1) {//Pre�o inv�lido �MPAR
			cout << "Introduza um pre�o v�lido: ";
			cin >> novoPreco;
		}
		else {
			precoValido = true; //Pre�o v�lido PAR
		}
	}
	//Percorre o armaz�m e atualiza o pre�o do 
	for (int i = 0; i < n_produtosArmazem; i++) { // Verifica se o produto existe
		if (nomeProd == armazem[i].nome) {//Encontrou
			armazem[i].preco = novoPreco;//Atualiza o produto
			cout << "Pre�o atualizado com sucesso" << endl;
			existeProduto = true;//Existe produto 
		}
	}
	//N�o existe produto no Armaz�m
	if (existeProduto == false) {
		cout << "Infelizmente o produto inserido n�o � v�lido!\nO item pode n�o se encontrar de momento em stock!" << endl;
	}
	return armazem;
}
//Imprime todos os produtos do armaz�m por ordem alfab�tica
void imprimeProdutoAlf(produto* armazem, setor* setores, int n_produtosArmazem, int numSetores) {
	produto temp;
	int n_prods=0;
	int index_prods=0;
	//produto* todos_produtos;
	//Quantos produtos existem nos setores!
	for (int i = 0; i < numSetores; i++) {
		n_prods += setores[i].num_produtos;
	}
	n_prods += n_produtosArmazem;//Num de produtos total
	produto* todos_produtos = new produto[n_prods]; //Array de produtos existentes no Supermerado

	for (int i = 0; i < n_produtosArmazem; i++) {
		todos_produtos[index_prods] = armazem[i];
		index_prods++;
	}
	for (int i = 0; i < numSetores; i++) {
		for (int j = 0; j < setores[i].num_produtos; j++) {
			todos_produtos[index_prods] = setores[i].produtos[j];
			index_prods++;
		}
	}



	for (int i = 0; i < n_prods; i++)
		for (int j = i + 1; j < n_prods; ++j) {
			if (todos_produtos[i].nome > todos_produtos[j].nome) {
				temp = todos_produtos[i];
				todos_produtos[i] = todos_produtos[j];
				todos_produtos[j] = temp;
				
			}
		}
	cout << endl << "Produtos do SuperEDA por ord�m Alfab�tica: " << endl;
	for (int i = 0; i < n_prods; i++) {
		cout << "Produto: " << todos_produtos[i].nome << " -> " <<todos_produtos[i].preco <<"$" << endl;
	}
}

//Imprime todos os produtos do armaz�m por ordem crescente de pre�os
void imprimeProdutoPreco(produto* armazem, setor* setores, int n_produtosArmazem, int numSetores) {
	produto temp;
	int n_prods = 0;
	int index_prods = 0;
	//produto* todos_produtos;
	for (int i = 0; i < numSetores; i++) {
		n_prods += setores[i].num_produtos;
	}
	n_prods += n_produtosArmazem;
	produto* todos_produtos = new produto[n_prods];

	for (int i = 0; i < n_produtosArmazem; i++) {
		todos_produtos[index_prods] = armazem[i];
		index_prods++;
	}
	for (int i = 0; i < numSetores; i++) {
		for (int j = 0; j < setores[i].num_produtos; j++) {
			todos_produtos[index_prods] = setores[i].produtos[j];
			index_prods++;
		}
	}

	//Fun��o Ordena��o
	for (int i = 0; i < n_prods; i++)
		for (int j = i + 1; j < n_prods; ++j) {
			if (todos_produtos[i].preco > todos_produtos[j].preco) {
				temp = todos_produtos[i];
				todos_produtos[i] = todos_produtos[j];
				todos_produtos[j]= temp;

			}
		}
	cout << endl << "Produtos do SuperEDA por ordem crescente de Pre�o: " << endl;
	for (int i = 0; i < n_prods; i++) {
		cout << "Produto: " << todos_produtos[i].nome << " -> " << todos_produtos[i].preco << "$" << endl;
	}
}

