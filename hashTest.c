#include <glib.h>
#include <gmodule.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct movimentos* Moves;
typedef struct coisas* Varios;

struct movimentos
{
	GHashTable* produtos;
};

struct coisas
{
	double preco;
	int quantidade;
	int filial[3];
};


int main()
{
	char* arrayChar[8] = {"AB123", "BC123", "SD222", "LO989", "PU741", "AB123", "MN987", "OI989"};
	Varios arrayStruct[8];
	Varios array;
	Moves atum = malloc(sizeof(struct movimentos));

	//inicializa o array estrutura de dados
	for (int i = 0; i < 8; ++i)
	{
		arrayStruct[i] = malloc(sizeof(struct coisas));
		arrayStruct[i]->preco = (i+1) * 2.3;
		arrayStruct[i]->quantidade = i + i + 1;
		arrayStruct[i]->filial[i % 3] = 1;
	}

	//cria uma hashtable vazia
	GHashTable* prod = g_hash_table_new(g_str_hash, g_str_equal);
	//atribui a nova hashtable inicializada na estrutura de dados
	atum->produtos = prod;
	
	for (int i = 0; i < 8; ++i)
	{
		array = g_hash_table_lookup(atum->produtos, arrayChar[i]);
		
		if(array == NULL)
			g_hash_table_insert(atum->produtos, arrayChar[i], arrayStruct[i]);

		else
		{
			array->preco += arrayStruct[i]->preco;
			array->quantidade += arrayStruct[i]->quantidade;
			for (int j = 0; j < 3; ++j)
			{
				if(array->filial[j] != arrayStruct[i]->filial[j])
					array->filial[j] = 1;
			}
		}
	}
	
	array = g_hash_table_lookup(atum->produtos, "AB123");

	printf("%f\n", array->preco);
	printf("%d\n", array->quantidade);
	for (int i = 0; i<3; ++i)
	{
		(array->filial[i])?printf("Vendeu-se na filial %d\n", i+1):printf("Não se vendeu na filial %d\n", i+1);
	}
}