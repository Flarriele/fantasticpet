//Projeto (Pet Shop  -  Fantastic Pet)

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <strings.h>

/*
 Criando constantes para o status de atendimento
*/
const char ATENDIMENTO_EM_ESPERA[] = "ATENDIMENTO EM ESPERA"; 
const char EM_ATENDIMENTO[] = "EM_ATENDIMENTO";
const char ATENDIMENTO_FINALIZADO[] = "ATENDIMENTO FINALIZADO";
const char ATENDIMENTO_PAGO[] = "ATENDIMENTO PAGO";

/*
 Declaracao das estruturas
*/

struct Pet;
struct NoPet;
struct Tutor;
struct NoTutor;
struct Atendimento;
struct NoAtendimento;

/*
 Armazenar dados Pet
*/

struct Pet {
	char nome[50];
	char tipo[50];
	int idade;
	float peso;
	char raca[50];
	Tutor *tutor; //**Conecta um tutor a um pet (guarda o endereco de um tutor)
};

/*
 Estrutura para o no de uma lista de pets
*/

struct NoPet {
	Pet *pet; //**Aponta para o pet
	NoPet *proxPet; //**Aponta para o proximo pet da lista 
}; 

/*
 Armazenar dados Tutor
*/

struct Tutor {
	char nome[50];
	char numero[50];
	char endereco[100];
	NoPet *listaPets; //**lista de pets de cada tutor (Aponta para o primneiro NoPet da lista)
};

struct NoTutor {
	Tutor *tutor; //**Aponta para o tutor
	NoTutor *proxTutor; //**Aponta para o proximo tutor da lista
};

/*
 Estrutura para o Atendimento
*/

struct Atendimento {
	int idAtendimento;
	Pet *pet; //**Aponta para o pet atendido
	float valor; //**valor tera como base peso, tipo do animal e servico 
	char status[50];
	char nivelSatisfacao; //**Nivel de satisfacao do cliente (1-5)
};

/*
 Estrutura para o no da fila de atendimentos
*/

struct NoAtendimento {
	Atendimento *atendimento; //**Aponta para o atendimento
	NoAtendimento *proxAtendimento; //** Aponta para o proximo atendimento da lista
};

/*
 Variaveis globais para armazenar listas de pets, tutores e fila de atendimento
*/

NoPet *listaPets = NULL; //**inicia em nulo, pois aponta para o próximo da lista
NoTutor *listaTutores = NULL;
NoAtendimento *filaAtendimento = NULL;
Atendimento *emAtendimento = NULL;

/*
Declaracao das funcoes
*/

void menu();
void cadastrarTutor();
void cadastrarPet();
void inserirAtendimento();
void proximoAtendimento();
void finalizarAtendimento();
Tutor *buscarTutor();
Pet *buscarPet();
void imprimirTutores();
void imprimirPets();
void imprimirAtendimentos();
void cancelarAtendimento();

/*
Declaracao das funcoes de apoio
*/

int inserirPagamento(float valor);
int inserirSatisfacaoAtendimento();

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	menu();
	
}

void menu(){
	
	int opcaomenu;
	
	printf("--- Bem-Vindo à Fantastic Pet ---\n\n");
	printf("\nVamos começar: \n");
	

	do{
		printf("\nSelecione a opção que deseja realizar:\n1 - Cadastrar tutor\n2 - Cadastrar pet\n3 - Novo atendimento\n4 - Próximo atendimento\n5 - Buscar tutor\n6 - Buscar pet\n7 - Imprimir Tutores\n8 - Imprimir Pets\n9 - Imprimir Atendimentos\n10 - Finalizar atendimento\n11 - Cancelar Atendimento\n\n0 - Sair do sistema\n\n");
		scanf("%d", &opcaomenu);
		system("cls");

		switch(opcaomenu){
			case 1:
				cadastrarTutor();
				break;
			case 2:
				cadastrarPet();
				break;
			case 3:
			 	inserirAtendimento();
				break;
			case 4:
				proximoAtendimento();
				break;
			case 5:
				buscarTutor();
				break;
			case 6:
				buscarPet();
				break;
			case 7:
				imprimirTutores();
				break;
			case 8:
				imprimirPets();
				break;
			case 9:
				imprimirAtendimentos();
				break;
			case 10:
				finalizarAtendimento();
				break;
			case 11:
				cancelarAtendimento();
				break;
			case 0:
				printf("Encerrando...\n\n");
				break;
			default:
				printf("Opção inválida\n");
				break;				
		}
    
    	system("pause");
    	system("cls");
	} while(opcaomenu != 0);
}

