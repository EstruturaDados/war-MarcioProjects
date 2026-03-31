#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do Território
typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void atribuirMissao(char **destino, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, Territorio *mapa, int tamanho);
void atacar(Territorio *atacante, Territorio *defensor);
void exibirMapa(Territorio *mapa, int tamanho);
void liberarMemoria(Territorio *mapa, char *missao);

int main() {
    srand(time(NULL));

    // 1. Criação do vetor de missões (descrições pré-definidas)
    char *listaMissoes[] = {
        "Conquistar 3 territorios",
        "Eliminar tropas da cor Vermelha",
        "Dominar o mapa com a cor Azul",
        "Ter mais de 10 tropas acumuladas",
        "Conquistar o primeiro e o ultimo territorio"
    };
    int totalMissoes = 5;
    int numTerritorios = 5;

    // 2. Alocação Dinâmica
    Territorio *mapa = (Territorio *) calloc(numTerritorios, sizeof(Territorio));
    char *missaoJogador = NULL; // Ponteiro para a missão

    if (mapa == NULL) {
        printf("Erro de memoria!\n");
        return 1;
    }

    // 3. Atribuição da Missão (Passagem por referência do ponteiro da missão)
    atribuirMissao(&missaoJogador, listaMissoes, totalMissoes);

    // Cadastro Inicial
    printf("=== CONFIGURACAO DO JOGO ===\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Nome do Territorio %d: ", i + 1);
        scanf("%s", mapa[i].nome);
        printf("Cor dominante: ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("---------------------------\n");
    }

    printf("\nSUA MISSAO SECRETA: %s\n", missaoJogador);
    printf("Pressione Enter para iniciar o combate...");
    getchar(); getchar();

    // 4. Loop de Jogo Simplificado (Fase de Ataque)
    int jogoAtivo = 1;
    while (jogoAtivo) {
        exibirMapa(mapa, numTerritorios);
        
        int atq, def;
        printf("\nEscolha o indice do Atacante (1-%d) ou 0 para sair: ", numTerritorios);
        scanf("%d", &atq);
        if (atq == 0) break;

        printf("Escolha o indice do Defensor (1-%d): ", numTerritorios);
        scanf("%d", &def);

        // Validação de índices e regras (Ataque apenas em inimigos)
        if (atq > 0 && atq <= numTerritorios && def > 0 && def <= numTerritorios && atq != def) {
            if (strcmp(mapa[atq-1].cor, mapa[def-1].cor) != 0) {
                atacar(&mapa[atq-1], &mapa[def-1]);
            } else {
                printf("\n[AVISO] Voce nao pode atacar seu proprio territorio!\n");
            }
        } else {
            printf("\n[ERRO] Selecao invalida!\n");
        }

        // 5. Verificação de Missão (Silenciosa/Ao final do turno)
        if (verificarMissao(missaoJogador, mapa, numTerritorios)) {
            printf("\n******************************************\n");
            printf("PARABENS! Voce cumpriu o objetivo:\n\"%s\"\n", missaoJogador);
            printf("VOCE EH O VENCEDOR!\n");
            printf("******************************************\n");
            jogoAtivo = 0;
        }
    }

    exibirMapa(mapa, numTerritorios);
    liberarMemoria(mapa, missaoJogador);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Atribui uma missão sorteada usando alocação dinâmica interna
void atribuirMissao(char **destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    // Aloca espaço para a string da missão
    *destino = (char *) malloc((strlen(missoes[indice]) + 1) * sizeof(char));
    if (*destino != NULL) {
        strcpy(*destino, missoes[indice]);
    }
}

// Lógica de ataque conforme requisitos
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("Ataque impossivel! %s precisa de ao menos 2 tropas para atacar.\n", atacante->nome);
        return;
    }

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\nBatalha: %s [%d] vs %s [%d]\n", atacante->nome, dadoAtk, defensor->nome, dadoDef);

    if (dadoAtk > dadoDef) {
        printf("Vitoria do Atacante! Territorio conquistado.\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // Transfere metade das tropas
        atacante->tropas -= defensor->tropas;   // Remove do atacante
    } else {
        printf("Vitoria do Defensor! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;
    }
}

// Exibe o estado atual do mapa
void exibirMapa(Territorio *mapa, int tamanho) {
    printf("\n--- ESTADO DO MAPA ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] %-15s | Cor: %-10s | Tropas: %d\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Verifica se a missão foi cumprida
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    // Exemplo de lógica para "Conquistar 3 territorios"
    // Aqui verificamos se a cor do primeiro território domina outros 2
    if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        int cont = 0;
        char *minhaCor = mapa[0].cor; // Assume-se que o jogador começa com o primeiro
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, minhaCor) == 0) cont++;
        }
        return (cont >= 3);
    }
    
    // Lógica para acumular tropas
    if (strcmp(missao, "Ter mais de 10 tropas acumuladas") == 0) {
        int total = 0;
        for (int i = 0; i < tamanho; i++) total += mapa[i].tropas;
        return (total > 10);
    }

    return 0; // Missão ainda não cumprida
}

// Liberação de memória de todos os recursos alocados
void liberarMemoria(Territorio *mapa, char *missao) {
    if (mapa != NULL) free(mapa);
    if (missao != NULL) free(missao);
    printf("\nMemoria liberada com sucesso. Fim de jogo!\n");
}