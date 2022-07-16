#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>

/*ï¿½rbol binario*/
typedef struct _nodo_{
  char info;
  struct _nodo_ *izq, *der;
}NODO;

typedef NODO *ARBOL;

typedef struct _elem_pila_{
  NODO *info;
  struct _elem_pila_ *sig;
} ELPILA;
struct LIFO {
	int t;
	char a[30];
};
typedef ELPILA *PILA;

int push(NODO *info, PILA *ppila);
NODO *pop(PILA *ppila);
int pilavacia(PILA pila); /*INFO peep(PILA pila);*/

ARBOL exprecionAlArbol(char *expresion);
NODO *creaNodo(char info);


int insertaInfo(char info, ARBOL *parbol);
int busca(char info, ARBOL arbol);
int preorden(ARBOL arbol);
int inorden(ARBOL arbol);
int posorden(ARBOL arbol);
ARBOL derivada(ARBOL a);
void in_a_pos (char *infijo,char *posfijo);
int operando (char c);
int prioridad (char op1,char op2);
char tope (struct LIFO p);
void init_pila (struct LIFO *p);
int pila_vacia (struct LIFO *p);
void ins_pila (struct LIFO *p,char s);
void retira_pila (struct LIFO *p,char *s);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
  char cadena[]="xxSxb^++";
  ARBOL a=NULL;
  PILA unaPila=NULL;
    int i, st;
    float valores[26];
    char infijo[50], *pc, posfijo[100];

    printf("Ingrese la función que desea evaluar (use parentesis para evitar confuciones): "); scanf("%s",&(*infijo));

    in_a_pos(infijo,posfijo);
  
  a = exprecionAlArbol(posfijo);
  
  printf("\nLa expresión ingresada es: \n");
  inorden(a);
  
  printf("\nLa derivada es:\n");
  inorden(derivada(a));

  printf("\nFin del programa.\n");
  
  return 0;
}


int insertaInfo(char info, ARBOL *pa)
{
  ARBOL aux;
  NODO *pnodo;
  
  if(pa==NULL) return -3;
  if( (pnodo = (NODO*)malloc(sizeof(NODO))) == NULL ){
    int mierr=errno;
    printf("Error al crear espacio en memoria: %d, <<%s>>.\n",
	  mierr, strerror(mierr));
    return -2;
  }
  pnodo->der=pnodo->izq=NULL;
  pnodo->info=info;
  
  if ((*pa) == NULL){
    *pa = pnodo;
    return 0;
  }
  aux = *pa;
  do{
    if( pnodo->info <= aux->info){
      if(aux->izq == NULL){
        aux->izq = pnodo;
        break;
	  }
	  aux = aux->izq;
	} else { /*pnodo->info > aux->info*/
      if(aux->der == NULL){
        aux->der = pnodo;
        break;
	  }
	  aux = aux->der;
	}
  } while(aux!=NULL);
  
  return 0;
}

int busca(char info, ARBOL a)
{
  if(a==NULL) return 0;
  while(a!=NULL){
    if(a->info == info) return 1;
    if(info < a->info) a = a->izq;
    else /*info>a->info*/ a = a->der;
  }
  return 0;
}

int preorden(ARBOL a)
{
  if(a==NULL) return 0;
  printf("%c", a->info);
  if(a->izq != NULL) preorden(a->izq);
  if(a->der != NULL) preorden(a->der);	

  return 0;
}

int inorden(ARBOL a)
{
  if(a==NULL) return 0;
  if(a->izq != NULL) inorden(a->izq);
  printf("%c", a->info);
  if(a->der != NULL) inorden(a->der);	

  return 0;
}

int posorden(ARBOL a)
{
  if(a==NULL) return 0;
  if(a->izq != NULL) posorden(a->izq);
  if(a->der != NULL) posorden(a->der);	
  printf("%c", a->info);

  return 0;
}

int push(NODO *info, PILA *ppila)
{
  ELPILA *pelp;

  if(ppila==NULL) return -2;

  if((pelp=(ELPILA*)malloc(sizeof(ELPILA)))==NULL){
  	int mierr = errno;
  	printf("Error al crear espacio: %d, <<%s>>\n",
	  mierr, strerror(mierr));
    return -3;
  }
  pelp->info = info;
  pelp->sig = *ppila;
  
  *ppila = pelp;  

  return 0;
}

