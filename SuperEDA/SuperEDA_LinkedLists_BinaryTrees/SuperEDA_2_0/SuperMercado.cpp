#include <iostream>
#include <string>
#include "SuperMercado.h"
#include "Ficheiros.h"

using namespace std;

//--------- NODEPRODUTO ---------//
//Cria uma nova struct nodeProduto
nodeProduto* criaNodeProduto(string* produtos, string* fornecedores, string* areasSetores, int n_areas) {
	int aux = 1;
	nodeProduto *novo = new nodeProduto;
	novo->nome = produtos[rand() % contaLinhas("nome.txt")];
	novo->fornecedor = fornecedores[rand() % contaLinhas("fornecedores.txt")];
	novo->area = areasSetores[rand() % n_areas];
	novo->campanha = false;

	while ((aux % 2) != 0) {
		aux = rand() % 80 + 1;
	}
	if ((aux % 2) == 0) {
		novo->preco = aux;
	}
	return novo;
}
//Insere um produto numa lista de produtos (nodeProduto)
void insereProduto(nodeProduto*& head, nodeProduto* novo ) {
	nodeProduto* temp = head;// Criar node Temporário
	
	if (head == NULL) { //Insere o produto se a lista está vazia
		head = novo;
		novo->next = NULL;
	}
	else {
		while (temp->next != NULL) { //Insere o produto no final da lista
			temp = temp->next;
		}
		temp->next = novo;
		novo->next = NULL;
	}
}


//--------- NODESETOR ---------//
//Cria um novo setor (nodeSetor)
nodeSetor* criaNodoSetor(string* areas, char id) {
	//Cria um novo nodeSetor 
	nodeSetor *novo_setor = new nodeSetor;
	//Damos os valores das variaveis
	novo_setor->identificador = id;
	novo_setor->area = areas[rand() % contaLinhas("areas.txt")]; //Qual a area do setor
	novo_setor->num_produtos = 0; //Numero inicial de produtos, 0.
	novo_setor->capacidade = rand() % 6 + 5; //Produtos máximos no supermercado

	//Iniciar a Lista de Produtos
	novo_setor->produtosHead = NULL;

	//Não impementado
	//REGISTO
	
	cout << "Introduza o responsável pelo setor " << novo_setor->identificador << " : ";
	getline(cin, novo_setor->responsavel);
	return novo_setor;
}

//Insire um setor numa lista ligada de setores
void insereSetor(nodeSetor*& head, nodeSetor *novo_setor) {
	nodeSetor* temp = head;// Criar node Temporário
	
	if (head == NULL) { //Insere o setor se a lista está vazia
		head = novo_setor;
		novo_setor->next = NULL;
	}
	else { //Insere o setor no final da lista
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = novo_setor;
		novo_setor->next = NULL;
	}
}


//	VISUALIZAÇÂO: IMPRIMIR OS PORDUTOS DOS SETORES E ARMAZÉM
//Função para imprimir todos os produtos dos Setores
void imprimeSetor(nodeSetor* head, int numSetores) {
	cout << endl << endl << "______________________________________________SuperEDA______________________________________________" << endl << endl;
	//Cria Auxiliars
	nodeSetor* iteratorSetores = head;
	nodeProduto* iteratorProdutos = new nodeProduto;
	//Percoore os setores todos
	for (int i = 0; i < numSetores; i++) {
		cout << endl << " Setor " << iteratorSetores->identificador << " | " << "Responsável : " << iteratorSetores->responsavel << " | " << "Produtos : " << iteratorSetores->num_produtos << " | " << "Capacidade : " << iteratorSetores->capacidade << " | " << "Área : " << iteratorSetores->area << endl;
		//Lista de produtos dentro da Lista de Setores
		iteratorProdutos = iteratorSetores->produtosHead;
		if (iteratorSetores == NULL) {//Não tem produtos
			cout << "  Não contém produtos de momento!" << endl << endl;
		}
		else {
			while (iteratorProdutos != NULL) {//Tem Produtos
				cout << "  Produto: " << iteratorProdutos->nome << " | " << "Fornecedor: " << iteratorProdutos->fornecedor << " | " << "Preço: " << iteratorProdutos->preco << " $" << endl;
				iteratorProdutos = iteratorProdutos->next;
			}
		}
		iteratorSetores = iteratorSetores->next;//Próximo setor
	}
}

//Imprime todos os produtos do armazém
void imprimeArmazem(nodeProduto* head) {
	cout << endl << endl << " ______________________________________________ARMAZÉM_____________________________________________" << endl << endl;
	int prodNum = 1;//Numear os produtos no armazém
	//Cria Apontador Auxiliar
	nodeProduto* iterator = head;
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	while (iterator != NULL) { //Enquanto não cehagr ao último elemento
		cout << prodNum << ": " << "PRODUTO: " << iterator->nome << " | " << "FORNECEDOR: " << iterator->fornecedor << " | " << "PREÇO: " << iterator->preco << " $" << " | " << "ÁREA: " << iterator->area << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		iterator = iterator->next;//Próximo
		prodNum++;
	}
	cout << endl;
	cout << endl;
}



