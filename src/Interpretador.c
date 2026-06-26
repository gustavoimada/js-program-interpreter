#include <stdio.h> // printf e scanf
#include "meuconio.h" //#include <conio2.h>
#include <conio.h>
#include <stdlib.h> // malloc e free
#include <string.h> // strlen strcmp strcpy conversor de string pra numeros
#include <math.h> // sqrt e abs
#include <ctype.h>

//#include <windows.h> NÃO É AUTOMATICO!! NÃO PRECISA DE SLEEP!!

#include "tadEstruturas.h" // TAD que possui a lista horizontal e a lista vertical
#include "tadPilhaVariaveis.h" // TAD da pilha de variaveis
#include "tadListaGen_Pilha.h" // TAD da lista gen + TAD das pilhas que vai salvar enderecos da lista gen
#include "tadPilhaExpressoesChar.h" // TAD da Pilha de Expressoes CHAR (operadores)
#include "tadPilhaExpressoesFloat.h" // TAD da Pilha de Expressoes FLOAT (valores)

// struct para salvar a funcao quando achar ela no codigo executado

struct TpFuncao
{
	char nome[30]; // nome da funcao
	ListaDE *inicioFuncao; // ponteiro q aponta pra linha dessa funcao
	struct Tpfuncao *prox; // aponta para uma proxima funcao que pode ser registrada
};
typedef struct TpFuncao Funcao; // struct TpFuncao = Funcao

// ========================================== FUNCOES PARA LAYOUT =======================================

void moldura(int ci, int li, int cf, int lf, int corf, int cort)
{
	int i;
	textcolor(cort);
	gotoxy(ci,li);
	printf("%c",201);
	gotoxy(ci,lf);
	printf("%c", 200);
	gotoxy(cf,li);
	printf("%c",187);
	gotoxy(cf,lf);
	printf("%c",188);
	for(i=ci+1; i<cf;i++)
	{
		gotoxy(i, li);
		printf("%c",205);
		gotoxy(i,lf);
		printf("%c", 205);
	}
	for(i=li+1; i<lf;i++)
	{
		gotoxy(ci,i);
		printf("%c",186);
		gotoxy(cf,i);
		printf("%c",186);
	}
}

void formulario()
{
	moldura(1,1,80,25,5,9);
	//moldura(2,2,79,4,10,15);
	//moldura(2,5,79,21,4,4);
	moldura(2,22,79,24,2,15);
}

void molduraS()
{
	textcolor(15);
	textbackground(0);
	clrscr();
	formulario();
}

void inicio()
{
	molduraS();
	gotoxy(27,11);
	printf("Luiz Carlos Marrafon Junior");
	gotoxy(27, 12);
	printf("Gustavo Carvalho Imada");
	gotoxy(4,23);
	printf("Pressione [ENTER] para Continuar ");
	gotoxy(37,23);
	getch();
}

// ========================================== FUNCOES PARA MENU =======================================

void printaArquivo(char nomeArq[30])
{
	int y = 2;
	char linha[100];
	gotoxy(3,y++);
	printf("C:\\%s\n", nomeArq);
	FILE *ptrArq = fopen(nomeArq, "r");
	while(!feof(ptrArq))
	{
		gotoxy(3,y++);
		fgets(linha, 100, ptrArq);
		printf("%s",linha);
	}
	fclose(ptrArq);
}

char menu(char flag, char nomeArq[30])
{
	molduraS();
	int y = 2; 
	char tecla, linha[100];
	gotoxy(12,23);
	printf("F7 - Abrir  ");
	printf("F8 - Executar  ");
	printf("F9 - Memoria RAM  ");
	printf("F10 - Tela");

	if(flag) // se o flag for verdadeiro, printa as linhas desse arquivo inteiro para o usuário
	{
		printaArquivo(nomeArq);
	}

	// as teclas especiais (como F1, F2, F7 etc), quando utilizamos getch(), tem um comportamento especial, possui "2 retornos"

	tecla = getch(); // le a tecla que o usuário digitou
	if (tecla == 0 || tecla == 224) // se for uma tecla especial, retorna 0 ou 224 primeiro
		tecla = getch(); // agora sim ele retorna o código da tecla de fato, p diferenciar entre elas F7 = 65 // F8 = 66 // F9 = 67 // F10 = 68
		
	return tecla;
}

