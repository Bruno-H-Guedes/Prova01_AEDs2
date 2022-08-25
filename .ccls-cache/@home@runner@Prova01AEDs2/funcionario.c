#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "funcionario.h"

void salva(TFuncionario *funcionario, FILE *out)
{

    fwrite(&funcionario->codigo, sizeof(int), 1, out);
    fwrite(funcionario->nome, sizeof(char), sizeof(funcionario->nome), out);
    fwrite(funcionario->cpf, sizeof(char), sizeof(funcionario->cpf), out);
    fwrite(funcionario->dataNascimento, sizeof(char), sizeof(funcionario->dataNascimento), out);
    fwrite(&funcionario->salario, sizeof(double), 1, out);

}

TFuncionario *leFuncioanario(FILE *in)
{

    TFuncionario *funcionario = (TFuncionario*)malloc(sizeof(TFuncionario));

    if(0>= fread(&funcionario->codigo, sizeof(int), 1, in))
    {
        free(funcionario);
        return NULL;
    }

    fread(funcionario->nome, sizeof(char), sizeof(funcionario->nome), in);
    fread(funcionario->cpf, sizeof(char), sizeof(funcionario->cpf), in);
    fread(funcionario->dataNascimento, sizeof(char), sizeof(funcionario->dataNascimento), in);
    fread(&funcionario->salario, sizeof(double), 1, in);

    return funcionario;
}

void criaBaseDados(FILE *arq, int numFuncioanrio)
{

    for(int i=1; i<=numFuncioanrio; i++)
    {
        TFuncionario funcionario;
        funcionario.codigo=i;
        sprintf(funcionario.nome, "Funcionario %d", i);
        sprintf(funcionario.cpf, "111.111.111-11");
        sprintf(funcionario.dataNascimento, "08/08/1996");
        funcionario.salario = 1000+i;
        fseek(arq,(i-1)*sizeof(TFuncionario), SEEK_SET);
        salva(&funcionario, arq);
    }
}

TFuncionario *buscaSequencial(int codigo, FILE *arq, int tamanho)
{

    int numeroComparacoes=0;
    double tempoExecucao=0.0;

    clock_t begin = clock();
    for(int i=1; i<=tamanho; i++)
    {

        fseek(arq,(i-1)*sizeof(TFuncionario), SEEK_SET);
        TFuncionario *funcionario = leFuncioanario(arq);

        if(codigo == funcionario->codigo)
        {
            clock_t end = clock();
            tempoExecucao += (double)(end - begin)/CLOCKS_PER_SEC;

            printf("O tempo de execucao da busca sequencial foi: %f segundos\n", tempoExecucao);
            numeroComparacoes++;
            printf("O numero de comparacoes feitas foi: %d\n", numeroComparacoes);
            return funcionario;
        }
        numeroComparacoes++;
    }
    clock_t end = clock();
    tempoExecucao += (double)(end - begin)/CLOCKS_PER_SEC;

    printf("O tempo de execucao da busca sequencial foi: %f segundos\n", tempoExecucao);
    printf("O numero de comparacoes feitas foi: %d\n", numeroComparacoes);
    return NULL;
}

TFuncionario *buscaBinaria(int codigo, FILE *arq, int tamanho)
{

    int left =0, right=tamanho-1;
    int numeroComparacoes=0;
    double tempoExecucao=0.0;

    clock_t begin = clock();
    while(left <= right)
    {
        int middle = (left+right)/2;
        fseek(arq, middle*sizeof(TFuncionario), SEEK_SET);
        TFuncionario *funcionario = leFuncioanario(arq);

        if(codigo == funcionario->codigo)
        {
            clock_t end = clock();
            tempoExecucao += (double)(end - begin)/CLOCKS_PER_SEC;

            printf("O tempo de execucao da busca Binaria foi: %f segundos\n", tempoExecucao);
            numeroComparacoes++;
            printf("O numero de comparacoes feitas foi: %d\n", numeroComparacoes);
            return funcionario;
        }
        else if(funcionario->codigo < codigo)
        {
            left= middle+1;
        }
        else
        {
            right = middle+1;
        }
        numeroComparacoes++;
    }

    clock_t end = clock();
    tempoExecucao += (double)(end - begin)/CLOCKS_PER_SEC;

    printf("O tempo de execucao da busca binaria foi: %f segundos\n", tempoExecucao);
    printf("O numero de comparacoes feitas foi: %d\n", numeroComparacoes);
    return NULL;
}