//Remove 1 só produto 
void removeProduto(nodeProduto*& head, nodeProduto* nodo_a_remover) {
	if (head == NULL) { return; }
	else {
		bool remove = false;
		if (head == nodo_a_remover) { //Remove no inicio
			nodeProduto* aux = head;
			head = head->next;
			delete aux;
			remove = true;
			
		}
		else {	// remove se o produto indicado pelo nome for o último produto da lista
			nodeProduto* aux = head; 
			while (aux->next->next != NULL) //Até chegar ao fim
			{
				aux = aux->next;
			}
			if (aux->next == nodo_a_remover) {
				delete aux->next;
				aux->next = NULL;
				remove = true;

			}
		}
		if (remove == false) { //Remove noutros casos
			nodeProduto* prod = head;
			nodeProduto* prodnext = head->next;

			while (prodnext != nodo_a_remover) {   //Conta o número de ciclos necessários para remover o produto que tem o nome indicado
				prod = prod->next;
					prodnext = prodnext->next;
			}
			prod = prod->next->next;
			prodnext = NULL;
		}
		
	}
}

//Remove um produto do armazém e acresenta no setor
void insereProdutoNoSetor(nodeProduto*& armazemHead, nodeSetor*& setoresHead) {
	//Criar apontadores auxiliares
	nodeProduto* armazem_iterator = armazemHead;
	nodeProduto* aux_armazem = armazemHead;
	nodeProduto* prev_aux_armazem = armazemHead;
	nodeSetor* aux_setor = setoresHead;
	bool move_para_setor = false;//Já moveu algum produto?
	while (move_para_setor == false && armazem_iterator->next != NULL) {

		if (aux_armazem->area == aux_setor->area && aux_setor->num_produtos < aux_setor->capacidade) {//Encontrou produto no setor
			if (aux_armazem == armazemHead) {//Se for o primeiro produto
				armazemHead = armazemHead->next;
				insereProduto(aux_setor->produtosHead, aux_armazem);
				aux_setor->num_produtos++;
				move_para_setor = true;

			}
			else if(aux_armazem == armazemHead->next){//Se for o segundo produto

				armazemHead->next = armazemHead->next->next;
				insereProduto(aux_setor->produtosHead, aux_armazem);
				aux_setor->num_produtos++;
				move_para_setor = true;

			}		
		}
		else if(aux_setor->next!=NULL) {//Next setor se o proximo não for null
			aux_setor = aux_setor->next;
		}
		else {//proximo setor == NULL
			aux_setor = setoresHead;
			prev_aux_armazem = aux_armazem;
			aux_armazem = aux_armazem->next;
		}
		armazem_iterator = armazem_iterator->next;//Proximo produto do aramazém
	}
}
		


//****************************** SIMULAÇÃO ******************************//

//Função para simulara  venda de produtos dos setores
void vender(nodeSetor* setoresHead) {
	//Auxiliares
	nodeSetor* iteratorSetor = setoresHead;
	nodeProduto* iteratorProduto = NULL;
	while (iteratorSetor->next != NULL) {//Todos os setores
		iteratorProduto = iteratorSetor->produtosHead;

		if (iteratorProduto == NULL) {
			iteratorSetor = iteratorSetor->next;

		}
		else {
			while (iteratorProduto->next != NULL) { //Enquanto houver produtos
				if (rand() % 4 + 1 == 1) {//25% para vender
					removeProduto(iteratorSetor->produtosHead, iteratorProduto);//"Vende o produto", remove do armazém e coloca nos setores
					break; 
				}
				iteratorProduto = iteratorProduto->next; // prox produto
			}
			iteratorSetor = iteratorSetor->next;//prox setor
		}
	}
}



//******************************* Menu Gestor *******************************//

//***CASO 1
//Remove o produto por nome dos setores e armazem
void removeProdutoSuperMercado(nodeProduto*& armazemHead, nodeSetor*& setoresHead) {
	//Auxiliar para Remover produto dos setores
	nodeSetor* iteratorS = setoresHead;

	//Auxiliar para Remover produto no armazém
	nodeProduto* iteratorA;
	nodeProduto* iterator_produtos_do_setor;
	
	int numProdsA = 0;
	string nomeProduto;//user input

	cout << "Insira o nome do produto que pretente remover: ";
	getline(cin, nomeProduto);
	cout << endl;

	//Remove do armazem
	if (armazemHead->nome == nomeProduto) { // remove se o produto indicado pelo nome for o primeiro produto da lista
		nodeProduto* aux = armazemHead;
		armazemHead = armazemHead->next;
		delete aux;
		cout << "Produto removido com sucesso do armazém!!! \n";
	}
	else {									// remove se o produto indicado pelo nome for o último produto da lista
		nodeProduto* aux = armazemHead;
		while (aux->next->next != NULL)
		{
			aux = aux -> next;
		} 
		if (aux->next->nome == nomeProduto) {
			delete aux->next;
			aux -> next = NULL;
			cout << "Produto removido com sucesso do armazém!!! \n";
		}
	}

	nodeProduto* aux = armazemHead;
	while (aux->next != NULL) {    //Conta o número de ciclos necessários para remover o produto que tem o nome indicado
		if (aux->nome == nomeProduto) {
			numProdsA++;
		}
		aux = aux->next;
	}

	for (int i = 0; i < numProdsA; i++) { // Cada ciclo elimina um produto do meio da lista 
		iteratorA = armazemHead;
		while (iteratorA->next->nome != nomeProduto) {
			iteratorA = iteratorA->next;
		}
		iteratorA->next = iteratorA->next->next;
		cout << "Produto removido com sucesso do armazém!!! \n";
	}
}

