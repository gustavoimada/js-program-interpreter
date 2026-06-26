struct enderecoRetorno 
{
    struct listaDE *linhaDeRetorno; // Ponteiro para a linha que fez a chamada
    char varDestino[150];           // Nome da variável que receberá o valor ex: "c" em "c = calcula(a, b)"
};typedef struct enderecoRetorno EnderecoRetorno;

union conteudoPV {
    float valor;
    char string[150];
    EnderecoRetorno retInfo; // Novo tipo de conteúdo que a pilha pode armazenar
};

struct pilhaVariaveis 
{
    char tipo; // v: valor(float), s: string, a: array/funcao, r: retorno
    char nome[150];
    union conteudoPV info;
    struct pilhaVariaveis *cauda;
};
typedef struct pilhaVariaveis PilhaVariaveis;

void inicializarPilhaVariaveis(PilhaVariaveis **topo) 
{
    *topo = NULL;
}

void pushFloatVariaveis(PilhaVariaveis **topo, char nome[150], float valor)
{
    PilhaVariaveis *novo = (PilhaVariaveis*)malloc(sizeof(PilhaVariaveis));
    novo->tipo = 'v';
    strcpy(novo->nome, nome);
    novo->info.valor = valor;
    novo->cauda = *topo;
    *topo = novo;
}

void pushString(PilhaVariaveis **topo, char nome[150], char valor[150])
{
    PilhaVariaveis *novo = (PilhaVariaveis*)malloc(sizeof(PilhaVariaveis));
    novo->tipo = 's';
    strcpy(novo->nome, nome);
    strcpy(novo->info.string, valor);
    novo->cauda = *topo;
    *topo = novo;
}

void pushRetorno(PilhaVariaveis **topo, ListaDE *linha, char *varDest) 
{
    PilhaVariaveis *novo = (PilhaVariaveis*)malloc(sizeof(PilhaVariaveis));
    novo->tipo = 'r'; 
    strcpy(novo->nome, "[endereco_retorno]"); // so p exibr
    novo->info.retInfo.linhaDeRetorno = linha;

    // Se não houver variável de destino (ex: uma chamada simples "minhaFunc();")
    if (varDest == NULL) 
	 {
        strcpy(novo->info.retInfo.varDestino, ""); // Deixa vazio
    } 
	 else 
	 {
        strcpy(novo->info.retInfo.varDestino, varDest);
    }

    novo->cauda = *topo;
    *topo = novo;
}

void popPilhaVariaveis(PilhaVariaveis **topo) 
{
    if(*topo != NULL) 
	 {
    	PilhaVariaveis *aux = *topo;
    	*topo = (*topo)->cauda;
    	free(aux);
    }
}

PilhaVariaveis* topoPilhaVariaveis(PilhaVariaveis *topo) 
{
    return topo;
}

void liberarPilhaVariaveis(PilhaVariaveis **topo) 
{
    while (*topo != NULL) 
	 {
        popPilhaVariaveis(topo);
    }
}

void exibirPilhaVariaveis(PilhaVariaveis *v)
{
     int y = 2;
     PilhaVariaveis *aux = v;
     gotoxy(20, y++);
     printf("--- ESTADO ATUAL DA MEMORIA (PILHA) ---");
     y++;

     if (aux == NULL) 
	  {
        gotoxy(3, y);
        printf("Pilha de variaveis vazia.");
     }

     while (aux != NULL)
     {
        gotoxy(3, y);
        printf("Nome: %-20s Valor: ", aux->nome);

        switch (aux->tipo)
        {
            case 'v':
                 printf("%.2f", aux->info.valor);
                 break;
            case 's':
                 printf("%s", aux->info.string);
                 break;
          
            case 'r':
                 printf("[RETORNO p/ var: '%s']", aux->info.retInfo.varDestino);
                 break;
        }
        y++;
        aux = aux->cauda;
     }
     gotoxy(3, 23);
     printf("Pressione [ENTER] para voltar para a execucao do programa.");
     getch();
}
