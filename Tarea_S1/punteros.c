/* punteros.c */

#include <stdio.h>

int suma1(int x1, int x2);
void suma2(int x1, int x2, int *x3);
int resta1(int x1, int x2);

// Por tareja 2.6
int mult1(int x1, int x2);
int div1(int x1, int x2);

struct s_4reglas {
    int (*suma)(int x1, int x2);
    int (*resta)(int x1, int x2);
    int (*multiplicacion)(int x1, int x2);
    int (*division)(int x1, int x2);
};

int main(int argc, char *argv[]){ 
  int a=6, b=2, c, d;
 
 //Declarando dos punteros a funciones 
  //int (*p_oper1)(int,int) = suma1;
  int (*p_oper1)(int,int) = resta1;
  void (*p_oper2)(int,int,int*) = suma1;

// Vector y estructuras de punteros a funciones
  int (*las4reglas[])(int, int) = {suma1, resta1, mult1, div1};
  struct s_4reglas mis4reglas = {suma1, resta1, mult1, div1};
  
  c= suma1(a, b); printf("F1: a(%p) + b(%p) = %d\n",&a,&b,c);
  suma2(a, b, &d); printf("F2: a + b = %d\n",d);

  c = (*p_oper1)(a, b); printf("FP1: p_oper1(%p): a(%p) + b(%p) = %d\n",p_oper1,&a,&b,c);
  (*p_oper2)(a, b, &d); printf("FP2: p_oper2(%p): a(%p) + b(%p) = %d(%p)\n",p_oper2,&a, &b, d,&d);

  c = las4reglas[0](a,b); printf("FP3: a + b = %d\n",c);
  c = mis4reglas.suma(a,b); printf("FP4: a + b = %d\n",c);  
  return 0;
}/* end main */

int suma1(int x1, int x2){ 
  return (x1+x2); 
} /* end suma1 */

void suma2(int x1, int x2, int *x3){
  *x3= x1 + x2;
} /* end suma2 */

int resta1(int x1, int x2) {
  return (x1-x2);
} /* end resta1 */

int mult1(int x1, int x2) {
  return (x1*x2);
} /* end mult1 */

int div1(int x1, int x2) {
  return (x1/x2);
} /* end div1 */