//***CASO 2
//Atualiza um preço do armazém
void atualizarPreco(nodeProduto*& head) {
	string nomeProd; //Nome to Produto para procurar
	int novoPreco; //Novo preço do produto
	bool existeProduto = false; //Encontrou o produto no armazém
	bool precoValido = false; //Preço é válido
	nodeProduto* iterator = head;

	cout << "Introduza o nome do Produto que deseja modificar: ";
	getline(cin, nomeProd);
	cout << "Introduza o novo preço: ";
	cin >> novoPreco;
	//Preço tem de ser válido PAR
	while (precoValido == false) {
		if (novoPreco % 2 == 1) {//Preço inválido ÍMPAR
			cout << "Introduza um preço válido: ";
			cin >> novoPreco;
		}
		else {
			precoValido = true; //Preço válido PAR
		}
	}

	//Percorre o armazém e atualiza o preço do Produto
	while (iterator->next != NULL) { //Enquanto existir
		if (iterator->nome == nomeProd) { //Encontrou o produto
			iterator->preco = novoPreco;	// Atualiza o Preço
			cout << "Preço atualizado com sucesso" << endl;
			existeProduto = true;//Existe produto 
		}
		iterator = iterator->next; //Próximo
	}
	//Verifica o último elemento da Lista Ligada!
	if (iterator->nome == nomeProd) {
		iterator->preco = novoPreco;	// Atualiza o Preço
		cout << "Preço atualizado com sucesso" << endl;
		existeProduto = true;//Existe produto 
	}
	//Não existe produto no Armazém
	if (existeProduto == false) {
		cout << "Infelizmente o produto inserido não é válido!\nO item pode não se encontrar de momento em stock!" << endl;
	}
}
//**CASO3
//Não Imprementado

//**CASO4
// No Ficheiros.cpp

//**CASO5
// no Ficheiros.cpp


//**CASO6
//Imprime todos os produtos
void imprimirProdutos(nodeProduto* armazemHead, nodeSetor* setoresHead, int numSetores) {
	int prodNum = 1;
	//armazem
	nodeProduto* iterator = armazemHead; //cria apontadors lista auxiliar
	//setores
	nodeSetor* iteratorSetores = setoresHead;
	nodeProduto* iteratorProdutos = new nodeProduto;
	cout << endl << endl << "_______________________________________PRODUTOS_SUPERMERCADO_______________________________________" << endl << endl;
	//Imprimir setores
	for (int i = 0; i < numSetores; i++) {
		//Lista de produtos dentro da Lista de Setores
		iteratorProdutos = iteratorSetores->produtosHead;
		while (iteratorProdutos != NULL) {
			cout << prodNum << ": " << "PRODUTO: " << iteratorProdutos->nome << " | " << "FORNECEDOR: " << iteratorProdutos->fornecedor << " | " << "PREÇO: " << iteratorProdutos->preco << " $" << " | " << "ÁREA: " << iteratorProdutos->area << endl;
			cout << "----------------------------------------------------------------------------------------------------" << endl;
			prodNum++;
			iteratorProdutos = iteratorProdutos->next;//Proximo
		}
		iteratorSetores = iteratorSetores->next;
	}
	//Imprimir Armazém
	while (iterator != NULL) { //Enquanto não chegar ao último elemento
		cout << prodNum << ": " << "PRODUTO: " << iterator->nome << " | " << "FORNECEDOR: " << iterator->fornecedor << " | " << "PREÇO: " << iterator->preco << " $" << " | " << "ÁREA: " << iterator->area << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		iterator = iterator->next;//Próximo
		prodNum++;
	}
}


//**CASO 7
//Cria uma nova area que o utilizador introduz
string* criaArea(string* areasSetores, int n_areas) {
	string* novasAreas = new string[n_areas + 1];
	string novaArea;
	cout << "Introduza uma nova área: ";
	cin.ignore();
	getline(cin, novaArea);
	cout << "A área " << novaArea << " foi criada." << endl;
	for (int i = 0; i < n_areas; i++) {
		novasAreas[i] = areasSetores[i];
	}
	novasAreas[n_areas] = novaArea;
	return novasAreas;
}
