/*************************
  UFFS CHAPECÓ
  github.com/barbs-pm
  Barbara Pegoraro Markus
 
 LISTA SIMPLES ENCADEADA
**************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

typedef struct ArvBin{
    int info;
    struct ArvBin *left;
    struct ArvBin *right;
} NO;

/**********************************************/
		/*As próximas duas funções são 
		apenas para a estética ao compilar
		o código (limpar terminal, etc...)*/

void entra(){
	system("clear");
	printf("___________~<>~___________\n");
}

void sai(){
	printf("\n___________~<>~___________\n");
	printf("Aperte enter para sair");
	getchar();
	getchar();
}
/**********************************************/

//Uma função para criar um novo nó na BST
NO *novoNo(int item){
    NO *temp =  (NO *)malloc(sizeof(NO));
    temp->info = item;
    temp->left = temp->right = NULL;
    return temp;
}

//Inserir um nó da BST
NO* push(NO *no, int num){
	int info = num;

	if (no == NULL) return novoNo(info); //se a árvore estiver vazia
										 // retorna um nó do valor do usuário

    //se não estiver vazia, faz uma "busca binária" até achar a posição correta
	if (info < no->info) 
        no->left  = push(no->left, info);
    else if (info > no->info)
        no->right = push(no->right, info);
}

//popr um nó da BST
NO* pop(NO *no, int num){
	int info = num;

	if(!no) return no;

	else if(info < no->info)	
		no->left = pop(no->left, info); //verifica se o valor é menor que o nó (busca binária)

	else if(info > no->info) 
		no->right = pop(no->right, info); // verifica se o valor é maior que o nó (busca binária)

	else{ //se ele econtrar com a busca binária, ele testa os tipos de filhos do nó
		if(!no->left && !no->right){ //o nó não possui filho
			free(no); //apenas libera o nó
			no = NULL;
		}

		else if(!no->left){ //possui só o filho direito, ou seja, lado esquerdo é null
			NO * aux = no; //copia o nó a ser excluído para um auxiliar
			no = no->right; //manda o filho direito para o seu lugar
			free(aux); //libera o nó auxiliar
		}

		else if(!no->right){ //possui só o filho esquerdo, ou seja, o lado direito é null
			NO * aux = no;//copia o nó a ser excluído para um auxiliar
			no = no->left;//manda o filho esquerdo para o seu lugar
			free(aux); //libera o nó auxiliar
		}

		else{ //se o nó possui dois filhos
			NO * aux = no->left; //salva o filho esquerdo num auxiliar

			while(aux->right) aux = aux->right;	//percorre até encontrar o maior nó que irá substitui-lo

			no->info = aux->info; //faz a troca
			aux->info = info;
			no->left = pop(no->left, info); //percorre para deletar o nó que foi trocado
		}
	}

	return no;
}

/**********************************************
Para a impressão em ordem, usamos a lógica
vista em sala: ESQUERDA -> VISITA NÓ -> DIREITA
**********************************************/

NO* displayEmOrdem(NO* no){
	int aux;

	if (no != NULL){
        displayEmOrdem(no->left);
        printf(" %d ", no->info);
        displayEmOrdem(no->right);
    }
}

/**********************************************
Para a impressão em pós-ordem, usamos a lógica
vista em sala: ESQUERDA -> DIREITA -> VISITA NÓ
**********************************************/
NO* displayPosOrdem(NO* no){
    if (no != NULL){
		displayPosOrdem(no->left);
		displayPosOrdem(no->right);
        printf(" %d ", no->info);
	}
}

/**********************************************
Para a impressão em pré-ordem, usamos a lógica
vista em sala: VISITA NÓ -> ESQUERDA -> DIREITA
**********************************************/
NO* displayPreOrdem(NO* no){
     if (no != NULL){
		printf(" %d ", no->info);  
		displayPreOrdem(no->left);  
		displayPreOrdem(no->right);	
     }
}    

int main(void){
	int op, num;
	NO *no = NULL;
	
	do{
		entra();
		printf("|0| Sair\n");
		printf("|1| Inserir nó\n");
		printf("|2| Excluir nó\n");
		printf("|3| Exibir árvore (em ordem)\n");
		printf("|4| Exibir árvore (pós-ordem)\n");
		printf("|5| Exibir árvore (pré-ordem)\n");
		printf("___________~<>~__________\n");
		printf("Escolha sua opção: ");
		scanf("%d", &op);

		switch(op){
			case 1:
				entra();
				printf("Valor do nó: ");
				scanf("%d", &num);
				no = push(no, num); 
				break;

			case 2: 
				entra();
				printf("Valor do nó: ");
				scanf("%d", &num);
				no = pop(no, num); 
				break;

			case 3: 
				entra();
				printf("    Árvore em ordem\n\n");
				displayEmOrdem(no); 
				sai();
				break;

			case 4: 
				entra();
				printf("   Árvore em pós-ordem\n\n");
				displayPosOrdem(no); 
				sai();
				break;

			case 5: 
				entra();
				printf("   Árvore em pré-ordem\n\n");
				displayPreOrdem(no); 
				sai();
				break;
		}
	
	} while(op != 0);
	
	return 0;
}