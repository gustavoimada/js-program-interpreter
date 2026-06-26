#include <stdio.h>
#include <conio2.h> 
#include <stdlib.h>
#include <string.h>
#include "tadEstruturas.h"



int main(){
	LinhaV *pPrograma;
	initL(&pPrograma);
	insereLV(&pPrograma);
	insereLH(pPrograma, "primeira");
	insereLH(pPrograma, "segunda");
	insereLV(&pPrograma);
	insereLH(pPrograma, "ter");
	insereLH(pPrograma, "fsdf");
	insereLH(pPrograma, "casc");
	insereLV(&pPrograma);
	exibeLV(pPrograma);
	getch();
	return 0;
	
	
}

