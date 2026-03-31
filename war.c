#include <stdio.h>
#include <string.h>

// Definição da struct para armazenar os dados do território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Declaração de um vetor de structs para armazenar 5 territórios
    struct Territorio territorios[5];
    int i;

    printf("--- Cadastro de Territórios ---\n\n");

    // Laço para entrada de dados
    for (i = 0; i < 5; i++) {
        printf("Digite os dados do %dº território:\n", i + 1);

        printf("Nome: ");
        scanf("%s", territorios[i].nome);

        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("-------------------------------\n");
    }

    // Exibição dos dados logo após o cadastro
    printf("\n--- Relatório de Territórios Cadastrados ---\n");
    printf("%-20s | %-10s | %-6s\n", "Nome", "Cor", "Tropas");
    printf("--------------------------------------------------\n");

    for (i = 0; i < 5; i++) {
        // Exibe os dados formatados para facilitar a leitura
        printf("%-20s | %-10s | %-6d\n", 
               territorios[i].nome, 
               territorios[i].cor, 
               territorios[i].tropas);
    }

    return 0;
}