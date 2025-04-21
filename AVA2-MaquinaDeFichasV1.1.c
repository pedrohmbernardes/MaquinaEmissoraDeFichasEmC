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

// Funcao definida para garantir a validacao de um inteiro na entrada do usuario. A funcao recebe um ponteiro de um vetor de caracteres (como string).
int entry_Validation_Integer(char *entry)
{

    // Se a entrada do usuario nao apontar para nenhum rastro de memoria (nulo) ou se for vazia, retornara falso.
    if (entry == NULL || strlen(entry) == 0)
    {
        return false;
    }

    // Para cada elemento do vetor da entrada (como string), que seja diferente de nulo, sera verificado se eh um numero de 0 a 9 ou nao. Caso nao, retornara falso.
    for (int i = 0; entry[i] != '\0'; i++)
    {
        if (!isdigit(entry[i]))
        {
            return false;
        }
    }

    // A variavel number recebera a conversao da entrada do usuario como vetor, para um numero inteiro.
    int number = atoi(entry);

    // Caso o valor de number, seja maior que zero, retornara o valor como resultado da funcao.
    if (number >= 0)
    {
        return number;
    }
    // Caso nao, retorna falso.
    else
    {
        return false;
    }
}

// Funcao definida para questionar o usuario se ele deseja continuar no programa ou nao.
int continue_Program()
{

    // Variavel definida como vetor de caracteres para receber qual opcao o usuario escolheu.
    char option[10];

    printf("\n\n\t --- Deseja emitir mais fichas?\n\t     [1] - Sim  |  [2] - Não\n\n >> ");

    // Recebendo a entrada do usuario como vetor e garantindo todas as posicoes até o \n.
    fgets(option, sizeof(option), stdin);
    option[strcspn(option, "\n")] = 0;

    // A variavel optionResult, recebera a entrada da variavel option apos passar pela validacao de inteiro, com objetivo de garantir que seja um numero inteiro.
    int optionResult = entry_Validation_Integer(option);

    // Caso a opcao seja diferente de 1 e 2, apresenta uma mensagem de erro, e solicita nova entrada ao usuario.
    while (optionResult != 1 && optionResult != 2)
    {
        printf("\n\t ~ Opção inválida. Insira [1] para continuar ou [2] para finalizar o programa.\n\n >> ");
        fgets(option, sizeof(option), stdin);
        option[strcspn(option, "\n")] = 0;
        optionResult = entry_Validation_Integer(option);
    }

    return optionResult;
}

// Somente um divisor para melhorar aspectos visuais do programa (sim eu sei que da pra melhorar o codigo dessa funcao).
void printing_Divider()
{
    printf("\t|                                                                                    |\n");
}

// Funcao referente a tela principal do programa. Aqui apresenta o menu ao usuario e garante que a entrada do usuario seja um numero inteiro e multiplo de 5.
int value_Buyed_Display()
{

    // Variavel valueBydString eh um vetor de caracteres para garantir que o valor que o usuario insira, passe pelas funcoes de validacao de entrada.
    char valueBydString[20];
    // Variavel de numero inteiro que ira receber o valor final apos as validacoes.
    int valueByd;

    // Esse laço se repete até encontrar o break.
    while (true)
    {
        printf("\t|  ************    -------    MÁQUINA EMISSORA DE FICHAS    -------    ************  |\n");
        printing_Divider();
        printf("\t| -- Fichas Disponíveis:                                                             |\n");
        printing_Divider();
        printf("\t|      [100]      |      [50]      |      [20]      |      [10]      |      [5]      |\n");
        printing_Divider();
        printf("\t| -- Insira o valor que deseja comprar:                                              |\n\t|____________________________________________________________________________________|\n\n >> ");

        // Recebendo a entrada do usuario como string.
        fgets(valueBydString, sizeof(valueBydString), stdin);
        valueBydString[strcspn(valueBydString, "\n")] = 0;

        // valueByd recebera o valor da entrada do usuario em valueBydString apos a verificacao para garantir a entrada de um numero inteiro.
        valueByd = entry_Validation_Integer(valueBydString);

        // Enquanto valueByd for -1 (referente a falso) ou nao seja um multiplo de 5, apresenta uma mensagem de erro ao usuario e solicita nova entrada.
        while (valueByd == -1 || ((valueByd % 5) != 0))
        {
            printf("\n\t ~ Entrada inválida! Por gentileza digite um número inteiro e múltiplo de 5.\n\n >> ");
            fgets(valueBydString, sizeof(valueBydString), stdin);
            valueBydString[strcspn(valueBydString, "\n")] = 0;
            valueByd = entry_Validation_Integer(valueBydString);
        }

        // Break para parar o laço.
        break;
    }

    return valueByd;
}

