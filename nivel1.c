#include <stdio.h>
#include <string.h>

/* 
   Definição da struct Territorio
   Agrupa informações relacionadas a um território:
   - nome: nome do território
   - cor: cor do exército que ocupa o território
   - tropas: quantidade de tropas naquele território
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Vetor de structs para armazenar 5 territórios
    Territorio territorios[5];

    // Entrada dos dados
    for(int i = 0; i < 5; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome);  // Lê string sem espaços

        printf("Digite a cor do exército: ");
        scanf("%s", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\n\n===== LISTA DE TERRITÓRIOS CADASTRADOS =====\n");

    for(int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
