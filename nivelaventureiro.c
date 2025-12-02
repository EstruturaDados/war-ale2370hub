#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================================================
   Struct Territorio
   Representa um território no jogo, com:
   - nome
   - cor do exército
   - número de tropas
   ============================================================ */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* ============================================================
   Função: cadastrarTerritorios
   Entrada: ponteiro para vetor de Territorio e quantidade
   Ação: preenche os dados via teclado
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

/* ============================================================
   Função: exibirTerritorios
   Mostra os dados atualizados de todos os territórios
   ============================================================ */
void exibirTerritorios(Territorio* mapa, int qtd) {
    printf("\n===== ESTADO ATUAL DOS TERRITÓRIOS =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

/* ============================================================
   Função: atacar
   Simula um ataque usando rolagem de dados (1 a 6)
   - atacante e defensor são ponteiros
   ============================================================ */
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n===== INICIANDO ATAQUE =====\n");
    printf("%s (%s) está atacando %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    // rolagem dos dados
    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Dado atacante: %d\n", dadoAtq);
    printf("Dado defensor: %d\n", dadoDef);

    if (dadoAtq > dadoDef) {
        printf("\n*** Ataque bem-sucedido! ***\n");

        // defensor muda de dono
        strcpy(defensor->cor, atacante->cor);

        // defensor recebe metade das tropas do atacante
        defensor->tropas = atacante->tropas / 2;

        printf("O território %s agora pertence a %s.\n",
               defensor->nome, defensor->cor);

    } else {
        printf("\n*** Ataque falhou! ***\n");

        // atacante perde uma tropa
        if (atacante->tropas > 0)
            atacante->tropas -= 1;

        printf("%s perdeu 1 tropa.\n", atacante->nome);
    }
}

/* ============================================================
   Função: liberarMemoria
   Libera o vetor alocado dinamicamente
   ============================================================ */
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso.\n");
}

/* ============================================================
   MAIN
   ============================================================ */
int main() {
    srand(time(NULL)); // aleatoriedade

    int qtd;

    printf("Digite o número total de territórios: ");
    scanf("%d", &qtd);

    // alocação dinâmica
    Territorio* mapa = (Territorio*) malloc(qtd * sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);
    exibirTerritorios(mapa, qtd);

    int opcao, atq, def;

    while (1) {
        printf("\n===== MENU DE ATAQUE =====\n");
        printf("1 - Realizar ataque\n");
        printf("2 - Mostrar territórios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 0)
            break;

        if (opcao == 1) {
            exibirTerritorios(mapa, qtd);

            printf("\nEscolha o número do território atacante: ");
            scanf("%d", &atq);

            printf("Escolha o número do território defensor: ");
            scanf("%d", &def);

            // validações
            if (atq < 1 || atq > qtd || def < 1 || def > qtd) {
                printf("Território inválido!\n");
                continue;
            }

            if (strcmp(mapa[atq - 1].cor, mapa[def - 1].cor) == 0) {
                printf("Você não pode atacar um território da mesma cor!\n");
                continue;
            }

            atacar(&mapa[atq - 1], &mapa[def - 1]);
        }

        if (opcao == 2)
            exibirTerritorios(mapa, qtd);
    }

    liberarMemoria(mapa);

    return 0;
}