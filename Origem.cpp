#define _CRT_SECURE_NO_WARNINGS
#define MAX 10
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>

enum menu
{
	consultar = 1, alterar, excluir, inserir, imprimir, sair
};
enum menuAltera
{
	alteraNome = 1, alteraCategoria, alteraPreco, alteraClassificacao, alteraSair
};
enum menuImprime
{
	ordenadoCod = 1, ordenadoNome, ordenadoCategoriaCod, ordenadoCategoriaNome, desordenado, ordenadoSair
};
enum menuCategoria
{
	comedia = 1, drama, romance, terror, sairCategoria
};

typedef struct {
	int codigo;
	char nome[20];
	char categoria[10]; //drama, romance, terror, comedia
	float preco;
	float classificacao; //nota da cr�tica
}filme;

typedef struct node {
	int info;
	struct node * link;
}no;

typedef struct {
	int posicaoInicial;
	char categoria[20];
}indexCategoria;

int buscaBinaria(int vet[][2], int chave, int qtd);
int leArquivo(filme filmes[]);
void escreveArquvio(filme filmes[], int qtd);
void imprime(filme filmeAtual);
int exclusao(filme filmes[], int posicao, int qtd);
int insere(filme filmeAtual, int qtd, filme * filmes);
void popularIndex(filme filmes[], int index[][2], int qtd);
void swap(int *x, int *y);
void bubbleSort(int index[][2], int qtd);
void imprimeOrdenadoCod(filme filmes[], int index[][2], int qtd);
int popularLista(filme filmes[], int qtd, int lista[]);
int menorNome(filme filmes[], int qtd);
void imprimeOrdNome(int lista[], int PRI, filme filmes[]);
void popularCatCod(filme filmes[], int qtd, int index[][2], indexCategoria indexCat[], int lista[]);
void imprimeCatCod(int lista[], indexCategoria index[], filme filmes[]);
//nao esta pronto
void popularCatNome(filme filmes[], int qtd, int PRI, int listaNome[], indexCategoria indexCat[], int lista[]);
void main() {
	filme filmes[MAX];
	filme filmeAtual;
	int opcao, opcaoAlterar, opcaoOrdenar,opcaoCat, qtd = 3, codAtual, posicao, i, PRI;
	int index[MAX][2];//chave, link
	char novoNome[20], novaCategoria[10];
	float novoPreco, novaNota;
	int lista[MAX];
	indexCategoria indexCat[MAX];
	int listaCod[MAX];
	indexCategoria indexCatNome[MAX];
	int listaNome[MAX];
	filmes[0].codigo = 2000;
	strcpy(filmes[0].nome, "Uma Noite no museu");
	strcpy(filmes[0].categoria, "comedia");
	filmes[0].classificacao = 5;
	filmes[0].preco = 1.5;

	filmes[1].codigo = 1000;
	strcpy(filmes[1].nome, "Titanic");
	strcpy(filmes[1].categoria, "romance");
	filmes[1].classificacao = 6.5;
	filmes[1].preco = 2.0;

	filmes[2].codigo = 3000;
	strcpy(filmes[2].nome, "E o vento levou");
	strcpy(filmes[2].categoria, "romance");
	filmes[2].classificacao = 8.5;
	filmes[2].preco = 1.5;

	escreveArquvio(filmes, qtd);

	//inicializa vetor
	qtd = leArquivo(filmes);

	popularIndex(filmes, index, qtd); //popula index primario (codigo)
	PRI = popularLista(filmes, qtd, lista);
	popularCatCod(filmes, qtd, index, indexCat, listaCod); //popula index e tabelas de categoria por codigo
	popularCatNome(filmes, qtd, PRI, lista, indexCatNome, listaNome);
	//for (i = 0; i < qtd; i++) {
	//	printf("Chave: %d  link = %d\n", index[i][0], index[i][1]);
	//}

	do {
		printf("Digite:\n");
		printf("%d) Consultar filme.\n", consultar);
		printf("%d) Alterar filme.\n", alterar);
		printf("%d) Excluir filme.\n", excluir);
		printf("%d) Inserir Filme.\n", inserir);
		printf("%d) Imprimir filme.\n", imprimir);
		printf("%d) Sair.\n", sair);
		scanf("%d", &opcao);

		switch (opcao)
		{
		case consultar:
			//Entrada da chave prim�ria;
			printf("Digite o codigo do filme (apenas numeros de 1000 - 9999):\n");
			scanf("%d", &codAtual);

			//Carregar �ndice denso (item a);
			popularIndex(filmes, index, qtd);

			//Chamar a fun��o Busca Bin�ria para localizar a chave;
			posicao = buscaBinaria(index, codAtual, qtd);

			//Caso exista o valor buscado;
			if (posicao != -1) {
				//Imprimir todas as informa��es do registro buscado;
				imprime(filmes[posicao]);

			}
			else {
				printf("Codigo do filme nao existe.\n");
			}
			break;
		case alterar:
			//Entrada da chave prim�ria;
			printf("Digite o codigo do filme (apenas numeros de 1000 - 9999):\n");
			scanf("%d", &codAtual);

			//Carregar �ndice denso (item a);
			popularIndex(filmes, index, qtd);

			//Chamar a fun��o Busca Bin�ria para localizar a chave;
			posicao = buscaBinaria(index, codAtual, qtd);
			if (posicao != -1) {
				do {
					//Perguntar qual campo ser� modificado, um a um;
					printf("Digite:\n");
					printf("%d) para alterar o nome filme.\n", alteraNome);
					printf("%d) para alterar a categoria do filme.\n", alteraCategoria);
					printf("%d) para alterar o preco filme.\n", alteraPreco);
					printf("%d) para alterar nota do filme.\n", alteraClassificacao);
					printf("%d) Sair.\n", alteraSair);
					scanf("%d", &opcaoAlterar);

					switch (opcaoAlterar) {
					case alteraNome:
						printf("Digite o nome do filme:\n");
						fflush(stdin);
						scanf(" %[^\n]s", novoNome);
						strcpy(filmes[posicao].nome, novoNome);
						//atualiza indice Secundario 
						PRI = popularLista(filmes, qtd, lista);

						break;
					case alteraCategoria:
						do {
							printf("Escolha uma categoria. Digite (apenas numeros de 1-4):\n");
							printf("%d) para  comedia.\n", comedia);
							printf("%d) para drama.\n", drama);
							printf("%d) para romance.\n", romance);
							printf("%d) para terror.\n", terror);
							scanf("%d", &opcaoCat);
							switch (opcaoCat) {
							case comedia:
								strcpy(novaCategoria, "comedia");
								break;
							case drama:
								strcpy(novaCategoria, "drama");
								break;
							case romance:
								strcpy(novaCategoria, "romance");
								break;
							case terror:
								strcpy(novaCategoria, "terror");
								break;
							default:
								printf("Opcao Invalida!\n");
								break;
							}
						} while ((opcaoOrdenar == comedia) ||
							(opcaoOrdenar == drama) ||
							(opcaoOrdenar == romance) ||
							(opcaoOrdenar == terror));

						strcpy(filmes[posicao].nome, novaCategoria);
						
						//atualiza indice
						popularCatCod(filmes, qtd, index, indexCat, listaCod);
						//popularCatNome(filmes, qtd, PRI, lista, indexCatNome, listaNome);

						break;
					case alteraPreco:
						printf("Digite o preco do filme(apenas numeros, use ponto para virgula):\n");
						scanf("%f", &novoPreco);
						filmes[posicao].preco = novoPreco;
						break;
					case alteraClassificacao:
						printf("Digite a nota do filme(apenas numeros, use ponto para virgula):\n");
						scanf("%f", &novaNota);
						filmes[posicao].classificacao = novaNota;
						break;
					case alteraSair:
						break;
					default:
						printf("Opcao Invalida!\n");
						break;
					}
				} while (opcaoAlterar != alteraSair);

			}
			else {
				printf("Codigo do filme nao existe.\n");
			}
			break;
		case inserir:
			do {
				//Entrada da chave prim�ria;
				printf("Digite o codigo do filme(apenas numeros de 1000 - 9999):\n");
				scanf("%d", &filmeAtual.codigo);

				//Verifica se o codigo do filmes ja existe
				posicao = buscaBinaria(index, filmeAtual.codigo, qtd);

				if (posicao == -1) {
					// pega as entradas e monta um filme
					printf("Digite o nome do filme:\n");
					fflush(stdin);
					scanf(" %[^\n]s", filmeAtual.nome);
					do {
						printf("Escolha uma categoria. Digite (apenas numeros de 1-4):\n");
						printf("%d) para  comedia.\n", comedia);
						printf("%d) para drama.\n", drama);
						printf("%d) para romance.\n", romance);
						printf("%d) para terror.\n", terror);
						scanf("%d", &opcaoCat);
						switch (opcaoCat) {
						case comedia:
							strcpy(filmeAtual.categoria,"comedia");
							break;
						case drama:
							strcpy(filmeAtual.categoria, "drama");
							break;
						case romance:
							strcpy(filmeAtual.categoria, "romance");
							break;
						case terror:
							strcpy(filmeAtual.categoria, "terror");
							break;
						default:
							printf("Opcao Invalida!\n");
							break;
						}
					} while ((opcaoOrdenar == comedia)|| 
							(opcaoOrdenar == drama)   ||
							(opcaoOrdenar == romance) || 
							(opcaoOrdenar == terror));

					printf("Digite o preco do filme(apenas numeros, use ponto para virgula):\n");
					scanf("%f", &filmeAtual.preco);
					printf("Digite a nota do filme(apenas numeros, use ponto para virgula):\n");
					scanf("%f", &filmeAtual.classificacao);

					qtd = insere(filmeAtual, qtd, filmes);
					printf("Insercao feita com sucesso!\n");

					//Atualizar os respectivos Índices;
					popularIndex(filmes, index, qtd); //popula index primario (codigo)
					PRI = popularLista(filmes, qtd, lista);
					popularCatCod(filmes, qtd, index, indexCat, listaCod);
					//popularCatNome(filmes, qtd, PRI, lista, indexCatNome, listaNome);
					printf("terminou aqui.\n");
				}
				else {
					printf("Codigo do filme ja existe.\n");
				}
			} while (posicao != -1);
			break;
		case excluir:
			//Entrada da chave prim�ria;
			printf("Digite o codigo do filme(apenas numeros de 1000 - 9999):\n");
			scanf("%d", &codAtual);

			//Carregar �ndice denso (item a);
			popularIndex(filmes, index, qtd); //popula index primario (codigo)

											  //Chamar a fun��o Busca Bin�ria para localizar a chave;
			posicao = buscaBinaria(index, codAtual, qtd);

			//Caso exista o valor buscado;
			if (posicao != -1) {
				//Inserir o registro no final do vetor;
				qtd = exclusao(filmes, posicao, qtd);
				//Atualizar os respectivos Índices;
				popularIndex(filmes, index, qtd); //popula index primario (codigo)
				PRI = popularLista(filmes, qtd, lista);
				popularCatCod(filmes, qtd, index, indexCat, listaCod);
				//popularCatNome(filmes, qtd, PRI, lista, indexCatNome, listaNome);
			}
			else {
				printf("Codigo do filme nao existe.\n");
			}
			break;
		case imprimir:
			do {
				printf("Digite:\n");
				printf("%d) para imprimir ordenado pelo codigo.\n", ordenadoCod);
				printf("%d) para imprimir ordenado pelo nome.\n", ordenadoNome);
				printf("%d) para imprimir ordenado pela categoria e codigo.\n", ordenadoCategoriaCod);
				printf("%d) para imprimir ordenado pela categoria e nome.\n", ordenadoCategoriaNome);
				printf("%d) para imprimir desordenado.\n", desordenado);
				printf("%d) Sair.\n", ordenadoSair);
				scanf("%d", &opcaoOrdenar);
				switch (opcaoOrdenar) {
				case ordenadoCod:
					//imprimir index denso
					imprimeOrdenadoCod(filmes, index, qtd);
					break;
				case ordenadoNome:
					//imprimir tabela invertida - ordem alfabetica
					imprimeOrdNome(lista, PRI, filmes);
					break;
				case ordenadoCategoriaCod:
					 //imprimir indice secundario com codigo
					imprimeCatCod(listaCod, indexCat, filmes);
					break;
				case ordenadoCategoriaNome:
					//imprimir indice secundario com codigo
					imprimeCatCod(listaNome, indexCatNome, filmes);
					break;
				case desordenado:
					for (i = 0; i<qtd; i++) {
						imprime(filmes[i]);
					}
					break;
				case ordenadoSair:
					break;
				default:
					printf("Opcao Invalida!\n");
					break;
				}
			} while (opcaoOrdenar != ordenadoSair);
			break;
		case sair:
			//atualiza arquivo
			escreveArquvio(filmes, qtd);
			break;
		default:
			printf("Opcao Invalida!\n");
			break;
		}
	} while (opcao != sair);
	system("pause");

}

