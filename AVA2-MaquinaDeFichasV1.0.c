/*
Disciplina  : [Introducao a Logica de Programacao]
Professor   : Rogerio Mandelli
Descricao   : Atividade Avaliativa 2 - Maquina Emissora de Fichas - Valores: 100, 50, 20, 10 e 5.
Autor(a)    : Grupo 3
Alunos(as)  : Pedro Henrique de Moura Bernardes; Ygor Trindade Maia; Kaio Eduardo de Oliveira Barbosa; Felipe Gabriel Pereira Alves Cruz
*/

/*
1. Objetivo
        > Desenvolver um algoritmo que simule uma maquina que emite fichas virtuais, calculando a
        menor quantidade possivel de fichas para compor um valor total inserido pelo usuario.
*/

// Definindo as bibliotecas a serem utilizadas no programa.
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int entry_Validation_Integer(char *entry)
{

    if (entry == NULL || strlen(entry) == 0)
    {
        return -1;
    }

    for (int i = 0; entry[i] != '\0'; i++)
    {
        if (!isdigit(entry[i]))
        {
            return -1;
        }
    }

    int number = atoi(entry);

    if (number >= 0)
    {
        return number;
    }
    else
    {
        return -1;
    }
}

int continue_Program()
{
    char option[20];

    printf("\n\n\t --- Deseja emitir mais fichas?\n\t     [1] - Sim  |  [2] - Não\n\n >> ");

    fgets(option, sizeof(option), stdin);
    option[strcspn(option, "\n")] = 0;

    int optionResult = entry_Validation_Integer(option);

    while (optionResult != 1 && optionResult != 2)
    {
        printf("\n\t ~ Opção inválida. Insira [1] para continuar ou [2] para finalizar o programa.\n\n >> ");
        fgets(option, sizeof(option), stdin);
        option[strcspn(option, "\n")] = 0;
        optionResult = entry_Validation_Integer(option);
    }

    return optionResult;
}

void printing_Divider()
{
    printf("\t|                                                                                    |\n");
}

int value_Buyed_Display()
{
    char valueBydString[20];
    int valueByd;

    while (1)
    {
        printf("\t|  ************    -------    MÁQUINA EMISSORA DE FICHAS    -------    ************  |\n");
        printing_Divider();
        printf("\t| -- Fichas Disponíveis:                                                             |\n");
        printing_Divider();
        printf("\t|      [100]      |      [50]      |      [20]      |      [10]      |      [5]      |\n");
        printing_Divider();
        printf("\t| -- Insira o valor que deseja comprar:                                              |\n\t|____________________________________________________________________________________|\n\n >> ");

        fgets(valueBydString, sizeof(valueBydString), stdin);
        valueBydString[strcspn(valueBydString, "\n")] = 0;

        valueByd = entry_Validation_Integer(valueBydString);

        while (valueByd == -1 || ((valueByd % 5) != 0))
        {
            printf("\n\t ~ Entrada inválida! Por gentileza digite um número inteiro e múltiplo de 5.\n\n >> ");
            fgets(valueBydString, sizeof(valueBydString), stdin);
            valueBydString[strcspn(valueBydString, "\n")] = 0;
            valueByd = entry_Validation_Integer(valueBydString);
        }

        break;
    }

    return valueByd;
}

void buffer_Input_Cleaner()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{

    SetConsoleOutputCP(65001);

    // Declaracao das variaveis globais do programa.
    int continueOption = 1;
    int confirmationOperation = 2;

    while (continueOption != 2)
    {
        while (confirmationOperation == 2)
        {
            int tokens[5] = {100, 50, 20, 10, 5};
            int tokensQuantity[5];
            char confirmationOperationString[5];

            int valueBuyed, valueBuyedCounter, count;
            int totalTokens = 0;

            valueBuyed = value_Buyed_Display();
            valueBuyedCounter = valueBuyed;

            // Utilizacao de algoritmo greedy
            for (int i = 0; i < 5; i++)
            {
                tokensQuantity[i] = div(valueBuyedCounter, tokens[i]).quot;
                valueBuyedCounter = valueBuyedCounter % tokens[i];
            }

            // Contar total de fichas
            for (int i = 0; i < 5; i++)
            {
                if (tokensQuantity[i] != 0)
                {
                    count = tokensQuantity[i];
                    totalTokens = totalTokens + count;
                }
            }

            printf("\n\t-----------------------------------------------------------------\n");
            printf("\tValor solicitado pelo cliente: %d.                            \n", valueBuyed);
            printf("\t-----------------------------------------------------------------\n");
            printf("\tFichas a receber:                                             \n");
            printf("\t                                                              \n");
            for (int i = 0; i < 5; i++)
            {
                if (tokensQuantity[i] != 0)
                {
                    printf("\t\t--> Fichas de %d --- %d un.\n", tokens[i], tokensQuantity[i]);
                }
            }
            printf("\t-----------------------------------------------------------------\n");
            printf("\tO total de fichas a serem emitidas: %d un.                     \n", totalTokens);
            printf("\t-----------------------------------------------------------------\n");
            printf("\t ---> Você confirma a operação?                               \n");
            printf("\t       [1] - Sim  [2] - Não                                   \n\n >> ");

            fgets(confirmationOperationString, sizeof(confirmationOperationString), stdin);
            confirmationOperationString[strcspn(confirmationOperationString, "\n")] = 0;

            confirmationOperation = entry_Validation_Integer(confirmationOperationString);

            while (confirmationOperation != 1 && confirmationOperation != 2)
            {
                printf("\n\t ~ Opção inválida! Por gentileza selecione 1 para confirmar ou 2 para voltar.\n\n >> ");
                fgets(confirmationOperationString, sizeof(confirmationOperationString), stdin);
                confirmationOperationString[strcspn(confirmationOperationString, "\n")] = 0;
                confirmationOperation = entry_Validation_Integer(confirmationOperationString);
            }

            if (confirmationOperation == 1)
            {
                printf("\n\t|-----------------------------------|\n");
                printf("\t    -- Você recebeu %d fichas! --  \n", totalTokens);
                printf("\t|-----------------------------------|\n");
                break;
            }
            else if (confirmationOperation == 2)
            {
                continue;
            }
        }

        // A variavel continueOption recebe o resultado da funcao continueProgram, sendo 1 para continuar ou 2 para sair.
        continueOption = continue_Program();
        confirmationOperation = 2;

        // Caso a opcao seja a 2, finaliza o programa.
        if (continueOption == 2)
        {
            printf("\n\n");
            printf("\t----- Saindo do programa...\n");
            exit(0);
        }
    }
}
