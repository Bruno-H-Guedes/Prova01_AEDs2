#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"

int main()
{
    FILE *arq = fopen("funcionario.dat", "wb+");
    int numFuncionario = 100;
    int opcao=-1;

    if(arq==NULL)
    {
        printf("Nao foi possivel abrir o arquivo\n");
        return 1;
    }

    criaBaseDados(arq, numFuncionario);

    printf("Qual busca deseja realizar:\n");
    printf("Digite 1 para busca sequencial\nDigite 2 para busca binaria\n");
    scanf("%d", &opcao);


    if(opcao==1)
    {
        TFuncionario *funcionario = buscaSequencial(60, arq, numFuncionario);
        if(funcionario == NULL)
        {
            printf("Funcionario nao enontrado\n");
        }
        else
        {
            printf("Funcionario encontrado\n");
            printf("Codigo: %d\n", funcionario->codigo);
            printf("Nome: %s\n", funcionario->nome);
            printf("CFP: %s\n", funcionario->cpf);
            printf("Data de nascimento: %s\n", funcionario->dataNascimento);
            printf("Salario: %f\n", funcionario->salario);
        }

        free(funcionario);
        fclose(arq);
    }


    else if(opcao==2)
    {
        TFuncionario *funcionario = buscaBinaria(60, arq, numFuncionario);
        if(funcionario == NULL)
        {
            printf("Funcionario nao enontrado\n");
        }
        else
        {
            printf("Funcionario encontrado\n");
            printf("Codigo: %d\n", funcionario->codigo);
            printf("Nome: %s\n", funcionario->nome);
            printf("CFP: %s\n", funcionario->cpf);
            printf("Data de nascimento: %s\n", funcionario->dataNascimento);
            printf("Salario: %f\n", funcionario->salario);
        }

        free(funcionario);
        fclose(arq);
    }


    return 0;
}