// ========================================== "TOKENIZACAO" =======================================

// ou seja, essa funcao le o arquivo e salva em "caixinhas", separando tudo que for necessario
// funcao chamada logo apos o usuario abrir o arquivo (apertar f7)

void inserirToken(FILE *ptrArq, ListaDE **pPrograma)
{
	char linha[120], caracter, salvar[50];
	int i, j;

	while(!feof(ptrArq))
	{
		linha[0] = '\0';
		fgets(linha, sizeof(linha), ptrArq);

		if(strlen(linha) > 0)
		{
			if(linha[0] != '\n' && linha[0] != '\r')
			{
				insereLD(&*pPrograma);
				ListaDE *pNoAtual = *pPrograma;
				
				while(pNoAtual->prox != NULL) 
				{
					pNoAtual = pNoAtual->prox;
				}
				strcpy(pNoAtual->linhaOriginal, linha);

				i = 0;
				j = 0;
				caracter = linha[i];
				while(caracter != '\0' && caracter != '\n')
				{
					if(caracter == 125)
					{
						if (j > 0) 
						{ 
							salvar[j] = '\0'; 
							insereT(*pPrograma, salvar); 
							j = 0; 
						}
						insereT(*pPrograma, "fim-func");
					}
					else
					{
						if(caracter == 34 || caracter == 39)
						{
							if(j > 0) 
							{ 
								salvar[j] = '\0'; 
								insereT(*pPrograma, salvar); 
								j = 0; 
							}
							
							salvar[j++] = caracter;
							caracter = linha[++i];
							
							while(caracter != '\0' && caracter != 34 && caracter != 39) 
							{
								salvar[j++] = caracter;
								caracter = linha[++i];
							}
							if(caracter == 34 || caracter == 39) 
							{
								salvar[j++] = caracter;
							}
							salvar[j] = '\0';
							insereT(*pPrograma, salvar);
							j = 0;
						}
						else
						{
							if(caracter != ' ' && caracter != '(' && caracter != ',' && caracter != ';' &&
								caracter != ')' && caracter != '{' && caracter != '.' &&
								caracter != '[' && caracter != ']' && caracter != '+' && caracter != '-' &&
								caracter != '*' && caracter != '/' && caracter != '%' && caracter != '=')
							{
								if((caracter == '!' || caracter == '<' || caracter == '>') && (linha[i+1] == '='))
								{
									if(j > 0)
									{
										salvar[j] = '\0';
										insereT(*pPrograma, salvar);
										j = 0;
									}
									
									salvar[j++] = caracter;
									salvar[j++] = linha[++i];
									salvar[j] = '\0';
									insereT(*pPrograma, salvar);
									j = 0;
								}
								else 
								{
									salvar[j++] = caracter; // Acumula caracteres
								}
							}
							else
							{
								// Salva a palavra que estava sendo formada antes do separador
								if(j > 0)
								{
									salvar[j] = '\0';
									insereT(*pPrograma, salvar);
									j = 0;
								}

								if(caracter != ' ' && caracter != ';')
								{
									// Checa por operadores de 2 chars como '==' ou '**'
									if((caracter == '=' || caracter == '*') && (linha[i+1] == caracter))
									{
										salvar[j++] = caracter;
										salvar[j++] = linha[++i];
										salvar[j] = '\0';
										insereT(*pPrograma, salvar);
										j = 0;
									}
									else // Se for um operador/separador de 1 char
									{
										salvar[j++] = caracter;
										salvar[j] = '\0';
										insereT(*pPrograma, salvar);
										j = 0;
									}
								}
							}
						}
					}
					caracter = linha[++i];
				}
				if (j > 0)
				{
					salvar[j] = '\0';
					insereT(*pPrograma, salvar);
				}
			}
		}
	}
}

