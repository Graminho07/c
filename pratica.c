#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 50
#define TAM_STRING 100

struct livro{
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
};

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(){
    struct livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    do {
        printf("Biblioteca:\n");
        printf("1. Cadastrar livro\n");
        printf("2. Mostrar livros\n");
        printf("0. Sair\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                printf("Cadastro de Novo Livro:\n\n");

                if (totalLivros < MAX_LIVROS) {
                    printf("Insira o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o nome do autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                    printf("Digite o nome da editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                    printf("Digite a edicao: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBuffer();

                    totalLivros++;
                    printf("\nLivro cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia, nao e possivel cadastrar o livro!\n");
                }
                printf("\nPressione enter para continuar: ");
                getchar();
                break;

            case 2:
                printf("Mostrar livros:\n\n");

                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("LIVRO %d\n", i + 1);
                        printf("Nome do livro: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edicao: %d\n", biblioteca[i].edicao);
                        printf("\n");
                    }
                }
                printf("\nPressione enter para continuar: ");
                getchar();
                break;

            case 0:
                printf("Saindo do sistema\n");
                break;

            default:
                printf("Opcao invalida!\n");
                printf("\nPressione enter para continuar: ");
                getchar();
                break;
        }
    } while (opcao != 0);

    return 0;
}
