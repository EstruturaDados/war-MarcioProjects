#include <stdio.h>
#include <string.h>

// Definição da estrutura conforme os requisitos da MateCheck
struct Territorio {
    char nome[30];
    char cor[15];
    int tropas;
};

int main() {
    // Vetor estático de 5 elementos para armazenar o mapa inicial
    struct Territorio mapa[5];
    int i;

    printf("### BEM-VINDO AO DESAFIO WAR ESTRUTURADO ###\n");
    printf("Nível: Novato | Empresa: MateCheck\n\n");

    // Cadastro dos Dados
    for (i = 0; i < 5; i++) {
        printf("--- Cadastro do %dº Território ---\n", i + 1);

        printf("Nome do Território: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0; // Remove o '\n' lido pelo fgets

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, 15, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        // Limpeza de buffer para que o próximo fgets não leia o 'Enter' deixado pelo scanf
        while (getchar() != '\n'); 

        printf("\n");
    }

    // Exibição do Estado Atual do Mapa
    printf("==========================================\n");
    printf("         ESTADO ATUAL DO MAPA            \n");
    printf("==========================================\n");
    printf("%-20s | %-10s | %s\n", "TERRITÓRIO", "COR", "TROPAS");
    printf("------------------------------------------\n");

    for (i = 0; i < 5; i++) {
        printf("%-20s | %-10s | %d\n", 
               mapa[i].nome, 
               mapa[i].cor, 
               mapa[i].tropas);
    }
    printf("==========================================\n");

    return 0;
}
