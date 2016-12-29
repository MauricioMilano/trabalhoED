#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct dir{
	int nArqs; 
	int nDirs; 
	char* datahoraCriacao;
	char* datahoraModific;
	void* ultimoFilho;
	void* ultimoIrmao;
	void* pai;
	char tipo;
	int tamanho;
	char nome[30];
}AD;



char* datetime(){
	char *array = (char*)malloc(sizeof(char)*25);
    time_t result;
    result = time(NULL);
    sprintf(array, "%s", asctime(localtime(&result)));
    array[25] = '\0';
    return array;
}

AD * iniciaArv(){
	AD * arv = NULL;
	return arv;
} 



AD* criarNovoDir(){
   AD* novoNo = (AD*)malloc(sizeof(AD));
   novoNo->ultimoFilho = NULL;
   novoNo->ultimoIrmao = NULL;
   printf("Digite um nome: ");
   scanf("%s", novoNo->nome);
   novoNo->tipo ='D';
	novoNo->nArqs = 0;
	novoNo->nDirs = 0;
	novoNo->datahoraCriacao = datetime();
	novoNo->datahoraModific = datetime();
	return novoNo;
}

AD* criaRaizDir(){
    return criarNovoDir();
} 

int numeroDeNos(AD* raiz){
   if (!raiz) return 0;
   int res = 1;
   AD* filhos = raiz->ultimoFilho;
   while (filhos != NULL){
      res += numeroDeNos(filhos);
      filhos = filhos->ultimoIrmao;
   }
   return res;
}

AD* criaArq (AD*dir){
	if(!dir){
		printf("Nao foi possivel criar arquivo, pois nao existe nenhum diretorio");
		return NULL;
	}else{
		AD* novo = (AD*) malloc (sizeof(AD));
		printf("Digite o nome do arquivo: ");
		scanf("%s", novo->nome);
		printf("Digite o tipo de arquivo: (T para Texto e B para binario) ");
		
		scanf(" %c", &novo->tipo);
		printf("Digite o tamanho do arquivo: ");
		int tam;
		scanf("%d", &tam);
		novo->tamanho = tam;
		novo->datahoraCriacao = datetime();
		novo->datahoraModific = datetime();

		return novo;
	}
}

void imprime(AD* raiz){
  if (raiz == NULL) return;
  if((raiz->tipo == 'T') || (raiz->tipo == 'B'))
  	printf("%c" "%c" "%s" "%c" "%s" "%c" "%s" "%c" "Tamanho: %d", raiz->tipo, '/', raiz->nome, '/', raiz->datahoraCriacao, '/', raiz->datahoraModific, '/',raiz->tamanho);
  if(raiz->tipo == 'D')
	printf("%c" "%c" "%s" "%c" "Numero de Arquivos: %d" "%c" "Numero de Dir: %d" "%c" "%s" "%c" "%s\n",raiz->tipo, '/', raiz->nome, '/', raiz->nArqs, '/', raiz->nDirs, '/',raiz->datahoraCriacao, '/', raiz->datahoraModific);
  
  AD* filhos = raiz->ultimoFilho;
  if (filhos == NULL) return;
  while (filhos != NULL){
    imprime(filhos);
    filhos = filhos->ultimoIrmao;
  }
}

AD* buscarDir(AD* raiz, char*nomeChave){
  if (raiz == NULL){
  	printf("nulo");
  	return NULL;
  }
  	
  if (strcmp(raiz->nome, nomeChave) == 0){
  	return raiz;
  }
   
  AD* aux = buscarDir(raiz->ultimoFilho, nomeChave);
  if (aux) 
  	return aux;
  return buscarDir(raiz->ultimoIrmao, nomeChave);
} 

AD* insereDir(AD*arv, char* nomePasta){
	AD*pai = buscarDir(arv, nomePasta);
	if(!pai)
		return NULL;
	AD*novo = criarNovoDir();
	novo->ultimoFilho = NULL;
	novo->ultimoIrmao = pai->ultimoFilho;
	pai->ultimoFilho = novo;
	pai->nDirs+= 1;
	novo->pai = pai;
	return novo;
}

