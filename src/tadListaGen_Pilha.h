union conteudo 
{
	float valor;
	char operador[3];
};

struct listagen 
{
	char tipo; // v: valor, o: operador
	union conteudo info;
	struct listagen *cabeca, *cauda;
};
typedef struct listagen ListaGen;

int buscaValorVariavel(PilhaVariaveis *pilha, char *nome, float *valorEncontrado)
{
    PilhaVariaveis *aux = pilha;
    int achou = 0;
    while(aux != NULL && achou == 0)
    {
        if(strcmp(aux->nome, nome) == 0)
        {
            if(aux->tipo == 'v')
            {
                *valorEncontrado = aux->info.valor;
                achou = 1;
            }
        }
        
        if(achou == 0) 
		  {
            aux = aux->cauda;
        }
    }
    return achou;
}

char ehDigito(char c)
{
    return (c >= '0' && c <= '9');
}

ListaGen* CriaNo(char tok[], PilhaVariaveis *pilhaVars)
{
    ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
    L->cauda = NULL;
    L->cabeca = NULL;

    // OPERADOR
    if (strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0 || strcmp(tok, "*") == 0 || strcmp(tok, "/") == 0 || strcmp(tok, "**") == 0 || strcmp(tok, "%") == 0)
    {
        L->tipo = 'O';
        strncpy(L->info.operador, tok, sizeof(L->info.operador) - 1);
        L->info.operador[sizeof(L->info.operador) - 1] = '\0';
    }
    // NÚMERO LITERAL
    else 
	 	if (ehDigito(tok[0]) || ( (tok[0] == '-' || tok[0] == '+') && tok[1] != '\0' && ehDigito(tok[1]) ))
    	{
      	L->tipo = 'V';
      	L->info.valor = atof(tok);
    	}
    // VARIÁVEL.
    else
    {
        float valor;
        L->tipo = 'V'; 
        if (buscaValorVariavel(pilhaVars, tok, &valor) == 1)
        {
            L->info.valor = valor;
        }
        else
        {
            L->info.valor = 0.0;
        }
    }
    return L;
}

void inicializarListaGen(ListaGen **L) 
{
	*L == NULL;
}

struct TpPilha 
{
    struct ListaGen *info;   
    struct TpPilha *prox;  
};
typedef struct TpPilha PilhaEnderecos;

void init(PilhaEnderecos **topo) 
{
    *topo = NULL;
}

int isEmptyEnderecos(PilhaEnderecos *topo) 
{
    return topo == NULL;
}

void push(PilhaEnderecos **topo, ListaGen *elemento)
{
    PilhaEnderecos *novo = (PilhaEnderecos*)malloc(sizeof(PilhaEnderecos));
    novo->info = elemento;
    novo->prox = *topo;
    *topo = novo;
}

void pop(PilhaEnderecos **topo, ListaGen **saida) 
{
    PilhaEnderecos *removido = *topo;
    *saida = removido->info;
    *topo = removido->prox;
    free(removido);
}
