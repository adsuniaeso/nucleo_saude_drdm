#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

typedef struct {
    char dia[2], mes[2], ano[4];
} Data;

typedef struct {
    char cpf[11], nome[30];
    Data data_nascimento;
} Dependente;

typedef struct {
    char cpf[11], nome[30], email[30], telefone[11];
    int sexo, plano;
    float valorPlano;
    Data data_nascimento, data_vencimento;
    Dependente dependentes[10];
} Titular;

Titular titular_aux;

FILE *base_clientes;

void linha();

void cabecalho();

void abre_arquivo();

Dependente popularDependente();

void inserir();

void listagem();

main() {
    int opcao;
    abre_arquivo();
    do {
        system("cls");
        cabecalho();
        printf("\nOpcoes: \n\n");
        printf("1 - Cadastrar novo Cliente\n");
        printf("2 - Editar Cliente\n");
        printf("3 - Remover Cliente\n");
        printf("4 - Listagem Geral\n");
        printf("5 - Listagem por Plano\n");
        printf("6 - Listagem dos Vencimentos do Plano de Saúde do Mees\n");
        printf("0 - Sair\n");
        linha();
        printf("Informe a opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                system("cls");
                inserir();
                break;
            case 2:
//                alterar();
                break;
            case 3:
//                remover();
                break;
            case 4:
                system("cls");
                listagem();
                break;
            case 5:
//                listagemPorPlano();
                break;
            case 6:
//                listagemVencimento();
                break;
            case 0:
                fclose(base_clientes);
                break;
            default:
                printf("\n\n\aOpcao invalida!");
                break;
        }
    } while (opcao != 0);
}

void linha() {
    for (int i = 1; i <= 120; i++) {
        printf("_");
    }
}

void cabecalho() {
    printf("\n");
    linha();
    printf("                                                   Nucleo Saude\n");
    linha();
}

void abre_arquivo() {
    base_clientes = fopen("..\\base_clientes.bin", "a+b");
}

Dependente popularDependente() {
    Dependente dependente;
    printf("\nCadastrar novo dependente\n");
    printf("\nCPF: ");
    scanf("%s", &dependente.cpf);
    printf("\nNome: ");
    fflush(stdin);
    gets(dependente.nome);
    printf("\nData de Nascimento:\nDia(xx):");
    scanf("%s", &dependente.data_nascimento.dia);
    printf("\nMes(xx):");
    scanf("%s", &dependente.data_nascimento.mes);
    printf("\nAno(xxxx):");
    scanf("%s", &dependente.data_nascimento.ano);
    return dependente;
}

void inserir() {
    int resposta;
    int temDependente;
    do {
        printf("\n");
        linha();
        printf("                                               Cadastrar novo Cliente\n");
        linha();
        printf("\n\nCPF: ");
        scanf("%s", &titular_aux.cpf);
        printf("\nNome: ");
        fflush(stdin);
        gets(titular_aux.nome);
        printf("\nSexo:\n1 - Feminino\n2 - Masculino\nEscolha:");
        scanf("%d", &titular_aux.sexo);
        printf("\nTelefone: ");
        scanf("%s", &titular_aux.telefone);
        printf("\nE-mail: ");
        fflush(stdin);
        gets(titular_aux.email);
        printf("\nData de Nascimento:\nDia(xx):");
        scanf("%s", &titular_aux.data_nascimento.dia);
        printf("\nMes(xx):");
        scanf("%s", &titular_aux.data_nascimento.mes);
        printf("\nAno(xxxx):");
        scanf("%s", &titular_aux.data_nascimento.ano);
        printf("\nPlano: \n1 - Ouro\n2 - Diamante\n3 - Prata\n4 - Esmeralda\nEscolha:");
        scanf("%d", &titular_aux.plano);

        int x = 0;
        do {
            printf("\nDeseja cadastrar um dependente?\n1 - Sim\n0 - Nao\nResposta:");
            scanf("%d", &temDependente);
            if (temDependente == 1) {
                titular_aux.dependentes[x] = popularDependente();
            }
            x++;
        } while (temDependente == 1);

        fseek(base_clientes, 0, SEEK_END);
        fwrite(&titular_aux, sizeof(Titular), 1, base_clientes);
        printf("\nCliente cadastrado com sucesso!\n");
        printf("\nDeseja cadastrar outro Cliente?\n1 - Sim\n0 - Nao\nResposta:");
        scanf("%d", &resposta);
        if(resposta == 1) {
            memset(titular_aux.dependentes, 0, sizeof(Dependente));
        }
    } while (resposta == 1);
}

void listagem() {
    printf("\n");
    linha();
    printf("                                                  Listagem Geral\n");
    linha();
    printf("CPF         Nome            Sexo Fone        Email                          Idade Plano Dependente Valor Plano Venc. do Plano\n");
    linha();
    rewind(base_clientes);
    fread(&titular_aux, sizeof(Titular), 1, base_clientes);

    SYSTEMTIME time;
    GetSystemTime(&time);
    int anoAtual = time.wYear;

    while (feof(base_clientes) == 0) {
        if (titular_aux.sexo != 0) {
            int idade = anoAtual - atoi(titular_aux.data_nascimento.ano);
            int qtdDep;
            for(qtdDep = 0; qtdDep < sizeof(titular_aux.dependentes) / sizeof(titular_aux.dependentes[0]);) {
                if(strcmp(titular_aux.dependentes[qtdDep].cpf, "")) {
                    qtdDep++;
                } else {
                    break;
                }
            }
            printf("%-11s %-15s %4d %-11s %-30s %5d %5d %10d %-11.2f %s/%s/%s\n", titular_aux.cpf,
                   titular_aux.nome, titular_aux.sexo,
                   titular_aux.telefone, titular_aux.email, idade, titular_aux.plano, qtdDep, titular_aux.valorPlano,
                   titular_aux.data_vencimento.dia, titular_aux.data_vencimento.mes, titular_aux.data_vencimento.ano);
        }
        fread(&titular_aux, sizeof(Titular), 1, base_clientes);
    }
    printf("\n\nTecle enter para voltar ao menu...");
    getche();
}