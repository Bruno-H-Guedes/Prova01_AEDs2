#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED
#include <stdio.h>

typedef struct Funcionario{

    int codigo;
    char nome[50];
    char cpf[15];
    char dataNascimento[11];
    double salario;
}TFuncionario;

typedef struct key_sorting
{
  int cod;
  long RRN;
} TKeySorting;

void salva(TFuncionario *funcionario, FILE *out);
TFuncionario *leFuncioanario(FILE *in);
void criaBaseDados(FILE *arq, int numFuncioanrio);
TFuncionario *buscaBinaria(int codigo, FILE *arq, int tamanho);
TFuncionario *buscaSequencial(int codigo, FILE *arq, int tamanho);
void OrdenarArrayKeySorting(TKeySorting *array, int quantidadeFuncionario);
void KeySorting(FILE *arq, FILE *arquivoOrdenado, int quantidadeFuncionario);
int Existe(int valores[],int tam, int valor);
int GeraAleatorios();
#endif // FUNCIONARIO_H_INCLUDED
