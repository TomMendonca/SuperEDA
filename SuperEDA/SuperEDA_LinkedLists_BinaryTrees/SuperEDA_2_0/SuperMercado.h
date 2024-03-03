#pragma once
#include <iostream>
#include <string>

using namespace std;

struct nodeProduto {
	//Atributos
	string nome, fornecedor, area;
	int preco;
	bool campanha;
	//próximo node
	nodeProduto* next;//Próximo produto
};

struct nodeSetor {
	//Atributos
	char identificador;
	string responsavel, area;
	int num_produtos, capacidade;
	//float desconto; Iria ser usado no Caso 3 campanha
	
	nodeProduto* produtosHead;//Onde começa a Lista Ligada

	//Não Implimentado
	//produto* registo; 
	//int n_produtos_registo;
	
	//próximo node
	nodeSetor* next; //Próximo setor
};


///   NODEPRODUTO   //
nodeProduto* criaNodeProduto(string* produtos, string* fornecedores, string* areasSetores, int n_areas);
void insereProduto(nodeProduto*& head, nodeProduto* novo);


//   NODESETOR  //
nodeSetor* criaNodoSetor(string* areas, char id);
void insereSetor(nodeSetor*& head, nodeSetor* novo_setor);


//Simulação
//Visualização
void imprimeSetor(nodeSetor* head, int numSetores);
void imprimeArmazem(nodeProduto* head);
//Funcionamento do Supermercado 
void removeProduto(nodeProduto*& armazemHead, nodeProduto* nodo_a_remover);
void insereProdutoNoSetor(nodeProduto*& armazemHead, nodeSetor*& setoresHead);
void vender(nodeSetor* setoresHead);



//MENU Gestor
//Caso1
void removeProdutoSuperMercado(nodeProduto*& armazemHead, nodeSetor*& setoresHead);

//Caso2
void atualizarPreco(nodeProduto*& head);

//CASO 6
void imprimirProdutos(nodeProduto* armazemHead, nodeSetor* setoresHead, int numSetores);

//Caso 7
string* criaArea(string* areasSetores, int n_setores);