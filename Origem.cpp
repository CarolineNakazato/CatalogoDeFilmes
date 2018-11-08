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
typedef struct {
	int codigo;
	char nome[20];
	char categoria[10]; //suspense, romance, terror, comedia
	float preco;
	float classificacao; //nota da cr�tica
}filme;

typedef struct {
	int link;
	char nome[20];
}indexSecundario;

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
void popularIndexSec(filme filmes[], indexSecundario indexSec[], int qtd);
void swapSec(indexSecundario *x, indexSecundario *y);
void bubbleSortSec(indexSecundario indexSec[], int qtd);
void imprimeOrdenadoNome(filme filmes[], indexSecundario indexSec[], int qtd);

void main() {
	filme filmes[MAX];
	filme filmeAtual;
	int opcao, opcaoAlterar, opcaoOrdenar, qtd = 2, codAtual, posicao, i;
	int index[MAX][2];//chave, link
	indexSecundario indexSec[MAX];
	char novoNome[20], novaCategoria[10];
	double novoPreco, novaNota;
	filmes[0].codigo = 2000;
	strcpy(filmes[0].nome, "Uma Noite no museu");
	strcpy(filmes[0].categoria, "comedia");
	filmes[0].classificacao = 5;
	filmes[0].preco = 1.5;

	filmes[1].codigo = 1000;
	strcpy(filmes[1].nome, "Uma bela mulher");
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
	popularIndexSec(filmes, indexSec, qtd); //popula index secundario (nome)

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
			printf("Digite o codigo do filme:\n");
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
			printf("Digite o codigo do filme:\n");
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
						scanf("%s", novoNome);
						strcpy(filmes[posicao].nome, novoNome);
						//atualiza indice Secundario 
						popularIndexSec(filmes, indexSec, qtd);

						break;
					case alteraCategoria:
						printf("Digite a categoria do filme:\n");
						scanf("%s", novaCategoria);
						strcpy(filmes[posicao].nome, novaCategoria);
						//atualiza indice

						break;
					case alteraPreco:
						printf("Digite o preco do filme:\n");
						scanf("%f", &novoPreco);
						filmes[posicao].preco = novoPreco;
						break;
					case alteraClassificacao:
						printf("Digite a nota do filme:\n");
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
				printf("Digite o codigo do filme:\n");
				scanf("%d", &filmeAtual.codigo);

				//Verifica se o codigo do filmes ja existe
				posicao = buscaBinaria(index, filmeAtual.codigo, qtd);

				if (posicao == -1) {
					// pega as entradas e monta um filme
					printf("Digite o nome do filme:\n");
					scanf("%s", filmeAtual.nome);
					printf("Digite a categoria do filme:\n");
					scanf("%s", filmeAtual.categoria);
					printf("Digite o preco do filme:\n");
					scanf("%f", &filmeAtual.preco);
					printf("Digite a nota do filme:\n");
					scanf("%f", &filmeAtual.classificacao);

					qtd = insere(filmeAtual, qtd, filmes);
					printf("Insercao feita com sucesso!\n");

					//Atualizar os respectivos Índices;
				}
				else {
					printf("Codigo do filme ja existe.\n");
				}
			} while (posicao != -1);
			break;
		case excluir:
			//Entrada da chave prim�ria;
			printf("Digite o codigo do filme:\n");
			scanf("%d", &codAtual);

			//Carregar �ndice denso (item a);

			//Chamar a fun��o Busca Bin�ria para localizar a chave;
			posicao = buscaBinaria(index, codAtual, qtd);

			//Caso exista o valor buscado;
			if (posicao != -1) {
				//Inserir o registro no final do vetor;
				qtd = exclusao(filmes, posicao, qtd);
				//Atualizar os respectivos Índices;

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
					imprimeOrdenadoNome(filmes, indexSec, qtd);
					break;
				case ordenadoCategoriaCod:
					//imprimir indice secundario com codigo
					break;
				case ordenadoCategoriaNome:
					//imprimir indice secundario com codigo
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
	for (i = 0; i <= qtd; i++) {
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
	if (qtd + 1<MAX - 1)
		filmes[qtd + 1] = filmeAtual;
	return qtd + 1;
}

void popularIndex(filme filmes[], int index[][2], int qtd) {
	int i;
	for (i = 0; i < qtd; i++) {
		index[i][0] = filmes[i].codigo; //chave primaria
		index[i][1] = i; //link
		//printf("Chave: %d  link = %d\n", index[i][0], index[i][1]);
	}
	bubbleSort(index,qtd);
}

void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void bubbleSort(int index[][2], int qtd) {
	int i, j;
	for (i = 0; i < qtd-1; i++)    
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

void popularIndexSec(filme filmes[], indexSecundario indexSec[], int qtd) {
	int i;
	for (i = 0; i < qtd; i++) {
		strcpy(indexSec[i].nome, filmes[i].nome); //chave secundaria
		indexSec[i].link = i; //link
		printf("Chave: %s  link = %d\n", indexSec[i].nome , indexSec[i].link);
	}
	bubbleSortSec(indexSec,qtd);
}

void swapSec(indexSecundario *x, indexSecundario *y) {
	indexSecundario temp = *x;
	*x = *y;
	*y = temp;
}

void bubbleSortSec(indexSecundario indexSec[], int qtd) {
	int i, j;
	for (i = 0; i < qtd - 1; i++)
		for (j = 0; j < qtd - i - 1; j++)
			if (strcmp(indexSec[j].nome,indexSec[j + 1].nome)>0) {//comparar chaves
				swapSec(&indexSec[j], &indexSec[j + 1]);
			}
}

void imprimeOrdenadoNome(filme filmes[], indexSecundario indexSec[], int qtd) {
	int i;
	for (i = 0; i < qtd; i++)
		imprime(filmes[indexSec[i].link]);
}