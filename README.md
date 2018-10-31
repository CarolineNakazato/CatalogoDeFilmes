# CatalogoDeFilmes
Trabalho sobre Técnicas de Indexação usando registro de filmes em arquivo binário.

1º. Criar um arquivo binário, com pelo menos 50 registros, desordenados.

	Os registros devem ter pelo menos 5 (cinco) campos, sendo:
1.	chave primária do tipo inteiro com 4 dígitos;
2.	campo nome/descrição – tipo string;
3.	campo passível de ser categorizado (4 ou 5 categorias) – tipo string;
4.	campo 4 – tipo real;
5.	campo 5 – qualquer tipo.
  
IMPORTANTE: não serve dados de alunos.

Esse arquivo pode ser criado em um programa independente.

2º. Programa objeto do trabalho:  criar índices e utilizar os métodos de busca.

 I - Índices exigidos:
a)	considerando que o arquivo principal está desordenado, criar um índice denso ou exaustivo, contendo todas as chaves primárias e a posição relativa linear que o registro se encontra no arquivo. Utilizar qualquer método para a ordenação desse índice, pela chave primária; 
b)	Tabela Invertida para a ordem alfabética do campo2 (string);
c)	dois índices secundários – listas ligadas de cada uma das categorias. Um dos índices deve seguir a ordenação da chave primária e o outro pela ordem alfabética do campo2 (Tabela Invertida – item b);
d)	
IMPORTANTE: considerando que para o exercício o arquivo é pequeno, os índices podem estar gravados ou gerados todas as vezes que o programa for executado.

II – Execução do Programa:


1)	apresentar um MENU:
a.	Consultar “um registro”: 
i.	entrada é pelo campo chave primária;
ii.	Carregar Índice denso (item a);
iii.	Chamar a função Busca Binária para localizar a chave;
iv.	Ler no arquivo o registro procurado;
v.	Imprimir todas as informações do registro buscado;
vi.	Caso não exista o valor buscado: imprimir mensagem e não fazer os passos iv e v, acima;
vii.	Voltar a exibir MENU.
b.	Alterar/Atualizar campo(s) de um registro (menos o campo chave primária):
i.	entrada é pelo campo chave primária;
ii.	Carregar Índice denso (item a);
iii.	Chamar a função Busca Binária para localizar a chave;
iv.	Ler no arquivo o registro procurado;
v.	Perguntar qual campo será modificado, um a um;
vi.	Alterar o(s) campo(s) no arquivo;
vii.	Caso a alteração ocorra no campo 2 e/ou no da categoria (campo3) – atualizar os respectivos Índices; 
viii.	Caso não exista o valor buscado: imprimir mensagem e não fazer os passos de iv a vii, acima;
ix.	Voltar a exibir MENU.
c.	Eliminar um registro do arquivo:
i.	entrada é pelo campo chave primária;
ii.	Carregar Índice denso (item a);
iii.	Chamar a função Busca Binária para localizar a chave;
iv.	Eliminar (*) o registro procurado do arquivo;
v.	Atualizar os respectivos Índices; 
vi.	Caso não exista o valor buscado: imprimir mensagem e não fazer os passos iv e v, acima;
vii.	Voltar a exibir MENU.
d.	Inserir um registro no arquivo:
i.	ler as informações do novo registro. Fazer a validação de o valor do campo chave primária já existir no arquivo. Caso já exista, repetir a digitação do campo até que se digite um valor válido;
ii.	Inserir o novo registro no final do arquivo;
iii.	Atualizar os respectivos Índices; 
iv.	Imprimir mensagem:” inserção feita com sucesso”;
v.	Voltar a exibir MENU.
e.	Impressão:
i.	Sub-menu:
1.	Imprimir todos por campo chave primária ordenada;
2.	imprimir todos por campo2 ordenado;
3.	imprimir todos por Categoria ordenado pelo campo chave;
4.	imprimir todos por categoria ordenado pelo campo2
5.	imprimir dados do arquivo desordenado


(*) para eliminação:
 1. carregar o arquivo numa tabela (memória principal) excluir o registro, “subindo” os registros que o sucedem, uma posição;
2. regravar os registros;
3. atualizar os índices.