// ========================================== ABRINDO ARQUIVO =======================================

// Abre o arquivo e chama a função inserirToken
// como vai tokenizar as linhas, precisa passar o pPrograma por referência
// passamos flag por referencia tabmem

void abrirArq(char nomeArq[30], char *flag, ListaDE **pPrograma)
{
	char caracter, tecla;
	molduraS();

	// pede o nome do arq para o usuário
	
	gotoxy(4,23);
	printf("Digite o nome do arquivo que deseja abrir: ");
	fflush(stdin);
	gets(nomeArq);

	// abre o arq

	FILE *ptrArq = fopen(nomeArq, "r");
	
	if(ptrArq == NULL) // se o arquivo digitado não existir
	{
		*flag=0; // não printa nada
		gotoxy(27, 12);
		printf("Arquivo nao existe");
		gotoxy(27, 13);
		printf("Pressione [ENTER] para voltar");
		getch();
	}
	else
	{
		// printa o diretorio do arq 
		printf("C:\\%s\n", nomeArq);

		inserirToken(ptrArq, &*pPrograma); // tokeniza e também passa por referência, afinal, posso e vou mexer no cabeça de lista
		*flag = 1; // pra printar lá no menu
		// ESSA LINHA MOSTRA A TOKENIZACAO SE QUISER exibeL(*pPrograma);
		fclose(ptrArq);
	}
}

// ========================================== FUNCOES PARA EXECUTAR AS LINHAS =======================================

char ehXToken(ListaDE *linha, char *tokenProcurado)
{
	char flag = 0;
	PTokens *tok = linha->pTokens; // pega o primeiro token da linha
	while(tok != NULL && flag == 0) // percorre todos os tokens da linha
	{
		if(strcmp(tok->token, tokenProcurado) == 0)
		{
			flag = 1; // achou o token
		}
		tok = tok->prox; // avança para o próximo token
	}
	if(flag == 1)
		return 1;
	return 0;
}

char isChamadaFuncao(char nome[30], Funcao *listaFuncoes)
{
	char flag = 0;
	Funcao *aux = listaFuncoes;
	while(aux != NULL && flag == 0)
	{
		if(strcmp(aux->nome, nome) == 0)
		{
			flag = 1; // achou, é chamada de função
		}
		aux = aux->prox;
	}
	if(flag == 1)
		return 1;
	return 0;
}

void salvarFuncao(Funcao **listaFuncoes, char nome[30], ListaDE *linhaInicio)
{
	// ponteiro auxiliar
	
	Funcao *aux = *listaFuncoes;
	
	// cria a caixinha dessa funcao
	Funcao *nova = (Funcao*)malloc(sizeof(Funcao));
	strcpy(nova->nome, nome);
	nova->inicioFuncao = linhaInicio;
	nova->prox = NULL;

	if(*listaFuncoes == NULL) // primeiro caso, se tiver vazia bota a primeira caixa
	{
		*listaFuncoes = nova;
	}
	else // se n tiver vazia, so tem o caso de ir colocando uma em seguida da outra
	{
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = nova;
	}
}

// * = 42 // + -> 43 // - -> 45 // \ -> 47

int prioridade(char op)
{
	char prioridade;
	
	if(op == '*' || op == '/' || op == '%')
		prioridade = 2;
	else
		if(op == '+' || op == '-')
			prioridade = 1;
		else // **
			prioridade = 3;
			
	return prioridade;
}

float aplicaOperador(float a, float b, char op)
{
	float resultado = 0;

	if (op == '+')
	{
		resultado = a + b;
	}
	else if (op == '-')
	{
		resultado = a - b;
	}
	else if (op == '*')
	{
		resultado = a * b;
	}
	else if (op == '/')
	{
		resultado = a / b;
	}
	else if (op == '%')
	{
		resultado = (int)a % (int)b; 
	}
	else 
	{
		resultado = pow(a,b); 
	}

	return resultado;
}

