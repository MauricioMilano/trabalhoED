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

AD* criarNovoDir(){
   AD* novoNo = (AD*)malloc(sizeof(AD));
   novoNo->ultimoFilho = NULL;
   novoNo->ultimoIrmao = NULL;
   printf("Digite um nome: ");
   scanf("%s", novoNo->nome);
   novoNo->tipo ='D';
	novoNo->nArqs = 0;
	novoNo->nDirs = 0;
	novoNo->pai = NULL;
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
	
	AD*pai = raiz->pai;
	if (raiz == NULL) return;
	if(!pai){
		char* paiNulo = "Pai: null";
		if((raiz->tipo == 'T') || (raiz->tipo == 'B'))
  			printf("%c" "%c" "%s" "%c" "%s" "%c" "%s" "%c" "%s" "%c" "Tamanho: %d\n", raiz->tipo, '/', raiz->nome, '/', paiNulo, '/', raiz->datahoraCriacao, '/', raiz->datahoraModific, '/',raiz->tamanho);
  		if(raiz->tipo == 'D')
			printf("%c" "%c" "%s" "%c" "%s" "%c" "Numero de Arquivos: %d" "%c" "Numero de Dir: %d" "%c" "%s" "%c" "%s\n",raiz->tipo, '/', raiz->nome, '/', paiNulo, '/', raiz->nArqs, '/', raiz->nDirs, '/',raiz->datahoraCriacao, '/', raiz->datahoraModific);
  	}else{
  		if((raiz->tipo == 'T') || (raiz->tipo == 'B'))
  			printf("%c" "%c" "%s" "%c" " Pai: %s" "%c" "%s" "%c" "%s" "%c" "Tamanho: %d\n", raiz->tipo, '/', raiz->nome, '/', pai->nome, '/', raiz->datahoraCriacao, '/', raiz->datahoraModific, '/',raiz->tamanho);
  		if(raiz->tipo == 'D')
			printf("%c" "%c" "%s" "%c" " Pai: %s" "%c" "Numero de Arquivos: %d" "%c" "Numero de Dir: %d" "%c" "%s" "%c" "%s\n",raiz->tipo, '/', raiz->nome, '/', pai->nome, '/', raiz->nArqs, '/', raiz->nDirs, '/',raiz->datahoraCriacao, '/', raiz->datahoraModific);
	}

  
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
	pai->datahoraModific = datetime();
	return novo;
}