void cadastrarTutor(){
	Tutor *tutor = (Tutor*)malloc(sizeof(Tutor)); //**Alocando memória para um novo tutor
	
	printf("\n\n--- Cadastro de Tutor ---\n\n");
	
	printf("Digite o nome do tutor: ");
    getchar();
    fgets(tutor->nome, sizeof(tutor->nome), stdin);
    tutor->nome[strcspn(tutor->nome, "\n")] = '\0';
 
    printf("Digite o numero do tutor: ");
    fgets(tutor->numero, sizeof(tutor->numero), stdin);
    tutor->numero[strcspn(tutor->numero, "\n")] = '\0';
    
    printf("Digite o endereço do tutor: ");
    fgets(tutor->endereco, sizeof(tutor->endereco), stdin);
    tutor->endereco[strcspn(tutor->endereco, "\n")] = '\0';
 
    NoTutor *novoTutor = (NoTutor*)malloc(sizeof(NoTutor)); //**Criou um no Tutor na memoria
    novoTutor->tutor = tutor; //**Informa o tutor do no, ou seja, o tutor que acabei de cadastrar 
    novoTutor->proxTutor = listaTutores; //**O proximo pet era o primeira da fila, ou seja, o ultimo antes desse a ser cadastrado. o próxio não e nulo 
    listaTutores = novoTutor; //**Esse no passa a ser o pimeiro da fila
	
	printf("\n\nCadastro concluído com sucesso!\n\n");
	
}
      
void cadastrarPet(){
    Pet *pet = (Pet*)malloc(sizeof(Pet)); //**Alocando memória para um novo pet
    
    printf("\n\n--- Cadastro de Pet ---\n\n");

    printf("Digite o nome do pet: ");
    getchar();
    fgets(pet->nome, sizeof(pet->nome), stdin);
    pet->nome[strcspn(pet->nome, "\n")] = '\0';

    printf("Digite o tipo do pet: ");
    fgets(pet->tipo, sizeof(pet->tipo), stdin);
    pet->tipo[strcspn(pet->tipo, "\n")] = '\0';

    printf("Digite a idade do pet: ");
    scanf("%d", &pet->idade);

    printf("Digite o peso do pet: ");
    scanf("%f", &pet->peso);

    printf("Digite a raça do pet: ");
    getchar();
    fgets(pet->raca, sizeof(pet->raca), stdin);
    pet->raca[strcspn(pet->raca, "\n")] = '\0';
    
    printf("Agora informe qual o tutor do pet\n\n");
	pet->tutor = buscarTutor();

	//**Erro ao encontrar um tutor cadastrado
    if (pet->tutor == NULL) {
		printf("\nPet não pode ser cadastrado sem tutor!\n");
    	return;
	}
    
    /*
    Adicionar novo pet na lista do tutor
    */
    
    NoPet *novoPetTutor = (NoPet*)malloc(sizeof(NoPet));
    novoPetTutor->pet = pet; 
    novoPetTutor->proxPet = pet->tutor->listaPets;  
    pet->tutor->listaPets = novoPetTutor; 

    NoPet *novoPetGlobal = (NoPet*)malloc(sizeof(NoPet)); //**Criou um noPET na memoria
    novoPetGlobal->pet = pet; //**Informa o pet do no, ou seja, o pet que acabei de cadastrar 
    novoPetGlobal->proxPet = listaPets; //**O proximo pet era o primeira da fila, ou seja, o ultimo antes desse a ser cadastrado. o próxio não e nulo 
    listaPets = novoPetGlobal; //**Esse no passa a ser o pimeiro da fila
	
    printf("\n\nPet cadastrado com sucesso!\n\n");
}