float calcula(ListaGen *recebido)
{
    PilhaFloat *Pf;
    PilhaChar *Pc;
    initFloat(&Pf);
    initChar(&Pc);
    char topo, op, opPop;
    float a, b, resultado, resultado_final;
    int continuarLoop;

    while(recebido != NULL)
    {
        if(recebido->tipo == 'O')
        {
            op = recebido->info.operador[0];

            continuarLoop = 1;
            while(!isEmptyChar(Pc) && continuarLoop == 1)
            {
                topo = top(Pc);
                if(prioridade(topo) >= prioridade(op))
                {
                    popChar(&Pc, &opPop);
                    popFloat(&Pf, &b);
                    popFloat(&Pf, &a);
                    resultado = aplicaOperador(a, b, opPop);
                    pushFloat(&Pf, resultado);
                }
                else
                {
                    continuarLoop = 0;
                }
            }
            pushChar(&Pc, op);
        }
        else
        {
            pushFloat(&Pf, recebido->info.valor);
        }
        recebido = recebido->cauda;
    }

    while(!isEmptyChar(Pc))
    {
        popChar(&Pc, &opPop);
        popFloat(&Pf, &b);
        popFloat(&Pf, &a);
        resultado = aplicaOperador(a, b, opPop);
        pushFloat(&Pf, resultado);
    }

    if (!isEmptyFloat(&Pf)) 
	 {
    	popFloat(&Pf, &resultado_final);
    } 
	 else 
	 {
    	resultado_final = 0;
    }
    return resultado_final;
}

int buscarVariavel(PilhaVariaveis *pilha, char nome[], char *tipoEncontrado, union conteudoPV *infoEncontrada)
{
    PilhaVariaveis *aux = pilha;
    int achou = 0;
    while(aux != NULL && achou == 0)
    {
        if(strcmp(aux->nome, nome) == 0)
        {
            *tipoEncontrado = aux->tipo;
            *infoEncontrada = aux->info;
            achou = 1;
        }
        aux = aux->cauda;
    }
    return achou;
}

float resolveEquacao(PTokens *lista, PilhaVariaveis *pilhaVars)
{
    PilhaEnderecos *P1, *P2;
    init(&P1); 
    init(&P2);
    ListaGen *L = NULL, *atual = NULL;
    float resultado = 0;
    PTokens* tokenAtual = lista;

    // Construir a Lista Generalizada 
    // O loop para ao encontrar delimitadores de fim de expressão
    while(tokenAtual != NULL && strcmp(tokenAtual->token, ",")!=0 && strcmp(tokenAtual->token, ";")!= 0 && strcmp(tokenAtual->token, ")")!= 0)
    {
        if (L == NULL) // Se for o primeiro token da expressão
        {
            if (strcmp(tokenAtual->token, "(")!= 0) 
				{
                L = atual = CriaNo(tokenAtual->token, pilhaVars);
                //printf("TESTE %f", L->info.valor);
                //getch();
                push(&P2, L);
            } 
				else // Se começar com '('
				{ 
                L = atual = CriaNo("0", pilhaVars); // Nó auxiliar para a sub-expressão
                atual->tipo = 'V';
                push(&P1, atual);
                push(&P2, atual);
                tokenAtual = tokenAtual->prox;
                atual->cabeca = CriaNo(tokenAtual->token, pilhaVars);
                atual = atual->cabeca;
            }
        }
        else // pros os outros tokens
        {
            if (strcmp(tokenAtual->token, "(") == 0) 
				{
                atual->cauda = CriaNo("0", pilhaVars);
                atual = atual->cauda;
                atual->tipo = 'V';
                push(&P1, atual);
                push(&P2, atual);
                tokenAtual = tokenAtual->prox;
                atual->cabeca = CriaNo(tokenAtual->token, pilhaVars);
                atual = atual->cabeca;
            } 
				else 
					if (strcmp(tokenAtual->token, ")") == 0) 
					{
               	pop(&P1, &atual);
            	} 
					else // operador ou operando
					{ 
               	atual->cauda = CriaNo(tokenAtual->token, pilhaVars);
               	atual = atual->cauda;
            	}
        }
        
        if (tokenAtual != NULL) 
		  {
           tokenAtual = tokenAtual->prox;
        }
    }

    // Com a lista generalizada construida, somente aq comeca a calcular o resultado de fato

    while (!isEmptyEnderecos(P2))
    {
        pop(&P2, &atual);
        if (atual->cabeca != NULL) // Se for um nó de sub-expressão (com parênteses)
        {
            atual->info.valor = calcula(atual->cabeca);
            atual->tipo = 'V'; // Transforma o nó em um nó de valor
            atual->cabeca = NULL; 
        }
    }
    
    resultado = calcula(L);
    //printf("TESTANDO %f", resultado); erro aq do 5
    //getch();
    return resultado;
}

