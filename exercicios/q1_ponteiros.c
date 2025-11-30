#include <stdio.h>
 
int main() {
    int inteiro;
    char caractere;
    char string[10];
    float natural;
    double real;

    int *pInteiro = &inteiro;
    char *pCaractere = &caractere;
    char *pString = string;
    float *pNatural = &natural;
    double *pReal = &real;

    scanf("%d", &inteiro);
    scanf(" %c", &caractere);
    scanf("%s", string);
    scanf("%f", &natural);
    scanf("%lf", &real);

    printf("Inteiro: %d\n", inteiro);
    printf("Caractere: %c\n", caractere);
    printf("String: %s\n", string);
    printf("Natural: %f\n", natural);
    printf("Real: %lf\n", real);
    
    printf("Inteiro via ponteiro: %d\n", *pInteiro);
    printf("Caractere via ponteiro: %c\n", *pCaractere);
    printf("String via ponteiro: %s\n", pString);
    printf("Natural via ponteiro: %f\n", *pNatural);
    printf("Real via ponteiro: %lf\n", *pReal);

    return 0;
}