AD* insereArq(AD*arv, char*nomePasta){
	AD*pai = buscarDir(arv, nomePasta);
	if(!pai)
		return NULL;
	if((pai->tipo == 'T') || (pai->tipo == 'B')){
		printf("nao pode inserir arquivo dentro de outro arquivo");
		return NULL;
	}
	AD*novo = criaArq(pai);
	novo->ultimoIrmao = pai->ultimoFilho;
	pai->ultimoFilho = novo;
	pai->nArqs+=1;
	novo->pai = pai;
	pai->datahoraModific=datetime();
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

void insereFilho(AD*arv, AD*dest){
	if(!dest->ultimoFilho){
		dest->ultimoFilho=arv;
		arv->pai = dest;
	}else{
		AD* filho = dest->ultimoFilho;
		while(filho->ultimoIrmao){
			filho = filho->ultimoIrmao;
		}
		filho->ultimoIrmao = arv;
		arv->pai = dest;
	}
	if(arv->tipo=='D'){
		dest->nDirs += 1;
	}else{
		dest->nArqs += 1;
	}
	arv->datahoraModific = datetime();
	dest->datahoraModific = datetime();
}

void mover(AD*raiz, char* nomePasta, char* destino){
	AD*aux = buscarDir(raiz, nomePasta);
	AD*dest = buscarDir(raiz, destino);
	AD* paiF = aux->pai;
	if(!dest){
		printf("querido usuario, destino nao encontrado!");
		return;
	}
	if(!aux){
		printf("querido usuario, a pasta que vc quer mover nao existe");
		return;		
	}
	if(aux->tipo=='D'){
		paiF->nDirs -=1;
	}else{
		paiF->nArqs -=1;
	}
	AD* pai = aux->pai;
	if(!pai){
		printf("não pode mover a raíz");
		return;
	}
	AD* filho = pai->ultimoFilho;
	if(!filho->ultimoIrmao){
		pai->ultimoFilho=NULL;
		insereFilho(filho, dest);
		return;
	}if(filho == aux){
		pai->ultimoFilho= filho->ultimoIrmao;
		insereFilho(filho, dest);
		return;
	}
	else{
		AD* ant = filho;
		filho = filho->ultimoIrmao;
		while(filho!=aux){
			ant = filho;
			filho = filho->ultimoIrmao;
		}
		ant->ultimoFilho= filho->ultimoFilho;
		filho->ultimoFilho=NULL;
		insereFilho(filho, dest);
	}

	
}


void libera(AD*arv){
	AD * pai = arv->pai;
	
	if(pai->ultimoFilho!=NULL){
		libera(arv->ultimoIrmao);
		libera(arv->ultimoFilho);
		free(arv);
	}
	return;
}

void excluirIrmaos(AD* arv){
	if(!arv) return;
	if(!arv->ultimoIrmao){
		printf("nao tem irmao");
		return;
	}
	while(arv->ultimoIrmao){
		AD* aux = arv->ultimoIrmao;
		arv->ultimoIrmao = aux->ultimoIrmao;
		free(aux);
		aux = NULL;	
		AD* pai = arv->pai;
		pai->nDirs--;
	}
}

void excluirFilhos(AD*arv){
	if (!arv) return;
	if(!arv->ultimoFilho){
		printf("nao tem filho");
		return;
	}
	AD*filho = arv->ultimoFilho;
	while(filho->ultimoIrmao){
		excluirIrmaos(filho);
	}
	free(arv->ultimoFilho);
	arv->ultimoFilho = NULL;
	arv->nDirs -= 1;
}

void excluirDir(AD*arv, char* nomePasta){
	if(!arv) return;
	AD*busca = buscarDir(arv, nomePasta);
	if(!busca){
		printf("nao foi encontrada a pasta/arquivo desejada! ");
		return;	
	}
	if(!busca->pai){
	printf("Nao e possivel remover a raiz.\n");
	 return;
	}
	if(busca->tipo == 'D'){
		printf("Voce tem certeza que deseja destruir esse diretorio e tudo que esta nele(s ou n)?");
		char opcao; 
		AD*pai;
		scanf(" %c", &opcao);
			if(opcao == 's'){
				if(busca->pai){
					pai = busca->pai;
				}
				if(busca->ultimoFilho){
					AD*filhos = busca->ultimoFilho;
				}
				if(busca == pai->ultimoFilho){
					if(busca->ultimoFilho){
						excluirFilhos(busca);
					}
					if(busca->ultimoIrmao){
						pai->ultimoFilho = busca->ultimoIrmao;
					}
					else if((!busca->ultimoFilho) && (!busca->ultimoIrmao)){
						pai->ultimoFilho = NULL;
						free(busca);
						return;
					}
					
			}
		}else{
			return;
		}

	}else{
		AD*pai = busca->pai;
		pai->ultimoFilho = NULL;
		free(busca);
		return;
	}
	
}




void modifica(char *nomeArv,AD* raiz){
	AD * arv = buscarDir(raiz,nomeArv);
	if(!arv){
		printf("nao foi encontrada a pasta/arquivo desejada! ");
		return;	
	}
	if(arv->tipo!='D'){
		arv->tipo='D';
		arv->tamanho=0;
		arv->nDirs = 0;
		arv->nArqs = 0;
		arv->datahoraModific = datetime();
	}else{
		printf("tem certeza que deseja modificar o diretório? todos arquivos dele serão apagados. S/N: ");
		char entrada;
		scanf(" %c", &entrada);
		if(entrada =='N'||entrada =='n'){
			return;
		}if(entrada=='S'|| entrada == 's'){
		
			printf("Qual tipo de arquivo deseja: B ou T ");
			scanf(" %c", &arv->tipo);
			printf("Qual o tamanho do arquivo: ");
			scanf(" %d", &arv->tamanho);
			arv->datahoraModific = datetime();
			excluirFilhos(arv);
		}
	}
}



int main(void) {
	AD* raiz = criaRaizDir();
	/*insereDir(raiz, "ab");
	
	insereDir(raiz, "aaa");
	//insereDir(raiz, "ab");
	imprime(raiz);
	printf("Digite qual pasta/arquivo quer mover: ");
	char mover1[20];
	scanf("%s", mover1);
	printf("Digite qual pasta destino: ");
	char mover2[20];
	scanf("%s", mover2);
	mover(raiz,mover1, mover2);
	
	//free(raiz->ultimoFilho);
	//raiz->ultimoFilho = NULL;
	//raiz = destruirDir("ab", raiz);
	//excluirDir(raiz, "as");
	printf("resultado\n");
	imprime(raiz);*/
	int opcao = -1;
	while(opcao!= 0){
		printf("Qual funcao vc deseja executar?\n");
		printf("Digite 1 para inserir diretorio.\n\nDigite 2 para inserir arquivo.\n\n");
		printf("Digite 3 para remover arquivo ou diretorio.\n\nDigite 4 para mover arquivo ou diretorio.\n\n");
		printf("Digite 5 para renomear diretorio.\n\nDigite 6 para modificar arquivo ou diretorio.\n\nDigite 7 para imprimir.\n\nDigite 0 para sair.\n\n");
		scanf("%d", &opcao);
		if(opcao == 1){
			if(raiz->ultimoFilho == NULL){
				printf("So existe a pasta raiz, sua pasta sera criada dentro da pasta raiz\n");
				insereDir(raiz, raiz->nome);
				imprime(raiz);
			}else{
				printf("Digite em qual pasta voce deseja inserir\n\n");
				imprime(raiz);
				char nome[30];
				scanf("%s", nome);
				insereDir(raiz, nome);
				imprime(raiz);

			}
		}
		if(opcao == 2){
			if(raiz->ultimoFilho == NULL){
				printf("So existe a pasta raiz, sua pasta sera criada dentro da pasta raiz\n");
				insereArq(raiz, raiz->nome);
				imprime(raiz);
			}else{
				printf("Digite em qual pasta voce deseja inserir\n\n");
				imprime(raiz);
				char nome[30];
				scanf("%s", nome);
				insereArq(raiz, nome);
				imprime(raiz);

			}
		}

		if(opcao == 3){
			printf("Digite a pasta ou arquivo que vc deseja remover\n\n");
			imprime(raiz);
			char nome[30];
			scanf("%s", nome);
			excluirDir(raiz, nome);
			imprime(raiz);
		}
		if(opcao == 4){
			printf("Digite o arquivo ou pasta que vc deseja mover\n\n");
			imprime(raiz);
			char nome[30];
			scanf("%s", nome);
			printf("Digite a pasta de destino\n\n");
			char dest[30];
			scanf("%s", dest);
			mover(raiz, nome, dest);
			imprime(raiz);
		}
		if(opcao == 5){
			printf("Digite o nome do arquivo ou pasta em que vc deseja renomear\n\n");
			imprime(raiz);
			char nome[30];
			scanf("%s", nome);
			renomear(nome, raiz);
			imprime(raiz);

		}
		if(opcao == 6){
			printf("Digite o nome da pasta ou arquivo que vc deseja modificar:\n\n");
			imprime(raiz);
			char nome[30];
			scanf("%s", nome);
			modifica(nome, raiz);
			imprime(raiz);
		}
		if(opcao == 7){
			imprime(raiz);
		}
	}

	return 0;
}