void insereTela(ListaDE **listaTela, char *saida)
{
	ListaDE *novo = (ListaDE*)malloc(sizeof(ListaDE));
	novo->prox = NULL;
   novo->ant = NULL; 

	
	novo->pTokens = (PTokens*)malloc(sizeof(PTokens)); 
	strcpy(novo->pTokens->token, saida); 
	novo->pTokens->prox = NULL;

	if (*listaTela == NULL) // caso 1
	{
		*listaTela = novo;
	}
	else // caso 2
	{
		ListaDE *aux = *listaTela;
		while (aux->prox != NULL)
		{
			aux = aux->prox;
		}
		aux->prox = novo;
      novo->ant = aux; 
	}
}

void avaliarExpressaoToString(PTokens *token, char saidaFinal[], PilhaVariaveis *pilhaVars)
{
    int indiceSaida = 0, len, i;
    saidaFinal[0] = '\0';
    char buffer[200], tipoVar;
    union conteudoPV infoVar;
    float resultado;
    PTokens* tokenAtual = token;

    while(tokenAtual != NULL && strcmp(tokenAtual->token, ")") != 0)
    {
        if (strcmp(tokenAtual->token, ",") != 0)
        {
            // string literal (ex: "resultado = ")
            if (tokenAtual->token[0] == '\'' || tokenAtual->token[0] == '"')
            {
                len = strlen(tokenAtual->token);
                for (i = 1; i < len - 1; i = i + 1) 
					 {
                	saidaFinal[indiceSaida++] = tokenAtual->token[i];
                }
                tokenAtual = tokenAtual->prox;
            }
            else // eh uma variável e o tipo dela eh string (ex: msg)
					if(buscarVariavel(pilhaVars, tokenAtual->token, &tipoVar, &infoVar) == 1 && tipoVar == 's')
            	{
	               int j = 0;
	               while(infoVar.string[j] != '\0') 
						{
	               	saidaFinal[indiceSaida++] = infoVar.string[j++];
	               }
	               tokenAtual = tokenAtual->prox;
            	}
	            else //eh uma expressão numérica (ex: 5, a, 5+2, a+b+c)
	            {
	                resultado = resolveEquacao(tokenAtual, pilhaVars);
	                sprintf(buffer, "%.2f", resultado);
	                
	                int j = 0;
	                while(buffer[j] != '\0') 
						 {
	                	saidaFinal[indiceSaida++] = buffer[j++];
	                }
	                
	                while(tokenAtual != NULL && strcmp(tokenAtual->token, ",") != 0 && strcmp(tokenAtual->token, ")") != 0) 
						 {
	                	tokenAtual = tokenAtual->prox;
	                }
	            }
	            
	            if(tokenAtual != NULL && strcmp(tokenAtual->token, ")")!= 0)
					{
	            	saidaFinal[indiceSaida++] = ' ';
	            }
        }
        else 
        {
            tokenAtual = tokenAtual->prox;
        }
    }
	saidaFinal[indiceSaida] = '\0';
}

