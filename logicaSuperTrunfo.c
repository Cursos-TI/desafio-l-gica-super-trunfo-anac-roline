#include <stdio.h>
#include <string.h>

// Estrutura para representar uma carta de cidade
struct Carta {
    char estado[50];
    char codigo[20];
    char nome[50];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
};

int main() {
    struct Carta carta1, carta2;

    // --- Cadastro da Primeira Carta ---
    printf("--- Cadastro da Primeira Carta (Cidade 1) ---\n");
    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]s", carta1.nome);
    printf("Digite o estado: ");
    scanf(" %[^\n]s", carta1.estado);
    printf("Digite o codigo da carta: ");
    scanf(" %[^\n]s", carta1.codigo);
    printf("Digite a populacao (em numero): ");
    scanf("%d", &carta1.populacao);
    printf("Digite a area (em km2): ");
    scanf("%f", &carta1.area);
    printf("Digite o PIB (em milhoes): ");
    scanf("%f", &carta1.pib);
    printf("Digite o numero de pontos turisticos: ");
    scanf("%d", &carta1.pontos_turisticos);

    printf("\n");

    // --- Cadastro da Segunda Carta ---
    printf("--- Cadastro da Segunda Carta (Cidade 2) ---\n");
    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]s", carta2.nome);
    printf("Digite o estado: ");
    scanf(" %[^\n]s", carta2.estado);
    printf("Digite o codigo da carta: ");
    scanf(" %[^\n]s", carta2.codigo);
    printf("Digite a populacao (em numero): ");
    scanf("%d", &carta2.populacao);
    printf("Digite a area (em km2): ");
    scanf("%f", &carta2.area);
    printf("Digite o PIB (em milhoes): ");
    scanf("%f", &carta2.pib);
    printf("Digite o numero de pontos turisticos: ");
    scanf("%d", &carta2.pontos_turisticos);
    
    // --- Exibição das Cartas Cadastradas ---
    printf("\n==================================================\n");
    printf("               Cartas Cadastradas\n");
    printf("==================================================\n");

    printf("\n### Cidade 1 ###\n");
    printf("Nome: %s\n", carta1.nome);
    printf("Estado: %s\n", carta1.estado);
    printf("Codigo: %s\n", carta1.codigo);
    printf("Populacao: %d habitantes\n", carta1.populacao);
    printf("Area: %.2f km2\n", carta1.area);
    printf("PIB: R$ %.2f milhoes\n", carta1.pib);
    printf("Pontos Turisticos: %d\n", carta1.pontos_turisticos);

    printf("\n### Cidade 2 ###\n");
    printf("Nome: %s\n", carta2.nome);
    printf("Estado: %s\n", carta2.estado);
    printf("Codigo: %s\n", carta2.codigo);
    printf("Populacao: %d habitantes\n", carta2.populacao);
    printf("Area: %.2f km2\n", carta2.area);
    printf("PIB: R$ %.2f milhoes\n", carta2.pib);
    printf("Pontos Turisticos: %d\n", carta2.pontos_turisticos);

    // --- Comparação e Exibição do Resultado ---
    printf("\n==================================================\n");
    printf("           Resultado da Comparacao\n");
    printf("==================================================\n");
    printf("Comparando pelo atributo: Populacao\n");

    if (carta1.populacao > carta2.populacao) {
        printf("\n🎉 A carta de %s venceu!\n", carta1.nome);
    } else if (carta2.populacao > carta1.populacao) {
        printf("\n🎉 A carta de %s venceu!\n", carta2.nome);
    } else {
        printf("\n🤝 A partida terminou em empate!\n");
    }

    return 0;
}