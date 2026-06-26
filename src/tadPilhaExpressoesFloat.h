struct TpPilhaFloat 
{
    float info;
    struct TpPilhaFloat *prox;
};
typedef struct TpPilhaFloat PilhaFloat;

void initFloat(PilhaFloat **topo) 
{
    *topo = NULL;
}

int isEmptyFloat(PilhaFloat *topo) 
{
    return (topo == NULL);
}

void pushFloat(PilhaFloat **topo, float elemento) 
{
    PilhaFloat *novo = (PilhaFloat*) malloc(sizeof(PilhaFloat));
    novo->info = elemento;
    novo->prox = *topo;
    *topo = novo;
}

void popFloat(PilhaFloat **topo, float *saida) 
{
	PilhaFloat *removido = *topo;
	*saida = removido->info;
   *topo = removido->prox;
	free(removido);
}

void destroiPilhaFloat(PilhaFloat **topo) 
{
    float temp;
    while (!isEmptyFloat(*topo)) 
	 {
        popFloat(topo, &temp);
    }
}

