#include <iostream>
#include <string>

using namespace std;


int contaLinhas(string ficheiro);
void leFicheiro(string ficheiro,string* lista);
void gravaSetores(setor* setores, int n_setores);
void gravaArmazem(produto* armazem, int n_produtos);
produto* carregaArmazem(int tamArmazem);
setor* carregaSetores();