AD* insereArq(AD*arv, char*nomePasta){
	AD*pai = buscarDir(arv, nomePasta);
	if(!pai)
		return NULL;
	AD*novo = criaArq(pai);
	novo->ultimoIrmao = pai->ultimoFilho;
	pai->ultimoFilho = novo;
	pai->nArqs+=1;
	novo->pai = pai;
	return novo;
}

void renomear(char* nomePasta, AD*arv){
	AD* aux = buscarDir(arv, nomePasta);
	if(!aux){
		printf("nao foi encontrada a pasta/arquivo desejada! ");
		return;
	}
	printf("Digite o novo nome para o arquivo/diretorio: ");
	scanf("%s", aux->nome);
}

void mover(AD*raiz, char* nomePasta, char* destino){
	AD*aux = buscarDir(raiz, nomePasta);
	AD*dest = buscarDir(raiz, destino);
	if(!dest){
		printf("querido usuario, destino nao encontrado!");
		return;
	}
	if(!aux){
		printf("querido usuario, a pasta que vc quer mover nao existe");
		return;		
	}
}


void* libera(AD*arv){
	AD * pai = arv->pai;
	
	if(pai->ultimoFilho!=NULL){
		libera(arv->ultimoIrmao);
		libera(arv->ultimoFilho);
		free(arv);
	}
	return;
}
void excluirDir(AD*arv){
	printf("chamou");
	if(!arv)
		return;
	AD* filhos = arv->ultimoFilho;
  	if (filhos == NULL){
		libera(arv);
		return;
	}
  	while (filhos != NULL){
    	excluirDir(filhos);
    	filhos = filhos->ultimoIrmao;
  		libera(filhos);
	}
}
/*void excluirDir(AD*arv){
 	if (arv == NULL){
  		printf("nulo");
  		return;
  	}
	if(!arv->ultimoFilho){
		free(arv);
		arv = NULL;
	}
}*/

AD* destruirDir(char*nomePasta, AD*arv){
	AD*aux = buscarDir(arv, nomePasta);
	if(!aux){
		printf("nao foi encontrada a pasta/arquivo desejada! ");
		return;	
	}
	printf("Voce tem certeza que deseja destruir esse diretorio e tudo que esta nele(s ou n)?");
	char opcao; 
	scanf(" %c", &opcao);
	if(opcao == 's'){
		printf("chegou aqui");
		excluirDir(aux);
		return arv;
	}else{
		return arv;
	}
}




/*
void destruirDir(char*nomePasta, AD*arv){
	AD* aux = buscaDir(nomePasta, arv);
	if(!aux){
		printf("nao foi encontrada a pasta/arquivo desejada! ");
		return;
	}
	printf("Voce tem certeza que deseja destruir esse diret?rio e tudo que esta nele(s ou n)?");
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
		printf("n?o foi encontrada a pasta/arquivo desejada! ");
		return;
	}
	printf("Voc? tem certeza que deseja destruir esse arquivo (s ou n)?");
	char opcao; 
	scanf("%c", &opcao);
	if(opcao == 's'){
		free(aux);
	}else{
		return;
	}
	
}
*/
void modifica(AD* arv){
	if(!arv->tipo=='D'){
		arv->tipo='D';
		arv->tamanho=0;
		arv->datahoraModific = datetime();
	}else{
		printf("Qual tipo de arquivo deseja: B ou T");
		scanf(" %c", &arv->tipo);
		printf("Qual é o tamanho do arquivo:");
		scanf(" %d", &arv->tamanho);
		arv->datahoraModific = datetime();
		AD * filho = arv->ultimoFilho;
		while(filho){
			destruirDir(filho->nome, arv);
			filho = filho->ultimoIrmao;
		}
	}
}


int main(void) {
	AD* raiz = criaRaizDir();
	insereDir(raiz, "ab");
	insereDir(raiz, "aaa");
	imprime(raiz);
	//free(raiz->ultimoFilho);
	//raiz->ultimoFilho = NULL;
	//raiz = destruirDir("ab", raiz);
	raiz = libera(raiz->ultimoFilho);
	printf("resultado\n");
	imprime(raiz);
	return 0;
}