//retorna posicao da chave no vetor ou -1 caso n�o existe no vetor
int buscaBinaria(int vet[][2], int chave, int qtd) {
	int inf = 0, sup = qtd - 1, meio;
	while (inf <= sup) {
		meio = (inf + sup) / 2;
		//printf("chave = %d\n", vet[meio][0]);
		if (chave == vet[meio][0]) {
			//printf("chave = %d\n", vet[meio][0]);
			return vet[meio][1];// retorna link			
		}
		if (chave < vet[meio][0])
			sup = meio - 1;
		else
			inf = meio + 1;
	}
	return -1;   // n�o encontrado
}

//retorna a quantidade de filmes de um arquivo e popula o vetor de filmes
int leArquivo(filme filmes[]) {
	FILE *arq;
	int qtd = -1;//não existe nenhum filme

				 // Abre um arquivo BIN�RIO para LEITURA
	arq = fopen("arq.dat", "rb");
	if (arq == NULL) {
		printf("Problemas na abertura do arquivo\n");
		return -1;
	}

	//fseek(arq, 0, SEEK_SET);
	while (!feof(arq)) {
		qtd++;
		fread(&filmes[qtd], sizeof(filme), 1, arq);
		//imprime(filmes[qtd]);

	}

	fclose(arq);
	//printf("qtd le arq = %d\n",qtd);
	return qtd;

}