void exibirTela(ListaDE *listaTela)
{
	molduraS();
	int y = 3; 
	gotoxy(25, 2); 
	printf("--- Saida do Console (Tela) ---");
	
	if (listaTela == NULL)
	{
		gotoxy(4, y);
		printf("Nenhuma saida no console ainda.");
	}
	else
	{
		ListaDE *aux = listaTela;
		while (aux != NULL)
		{
			// Verifica se o no e os tokens sao validos antes de imprimir
			if (aux->pTokens != NULL)
			{
				gotoxy(4, y++);
				printf("%s", aux->pTokens->token);
			}
			aux = aux->prox;
		}
	}
	gotoxy(4, 23);
	printf("Pressione qualquer tecla para voltar a execucao...");
	getch();
}

void ExibeDestacaLinha(ListaDE *pPrograma, ListaDE *linhaAtual)
{
    ListaDE* auxLinha = pPrograma;
    int y = 3; 

    while(auxLinha != NULL)
    {
        gotoxy(3, y);

        if (auxLinha == linhaAtual)
        {
            textbackground(4); // Fundo vermelho para destaque
            textcolor(15);
        }

        printf("%s", auxLinha->linhaOriginal);

        if (auxLinha == linhaAtual)
        {
            textbackground(0); // Restaura fundo preto
        }

        // Incrementa o Y para a próxima iteração do gotoxy
        y++;
        auxLinha = auxLinha->prox;
    }
}

Funcao* buscarFuncao(Funcao *lista, char *nome)
{
    Funcao *aux = lista;
    int achou = 0;
    while(aux != NULL && achou == 0)
    {
        if(strcmp(aux->nome, nome) == 0)
        {
            achou = 1;
        }
        else
        {
            aux = aux->prox;
        }
    }
    return aux; // Retorna o ponteiro para a função ou NULL se não achar
}

void atualizarVariavel(PilhaVariaveis *pilha, char *nome, float valor)
{
	PilhaVariaveis *aux = pilha;
   int achou = 0;
   while(aux != NULL && achou == 0)
   {
   	if(strcmp(aux->nome, nome) == 0)
   	{
      	if (aux->tipo == 'v')
         {
         	aux->info.valor = valor;
         }
         achou = 1;
      }
      else
      {
      	aux = aux->cauda;
      }
   }
}

