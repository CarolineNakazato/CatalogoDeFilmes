#define _CRT_SECURE_NO_WARNINGS
#define MAX 60
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
	int opcao, opcaoAlterar, opcaoOrdenar, opcaoCat, qtd, codAtual, posicao, i, PRI;
	//int qtd = 49;
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

	filmes[3].codigo = 1001;
	strcpy(filmes[3].nome, "Me before you");
	strcpy(filmes[3].categoria, "romance");
	filmes[3].classificacao = 7.5;
	filmes[3].preco = 5.5;

	filmes[4].codigo = 1002;
	strcpy(filmes[4].nome, "Casablanca");
	strcpy(filmes[4].categoria, "romance");
	filmes[4].classificacao = 5.7;
	filmes[4].preco = 1.0;

	filmes[5].codigo = 1003;
	strcpy(filmes[5].nome, "Cantando na chuva");
	strcpy(filmes[5].categoria, "romance");
	filmes[5].classificacao = 6.5;
	filmes[5].preco = 1.5;

	filmes[6].codigo = 2001;
	strcpy(filmes[6].nome, "Before Midnight");
	strcpy(filmes[6].categoria, "romance");
	filmes[6].classificacao = 5;
	filmes[6].preco = 4.5;

	filmes[7].codigo = 2002;
	strcpy(filmes[7].nome, "A bela e a fera");
	strcpy(filmes[7].categoria, "romance");
	filmes[7].classificacao = 6.5;
	filmes[7].preco = 2.0;

	filmes[8].codigo = 2003;
	strcpy(filmes[8].nome, "Her");
	strcpy(filmes[8].categoria, "romance");
	filmes[8].classificacao = 5.5;
	filmes[8].preco = 1.5;

	filmes[9].codigo = 3001;
	strcpy(filmes[9].nome, "Forrest gump");
	strcpy(filmes[9].categoria, "romance");
	filmes[9].classificacao = 2.5;
	filmes[9].preco = 1.5;

	filmes[10].codigo = 3002;
	strcpy(filmes[10].nome, "Suite Francesa");
	strcpy(filmes[10].categoria, "romance");
	filmes[10].classificacao = 6.7;
	filmes[10].preco = 2.0;

	filmes[11].codigo = 3003;
	strcpy(filmes[11].nome, "Bonequinha de luxo");
	strcpy(filmes[11].categoria, "romance");
	filmes[11].classificacao = 6.5;
	filmes[11].preco = 1.5;

	filmes[12].codigo = 3004;
	strcpy(filmes[12].nome, "Tempos modernos");
	strcpy(filmes[12].categoria, "comedia");
	filmes[12].classificacao = 9.5;
	filmes[12].preco = 1.5;

	filmes[13].codigo = 1004;
	strcpy(filmes[13].nome, "La La Land");
	strcpy(filmes[13].categoria, "romance");
	filmes[13].classificacao = 7.5;
	filmes[13].preco = 6.5;

	filmes[14].codigo = 1005;
	strcpy(filmes[14].nome, "A vida eh bela");
	strcpy(filmes[14].categoria, "drama");
	filmes[14].classificacao = 5.8;
	filmes[14].preco = 1.0;

	filmes[15].codigo = 1006;
	strcpy(filmes[15].nome, "Little miss sun");
	strcpy(filmes[15].categoria, "comedia");
	filmes[15].classificacao = 8.5;
	filmes[15].preco = 2.5;

	filmes[16].codigo = 2004;
	strcpy(filmes[16].nome, "O ditador");
	strcpy(filmes[16].categoria, "comedia");
	filmes[16].classificacao = 9;
	filmes[16].preco = 1.5;

	filmes[17].codigo = 2005;
	strcpy(filmes[17].nome, "Beautiful Fantastic");
	strcpy(filmes[17].categoria, "romance");
	filmes[17].classificacao = 7.5;
	filmes[17].preco = 2.0;

	filmes[18].codigo = 2006;
	strcpy(filmes[18].nome, "Mamma Mia");
	strcpy(filmes[18].categoria, "comedia");
	filmes[18].classificacao = 5.5;
	filmes[18].preco = 1.5;

	filmes[19].codigo = 3004;
	strcpy(filmes[19].nome, "Aprendiz");
	strcpy(filmes[19].categoria, "drama");
	filmes[19].classificacao = 9.5;
	filmes[19].preco = 2.5;

	filmes[20].codigo = 3005;
	strcpy(filmes[20].nome, "Big Hero");
	strcpy(filmes[20].categoria, "comedia");
	filmes[20].classificacao = 7.7;
	filmes[20].preco = 5.0;

	filmes[21].codigo = 3006;
	strcpy(filmes[21].nome, "Clube do cinco");
	strcpy(filmes[21].categoria, "comedia");
	filmes[21].classificacao = 8.5;
	filmes[21].preco = 1.5;

	filmes[22].codigo = 3007;
	strcpy(filmes[22].nome, "Amelie Poulain");
	strcpy(filmes[22].categoria, "romance");
	filmes[22].classificacao = 7.5;
	filmes[22].preco = 3.5;

	filmes[23].codigo = 4000;
	strcpy(filmes[23].nome, "Wonder woman");
	strcpy(filmes[23].categoria, "drama");
	filmes[23].classificacao = 6.9;
	filmes[23].preco = 6.25;

	filmes[24].codigo = 4001;
	strcpy(filmes[24].nome, "The Goodfather");
	strcpy(filmes[24].categoria, "drama");
	filmes[24].classificacao = 7.2;
	filmes[24].preco = 3.0;

	filmes[25].codigo = 4002;
	strcpy(filmes[25].nome, "Planeta dos macacos");
	strcpy(filmes[25].categoria, "drama");
	filmes[25].classificacao = 7.4;
	filmes[25].preco = 4.5;

	filmes[26].codigo = 4003;
	strcpy(filmes[26].nome, "Star Wars");
	strcpy(filmes[26].categoria, "drama");
	filmes[26].classificacao = 9;
	filmes[26].preco = 10.50;

	filmes[27].codigo = 4004;
	strcpy(filmes[27].nome, "Harry Potter");
	strcpy(filmes[27].categoria, "drama");
	filmes[27].classificacao = 7.5;
	filmes[27].preco = 8.5;

	filmes[28].codigo = 4005;
	strcpy(filmes[28].nome, "Maze Runner");
	strcpy(filmes[28].categoria, "drama");
	filmes[28].classificacao = 6.5;
	filmes[28].preco = 7.5;

	filmes[29].codigo = 4006;
	strcpy(filmes[29].nome, "Run");
	strcpy(filmes[29].categoria, "terror");
	filmes[29].classificacao = 3.5;
	filmes[29].preco = 1.5;

	filmes[30].codigo = 6000;
	strcpy(filmes[30].nome, "Lawrence da arabia");
	strcpy(filmes[30].categoria, "drama");
	filmes[30].classificacao = 5.7;
	filmes[30].preco = 1.0;

	filmes[31].codigo = 6001;
	strcpy(filmes[31].nome, "King Kong");
	strcpy(filmes[31].categoria, "terror");
	filmes[31].classificacao = 5.0;
	filmes[31].preco = 3.5;

	filmes[32].codigo = 6002;
	strcpy(filmes[32].nome, "Teoria de tudo");
	strcpy(filmes[32].categoria, "drama");
	filmes[32].classificacao = 8.5;
	filmes[32].preco = 5.5;

	filmes[33].codigo = 6003;
	strcpy(filmes[33].nome, "Eye of the needle");
	strcpy(filmes[33].categoria, "drama");
	filmes[33].classificacao = 8.9;
	filmes[33].preco = 1.25;

	filmes[34].codigo = 6004;
	strcpy(filmes[34].nome, "Imitation Game");
	strcpy(filmes[34].categoria, "drama");
	filmes[34].classificacao = 7.5;
	filmes[34].preco = 3.5;

	filmes[35].codigo = 6005;
	strcpy(filmes[35].nome, "ET");
	strcpy(filmes[35].categoria, "comedia");
	filmes[35].classificacao = 6.4;
	filmes[35].preco = 2.25;

	filmes[36].codigo = 6006;
	strcpy(filmes[36].nome, "Ghostbusters");
	strcpy(filmes[36].categoria, "comedia");
	filmes[36].classificacao = 6.0;
	filmes[36].preco = 5.5;

	filmes[37].codigo = 5000;
	strcpy(filmes[37].nome, "Back to the future");
	strcpy(filmes[37].categoria, "comedia");
	filmes[37].classificacao = 7.0;
	filmes[37].preco = 2.5;

	filmes[38].codigo = 5001;
	strcpy(filmes[38].nome, "Schindlers list");
	strcpy(filmes[38].categoria, "drama");
	filmes[38].classificacao = 6.5;
	filmes[38].preco = 5.5;

	filmes[39].codigo = 5002;
	strcpy(filmes[39].nome, "Piratas do Caribe");
	strcpy(filmes[39].categoria, "comedia");
	filmes[39].classificacao = 3.5;
	filmes[39].preco = 1.5;
	
	filmes[40].codigo = 7000;
	strcpy(filmes[40].nome, "Voice in the stone");
	strcpy(filmes[40].categoria, "terror");
	filmes[40].classificacao = 7.8;
	filmes[40].preco = 5.0;

	filmes[41].codigo = 7001;
	strcpy(filmes[41].nome, "Psicose");
	strcpy(filmes[41].categoria, "terror");
	filmes[41].classificacao = 7.0;
	filmes[41].preco = 3.5;

	filmes[42].codigo = 7002;
	strcpy(filmes[42].nome, "Jaw");
	strcpy(filmes[42].categoria, "terror");
	filmes[42].classificacao = 5.5;
	filmes[42].preco = 1.5;

	filmes[43].codigo = 7003;
	strcpy(filmes[43].nome, "Laranja Mecanica");
	strcpy(filmes[43].categoria, "drama");
	filmes[43].classificacao = 8.9;
	filmes[43].preco = 3.25;

	filmes[44].codigo = 7004;
	strcpy(filmes[44].nome, "Donnie darko");
	strcpy(filmes[44].categoria, "drama");
	filmes[44].classificacao = 8.5;
	filmes[44].preco = 3.5;

	filmes[45].codigo = 7005;
	strcpy(filmes[45].nome, "Matrix");
	strcpy(filmes[45].categoria, "drama");
	filmes[45].classificacao = 5.7;
	filmes[45].preco = 2.25;

	filmes[46].codigo = 8000;
	strcpy(filmes[46].nome, "Clube da Luta");
	strcpy(filmes[46].categoria, "drama");
	filmes[46].classificacao = 4.5;
	filmes[46].preco = 5.5;

	filmes[47].codigo = 8001;
	strcpy(filmes[47].nome, "Jigsaw");
	strcpy(filmes[47].categoria, "terror");
	filmes[47].classificacao = 7.0;
	filmes[47].preco = 2.5;

	filmes[48].codigo = 8002;
	strcpy(filmes[48].nome, "Massacre no Texas");
	strcpy(filmes[48].categoria, "terror");
	filmes[48].classificacao = 6.5;
	filmes[48].preco = 2.5;

	filmes[49].codigo = 9002;
	strcpy(filmes[49].nome, "Indiana Jones");
	strcpy(filmes[49].categoria, "comedia");
	filmes[49].classificacao = 5.6;
	filmes[49].preco = 5.5;

	//escreveArquvio(filmes, qtd);
	
	//escreveArquvio(filmes, qtd);

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
						printf("Digite o nome do filme(primeira letra em maiusculo):\n");
						//fflush(stdin);
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

						strcpy(filmes[posicao].categoria, novaCategoria);

						//atualiza indice
						popularCatCod(filmes, qtd, index, indexCat, listaCod);
						popularCatNome(filmes, qtd, PRI, lista, indexCatNome, listaNome);

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
					printf("Digite o nome do filme (primeira letra em maiusculo):\n");
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
							strcpy(filmeAtual.categoria, "comedia");
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
					} while ((opcaoOrdenar == comedia) ||
						(opcaoOrdenar == drama) ||
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
					popularCatNome(filmes, qtd, PRI, lista, indexCatNome, listaNome);
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
				popularCatNome(filmes, qtd, PRI, lista, indexCatNome, listaNome);
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
	return (qtd - 1);
}