//escreve no arquivo os filmes no arquivo
void escreveArquvio(filme filmes[], int qtd) {
	FILE *arq;
	int i;

	// Abre um arquivo BIN�RIO para ESCRITA
	arq = fopen("arq.dat", "wb");
	if (arq == NULL) {
		printf("Problemas na abertura do arquivo\n");
	}

	//fseek(arq, 0, SEEK_SET);
	for (i = 0; i < qtd; i++) {
		fwrite(&filmes[i], sizeof(filme), 1, arq);
	}

	fclose(arq);
}

//Imprime as informa��es do filme;
void imprime(filme filmeAtual) {
	printf("Codigo do filme: %d\n", filmeAtual.codigo);
	printf("Nome do filme: %s\n", filmeAtual.nome);
	printf("Tipo do filme: %s\n", filmeAtual.categoria);
	printf("Preco do filme: %.2f\n", filmeAtual.preco);
	printf("Nota da critica: %.2f\n", filmeAtual.classificacao);
}

//exclui um filme do vetor
int exclusao(filme filmes[], int posicao, int qtd) {
	int i;
	for (i = posicao + 1; i < qtd; ++i)
		filmes[i - 1] = filmes[i];
	return qtd - 1;
}

//inserir filme no final do vetor
int insere(filme filmeAtual, int qtd, filme * filmes)
{
	printf("qtd + 1=  %d\n", qtd + 1);
	if (qtd < MAX)
		filmes[qtd] = filmeAtual;
	return qtd + 1;
}

