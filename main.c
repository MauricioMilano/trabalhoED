#include <stdio.h>
#include <time.h>
#include<stdlib.h>

typedef struct Dir{
	char * nome;
	int nArqs; 
	int nDirs; 
	char dataCriacao[9];
	char horaCriacao[9];
	char dataModific[9];
	char horaModific[9];
	void * filho;
	void * proxIrmao;
	void * antIrmao;
	void * pai;
	char tipo;
	int tamanho;
}AD;

AD * iniciaArv(){
	AD * arv = NULL;
	return arv;
} 
AD * buscaDir(char * nome, AD * arv){
	if(arv== NULL){
		return NULL;
	}if(nome == arv->nome ){
		return arv;
	}else{
		buscaDir(nome,arv->proxIrmao);
		buscaDir(nome,arv->filho);
	}
	
}

void imprimir(AD*arv){
	if(arv== NULL){
		printf("esta Vazia!");
		return;
	}
	printf("%s",arv->nome);
	AD * aux = arv->filho;
	if (aux == NULL){
	 return;
	}	
  	printf("(");
  	 while (aux != NULL){
    	imprimir(aux->filho);
    	aux = aux->filho;
	} 
	printf(")");
	
}

AD* criaDir(){
	AD* novo = (AD*)malloc(sizeof(AD));
	printf("Digite um nome: ");
    scanf("%s", novo->nome);
    novo->tipo ='D';
	novo->nArqs = 0;
	novo->nDirs = 0;
	_strdate( novo->dataCriacao);
	_strdate( novo->dataModific);
	_strtime( novo->horaCriacao);
	_strtime( novo->horaModific);
	return novo;

}

AD* criaArq (){
	AD * novo = (AD*) malloc (sizeof(AD));
	printf("Digite o nome do arquivo: ");
	scanf("%s", novo->nome);
	printf("Digite o tipo de arquivo: (T para Texto e B para binário) ");
	scanf("%s", novo->tipo);
	printf("Digite o tamanho do arquivo: ");
	scanf("%d", &novo->tamanho);
	_strdate( novo->dataCriacao);
	_strdate( novo->dataModific);
	_strtime( novo->horaCriacao);
	_strtime( novo->horaModific);
	
	return novo;
	
	
}

void insereDir(char* nomePasta,AD * arv){
	AD * novo = criaDir();
	if (arv == NULL){
		arv = novo;
		return;
	}
	
	AD * aux = buscaDir(nomePasta,arv);
	if(!aux){
		printf("não foi encontrada a pasta desejada! ");
		return;
	}
	
	if(aux->filho == NULL){
		aux-> filho = novo;
		novo->pai = aux;
	}else{
		AD* auxFilho = aux->filho;
		while(auxFilho->proxIrmao){
			auxFilho = auxFilho->proxIrmao;
		}
		auxFilho->proxIrmao = novo; 
		novo->antIrmao = auxFilho;	
	}
	aux->nDirs += 1; 
}
void insereArq(char * nomePasta, AD * arv){
	AD * novo = criaArq();
	if (arv == NULL){
		arv = novo;
		return;
	}
	
	AD * aux = buscaDir(nomePasta,arv);
	if(!aux){
		printf("não foi encontrada a pasta desejada! ");
		return;
		
	}
	if(aux->filho == NULL){
		aux-> filho = novo;
		novo->pai = aux;
	}else{
		AD * auxFilho = aux->filho;
		while(auxFilho->proxIrmao){
			auxFilho = auxFilho->proxIrmao;
		}
		auxFilho->proxIrmao = novo; 
		novo->antIrmao = auxFilho;	
	}
	aux->nArqs += 1; 
}

void renomear(char* nomePasta, AD*arv){
	AD* aux = buscaDir(nomePasta, arv);
	if(!aux){
		printf("não foi encontrada a pasta/arquivo desejada! ");
		return;
	}
	printf("Digite o novo nome para o arquivo/diretorio");
	scanf("%s", aux->nome);
}

void destruirDir(char*nomePasta, AD*arv){
	AD* aux = buscaDir(nomePasta, arv);
	if(!aux){
		printf("não foi encontrada a pasta/arquivo desejada! ");
		return;
	}
	printf("Você tem certeza que deseja destruir esse diretório e tudo que está nele(s ou n)?");
	char opcao; 
	scanf("%c", &opcao);
	if(opcao == 's'){
		while(aux->filho){
			AD*filho = aux->filho;
			aux->filho = filho->proxIrmao;
			free(filho);
		}
		free(aux);
	}else{
		return;
	}

}

void destruirArq(char*nomePasta, AD*arv){
	AD* aux = buscaDir(nomePasta, arv);
	if(!aux){
		printf("não foi encontrada a pasta/arquivo desejada! ");
		return;
	}
	printf("Você tem certeza que deseja destruir esse arquivo (s ou n)?");
	char opcao; 
	scanf("%c", &opcao);
	if(opcao == 's'){
		free(aux);
	}else{
		return;
	}
	
}




int main(void) {
	AD* arv2 = iniciaArv();
	arv2 = criaDir();
	imprimir(arv2);
	return 0;
}
