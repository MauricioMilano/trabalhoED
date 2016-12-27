#include <stdio.h>
#include <time.h>
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

AD* criaDir(){
	AD* novo = (AD*)malloc(sizeof(AD));
	printf("Digite um nome: ");
    scanf("%s", &novo->nome);
    novo->tipo ='D';
	novo->nArqs = 0;
	novo->nDirs = 0;
	_strdate( novo->dataCriacao);
	_strdate( novo->dataModific);
	_strtime( novo->horaCriacao);
	_strtime( novo->horaModific);
	return novo;

}

AD * criaArq (){
	AD * novo = (AD * ) malloc (sizeof(AD));
	printf("Digite o nome do arquivo: ");
	scanf("%s", &novo->nome);
	printf("Digite o tipo de arquivo: (T para Texto e B para binário) ");
	scanf("%d", &novo->tipo);
	_strdate( novo->dataCriacao);
	_strdate( novo->dataModific);
	_strtime( novo->horaCriacao);
	_strtime( novo->horaModific);
	
	return novo;
	
	
}

void * insereDir(char * nomePasta,AD * arv){
	AD * novo = criaDir();
	if (arv == NULL){
		arv = novo;
		return;
	}
	AD * aux = buscaDir(nomePasta,arv);
	if(aux->filho == NULL){
		aux -> filho = novo;
		novo ->pai = aux;
	}else{
		AD * auxFilho = aux->filho;
		while(auxFilho->proxIrmao){
			auxFilho = auxFilho->proxIrmao;
		}
		auxFilho->proxIrmao = novo; 
		novo->antIrmao = auxFilho;	
	}
	aux->nDirs += 1; 
}
void * insereArq(char * nomePasta, AD * arv){
	AD * novo = criaArq();
	if (arv == NULL){
		arv = novo;
		return;
	}
	AD * aux = buscaDir(nomePasta,arv);
	if(aux->filho == NULL){
		aux -> filho = novo;
		novo ->pai = aux;
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



int main(int argc, char** argv) {
	//AD* arv = iniciaArv();
	//insereArq("aaaa",arv);
	return 0;
}
