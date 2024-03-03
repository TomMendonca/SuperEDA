#pragma once
#include <iostream>
#include <string>


using namespace std;

struct produto {
	string nome, fornecedor, area;
	int preco;
	bool campanha;
};


struct setor {
	char identificador;
	string responsavel, area;
	int num_produtos, capacidade;
	produto* produtos;
	produto* registo;
	int n_produtos_registo;
	float desconto;
};


setor criaSetor(string* areas, char id);
void imprimeSetor(int n, setor* setores);
produto criaProduto(string* produtos, string* fornecedores, string* areaSetor, int n_areas);
void imprimeArmazem(produto* armazem, int n_produtos);
bool addProduto(produto* armazem, setor* setores, int numSetores, int n_produtos);
void removeProduto(produto* lista, produto p, int n_produtos);
int remove_produto_por_nome(setor* setores, int n_setores, produto* armazem, int n_produtos);
void vender(setor* setores, int n_setores);
string* criaArea(string* areasSetores, int n_setores);
setor* alteraArea(setor* setores, int numSetores, string* areas, int n_areas);
setor* campanha(setor* setores, int numSetores);
produto* atualizaPreco(produto* armazem, int n_produtosArmazem);
void imprimeProdutoAlf(produto* armazem, setor* setores, int n_produtosArmazem, int numSetores);
void imprimeProdutoPreco(produto* armazem, setor* setores, int n_produtosArmazem, int numSetores);