NODO* pop(PILA *ppila)
{
  ELPILA *pelp;
  NODO* miinfo;

   /* en caso de que el valor a regresar fuera en uno de los parï¿½metros
   if(ppila==NULL) return -2;
   if(*ppila ==NULL) return -1;
   */
  pelp = *ppila;
  (*ppila) = (*ppila)->sig;
  miinfo = pelp->info;
  pelp->info=0;
  pelp->sig = NULL;
  free(pelp);
  pelp = NULL;

  return miinfo;
}
  
int pilavacia(PILA pila) /*INFO peep(PILA pila);*/
{
  return pila == NULL;
}

NODO *creaNodo(char info)
{
  NODO *ret;

  if((ret=(NODO*)malloc(sizeof(NODO)))!=NULL){
    ret->der = ret->izq = NULL;
    ret->info=info;
  }
  
  return ret;
}

ARBOL exprecionAlArbol(char *expresion)
{
  /*Se va a meter la expresiï¿½n a un ï¿½rbol
  */
  char *pc;
  NODO *segundo, *ret, *aux;
  PILA mipila=NULL;
  
  for(pc=expresion; *pc!='\0'; pc++){
	if('a'<=*pc && *pc<='z'){
      aux = creaNodo(*pc);
      push(aux, &mipila);
      continue;
	}
	switch(*pc){
      case '+':
      case '-':
      case '*':
      case '^':
                if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }
                segundo = pop(&mipila);
                if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }
                aux = creaNodo(*pc);
                aux->der = segundo;
                aux->izq = pop(&mipila);
                push(aux, &mipila);
                break;
      case 'S':  
      case 'C': 
      case 'L': 
                if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }
                aux = creaNodo(*pc);
                aux->izq=NULL;
				aux->der = pop(&mipila);
                /*if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }*/
                push(aux, &mipila);
                break;
	}
  }
  
  if(pilavacia(mipila)){ 
    printf("Error, pila no deberï¿½a estar vacï¿½a\n");
    return NULL;
  }
  ret = pop(&mipila);
  
  if(!pilavacia(mipila)){ 
    printf("Error, pila deberï¿½a quedar vacï¿½a\n");
    return NULL;
  }
  
  return ret;
}

ARBOL derivada(ARBOL a)
{
  /*Se va a meter la expresiï¿½n a un ï¿½rbol
  */
  char *pc, r[20];
  NODO *segundo, *ret, *aux, *sub1, *sub2, *sub3;
  PILA mipila=NULL;
  if(a==NULL) return 0;

	if('a'<=a->info && a->info<='z'){
        aux = creaNodo('0');
        push(aux, &mipila);
	}
    if(a->info=='x'){
        aux = creaNodo('1');
        push(aux, &mipila);
	}
	switch(a->info){
      case '+':
                /*if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }
                segundo = pop(&mipila);
                if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }*/
                aux = creaNodo(a->info);
                aux->der = derivada(a->der);
                aux->izq = derivada(a->izq);
                push(aux, &mipila);
                break;
      case '-':
                /*if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }
                segundo = pop(&mipila);
                if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }*/
                aux = creaNodo(a->info);
                aux->der = derivada(a->der);
                aux->izq = derivada(a->izq);
                push(aux, &mipila);
                break;
      case '*':
                /*if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }
                segundo = pop(&mipila);
                if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }*/
                aux = creaNodo('+');
                sub1 = creaNodo('*');
                sub2 = creaNodo('*');
                aux->der = sub2;
                aux->izq = sub1;

                sub2->izq = a->izq;
                sub2->der = derivada(a->der);
                sub1->izq = derivada(a->izq);
                sub1->der = a->der;
                push(aux, &mipila);
                break;
      case '^':
                /*if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }
                segundo = pop(&mipila);
                if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }*/
                aux = creaNodo('*');
                sub1 = creaNodo('*');
                sub2 = creaNodo('^');
                aux->der = derivada(a->izq);
                aux->izq = sub1;
                sub1->izq = a->der;
                sub1->der = sub2;
                sub2->izq = a->izq;
                //strcat(strcpy(r, (a->der->info)), "-1");
                sub2->der = creaNodo('-');
                (sub2->der)->der =creaNodo('1');
                (sub2->der)->izq = a->der;
                push(aux, &mipila);
                break;
      case 'S':  
                /*if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }*/
                aux = creaNodo('*');
                sub1 = creaNodo('C');
                aux->izq = sub1;
                sub1->izq=NULL;
                sub1->der = a->der;
			        	aux->der = derivada(a->der);
                /*if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }*/
                push(aux, &mipila);
                break;
      case 'C': 
                /*if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }*/
                sub2 = creaNodo('-');
                aux = creaNodo('*');
                sub1 = creaNodo('S');
                sub2->izq=creaNodo('0');
                sub2->der = sub1;
                aux->izq = sub2;
                sub1->izq=NULL;
                sub1->der = a->der;
			        	aux->der = derivada(a->der);
                /*if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }*/
                push(aux, &mipila);
                break;
      case 'L': 
                /*if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }*/
                aux = creaNodo('*');
                sub1 = creaNodo('^');
                aux->izq = sub1;
                sub1->izq = a->der;
                sub1->der = creaNodo('-');
                (sub1->der)->der = creaNodo('0');
                (sub1->der)->izq = creaNodo('1');
			        	aux->der = derivada(a->der);
                /*if(pilavacia(mipila)){ 
                  printf("Error, pila no deberï¿½a estar vacï¿½a\n");
                  return NULL;
                }*/
                push(aux, &mipila);
                break;
	}
  
  
  /*if(pilavacia(mipila)){ 
    printf("Error, pila no deberï¿½a estar vacï¿½a\n");
    return NULL;
  }
  ret = pop(&mipila);
  
  if(!pilavacia(mipila)){ 
    printf("Error, pila deberï¿½a quedar vacï¿½a\n");
    return NULL;
  }*/
  
  return aux;
}

