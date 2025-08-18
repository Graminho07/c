#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 = disponível, 0 = emprestado
};

struct Emprestimos {
    int indiceLivro;
    char nomeUsuario[TAM_STRING];
};

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Livro *biblioteca;
    struct Emprestimos *emprestimos;

    biblioteca = (struct Livro *)calloc(MAX_LIVROS, sizeof(struct Livro));
    emprestimos = (struct Emprestimos *)malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimos));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memoria");
        return 1;
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do {
        printf("Biblioteca:\n");
        printf("1. Cadastrar livro\n");
        printf("2. Mostrar livros\n");
        printf("3. Realizar emprestimo\n");
        printf("4. Mostrar emprestimos\n");
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

                    biblioteca[totalLivros].disponivel = 1; // inicializa como disponível

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
                        printf("Status: %s\n", biblioteca[i].disponivel ? "Disponível" : "Emprestado");
                        printf("\n");
                    }
                }
                printf("\nPressione enter para continuar: ");
                getchar();
                break;

            case 3:
                printf("Realizar emprestimo:\n\n");

                if (totalEmprestimos >= MAX_EMPRESTIMOS) {
                    printf("Limite de emprestimos atingido!\n");
                } else {
                    printf("Livros disponiveis:\n");
                    int disponiveis = 0;
                    for (int i = 0; i < totalLivros; i++) {
                        if (biblioteca[i].disponivel) {
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }
                    if (disponiveis == 0) {
                        printf("Nenhum livro disponivel para emprestimo\n");
                    } else {
                        printf("Digite o numero do livro que deseja emprestar:\n");
                        int numLivro;
                        scanf("%d", &numLivro);
                        limparBuffer();

                        int indice = numLivro - 1;

                        if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                            printf("Digite o nome do usuario que esta pegando o livro: ");
                            fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                            emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = '\0';

                            emprestimos[totalEmprestimos].indiceLivro = indice;

                            biblioteca[indice].disponivel = 0; // agora não está mais disponível
                            totalEmprestimos++;
                            printf("\nEmprestimo realizado com sucesso!\n");
                        } else {
                            printf("Numero de livro invalido ou livro indisponivel.\n");
                        }
                    }
                }
                printf("\nPressione enter para continuar: ");
                getchar();
                break;

            case 4:
                printf("Mostrar emprestimos:\n\n");
                if (totalEmprestimos == 0) {
                    printf("Nenhum emprestimo realizado\n");
                } else {
                    for (int i = 0; i < totalEmprestimos; i++) {
                        int indiceLivro = emprestimos[i].indiceLivro;
                        printf("Emprestimo %d\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
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

    free(biblioteca);
    free(emprestimos);

    printf("Memoria liberada com sucesso!\n");

    return 0;
}
