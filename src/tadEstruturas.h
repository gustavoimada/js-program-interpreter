struct pTokens // stuct da linha horizontal
{
	char token[50];
	struct pTokens *prox;
};typedef struct pTokens PTokens;

struct listaDE // struct da linha vertical
{
	char linhaOriginal[120];
	struct listaDE *ant, *prox;
	PTokens *pTokens;
};typedef struct listaDE ListaDE; 

void initL(ListaDE **lista)
{
	*lista = NULL;
}

char isEmpty(ListaDE *lista)
{
	return lista==NULL;
}

void insereLD(ListaDE **lista)
{
	ListaDE *caixa = (ListaDE*)malloc(sizeof(ListaDE));
	caixa->ant = NULL;
	caixa->prox = NULL;
	caixa->pTokens = NULL;
	ListaDE *aux;
	if(isEmpty(*lista))
	{
		*lista = caixa;
	}
	else
	{
		aux = *lista;
		while(aux->prox != NULL)
		{
			aux = aux->prox;
		}
		aux->prox = caixa;
		caixa->ant = aux;
	}
}
char isEmptyT(PTokens *lista)
{
	return lista == NULL;
}

void exibeTokens(PTokens *lista)
{
	while(!isEmptyT(lista))
	{
		printf("{%s}", lista->token);
		lista = lista->prox;
	}
}

void exibeL(ListaDE *lista)
{
	int i=1;
	while(!isEmpty(lista))
	{
		printf("%d", i++);
		exibeTokens(lista->pTokens);
		printf("\n");
		lista = lista->prox;
	}
	getch();
}

void insereT(ListaDE *lista, char nome[20])
{
	PTokens *caixa = (PTokens*)malloc(sizeof(PTokens));
	PTokens *aux;
	caixa->prox = NULL;
	strcpy(caixa->token, nome);
	while(lista->prox != NULL)
		lista = lista->prox;
	if(lista->pTokens == NULL)
		lista->pTokens = caixa;
	else{
		aux = lista->pTokens;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = caixa;
	}
}

void freeT(PTokens *token)
{
	PTokens *aux;
	while(!isEmptyT(token))
	{
		aux = token;
		token = token->prox;
		free(aux);
	}
}

void freeLDE(ListaDE **lista)
{
    ListaDE *aux;
    while (*lista != NULL)
    {
        aux = *lista;           
        *lista = (*lista)->prox; 
        freeT(aux->pTokens);    
        free(aux);              
    }
}








