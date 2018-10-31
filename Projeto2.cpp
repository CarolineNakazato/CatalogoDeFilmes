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
	char categoria[20]; //suspense, romance, terror
	float preco;
	float classificacao; //nota da crítica
}filme;


int buscaBinaria (int vet[], int chave);
filme leArquivo(int posicao, int chave);
void imprime(filme filmeAtual);

void main() {
	filme filmes[MAX];
	filme filmeAtual;
	int opcao, opcaoAlterar, codAtual, posicao;
	int index[MAX];

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
			//Entrada da chave primária;
			printf("Digite o codigo do filme:\n");
			scanf("%d", &codAtual);

			//Carregar Índice denso (item a);

			//Chamar a função Busca Binária para localizar a chave;
			posicao = buscaBinaria(index, codAtual);

			//Caso exista o valor buscado;
			if(posicao!=-1){
				//Le no arquivo o registro procurado;
				filmeAtual = leArquivo(posicao, codAtual);
				//Imprimir todas as informações do registro buscado;
				imprime(filmeAtual);
				
			}else{
				printf("Codigo do filme nao existe.\n");
			}
			break;
		case alterar:
			//Entrada da chave primária;
			printf("Digite o codigo do filme:\n");
			scanf("%d", &codAtual);

			//Carregar Índice denso (item a);

			//Chamar a função Busca Binária para localizar a chave;
			posicao = buscaBinaria(index, codAtual);

			//Caso exista o valor buscado;
			if(posicao!=-1){
				//Le no arquivo o registro procurado;
				filmeAtual = leArquivo(posicao, codAtual);
				//Perguntar qual campo será modificado, um a um;
				printf("Digite:\n");
				printf("%d) para alterar o nome filme.\n", alteraNome);
				printf("%d) para alterar a categoria do filme.\n", alteraCategoria);
				printf("%d) para alterar o preco filme.\n", alteraPreco);
				printf("%d) para alterar nota do filme.\n", alteraClassificacao);
				printf("%d) Sair.\n", alteraSair);
				scanf("%d", &opcaoAlterar);
				//Alterar o(s) campo(s) no arquivo;
				//Caso a alteração ocorra no campo 2 e/ou no da categoria (campo3) – atualizar os respectivos Índices; 
				switch (opcaoAlterar){
				case alteraNome:
						break;
				case alteraCategoria:
						break;
				case alteraPreco:
						break;
				case alteraClassificacao:
						break;
				case alteraSair:
						break;
				default:
					printf("Opcao Invalida!\n");
					break;
				} while (opcao != alteraSair);
			
			}else{
				printf("Codigo do filme nao existe.\n");
			}
			break;
		case excluir:
			break;
		case inserir:
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

//retorna posicao da chave no vetor ou -1 caso não existe no vetor
int buscaBinaria (int vet[], int chave){
     int inf = 0, sup = MAX-1, meio;
     while (inf <= sup){
          meio = (inf + sup)/2;
          if (chave == vet[meio])
               return meio;
          if (chave < vet[meio])
               sup = meio-1;
          else
               inf = meio+1;
     }
     return -1;   // não encontrado
}

//retorna do arquivo um filme especifico
filme leArquivo(int posicao, int chave){
	FILE *arq;
	filme filmes[MAX], filmeAtual;
	int i, qtd;

	// Abre um arquivo BINÁRIO para LEITURA
	arq = fopen("arq.dat", "rb");
	if (arq == NULL){
		printf("Problemas na abertura do arquivo\n");
		return filmeAtual;
	}

	qtd = fread(&filmes[0], sizeof(filme), 100, arq);

	for (i=0; i<qtd; i++)
		if(chave == filmes[i].codigo){
			filmeAtual = filmes[i];
		}

	return filmeAtual;
	fclose(arq);
}

//Imprime as informações do filme;
void imprime(filme filmeAtual){
	printf("Codigo do filme: %d\n",filmeAtual.codigo);
	printf("Nome do filme: %s\n",filmeAtual.nome);
	printf("Tipo do filme: %s\n",filmeAtual.categoria);
	printf("Preco do filme: %.2f\n",filmeAtual.preco);
	printf("Nota da critica: %.2f\n",filmeAtual.classificacao);
}