void Executar(char nomeArq[30], ListaDE *pPrograma, PilhaVariaveis **pilhaVariaveis, ListaDE **listaTela)
{
    char tecla, nomeVar[150], saida[256], varDestino[150];
    int executando = 1, fezSalto = 0, acabou = 0;
    float valor = 0, valArg = 0, valorRetornado = 0;
    
    ListaDE *linhaAtual = pPrograma;
    Funcao *listaFuncoes = NULL;
    PTokens *tok = NULL;
    PTokens *ladoDireito = NULL;
    PTokens *paramDef = NULL;
    PTokens *argChamada = NULL;
    Funcao* funcDef = NULL;

    while (linhaAtual != NULL && executando == 1)
    {
        fezSalto = 0;
        molduraS();
        gotoxy(3,2);
        printf("C:\\%s\n", nomeArq);
        ExibeDestacaLinha(pPrograma, linhaAtual);
        gotoxy(12,23);
        printf("F7-Abrir  F8-Executar  F9-Memoria RAM  F10-Tela  [ESC]-Sair");
        tecla = getch();

        if (tecla == 13)
        {
            tok = linhaAtual->pTokens;
            if (tok != NULL)
            {
                if (strcmp(tok->token, "let") == 0 || strcmp(tok->token, "const") == 0)
                {
                    if (tok->prox != NULL)
                    {
                        strcpy(nomeVar, tok->prox->token);
                        
                        if (tok->prox->prox != NULL && strcmp(tok->prox->prox->token, "=") == 0 && tok->prox->prox->prox != NULL)
                        {
                            ladoDireito = tok->prox->prox->prox;

                            if (isChamadaFuncao(ladoDireito->token, listaFuncoes))
                            {
                                funcDef = buscarFuncao(listaFuncoes, ladoDireito->token);
                                if (funcDef != NULL)
                                {
                                    pushFloatVariaveis(pilhaVariaveis, nomeVar, 0.0);
                                    pushRetorno(pilhaVariaveis, linhaAtual, nomeVar);
                                    
                                    paramDef = funcDef->inicioFuncao->pTokens->prox->prox->prox;
                                    argChamada = ladoDireito->prox->prox;
                                    acabou = 0;
                                    while(paramDef != NULL && strcmp(paramDef->token, ")") != 0 && acabou == 0)
                                    {
                                        if(strcmp(paramDef->token, ",") == 0) { paramDef = paramDef->prox; }
                                        if(paramDef != NULL && strcmp(paramDef->token, ")") != 0)
                                        {
                                            valArg = resolveEquacao(argChamada, *pilhaVariaveis);
                                            pushFloatVariaveis(pilhaVariaveis, paramDef->token, valArg);
                                            while(argChamada != NULL && strcmp(argChamada->token, ",") != 0 && strcmp(argChamada->token, ")") != 0) { argChamada = argChamada->prox; }
                                            if(argChamada != NULL && strcmp(argChamada->token, ",") == 0) { argChamada = argChamada->prox; }
                                            paramDef = paramDef->prox;
                                        } else { acabou = 1; }
                                    }
                                    linhaAtual = funcDef->inicioFuncao->prox;
                                    if (linhaAtual != NULL) { linhaAtual = linhaAtual->prox; }
                                    fezSalto = 1;
                                }
                            }
                            else
                            {
                                if (ladoDireito->token[0] == '\"' || ladoDireito->token[0] == '\'') {
                                    pushString(pilhaVariaveis, nomeVar, ladoDireito->token);
                                } else {
                                    valor = resolveEquacao(ladoDireito, *pilhaVariaveis);
                                    pushFloatVariaveis(pilhaVariaveis, nomeVar, valor);
                                }
                            }
                        }
                        else
                        {
                            pushFloatVariaveis(pilhaVariaveis, nomeVar, 0.0);
                        }
                    }
                }
                else if (strcmp(tok->token, "console") == 0 && tok->prox != NULL && strcmp(tok->prox->token, ".") == 0 && tok->prox->prox != NULL && strcmp(tok->prox->prox->token, "log") == 0)
                {
                    if (tok->prox->prox->prox != NULL && tok->prox->prox->prox->prox != NULL)
                    {
                        avaliarExpressaoToString(tok->prox->prox->prox->prox, saida, *pilhaVariaveis);
                        insereTela(listaTela, saida);
                    }
                }
                else if (strcmp(tok->token, "function") == 0 && tok->prox != NULL)
                {
                    salvarFuncao(&listaFuncoes, tok->prox->token, linhaAtual);
                    while (linhaAtual != NULL && !ehXToken(linhaAtual, "fim-func"))
                    {
                        linhaAtual = linhaAtual->prox;
                    }
                    fezSalto = 1;
                }
                else if (strcmp(tok->token, "return") == 0)
                {
                    valorRetornado = resolveEquacao(tok->prox, *pilhaVariaveis);
                    
                    while (*pilhaVariaveis != NULL && (*pilhaVariaveis)->tipo != 'r')
                    {
                        popPilhaVariaveis(pilhaVariaveis);
                    }

                    if (*pilhaVariaveis != NULL)
                    {
                        ListaDE* linhaDeRetorno = (*pilhaVariaveis)->info.retInfo.linhaDeRetorno;
                        strcpy(varDestino, (*pilhaVariaveis)->info.retInfo.varDestino);
                        
                        popPilhaVariaveis(pilhaVariaveis);
                        
                        if (strlen(varDestino) > 0)
                        {
                            atualizarVariavel(*pilhaVariaveis, varDestino, valorRetornado);
                        }
                        
                        linhaAtual = linhaDeRetorno->prox;
                        fezSalto = 1;
                    }
                }
                else 
                {
                    if (tok->prox != NULL && strcmp(tok->prox->token, "=") == 0 && tok->prox->prox != NULL)
                    {
                        strcpy(nomeVar, tok->token);
                        ladoDireito = tok->prox->prox;

                        if(isChamadaFuncao(ladoDireito->token, listaFuncoes))
                        {
                            funcDef = buscarFuncao(listaFuncoes, ladoDireito->token);
                            if (funcDef != NULL)
                            {
                                pushRetorno(pilhaVariaveis, linhaAtual, nomeVar);
                                paramDef = funcDef->inicioFuncao->pTokens->prox->prox->prox;
                                argChamada = ladoDireito->prox->prox;
                                acabou = 0;
                                while(paramDef != NULL && strcmp(paramDef->token, ")") != 0 && acabou == 0)
                                {
                                    if(strcmp(paramDef->token, ",") == 0) { paramDef = paramDef->prox; }
                                    if(paramDef != NULL && strcmp(paramDef->token, ")") != 0)
                                    {
                                        valArg = resolveEquacao(argChamada, *pilhaVariaveis);
                                        pushFloatVariaveis(pilhaVariaveis, paramDef->token, valArg);
                                        while(argChamada != NULL && strcmp(argChamada->token, ",") != 0 && strcmp(argChamada->token, ")") != 0) { argChamada = argChamada->prox; }
                                        if(argChamada != NULL && strcmp(argChamada->token, ",") == 0) { argChamada = argChamada->prox; }
                                        paramDef = paramDef->prox;
                                    } else { acabou = 1; }
                                }
                                linhaAtual = funcDef->inicioFuncao->prox;
                                if (linhaAtual != NULL) { linhaAtual = linhaAtual->prox; }
                                fezSalto = 1;
                            }
                        }
                        else
                        {
                            valor = resolveEquacao(ladoDireito, *pilhaVariaveis);
                            atualizarVariavel(*pilhaVariaveis, nomeVar, valor);
                        }
                    }
                }
            }

            if(fezSalto == 0)
            {
                linhaAtual = linhaAtual->prox;
            }
        }
        else if (tecla == 0 || tecla == 224)
        {
            tecla = getch();
            if (tecla == 67)
            {
                molduraS();
                exibirPilhaVariaveis(*pilhaVariaveis);
            }
            else if (tecla == 68)
            {
                exibirTela(*listaTela);
            }
        }
        else if (tecla == 27)
        {
        		executando = 0;
        }
    }
}

