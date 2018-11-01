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
typedef struct {
	int codigo;
	char nome[20];
	char categoria[10]; //suspense, romance, terror, comedia
	float preco;
	float classificacao; //nota da cr�tica
}filme;


int buscaBinaria(int vet[], int chave);
int leArquivo(filme filmes[]);
void imprime(filme filmeAtual);
int exclusao(filme filmes[], int posicao, int qtd);
int insere(filme filmeAtual, int qtd, filme filmes[]);

void main() {
	filme filmes[MAX];
	filme filmeAtual;
	int opcao, opcaoAlterar, qtd = -1, codAtual, posicao;
	int index[MAX];
	char novoNome[20], novaCategoria[10];
	double novoPreco, novaNota;
	//inicializa vetor
	qtd = leArquivo(filmes);
	
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

			//Chamar a fun��o Busca Bin�ria para localizar a chave;
			posicao = buscaBinaria(index, codAtual);

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

			//Chamar a fun��o Busca Bin�ria para localizar a chave;
			posicao = buscaBinaria(index, codAtual);
			if (posicao != -1) {
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
					strcpy(filmes[posicao].nome,novoNome);
					//atualiza indice 
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
				} while (opcao != alteraSair);
				//atualizar arquivo???
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
				posicao = buscaBinaria(index, filmeAtual.codigo);
				
				if (posicao == -1) {
					printf("Digite o nome do filme:\n");
					scanf("%s", filmeAtual.nome);
					printf("Digite a categoria do filme:\n");
					scanf("%s", filmeAtual.categoria);
					//falta classificacao e preco
					qtd = insere(filmeAtual, qtd, filmes);
					printf("Insercao feita com sucesso!\n");
					//Atualizar os respectivos Índices;
				}
				else {
					printf("Codigo do filme ja existe.\n");
				}
			} while (posicao!=-1);
			break;
		case excluir:
			//Entrada da chave prim�ria;
			printf("Digite o codigo do filme:\n");
			scanf("%d", &codAtual);

			//Carregar �ndice denso (item a);

			//Chamar a fun��o Busca Bin�ria para localizar a chave;
			posicao = buscaBinaria(index, codAtual);

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
			break;
		case sair:
			break;
		default:
			printf("Opcao Invalida!\n");
			break;
		}
	} while (opcao != sair);
	system("pause");

}

//retorna posicao da chave no vetor ou -1 caso n�o existe no vetor
int buscaBinaria(int vet[], int chave) {
	int inf = 0, sup = MAX - 1, meio;
	while (inf <= sup) {
		meio = (inf + sup) / 2;
		if (chave == vet[meio])
			return meio;
		if (chave < vet[meio])
			sup = meio - 1;
		else
			inf = meio + 1;
	}
	return -1;   // n�o encontrado
}

//retorna a quantidade de filmes de um arquivo e popula o vetor de filmes
int leArquivo(filme filmes[]){
	FILE *arq;
	filme filmeAtual;
	int i, qtd = -1;//não existe nenhum filme

	// Abre um arquivo BIN�RIO para LEITURA
	arq = fopen("arq.dat", "rb");
	if (arq == NULL) {
		printf("Problemas na abertura do arquivo\n");
		return -1; 
	}

	fseek(arq, 0, SEEK_SET);
	while (!feof(arq)) {
		qtd++;
		fread(&filmes[qtd], sizeof(filme), 1, arq);
	}

	fclose(arq);
	return qtd;
	
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
int insere(filme filmeAtual, int qtd, filme filmes[])
{
	if(qtd+1<MAX-1)
		filmes[qtd+1] = filmeAtual;
	return qtd + 1;
}
