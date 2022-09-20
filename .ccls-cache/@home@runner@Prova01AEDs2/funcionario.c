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

int Existe(int valores[],int tam, int valor){
    for(int i = 0;i<tam;i++){
        if(valores[i]==valor)
            return 0;
    }
    return 1;
}

int GeraAleatorios(){
    srand(time(NULL));

    int num;
    int numeros[100];
    for(int i=0;i<100;i++){
        num = rand() % 100;
        while(Existe(numeros,i,num)==0){
            num = rand() % 100;
        }
        numeros[i] = num;
        return num;
    }

}

void criaBaseDados(FILE *arq, int numFuncioanrio)
{
   srand(time(NULL));
    for(int i=1; i<=numFuncioanrio; i++)
    {
        TFuncionario funcionario;
        funcionario.codigo= GeraAleatorios();
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
void OrdenarArrayKeySorting(TKeySorting *array, int quantidadeFuncionario)
{

  for (int i = 0; i < quantidadeFuncionario; i++)
  {
    for (int j = i + 1; j < quantidadeFuncionario; j++)
    {
      if (array[i].cod > array[j].cod)
      {
        TKeySorting aux = array[i];
        array[i] = array[j];
        array[j] = aux;
      }
    }
  }
}

void KeySorting(FILE *arq, FILE *arquivoOrdenado, int quantidadeFuncionario)
{
  printf("\nReaizando metodo do Key Sorting ... \n");

  clock_t comecoTime, fimTime;
  double tempoDeExecucao = 0.0;

  comecoTime = clock();

  TKeySorting array[quantidadeFuncionario];

  rewind(arq);

  for (int i = 0; i < quantidadeFuncionario; i++)
  {
    fseek(arq, i * sizeof(TFuncionario), SEEK_SET);
    array[i].RRN = ftell(arq);
   TFuncionario *funcionario = leFuncioanario(arq);
    array[i].cod = funcionario->codigo;
  }

  OrdenarArrayKeySorting(array, quantidadeFuncionario);

  rewind(arq);

  for (int i = 0; i < quantidadeFuncionario; i++)
  {

    fseek(arq, array[i].RRN, SEEK_SET);
    TFuncionario *funcionario = leFuncioanario(arq);

    fseek(arquivoOrdenado, i * sizeof(TFuncionario), SEEK_SET);
    salva(funcionario, arquivoOrdenado);
  }

  printf("Termino do KeySorting!\n");
  fimTime = clock();
  tempoDeExecucao += (double)(fimTime - comecoTime) / CLOCKS_PER_SEC;
  printf("\nTempo gasto na execucao do Key Sorting: %.8f s\n", tempoDeExecucao);
}