int main(void)
{
	char opcao, nomeArq[30], flag = 0; // flag sinaliza que o arquivo não foi aberto para o menu (pois o menu pecisa saber se printa o arquivo ou não)
	ListaDE *pPrograma; // ListaDE -> Lista Duplamente Encadeada, ou seja, a lista vertical
	initL(&pPrograma); // inicia essa lista
	PilhaVariaveis *pilhaVariaveis; // Cria a pilha de variaveis
	inicializarPilhaVariaveis(&pilhaVariaveis); // inicializa a pilha de variaveis
	ListaDE *listaTela = NULL;

	inicio(); // nome dos participantes
	do
	{
		opcao = menu(flag, nomeArq);
		switch (opcao)
		{
			case 65: // F7
			
				// se for abrir um novo arquivo, da um free que deleta TODA a lista tokenizada do outro programa (pPrograma)
				liberarPilhaVariaveis(&pilhaVariaveis);
				freeLDE(&pPrograma);
				freeLDE(&listaTela);
				
				// abre o arquivo + tokeniza as linhas desse arq (transforma em caixas para deopis serem lidas no Executar)
				abrirArq(nomeArq, &flag, &pPrograma);
				break;

			case 66: // F8
				// Vai executando cada linha individualmente de acordo com a interação com o usuário, dentro dele, vai ter as opções de mostrar RAM e mostrar TELA
				Executar(nomeArq, pPrograma, &pilhaVariaveis, &listaTela);
				break;

			case 67: // F9
				molduraS();
    			exibirPilhaVariaveis(pilhaVariaveis);
				break;

			case 68: // F10
				molduraS();
				exibirTela(listaTela);
				break;
		}
	} while(opcao != 27);
	
	return 0;
}
