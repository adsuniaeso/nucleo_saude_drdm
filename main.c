#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    char cpf[14], nome[50], dataNascimento[10];
} Dependente;

typedef struct {
    char cpf[14], nome[50], email[50], data_nascimento[10], telefone[14], data_vencimento[10];
    int sexo, plano;
    float valorPlano;
    Dependente dependentes[];
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
                inserir();
                break;
            case 2:
//                alterar();
                break;
            case 3:
//                remover();
                break;
            case 4:
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
    for (int i = 1; i <= 80; i++) {
        printf("_");
    }
    printf("\n");
}

void cabecalho() {
//    system("cls");
    printf("Nucleo Saude");
    linha();
}

void abre_arquivo() {
    base_clientes = fopen("..\\base_clientes.txt", "r+b");
    if (base_clientes == NULL)
        base_clientes = fopen("..\\base_clientes.txt", "w+b");
}

Dependente popularDependente() {
    Dependente dependente;
    printf("\n\nCadastrar novo dependente\n\n");
    printf("\nCPF: ");
    scanf("%s", &dependente.cpf);
    printf("\nNome: ");
    fflush(stdin);
    gets(dependente.nome);
    printf("\nData de Nascimento: ");
    scanf("%s", &dependente.dataNascimento);
    return dependente;
}

void inserir() {
    int resposta;
    int temDependente;
    do {
        cabecalho();
        printf("\n\nCadastrar novo Cliente\n\n");
        printf("\nCPF: ");
        scanf("%s", &titular_aux.cpf);
        printf("\nNome: ");
        fflush(stdin);
        gets(titular_aux.nome);
        printf("\nSexo:\n1 - Feminino\n2 - Masculino\nEscolha:");
        scanf("%d", &titular_aux.sexo);
        printf("\nE-mail: ");
        scanf("%s", &titular_aux.email);
        printf("\nData de Nascimento: ");
        scanf("%s", &titular_aux.data_nascimento);
        printf("\nPlano: \n1 - Ouro\n2 - Diamante\n3 - Prata\n4 - Esmeralda\nEscolha:");
        scanf("%f", &titular_aux.plano);
        printf("\nData de Nascimento: ");
        scanf("%f", &titular_aux.data_nascimento);

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
        printf("\n\nCliente cadastrado com sucesso!\n\n");
        printf("\nDeseja cadastrar outro Cliente?\n1 - Sim\n0 - Nao\nResposta:");
        scanf("%d", &resposta);
    } while (resposta == 1);
}

void listagem() {
    cabecalho();
    printf("\n\nListagem Geral\n\n\n");
    linha();
    printf("CPF Nome Sexo\n");
    linha();
    rewind(base_clientes);
    fread(&titular_aux, sizeof(Titular), 1, base_clientes);
    while (feof(base_clientes) == 0) {
        if (titular_aux.sexo != 0)
            printf("%9d %-20s %5.1f\n", titular_aux.cpf, titular_aux.nome, titular_aux.sexo);
        fread(&titular_aux, sizeof(Titular), 1, base_clientes);
    }
    linha();
    printf("tecle enter para voltar ao menu...");
    getche();
}