// Funcao definida para limpar o buffer de entrada do teclado.
void buffer_Input_Cleaner()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{

    // Essa funcao vem da biblioteca e api do windows para garantir a saida em utf-8 e que as palavras possuam acentuacao e caracteres corretos.
    SetConsoleOutputCP(65001);

    // Declaracao das variaveis globais do programa.
    int continueOption = 1;
    int confirmationOperation = 2;

    while (continueOption != 2)
    {
        while (confirmationOperation == 2)
        {

            // Variaveis utilizadas na parte principal do programa.
            int tokens[5] = {100, 50, 20, 10, 5};
            int tokensQuantity[5];
            char confirmationOperationString[5];

            int valueBuyed, valueBuyedCounter, count;
            int totalTokens = 0;

            // Esta parte, a variavel valueBuyed recebera o resultado da funcao value_Buyed_Display (referente a tela e menu principal do programa).
            valueBuyed = value_Buyed_Display();

            // Utilizei esta variavel com o mesmo valor de valueBuyed para utilizacao do algoritmo greedy.
            valueBuyedCounter = valueBuyed;

            // Como todas as nossas fichas sao multiplos de 5 e a entrada do usuario tambem deve ser, obrigatoriamente, multiplo de 5, podemos entao utilizar o algoritmo greedy.
            for (int i = 0; i < 5; i++)
            {
                /*
                O algoritmo greedy, neste caso, utiliza a divisao basica para facilitar o resultado que buscamos.
                Utilizando a funcao div para dividir o valor entrado pelo usuario pela ficha na posicao 0 (nesse caso, a ficha na posicao zero sera sempre a maior, indo do
                maior para o menor), dessa forma, o quociente encontrado sera o total de fichas daquele valor, e o valor de entrada do usuario sera atualizado como o resto
                dessa divisao. Dessa forma, no proximo loop, o resto passa a ser o "novo" valor da entrada do usuario. Assim, conseguimos calcular o valor completo que o
                usuario entrou ate que o resto seja zero.
                */
                tokensQuantity[i] = div(valueBuyedCounter, tokens[i]).quot;
                valueBuyedCounter = valueBuyedCounter % tokens[i];
            }

            // Loop feito para contar o total de fichas encontrados que sejam diferentes de zero.
            for (int i = 0; i < 5; i++)
            {
                if (tokensQuantity[i] != 0)
                {
                    count = tokensQuantity[i];
                    totalTokens = totalTokens + count;
                }
            }

            // Resumo sobre a operacao ate aqui, e solicitando confirmacao por parte do usuario.
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

            // O usuario precisa confirmar a operacao. Neste caso, solicita entrada do usuario, e tem que ser 1 ou 2.
            fgets(confirmationOperationString, sizeof(confirmationOperationString), stdin);
            confirmationOperationString[strcspn(confirmationOperationString, "\n")] = 0;

            confirmationOperation = entry_Validation_Integer(confirmationOperationString);

            // Caso diferente de 1 ou 2, apresenta mensagem de erro para o usuario e le nova entrada.
            while (confirmationOperation != 1 && confirmationOperation != 2)
            {
                printf("\n\t ~ Opção inválida! Por gentileza selecione 1 para confirmar ou 2 para voltar.\n\n >> ");
                fgets(confirmationOperationString, sizeof(confirmationOperationString), stdin);
                confirmationOperationString[strcspn(confirmationOperationString, "\n")] = 0;
                confirmationOperation = entry_Validation_Integer(confirmationOperationString);
            }

            // Se 1 (ou seja, confirmado a operacao), apresenta a mensagem do total de fichas que o usuario recebeu, e da o break para sair desse loop do programa.
            if (confirmationOperation == 1)
            {
                printf("\n\t|-----------------------------------|\n");
                printf("\t    -- Você recebeu %d fichas! --  \n", totalTokens);
                printf("\t|-----------------------------------|\n");
                break;
            }

            // Caso 2 (nao confirmado a operacao), continua o programa sem sair desse loop e retorna a parte inicial do programa.
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