void popularIndex(filme filmes[], int index[][2], int qtd) {
	int i;
	for (i = 0; i < qtd; i++) {
		index[i][0] = filmes[i].codigo; //chave primaria
		index[i][1] = i; //link
						 //printf("Chave: %d  link = %d\n", index[i][0], index[i][1]);
	}
	bubbleSort(index, qtd);
}

void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void bubbleSort(int index[][2], int qtd) {
	int i, j;
	for (i = 0; i < qtd - 1; i++)
		for (j = 0; j < qtd - i - 1; j++)
			if (index[j][0] > index[j + 1][0]) {//comparar chaves
				swap(&index[j][0], &index[j + 1][0]);//troca chave
				swap(&index[j][1], &index[j + 1][1]);//troca link
			}
}
void imprimeOrdenadoCod(filme filmes[], int index[][2], int qtd) {
	int i;
	for (i = 0; i < qtd; i++)
		imprime(filmes[index[i][1]]);
}

int popularLista(filme filmes[], int qtd, int lista[]) {
	filme aux[MAX];
	int i, pos, posprox, pri = -1;

	for (i = 0; i < qtd; i++) {
		aux[i] = filmes[i];
	}
	
	//menor nome fica no pri
	pos = menorNome(aux, qtd);
	strcpy(aux[pos].nome, "0");//invalido
	pri = pos;

	for (i = 0; i < qtd; i++) {
		posprox = menorNome(aux, qtd);
		strcpy(aux[pos].nome, "0");//invalido
		lista[pos] =  posprox;
		pos = posprox;
	//	printf(" pos = %d, posprox = %d\n", pos, posprox);
	}
	pos = menorNome(aux, qtd);
	lista[pos] = -1;
	//printf(" pos final = %d\n", pos);

	for (i = 0; i < qtd; i++) {
	//	printf(" lista[%d] = %d\n", i, lista[i]);
	}
		
	
	return pri;
}