void in_a_pos(char *infijo,char *posfijo)
{
	struct LIFO pila;
	int i,j;
	char elemento;
	i=0;
	j=-1;
	init_pila (&pila);
	while (infijo [i] != '\0') {
	   if (operando (infijo [i]) )
		   posfijo [++j] = infijo [i++];
	   else {
		     while (!pila_vacia (&pila)  &&
			 prioridad (tope (pila),infijo [i] ) )  {
			     retira_pila (&pila,&elemento);
			     posfijo [++j] = elemento;
		      }
		      if (infijo [i] == ')')
			   retira_pila (&pila,&elemento);
		      else ins_pila (&pila,infijo [i]);
		      i++;
		}
	}
	while (!pila_vacia (&pila) ) {
		retira_pila (&pila,&elemento);
		posfijo [++j] = elemento;
	}
	posfijo [++j] = '\0';
}


int operando (char c)
{
	return ( c != '+' &&
		 c != '-' &&
		 c != '*' &&
		 c != '/' &&
		 c != '^' &&
		 c != ')' &&
		 c != '(' &&
		 c != 'S' &&
		 c != 'L' &&
		 c != 'C');
}

static int m[6][7] = {
	{ 1,1,0,0,0,0,1 },
	{ 1,1,0,0,0,0,1 },
	{ 1,1,1,1,0,0,1 },
	{ 1,1,1,1,0,0,1 },
	{ 1,1,1,1,1,0,1 },
	{ 0,0,0,0,0,0,0 }
};

int prioridad (char op1,char op2)
{
	int i,j;
	
	switch (op1) {
		case '+' :  i = 0; break;
		case '-' :  i = 1; break;
		case '*' :  i = 2; break;
		case '/' :  i = 3; break;
		case '^' :  i = 4; break;
		case '(' :  i = 5; break;
		case 'S' :  i = 6; break;
		case 'C' :  i = 7; break;
		case 'L' :  i = 8; break;
	}
	switch (op2) {
		case '+' :  j = 0; break;
		case '-' :  j = 1; break;
		case '*' :  j = 2; break;
		case '/' :  j = 3; break;
		case '^' :  j = 4; break;
		case '(' :  j = 5; break;
		case ')' :  j = 6; break;
		case 'S' :  j = 7; break;
		case 'C' :  i = 8; break;
		case 'L' :  i = 9; break;
	}	
	return (m [i][j]);
}

char tope (struct LIFO p)
{
	return ( p.a [p.t -1] );
}

void init_pila (struct LIFO *p)
{
	p->t = 0;
}

int pila_vacia (struct LIFO *p)
{
	return (!p->t);
}

void ins_pila (struct LIFO *p,char s)
{
	if (p->t == 30)
		printf ("la pila no soporta mas elementos\n");
	else  {
		  p->t++;
		  p->a [p->t - 1] = s;
	}
}

void retira_pila (struct LIFO *p,char *s)
{
	if (pila_vacia (p) )  {
		printf ("la pila esta vacia\n");
		*s = '\0';
	}
	else  {
		  *s = p->a [p->t - 1];
		  p->t--;
	}
}
