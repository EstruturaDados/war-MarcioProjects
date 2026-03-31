#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Necessário para a semente do rand()

struct Territorio {
    char nome[30];
    char cor[15];
    int tropas;
};

// Função para simular o ataque
void realizarAtaque(struct Territorio *atacante, struct Territorio *defensor) {
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("\n--- BATALHA: %s vs %s ---\n", atacante->nome, defensor->nome);
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtaque, dadoDefesa);

    // Lógica: Empate ou vitória do atacante favorece o atacante (conforme requisito)
    if (dadoAtaque >= dadoDefesa) {
        printf("VITÓRIA DO ATACANTE! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;
        
        if (defensor->tropas <= 0) {
            printf("!!! TERRITÓRIO %s CONQUISTADO POR %s !!!\n", defensor->nome, atacante->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1; // Ocupação mínima
        }
    } else {
        printf("VITÓRIA DO DEFENSOR! O atacante não avançou.\n");
    }
}

int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios reais

    // ALOCAÇÃO DINÂMICA: Criando espaço para 5 territórios
    struct Territorio *mapa = (struct Territorio *) calloc(5, sizeof(struct Territorio));

    if (mapa == NULL) {
        printf("Erro: Memória insuficiente!\n");
        return 1;
    }

    // Cadastro Simplificado (Reaproveitado do Novato)
    for (int i = 0; i < 5; i++) {
        printf("Nome do %dº Território: ", i + 1);
        scanf("%s", mapa[i].nome);
        printf("Cor: ");
        scanf("%s", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("-------------------\n");
    }

    int opAtk, opDef;
    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o número do território ATACANTE (1-5): ");
    scanf("%d", &opAtk);
    printf("Escolha o número do território DEFENSOR (1-5): ");
    scanf("%d", &opDef);

    // Ajuste de índice (usuário digita 1-5, o vetor é 0-4)
    if (opAtk != opDef && opAtk >= 1 && opAtk <= 5 && opDef >= 1 && opDef <= 5) {
        realizarAtaque(&mapa[opAtk - 1], &mapa[opDef - 1]);
    } else {
        printf("Ataque inválido!\n");
    }

    // Exibição Final
    printf("\n=== ESTADO ATUAL DO MAPA ===\n");
    for (int i = 0; i < 5; i++) {
        printf("[%d] %-15s | Cor: %-10s | Tropas: %d\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    // LIBERAÇÃO DE MEMÓRIA: Importante em alocação dinâmica!
    free(mapa);

    return 0;
}