int menorNome(filme filmes[], int qtd) {
	char menor[20];
	int i = 0, pos = -1; //lista vazia
	while (strcmp(filmes[i].nome, "0") == 0)
		i++;
	if (i < qtd) {
		strcpy(menor, filmes[i].nome);
		pos = i;
	}
	for (i = 0; i < qtd; i++) {
		if ((strcmp(menor, filmes[i].nome) > 0) && (strcmp(filmes[i].nome, "0") != 0)) {
			strcpy(menor, filmes[i].nome);
			pos = i;
		}
	}
	return pos;
}
void imprimeOrdNome(int lista[], int PRI, filme filmes[]) {
	int x;
	x = PRI;
	//printf(" PRI = %d \n", PRI);
	//imprime(filmes[PRI]);
	while (lista[x] != -1) {
		//printf(" x = %d \n", x);
		//printf(" lista[x] = %d \n", lista[x]);
		imprime(filmes[x]);
		x = lista[x];
	}
	imprime(filmes[x]);
}

void popularCatCod(filme filmes[], int qtd, int index[][2], indexCategoria indexCat[], int lista[]) {
	filme aux[MAX];
	int i, x, pos, posprox, pri = -1;


	//inicializa index com as categoria possiveis
	strcpy(indexCat[0].categoria, "comedia\0");
	strcpy(indexCat[1].categoria, "drama\0");
	strcpy(indexCat[2].categoria, "romance\0");
	strcpy(indexCat[3].categoria, "terror\0");
	indexCat[0].posicaoInicial = -1;
	indexCat[1].posicaoInicial = -1;
	indexCat[2].posicaoInicial = -1;
	indexCat[3].posicaoInicial = -1;
	
	for (i = 0; i < qtd; i++) {
		lista[i] = -1;
	}
	
	for (i = 0; i < qtd; i++) {
		pos = index[i][1];
		if (strcmp(filmes[pos].categoria, indexCat[0].categoria) == 0) { //comedia
			if (indexCat[0].posicaoInicial == -1) {
				indexCat[0].posicaoInicial = pos;
			}
			else {
				x = indexCat[0].posicaoInicial;
				while (lista[x] != -1) {
					x = lista[x];
				}
				lista[x] = pos;
			}
		}

		if (strcmp(filmes[pos].categoria, indexCat[1].categoria) == 0) { //drama
			if (indexCat[1].posicaoInicial == -1) {
				indexCat[1].posicaoInicial = pos;
			}
			else {
				x = indexCat[1].posicaoInicial;
				while (lista[x] != -1) {
					x = lista[x];
				}
				lista[x] = pos;
			}
		}

		if (strcmp(filmes[pos].categoria, indexCat[2].categoria) == 0) { //romance
			if (indexCat[2].posicaoInicial == -1) {
				indexCat[2].posicaoInicial = pos;
			}
			else {
				x = indexCat[2].posicaoInicial;
				while (lista[x] != -1) {
					x = lista[x];
				}
				lista[x] = pos;
			}
		}

		if (strcmp(filmes[pos].categoria, indexCat[3].categoria) == 0) { //terror
			if (indexCat[3].posicaoInicial == -1) {
				indexCat[3].posicaoInicial = pos;
			}
			else {
				x = indexCat[3].posicaoInicial;
				while (lista[x] != -1) {
					x = lista[x];
				}
				lista[x] = pos;
			}
		}
	}
	//for (i = 0; i < qtd; i++) {
		//printf(" lista[%d] = %d\n", i, lista[i]);
	//}
	//for (i = 0; i < 4; i++) {
		//printf(" categoria = %s, PRI = %d\n", indexCat[i].categoria, indexCat[i].posicaoInicial);
	//}
}

