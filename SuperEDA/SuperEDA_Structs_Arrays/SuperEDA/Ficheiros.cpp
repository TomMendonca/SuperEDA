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
void leFicheiro(string ficheiro,string*lista) {
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

//Grava tudo o que está nos setores para ficheiros .txt - Guardar Supermercado
void gravaSetores(setor* setores, int n_setores) {
	ofstream file;
	file.open("Resp_Areas.txt"); //Criar um ficheiro que guarda os responsaveis pelos setores e as areas de cada setor
	for (int i = 0;i < n_setores;i++) {
		file << setores[i].responsavel << endl << setores[i].area << endl; // Escreve numa linha o responsavel e na seguinte a area(faz isto para todos os  setores)
	}
	file.close(); // Fechar o ficheiro criado

	file.open("InfoSet.txt"); //Criar um ficheiro que guarda o identificador, o numero de produtos, a capacidade e o numero de produtos do registo de cada setor(isto é gravado de maneira a ser lido por formato)
	for (int i = 0;i < n_setores;i++) {
		file << setores[i].identificador << " | " << setores[i].num_produtos << " | " << setores[i].capacidade <<  " | " << setores[i].n_produtos_registo << endl;
	}
	file.close();
	
	file.open("NomesP.txt"); //Cria um ficheiro que guarda por linha os nomes dos produtos de cada setor
	for (int i = 0;i < n_setores;i++) {
		for (int j = 0; j < setores[i].num_produtos;j++) { 

			file << setores[i].produtos[j].nome << endl;
		}
	}
	file.close();
	
	file.open("FornecedoresP.txt");	//Cria um ficheiro que guarda por linha os fornecedores dos produtos de cada setor
	for (int i = 0;i < n_setores;i++) {
		for (int j = 0; j < setores[i].num_produtos;j++) {

			file << setores[i].produtos[j].fornecedor << endl;
		}
	}
	file.close();

	file.open("PrecosP.txt");//Cria um ficheiro que guarda por linha os preços dos produtos de cada setor
	for (int i = 0;i < n_setores;i++) {
		for (int j = 0; j < setores[i].num_produtos;j++) {

			file << setores[i].produtos[j].preco << endl;
		}
	}
	file.close();

	file.open("RegistoNomes.txt");	//Cria um ficheiro que guarda por linha os nomes dos produtos do registo de vendas
	for (int i = 0;i < n_setores;i++) {
		for (int j = 0;j < setores[i].n_produtos_registo;j++) {
			file << setores[i].registo[j].nome << endl;
		}
	}
	file.close();

	file.open("RegistoPrecos.txt");
	for (int i = 0;i < n_setores;i++) { //Cria um ficheiro que guarda por linha os preços dos produtos do registo de vendas
		for (int j = 0;j < setores[i].n_produtos_registo;j++) {
			file << setores[i].registo[j].preco << endl;
		}
	}
	file.close();
}


//Grava tudo o que está no armazém para ficheiros .txt - Guardar Supermercado
void gravaArmazem( produto* armazem, int n_produtos) {
	ofstream file;
	file.open("Armazem.txt");//cria um ficheiro que guarda por linha o nome, fornecedor e area de cada produto do armazém

	for (int i = 0;i < n_produtos;i++) {
		file <<armazem[i].nome << endl << armazem[i].fornecedor << endl  << armazem[i].area << endl;
	}
	file.close();

	file.open("PrecosArmazem.txt");//cria um ficheiro que guarda por linha o preço de cada produto do armazém

	for (int i = 0;i < n_produtos;i++) {
		file << armazem[i].preco << endl;
	}
	file.close();
}


//Carrega todos os ficheiros .txt com a informação dos Setores - Carregar Supermercado
setor* carregaSetores() {
	int size = contaLinhas("InfoSet.txt"); // O número de setores é  neste caso o número de linhas do ficheiro "InfoSet.txt" 
	setor* novosSetores = new setor[size]; // criação de array dinâmico para guardar os setores

	int i = 0;
	fstream InfoSet("InfoSet.txt", ios::in); // ler o ficheiro "InfoSet.txt"
	char id, c;
	int n_produtos, capacidade, n_produtos_registo;

	while ((InfoSet >> id >> c >> n_produtos >> c >> capacidade >> c >> n_produtos_registo)  ) { //Lê enquanto cada linha tiver esse formato 
		novosSetores[i].identificador = id;														//O primeiro elemento de cada linha corresponde aos ids dos setores
		novosSetores[i].num_produtos = n_produtos;												//O segundo elemento de cada linha corresponde ao numero de produtos dos setores
		novosSetores[i].capacidade = capacidade;												//O terceiro elemento de cada linha corresponde á capacidade dos setores
		novosSetores[i].n_produtos_registo = n_produtos_registo;								//O último elemento de cada linha corresponde ao número de produtos do registo dos setores
		i++;
	}
	//2 elementos(responsavel,area)
	int elemento = 0;																			
	//setor correspondente
	int s = 0;

	string line;		
	ifstream Resp_Areas("Resp_Areas.txt");
	while (getline(Resp_Areas, line)) {

		if (elemento == 0) {
			novosSetores[s].responsavel = line;//O primeiro elemento é o responsável
			elemento++;

		}
		else if (elemento == 1) {
			novosSetores[s].area = line;//O segundo elemento é a area
			elemento=0;					//Volta a 0 porque o seguinte elemento irá ser outro responsável 
			s++;						//Passa para o setor seguinte
		}
	}
	Resp_Areas.close();
	
	//Criação dos arrays de produtos para cada setor
	for (int i = 0;i < size;i++) {
		novosSetores[i].produtos = new produto[novosSetores[i].capacidade];
	}

	string* nomes = new string[contaLinhas("NomesP.txt")];
	i = 0;
	ifstream NomesP("NomesP.txt");
	while (getline(NomesP, line)) {
		nomes[i] = line;
		i++;
	}
	NomesP.close();

	int contaNomes = 0;
	for (int i = 0;i < size;i++) {
		for (int j = 0; j < novosSetores[i].num_produtos; j++) {
			
				novosSetores[i].produtos[j].nome = nomes[contaNomes];
				contaNomes++;
		}
		
	}

	string* fornecedores = new string[contaLinhas("FornecedoresP.txt")];
	i = 0;
	ifstream FornecedoresP("FornecedoresP.txt");
	while (getline(FornecedoresP, line)) {
		fornecedores[i]= line;
		i++;
	}
	FornecedoresP.close();
	int contaFornecedores = 0;
	
	for (int i = 0;i < size;i++) {
		
		for (int j = 0; j < novosSetores[i].num_produtos;j++) {
			novosSetores[i].produtos[j].fornecedor = fornecedores[contaFornecedores];
			contaFornecedores++;
		}
	}
	

	int* precos = new int[contaLinhas("PrecosP.txt")];
	i = 0;
	fstream file("PrecosP.txt", ios::in);
	int preco;
	while ((file >> preco)) {
		precos[i] = preco;
		i++;
	}
	int contaPrecos = 0;
	for (int i = 0;i < size;i++) {
		for (int j = 0; j < novosSetores[i].num_produtos;j++) {
				novosSetores[i].produtos[j].preco = precos[contaPrecos];
				contaPrecos++;
		}
	}


	for (int i = 0;i < size;i++) {
		novosSetores[i].registo = new produto[100];
		for (int j = 0;j < novosSetores[i].num_produtos;j++) {
			novosSetores[i].produtos[j].area = novosSetores[i].area;
		}
	}


	string* nomesRegisto = new string[contaLinhas("RegistoNomes.txt")];
	i = 0;
	ifstream RegistoNomes("RegistoNomes.txt");
	while (getline(RegistoNomes, line)) {
		nomes[i] = line;
		i++;
	}
	RegistoNomes.close();

	int contaNomesR = 0;
	for (int i = 0;i < size;i++) {
		for (int j = 0; j < novosSetores[i].n_produtos_registo; j++) {

			novosSetores[i].registo[j].nome = nomes[contaNomesR];
			contaNomesR++;
		}

	}


	int* precosR = new int[contaLinhas("RegistoPrecos.txt")];
	i = 0;
	fstream precos_registo("RegistoPrecos.txt", ios::in);
	int precoR;
	while ((precos_registo >> precoR)) {
		precosR[i] = precoR;
		i++;
	}
	int contaPrecosR = 0;
	for (int i = 0;i < size;i++) {
		for (int j = 0; j < novosSetores[i].n_produtos_registo;j++) {
			novosSetores[i].registo[j].preco = precosR[contaPrecosR];
			contaPrecosR++;
		}
	}

	return novosSetores;
}


//Carrega todos os ficheiros .txt com a informação do Armazém - Carregar Supermercado
produto* carregaArmazem(int tamArmazem) {
	produto* novoArmazem = new produto[tamArmazem];
	
	//4 elementos(nome, fornecedor, preço, area)
	int elemento = 0;

	//Produto só incrementa depois dos 4 elementos(nome,fornecedor,preço,area)
	int produto = 0;


	string line;
	ifstream MyReadFile("Armazem.txt");
	while (getline(MyReadFile, line)) {
		if (elemento == 0) {
			novoArmazem[produto].nome = line;
			elemento++;
			
		}
		else if (elemento == 1) {
			novoArmazem[produto].fornecedor = line;
			elemento++;
			
		}
		else if (elemento == 2) {
			novoArmazem[produto].area = line;
			elemento = 0;
			produto++;

		}	
	}
	MyReadFile.close();

	int i = 0;
	fstream InfoSet("PrecosArmazem.txt", ios::in);
	int preco;
	while ((InfoSet >> preco)) {
		novoArmazem[i].preco = preco;
		i++;
	}
	return novoArmazem;
}