//inserir filme no final do vetor
int insere(filme filmeAtual, int qtd, filme * filmes)
{
	//printf("qtd + 1=  %d\n", qtd + 1);
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
	for (i = 0; i < qtd; i++) {
		lista[i] = -1;
	}

	//menor nome fica no pri
	pos = menorNome(aux, qtd);
	strcpy(aux[pos].nome, "0");//invalido
							   //printf("aux[%d].nome = %s\n", pos, aux[pos].nome);
	pri = pos;

	for (i = 0; i < qtd; i++) {
		posprox = menorNome(aux, qtd);
		//printf("aux[%d].nome = %s\n", posprox, aux[posprox].nome);
		strcpy(aux[posprox].nome, "0");//invalido
		lista[pos] = posprox;
		//printf(" pos = %d, posprox = %d\n", pos, posprox);
		pos = posprox;
	}
	//pos = menorNome(aux, qtd);
	//lista[pos] = -1;
	//printf(" pos final = %d\n", pos);

	for (i = 0; i < qtd; i++) {
		//printf(" lista[%d] = %d\n", i, lista[i]);
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
	int x, i;
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
	int i, x, y, pos, posprox, pri = -1, cat;

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
		//printf(" lista[%d] = %d\n", i, lista[i]);
	}

	for (i = 0; i < qtd; i++) {
		listaNome[i] = -1;
	}

	for (i = 0; i < 4; i++) {
		x = PRI;
		//printf(" PRI = %d \n", PRI);
		//imprime(filmes[PRI]);
		while (x != -1) {
			//printf("-1) x = %d \n", x);
			//printf("0) lista[x] = %d \n", lista[x]);

			pos = x;
			if (strcmp(filmes[pos].categoria, indexCat[i].categoria) == 0) { //comedia
				if (indexCat[i].posicaoInicial == -1) {
					//printf("1) categoria = %s, PRI = %d\n", indexCat[i].categoria, indexCat[i].posicaoInicial);
					//printf("1.5)%d indexCat[%d].posicaoInicial =  %d\n", indexCat[i].posicaoInicial ,i,pos);
					indexCat[i].posicaoInicial = pos;
				}
				else {
					y = indexCat[i].posicaoInicial;
					while (listaNome[y] != -1) {
						y = listaNome[y];
					}
					listaNome[y] = pos;
					//printf("2) listaNome[%d] = %d\n", y, pos);
					pos = y;

				}
			}


			x = lista[x];
			//printf("3) x = %d \n", x);
		}
		//imprime(filmes[x]);
	}

	for (i = 0; i < qtd; i++) {
		//printf(" listaNome[%d] = %d\n", i, listaNome[i]);
	}
	for (i = 0; i < 4; i++) {
		//printf(" categoria = %s, PRI = %d\n", indexCat[i].categoria, indexCat[i].posicaoInicial);
	}

	//printf("terminou na funcao.\n");

}