void inserirAtendimento(){
	
    Atendimento *atendimento = (Atendimento*)malloc(sizeof(Atendimento));  // Aloca memória para um novo atendimento

    printf("\n\n--- Inserir Atendimento ---\n\n");
    
    char nomePet[50];
    printf("Digite o nome do pet para o atendimento: ");
    getchar(); 
    fgets(nomePet, sizeof(nomePet), stdin);
    nomePet[strcspn(nomePet, "\n")] = '\0';  

    // Encontrar o pet na lista de pets
    NoPet *noAtual = listaPets;
    Pet *petEncontrado = NULL;
    while (noAtual != NULL) {
        if (strcmp(noAtual->pet->nome, nomePet) == 0) {
            petEncontrado = noAtual->pet;
            break;
        }
        noAtual = noAtual->proxPet;
    }
    
    if (petEncontrado == NULL) {
        printf("Pet não encontrado!\n");
        return;
    }
    
    // Associando o pet ao atendimento
    atendimento->pet = petEncontrado;

    // Calcular o valor do atendimento
    if (strcmp(petEncontrado->tipo, "Cachorro") == 0) {
        atendimento->valor = petEncontrado->peso * 15;
    } else if (strcmp(petEncontrado->tipo, "Gato") == 0) {
        atendimento->valor = petEncontrado->peso * 10;
    } else {
        atendimento->valor = petEncontrado->peso * 20;
    }

    // Definir o status do atendimento
    strcpy(atendimento->status, ATENDIMENTO_EM_ESPERA);
    
    // Inserir o atendimento na fila de atendimentos (no final da lista)
    NoAtendimento *novoAtendimento = (NoAtendimento*)malloc(sizeof(NoAtendimento));  // Aloca memória para o nó de atendimento
    novoAtendimento->atendimento = atendimento;
    novoAtendimento->proxAtendimento = NULL;  // O próximo atendimento será NULL, pois este é o último na fila

    if (filaAtendimento == NULL) {
        filaAtendimento = novoAtendimento;  // Se a fila estiver vazia, o novo atendimento é o primeiro
    } else {
        // Caso contrário, percorre a fila até o último atendimento
        NoAtendimento *noAtual = filaAtendimento;
        while (noAtual->proxAtendimento != NULL) {
            noAtual = noAtual->proxAtendimento;
        }
        // Adiciona o novo atendimento ao final da fila
        noAtual->proxAtendimento = novoAtendimento;
    }

    printf("\nAtendimento inserido com sucesso para o pet: %s\n", petEncontrado->nome);
}

void proximoAtendimento(){
	/*
	Verifica se a fila de atendimentos esta vazia
	*/
    if (filaAtendimento == NULL) {
        printf("\nNão há atendimentos pendentes na fila.\n\n");
        return;
    }
    
    /*
	Verifica se tem atendimento em andamento
	*/
    if (emAtendimento != NULL) {
        printf("\nHá um atendimento em andamento. Encerre-o antes de continuar.\n\n");
        return;
    }

    NoAtendimento *atendimentoAtual = filaAtendimento; //**Pega o primeiro atendimento da fila

    filaAtendimento = filaAtendimento->proxAtendimento; //**Atualiza a fila para apontar para o proximo atendimento

    Atendimento *atendimento = atendimentoAtual->atendimento;
    strcpy(atendimento->status, EM_ATENDIMENTO); //**Atualiza o status para "em atendimento"
    
    emAtendimento = atendimento;

    printf("\nAtendimento para o pet %s iniciado.\n", atendimento->pet->nome);
    
    free(atendimentoAtual); //**Liberar a memória do no atual, pois ele foi processado
}

