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

// Protótipos
void exibirMenu();
void cadastrarLivro(struct Livro *biblioteca, int *totalLivros);
void listarLivros(const struct Livro *biblioteca, int totalLivros);
void realizarEmprestimos(struct Livro *biblioteca, int totalLivros, struct Emprestimos *emprestimos, int *totalEmprestimos);
void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimos *emprestimos, int totalEmprestimos);
void limparBuffer();

int main() {
    struct Livro *biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));
    struct Emprestimos *emprestimos = (struct Emprestimos *) calloc(MAX_EMPRESTIMOS, sizeof(struct Emprestimos));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarLivro(biblioteca, &totalLivros);
                break;

            case 2:
                listarLivros(biblioteca, totalLivros);
                break;

            case 3:
                realizarEmprestimos(biblioteca, totalLivros, emprestimos, &totalEmprestimos);
                break;

            case 4:
                listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
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

// Função para limpar buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Exibir o menu
void exibirMenu() {
    printf("\nBiblioteca:\n");
    printf("1. Cadastrar livro\n");
    printf("2. Mostrar livros\n");
    printf("3. Realizar emprestimo\n");
    printf("4. Mostrar emprestimos\n");
    printf("0. Sair\n");
    printf("Opcao: ");
}

// Cadastrar livro
void cadastrarLivro(struct Livro *biblioteca, int *totalLivros) {
    if (*totalLivros >= MAX_LIVROS) {
        printf("Limite de livros atingido!\n");
        return;
    }

    struct Livro *novo = &biblioteca[*totalLivros];

    printf("Digite o nome do livro: ");
    fgets(novo->nome, TAM_STRING, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("Digite o autor: ");
    fgets(novo->autor, TAM_STRING, stdin);
    novo->autor[strcspn(novo->autor, "\n")] = '\0';

    printf("Digite a editora: ");
    fgets(novo->editora, TAM_STRING, stdin);
    novo->editora[strcspn(novo->editora, "\n")] = '\0';

    printf("Digite a edicao: ");
    scanf("%d", &novo->edicao);
    limparBuffer();

    novo->disponivel = 1; // disponível

    (*totalLivros)++;
    printf("Livro cadastrado com sucesso!\n");
}

// Listar livros
void listarLivros(const struct Livro *biblioteca, int totalLivros) {
    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Livros ---\n");
    for (int i = 0; i < totalLivros; i++) {
        printf("LIVRO %d\n", i + 1);
        printf("Nome: %s\n", biblioteca[i].nome);
        printf("Autor: %s\n", biblioteca[i].autor);
        printf("Editora: %s\n", biblioteca[i].editora);
        printf("Edicao: %d\n", biblioteca[i].edicao);
        printf("Status: %s\n", biblioteca[i].disponivel ? "Disponível" : "Emprestado");
        printf("\n");
    }
}

// Realizar empréstimo
void realizarEmprestimos(struct Livro *biblioteca, int totalLivros, struct Emprestimos *emprestimos, int *totalEmprestimos) {
    if (totalLivros == 0) {
        printf("Nao ha livros cadastrados para emprestimo.\n");
        return;
    }

    if (*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Limite de emprestimos atingido!\n");
        return;
    }

    listarLivros(biblioteca, totalLivros);

    int escolha;
    printf("Digite o numero do livro que deseja emprestar: ");
    scanf("%d", &escolha);
    limparBuffer();

    if (escolha < 1 || escolha > totalLivros) {
        printf("Livro invalido!\n");
        return;
    }

    int indice = escolha - 1;
    if (!biblioteca[indice].disponivel) {
        printf("Livro ja esta emprestado.\n");
        return;
    }

    biblioteca[indice].disponivel = 0;

    struct Emprestimos *novoEmp = &emprestimos[*totalEmprestimos];
    novoEmp->indiceLivro = indice;

    printf("Digite o nome do usuario: ");
    fgets(novoEmp->nomeUsuario, TAM_STRING, stdin);
    novoEmp->nomeUsuario[strcspn(novoEmp->nomeUsuario, "\n")] = '\0';

    (*totalEmprestimos)++;
    printf("Emprestimo realizado com sucesso!\n");
}

// Listar empréstimos
void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimos *emprestimos, int totalEmprestimos) {
    if (totalEmprestimos == 0) {
        printf("Nenhum emprestimo registrado.\n");
        return;
    }

    printf("\n--- Lista de Emprestimos ---\n");
    for (int i = 0; i < totalEmprestimos; i++) {
        int indice = emprestimos[i].indiceLivro;
        printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
        printf("Livro: %s (Autor: %s)\n", biblioteca[indice].nome, biblioteca[indice].autor);
        printf("\n");
    }
}