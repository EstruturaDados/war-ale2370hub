#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================================================
   Struct Territorio
   ============================================================ */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* ============================================================
   Função: atribuirMissao
   Sorteia uma missão e copia para o destino dinamicamente
   ============================================================ */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

/* ============================================================
   Função: exibirMissao
   Mostra a missão atribuída ao jogador
   ============================================================ */
void exibirMissao(char* missao) {
    printf("\n===== SUA MISSÃO =====\n");
    printf("%s\n", missao);
}

/* ============================================================
   Verificação básica da missão
   ============================================================ */
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    // Missão 1: "Conquistar 3 territórios da cor azul"
    if (strcmp(missao, "Conquistar 3 territorios azuis") == 0) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0)
                count++;
        }
        if (count >= 3)
            return 1;
    }

    // Missão 2: "Eliminar todas as tropas da cor vermelha"
    if (strcmp(missao, "Eliminar todas as tropas vermelhas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0)
                return 0;
        }
        return 1;
    }

    // Missão 3: "Conquistar qualquer território"
    if (strcmp(missao, "Conquistar pelo menos 1 territorio") == 0) {
        // lógica simples: se existir qualquer território com tropas > 0
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 0)
                return 1;
        }
    }

    return 0;
}

/* ============================================================
   Funções de Território
   ============================================================ */
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

/* ============================================================
   Função: atacar
   ============================================================ */
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n===== ATAQUE =====\n");
    printf("%s (%s) está atacando %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Dado atacante: %d\n", dadoAtq);
    printf("Dado defensor: %d\n", dadoDef);

    if (dadoAtq > dadoDef) {
        printf(">> Vitória do atacante!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf(">> Ataque falhou!\n");
        if (atacante->tropas > 0)
            atacante->tropas -= 1;
    }
}

/* ============================================================
   Liberação de memória
   ============================================================ */
void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
    printf("\nMemória liberada com sucesso.\n");
}

/* ============================================================
   MAIN
   ============================================================ */
int main() {
    srand(time(NULL));

    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios azuis",
        "Eliminar todas as tropas vermelhas",
        "Conquistar pelo menos 1 territorio",
        "Manter 2 territorios verdes",
        "Eliminar 1 territorio inimigo"
    };

    int totalMissoes = 5;
    int qtdTerritorios;

    printf("Digite a quantidade de territorios do mapa: ");
    scanf("%d", &qtdTerritorios);

    Territorio* mapa = (Territorio*) malloc(qtdTerritorios * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtdTerritorios);

    // Alocar missão do jogador
    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    printf("\n>>> SUA MISSÃO FOI DEFINIDA AUTOMATICAMENTE!\n");
    exibirMissao(missaoJogador);

    int opcao, atq, def;

    while (1) {
        printf("\n===== MENU =====\n");
        printf("1 - Atacar\n");
        printf("2 - Exibir mapa\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 0)
            break;

        if (opcao == 1) {
            exibirMapa(mapa, qtdTerritorios);

            printf("Território atacante: ");
            scanf("%d", &atq);

            printf("Território defensor: ");
            scanf("%d", &def);

            if (atq < 1 || atq > qtdTerritorios || def < 1 || def > qtdTerritorios) {
                printf("Território inválido!\n");
                continue;
            }

            if (strcmp(mapa[atq-1].cor, mapa[def-1].cor) == 0) {
                printf("Não pode atacar territórios da mesma cor!\n");
                continue;
            }

            atacar(&mapa[atq-1], &mapa[def-1]);

            // Verificação silenciosa da missão
            if (verificarMissao(missaoJogador, mapa, qtdTerritorios)) {
                printf("\n\n===== MISSÃO CUMPRIDA! VOCÊ VENCEU! =====\n");
                break;
            }
        }

        if (opcao == 2)
            exibirMapa(mapa, qtdTerritorios);
    }

    liberarMemoria(mapa, missaoJogador);
    return 0;
}