void finalizarAtendimento(){
    Atendimento *atendimento = emAtendimento;

	strcpy(atendimento->status, ATENDIMENTO_FINALIZADO);

    printf("\n--- Detalhes do Pagamento ---\n");
    printf("Pet: %s\n", atendimento->pet->nome);
    printf("Valor do atendimento: %.2f\n", atendimento->valor);

    int pago = inserirPagamento(atendimento->valor);
    
    if (pago == 1) {
    	printf("\nPago com SUCESSO!\n");
    	
    	strcpy(atendimento->status, ATENDIMENTO_PAGO);
    	
    	atendimento->nivelSatisfacao = inserirSatisfacaoAtendimento();
    	if (atendimento->nivelSatisfacao >= 0 || atendimento->nivelSatisfacao <= 5) {
			printf("\nA nota para o atendimento foi %d!\n", atendimento->nivelSatisfacao);
    	} else {
    		printf("\nNão foi adicionado uma nota de atendimento.");
		}
		
    	emAtendimento = NULL;
	} else {
		printf("\nAtendimento não foi pago.\n");
	}

    printf("Status do atendimento: %s\n\n", atendimento->status);
}

void cancelarAtendimento(){
	imprimirAtendimentos();
	
	int escolha;
	printf("Digite o número do atendimento que deseja cancelar: ");
	scanf("%d", &escolha);
	
	NoAtendimento *atual = filaAtendimento;
    NoAtendimento *anterior = NULL;

    /*
	Caso a fila esteja vazia
	*/
    if (atual == NULL) {
        printf("A fila de atendimentos está vazia.\n");
        return;
    }

	int i = 0;
    while (atual != NULL && escolha <= i) {
        if (escolha == i) { //**Encontrou o atendimento a ser removido
            
            if (anterior == NULL) { //**O atendimento a ser removido está no início da fila
                filaAtendimento = atual->proxAtendimento;
            } else {
                anterior->proxAtendimento = atual->proxAtendimento; //**O atendimento a ser removido está no meio ou final da fila
            }
            
            /*
			Liberar a memória alocada para o atendimento e o nó
			*/
            free(atual->atendimento);
            free(atual);

            printf("Atendimento removido com sucesso.\n\n");
            return;
        }
        
        /*
        Avanca para proximo no
        */
        anterior = atual;
        atual = atual->proxAtendimento;
        i++;
    }

    // Se chegar aqui, não encontrou o atendimento com o ID
    printf("Atendimento %d não encontrado.\n", escolha);
}

Tutor *buscarTutor(){
	int escolha = 1;
	do {
    	char nomeBuscaTutor[50];
	
	    printf("\nDigite o nome do tutor que deseja buscar: ");
	    fgets(nomeBuscaTutor, sizeof(nomeBuscaTutor), stdin);
	    nomeBuscaTutor[strcspn(nomeBuscaTutor, "\n")] = '\0';
	
	    NoTutor *noAtual = listaTutores; //**Pega o endereço do primeiro no da lista que aponta para o proximo
	    
	    while (noAtual != NULL) {
	        if (strcmp(noAtual->tutor->nome, nomeBuscaTutor) == 0) { //**Compara o nome com o da busca (0 = encontrado)
	            printf("\nTutor encontrado!\nNome: %s\nNúmero: %s\nEndereço: %s\n", noAtual->tutor->nome, noAtual->tutor->numero, noAtual->tutor->endereco);
	            return noAtual->tutor;
	        }
	        noAtual = noAtual->proxTutor;
	    }
		
		//**Erro ao encontrar um tutor cadastrado
     	printf("\nDigite 1 para buscar novamente.\nDigite 0 para retornar.\n");
    	scanf("%d", &escolha);

	} while(escolha == 1);
	

}

Pet *buscarPet(){
	int escolha = 1;
	do {
		char nomeBuscaPet[50];
		
	    printf("\nDigite o nome do pet que deseja buscar: ");
	    fgets(nomeBuscaPet, sizeof(nomeBuscaPet), stdin);
	    nomeBuscaPet[strcspn(nomeBuscaPet, "\n")] = '\0';
	
	    NoPet *noAtual = listaPets;
	    
	    while (noAtual != NULL) {
	        if (strcmp(noAtual->pet->nome, nomeBuscaPet) == 0) {
	            printf("\nPet encontrado!\nNome: %s\nTipo: %s\nIdade: %d\nPeso: %.2f\nRaça: %s\n", noAtual->pet->nome, noAtual->pet->tipo, noAtual->pet->idade, noAtual->pet->peso, noAtual->pet->raca);
	            return noAtual->pet;
	        }
	        noAtual = noAtual->proxPet;
	    }
	
	    //**Erro ao encontrar um pet cadastrado
     	printf("\nDigite 1 para buscar novamente.\nDigite 0 para retornar.\n");
    	scanf("%d", &escolha);

	} while(escolha == 1);
}