void imprimeCatCod(int lista[], indexCategoria index[], filme filmes[]) {
	int x , i;
	for (i = 0; i < 4; i++) {
		printf("Categoria = %s.\n", index[i].categoria);
		x = index[i].posicaoInicial;
		if (x != -1) {
			while (lista[x] != -1) {
				imprime(filmes[x]);
				x = lista[x];
			}
			imprime(filmes[x]);
		}
	}
}
void popularCatNome(filme filmes[], int qtd, int PRI, int lista[], indexCategoria indexCat[], int listaNome[]) {
	filme aux[MAX];
	int i, x, y, pos, posprox, pri = -1;

	//inicializa index com as categoria possiveis
	strcpy(indexCat[0].categoria, "comedia\0");
	strcpy(indexCat[1].categoria, "drama\0");
	strcpy(indexCat[2].categoria, "romance\0");
	strcpy(indexCat[3].categoria, "terror\0");
	indexCat[0].posicaoInicial = -1;
	indexCat[1].posicaoInicial = -1;
	indexCat[2].posicaoInicial = -1;
	indexCat[3].posicaoInicial = -1;

	for (i = 0; i < qtd; i++) {
		listaNome[i] = -1;
	}
	x = PRI;
	while (x != -1) {
		pos = x;
		//printf(" pos = %d\n", pos);
		
		if (strcmp(filmes[pos].categoria, indexCat[0].categoria) == 0) { //comedia
			if (indexCat[0].posicaoInicial == -1) {
				indexCat[0].posicaoInicial = pos;
			}
			else {
				y = indexCat[0].posicaoInicial;
				while (listaNome[y] != -1) {
					y = listaNome[y];
				}
				listaNome[y] = pos;
			}
		}

		if (strcmp(filmes[pos].categoria, indexCat[1].categoria) == 0) { //drama
			if (indexCat[1].posicaoInicial == -1) {
				indexCat[1].posicaoInicial = pos;
			}
			else {
				y = indexCat[1].posicaoInicial;
				while (listaNome[y] != -1) {
					y = listaNome[y];
				}
				listaNome[y] = pos;
			}
		}

		if (strcmp(filmes[pos].categoria, indexCat[2].categoria) == 0) { //romance
			if (indexCat[2].posicaoInicial == -1) {
				indexCat[2].posicaoInicial = pos;
			}
			else {
				y = indexCat[2].posicaoInicial;
				while (listaNome[y] != -1) {
					y = listaNome[y];
				}
				listaNome[y] = pos;
			}
		}

		if (strcmp(filmes[pos].categoria, indexCat[3].categoria) == 0) { //terror
			if (indexCat[3].posicaoInicial == -1) {
				indexCat[3].posicaoInicial = pos;
			}
			else {
				y = indexCat[3].posicaoInicial;
				while (listaNome[y] != -1) {
					y = listaNome[y];
				}
				listaNome[y] = pos;
			}
		}

		x = lista[x];
	//	printf(" x = %d\n", x);
	}


//	for (i = 0; i < qtd; i++) {
//		printf(" listaNome[%d] = %d\n", i, listaNome[i]);
//	}
//	for (i = 0; i < 4; i++) {
//		printf(" categoria = %s, PRI = %d\n", indexCat[i].categoria, indexCat[i].posicaoInicial);
//	}

	printf("terminou na funcao.\n");

}