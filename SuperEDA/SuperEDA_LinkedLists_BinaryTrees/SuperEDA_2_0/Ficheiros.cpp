#include <iostream>
#include <string>
#include <fstream>
#include "SuperMercado.h"

using namespace std;

//Conta linhas de um ficheiro .txt
int contaLinhas(string ficheiro) {
	int cont = 0;
	ifstream file;
	string line;
	file.open(ficheiro);
	if (file.is_open()) {
		while (getline(file, line)) {
			cont++;
		}
	}
	file.close();
	return cont;
}

//Lê o conteúdo do ficheiro .txt
void leFicheiro(string ficheiro, string* lista) {
	int aux = 0;
	ifstream myFile;
	string line;
	myFile.open(ficheiro);
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			lista[aux] = line;
			aux++;
		}
	}
	myFile.close();
}


//CASO 4 e CASO 5
//GRAVAR E CARREGAR O SUPERMERCADO

//Grava tudo o que está no armazém para ficheiros .txt - Guardar Supermercado
void gravaArmazem(nodeProduto* armazemHead) {
	ofstream file;
	file.open("Armazem.txt");//cria um ficheiro que guarda por linha o nome, fornecedor e area de cada produto do armazém
	nodeProduto* iterator1 = armazemHead;
	while (iterator1 != NULL) {
		file << iterator1->nome << endl << iterator1->fornecedor << endl << iterator1->area << endl;
		iterator1 = iterator1->next;
	}
	file.close();

	file.open("PrecosArmazem.txt");//cria um ficheiro que guarda por linha o preço de cada produto do armazém
	nodeProduto* iterator2 = armazemHead;
	while (iterator2 != NULL) {
		file << iterator2->preco << endl;
		iterator2 = iterator2->next;
	}
	file.close();
	cout << "Armazém Gravado com Sucesso\n";
}

//Carrega todos os ficheiros .txt com a informação do Armazém - Carregar Supermercado
nodeProduto* carregaArmazem(nodeProduto* armazemHead) {
	nodeProduto* iterator = armazemHead;
	nodeProduto* iterator1 = armazemHead;

	//4 elementos(nome, fornecedor, preço, area)
	int elemento = 0;

	//Produto só incrementa depois dos 4 elementos(nome,fornecedor,preço,area)
	int produto = 0;


	string line;
	ifstream MyReadFile("Armazem.txt");
	while (getline(MyReadFile, line)) {
		if (elemento == 0) {
			iterator->nome = line;
			elemento++;

		}
		else if (elemento == 1) {
			iterator->fornecedor = line;
			elemento++;

		}
		else if (elemento == 2) {
			iterator->area = line;
			elemento = 0;
			produto++;
			iterator = iterator->next;
		}

	}
	MyReadFile.close();

	fstream InfoSet("PrecosArmazem.txt", ios::in);
	int preco;
	while ((InfoSet >> preco)) {
		iterator1->preco = preco;
		iterator1 = iterator1->next;
	}
	cout << "Armazem Carregado com Sucesso\n";
	return armazemHead;
}



//Grava tudo o que está nos setores para ficheiros .txt - Guardar Supermercado
void gravaSetores(nodeSetor* setoresHead) {

	ofstream file;

	file.open("Responsaveis_Areas.txt"); //Criar um ficheiro que guarda os responsaveis pelos setores e as areas de cada setor
	nodeSetor* iterator1 = setoresHead;

	while (iterator1 != NULL) {
		file << iterator1->responsavel << endl << iterator1->area << endl; // Escreve numa linha o responsavel e na seguinte a area(faz isto para todos os  setor
		iterator1 = iterator1->next;
	}
	file.close(); // Fechar o ficheiro criado



	file.open("InfoSet.txt"); //Criar um ficheiro que guarda o identificador, o numero de produtos, a capacidade e o numero de produtos do registo de cada setor(isto é gravado de maneira a ser lido por formato)
	nodeSetor* iterator2 = setoresHead;
	while (iterator2 != NULL) {
		file << iterator2->identificador << " | " << iterator2->num_produtos << " | " << iterator2->capacidade << endl;
		iterator2 = iterator2->next;
	}
	file.close();



	file.open("FornecedoresP.txt");	//Cria um ficheiro que guarda por linha os fornecedores dos produtos de cada setor
	nodeSetor* iterator4 = setoresHead;
	while (iterator4 = NULL) {
		while (iterator4->produtosHead != NULL) {
			file << iterator4->produtosHead->fornecedor << endl;
			iterator4->produtosHead = iterator4->produtosHead->next;
		}
		iterator4 = iterator4->next;

	}
	file.close();

	file.open("NomesP.txt"); //Cria um ficheiro que guarda por linha os nomes dos produtos de cada setor

	nodeSetor* iterator3 = setoresHead;
	while (iterator3 != NULL) {
		while (iterator3->produtosHead != NULL) {
			file << iterator3->produtosHead->nome << endl;
			iterator3->produtosHead = iterator3->produtosHead->next;
		}
		iterator3 = iterator3->next;

	}
	file.close();

	file.open("PrecosP.txt");//Cria um ficheiro que guarda por linha os preços dos produtos de cada setor
	nodeSetor* iterator5 = setoresHead;
	while (iterator5 != NULL) {
		while (iterator5->produtosHead != NULL) {
			file << iterator5->produtosHead->preco << endl;
			iterator5->produtosHead = iterator5->produtosHead->next;
		}
		iterator5 = iterator5->next;

	}
	file.close();


	cout << "Setor Gravado com Sucesso\n";
}

//Não consigos colocar a funcionar :/
//Carrega todos os ficheiros .txt com a informação dos Setores - Carregar Supermercado
/*
void carregaSetores(nodeSetor*& setoresHead) {
	int i = 0;
	fstream InfoSet("InfoSet.txt", ios::in); // ler o ficheiro "InfoSet.txt"
	char id, c;
	int n_produtos, capacidade, n_produtos_registo;
	nodeSetor* iterator = setoresHead;

	while ((InfoSet >> id >> c >> n_produtos >> c >> capacidade >> c >> n_produtos_registo)) {
		 iterator->identificador=id;
		 iterator->identificador = n_produtos;
		 iterator->identificador = capacidade;
		 iterator->identificador = n_produtos_registo;
		 iterator = iterator->next;

		i++;
	}
	//2 elementos(responsavel,area)
	int elemento = 0;

	nodeSetor* iterator1 = setoresHead;
	string line;
	ifstream Resp_Areas("Resp_Areas.txt");
	while (getline(Resp_Areas, line)) {

		if (elemento == 0) {
			iterator1->responsavel = line;//O primeiro elemento é o responsável
			elemento++;

		}
		else if (elemento == 1) {
			iterator1->area = line;
			elemento = 0;
			iterator1 = iterator1->next;

		}
	}
	Resp_Areas.close();



	nodeSetor* iterator2 = setoresHead;
	i = 0;
	ifstream NomesP("NomesP.txt");
	while (getline(NomesP, line)) {
		iterator2->produtosHead->nome = line;
		if (iterator2->produtosHead->next == NULL) {
			iterator2->produtosHead = iterator2->produtosHead->next;

		}
		else {
			iterator2->produtosHead = iterator2->produtosHead->next;

		}

	}
	NomesP.close();



}
*/


