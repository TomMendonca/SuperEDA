#pragma once
#include <iostream>
#include <string>

using namespace std;

//Trabalhar com Ficheiros do Professor
int contaLinhas(string ficheiro);
void leFicheiro(string ficheiro, string* lista);

//Trabalhar com ficheiros Nossos
void gravaSetores(nodeSetor* setoresHead);
void gravaArmazem(nodeProduto* armazemHead);
//void carregaSetores(nodeSetor*& setoresHead);
nodeProduto* carregaArmazem(nodeProduto* armazemHead);