int inserirPagamento(float valor){
	int opcao, pago;
	
	printf("\n--- Pagamento ---\n\n");
	printf("Insira qual a o forma de pagamento:\n1 - Pagamento em espécie\n2 - Pagamento por débito\n3 - Pagamento por crédito\n0 - Não pagar\n\n");

	printf("Opção: ");
	scanf("%d", &opcao);

	switch(opcao){
		case 1:
			printf("\nPagamento em espécie: %.2f\n", valor*0.9);
			break;
		case 2:
			printf("\nPagamento por débito: %.2f\n", valor);
			break;
		case 3:
			printf("\nPagamento por crédito: %.2f\n", valor);
			break;
		case 0:
			printf("\nSair de pagamento..\n");
			return 0;
		default:
			printf("\nOpção  inválida\n\n");
			return 0;
	}
	
	printf("\nPago com sucesso?\n1 - Sim\n2 - Não\n\n");
	scanf("%d", &pago);

	if (pago == 1) {
		return 1;
	} else {
		return 0;
	}
}

int inserirSatisfacaoAtendimento(){
	int satisfacao;
	
    printf("A Fantastic Pet Shop agradece sua preferência!\n");
    printf("Agora insira seu nível de satisfação de 0 a 5: ");
    
    scanf("%d", &satisfacao);
    
    if (satisfacao<0 || satisfacao>5) {
    	return -1;
	}
	
	return satisfacao;
}

void imprimirTutores(){ //funcao para imprimir os tutores 
    NoTutor *noAtual = listaTutores; //**Pega o endereco do primeiro no da lista que aponta para o proximo
    while (noAtual != NULL) {
        printf("\nTutor encontrado!\nNome: %s\nNúmero: %s\nEndereço: %s\n", noAtual->tutor->nome, noAtual->tutor->numero, noAtual->tutor->endereco);
        noAtual = noAtual->proxTutor;
    }
    printf("\n");
}
  
void imprimirPets(){ //funcao para imprimir os pets
    NoPet *noAtual = listaPets; //**Pega o endereco do primeiro no da lista que aponta para o proximo
    while (noAtual != NULL) {
        printf("\nPet encontrado!\nNome: %s\nTipo: %s\nIdade: %d\nPeso: %2.f\nRaça: %s\nTutor %s\n", noAtual->pet->nome, noAtual->pet->tipo, noAtual->pet->idade, noAtual->pet->peso, noAtual->pet->raca, noAtual->pet->tutor);
    	noAtual = noAtual->proxPet;
	}
	
	printf("\n");
}

void imprimirAtendimentos(){ //funcao para imprimir os atendimentos
	
	int i = 1; //**numera os atendimentos
    NoAtendimento *noAtual = filaAtendimento; //**Pega o endereco do primeiro no da lista que aponta para o proximo
	
	
	/*
	Verifica se tem atendimento emAtendimento
	*/
	if (emAtendimento != NULL) {
		printf("\nAtendimento atual\nPet: %s - %s \nValor: %.2f\n", emAtendimento->pet->nome, emAtendimento->pet->tipo, emAtendimento->valor);
	}

	/*
	Verifica se fila esta vazia
	*/
	if (noAtual == NULL) {
		printf("\nFila sem atendimentos.\n\n");
		return;
	}
	
	while (noAtual != NULL) {
        printf("\nFila Atendimento %d\nPet: %s - %s \nValor: %.2f\n", i, noAtual->atendimento->pet->nome, noAtual->atendimento->pet->tipo, noAtual->atendimento->valor);
        
        i++;
		noAtual = noAtual->proxAtendimento;
	}
	
	printf("\n");
}
