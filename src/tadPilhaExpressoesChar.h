struct TpPilhaChar 
{
    char info;
    struct TpPilhaChar *prox;
};
typedef struct TpPilhaChar PilhaChar;

void initChar(PilhaChar **topo) 
{
    *topo = NULL;
}

int isEmptyChar(PilhaChar *topo) 
{
    return (topo == NULL);
}

void pushChar(PilhaChar **topo, char elemento) 
{
    PilhaChar *novo = (PilhaChar*) malloc(sizeof(PilhaChar));
    novo->info = elemento;
    novo->prox = *topo;
    *topo = novo;
}

void popChar(PilhaChar **topo, char *saida) 
{
    PilhaChar *removido = *topo;
    *saida = removido->info;
    *topo = removido->prox;
    free(removido);
}

char top(PilhaChar *topo)
{
	return topo->info;
}


void destroiPilhaChar(PilhaChar **topo) 
{
    char temp;
    while (!isEmptyChar(*topo)) 
	 {
        popChar(topo, &temp);
    }
}

