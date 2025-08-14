#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct para representar um território no jogo War
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Protótipos das funções ---
void cadastrarTerritorios(Territorio** mapa, int numTerritorios);
void exibirTerritorios(Territorio* mapa, int numTerritorios);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    // Inicializa a semente para a geração de números aleatórios
    srand(time(NULL));
    
    int numTerritorios;
    Territorio* mapa = NULL; // Ponteiro para o vetor de territórios
    int opcao;

    printf("--- Simulador de Batalha de Territorios do War ---\n");
    printf("Quantos territorios voce deseja criar? ");
    scanf("%d", &numTerritorios);
    // Limpa o buffer do teclado após a leitura do número
    while (getchar() != '\n');
    
    // Aloca dinamicamente o vetor de territórios usando calloc
    mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Chama a função para cadastrar os territórios
    cadastrarTerritorios(&mapa, numTerritorios);
    
    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Exibir todos os territorios\n");
        printf("2. Simular um ataque\n");
        printf("3. Sair do programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        // Limpa o buffer do teclado após a leitura da opção
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                exibirTerritorios(mapa, numTerritorios);
                break;
            case 2:
                // Valida se há pelo menos dois territórios para o ataque
                if (numTerritorios < 2) {
                    printf("Nao ha territorios suficientes para simular um ataque.\n");
                } else {
                    int atacante_idx, defensor_idx;
                    
                    // Exibe os territórios para o usuário escolher
                    exibirTerritorios(mapa, numTerritorios);
                    
                    // Lógica para o usuário escolher os territórios atacante e defensor
                    do {
                        printf("\nEscolha o numero do territorio atacante (1 a %d): ", numTerritorios);
                        scanf("%d", &atacante_idx);
                        printf("Escolha o numero do territorio defensor (1 a %d): ", numTerritorios);
                        scanf("%d", &defensor_idx);
                        
                        // Ajusta os índices para acessar o vetor (0-based)
                        atacante_idx--;
                        defensor_idx--;
                        
                        // Valida se os índices estão dentro dos limites e se os territórios pertencem a cores diferentes
                        if (atacante_idx < 0 || atacante_idx >= numTerritorios ||
                            defensor_idx < 0 || defensor_idx >= numTerritorios) {
                            printf("Erro: Indice de territorio invalido. Tente novamente.\n");
                        } else if (atacante_idx == defensor_idx) {
                            printf("Erro: Um territorio nao pode atacar a si mesmo. Tente novamente.\n");
                        } else if (strcmp(mapa[atacante_idx].cor, mapa[defensor_idx].cor) == 0) {
                            printf("Erro: Nao eh possivel atacar um territorio da sua propria cor. Tente novamente.\n");
                        } else {
                            // Chama a função de ataque com os ponteiros para os territórios
                            atacar(&mapa[atacante_idx], &mapa[defensor_idx]);
                            break; // Sai do loop de escolha
                        }
                    } while (1);
                }
                break;
            case 3:
                printf("Saindo do programa. Memoria sera liberada.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 3);
    
    // Libera a memória alocada dinamicamente
    liberarMemoria(mapa);
    
    return 0;
}

/**
 * @brief Cadastra os dados de cada território.
 * * @param mapa O ponteiro para o ponteiro do vetor de territórios.
 * @param numTerritorios O número total de territórios.
 */
void cadastrarTerritorios(Territorio** mapa, int numTerritorios) {
    printf("\n--- Cadastro de Territorios ---\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Dados do territorio %d:\n", i + 1);
        printf("Nome: ");
        // Le o nome do território, incluindo espaços
        fgets((*mapa)[i].nome, sizeof((*mapa)[i].nome), stdin);
        // Remove o caractere de nova linha
        (*mapa)[i].nome[strcspn((*mapa)[i].nome, "\n")] = 0;

        printf("Cor do exercito: ");
        fgets((*mapa)[i].cor, sizeof((*mapa)[i].cor), stdin);
        (*mapa)[i].cor[strcspn((*mapa)[i].cor, "\n")] = 0;

        printf("Numero de tropas: ");
        scanf("%d", &(*mapa)[i].tropas);
        while (getchar() != '\n');
        printf("\n");
    }
}

/**
 * @brief Exibe os dados de todos os territórios cadastrados.
 * * @param mapa O ponteiro para o vetor de territórios.
 * @param numTerritorios O número total de territórios.
 */
void exibirTerritorios(Territorio* mapa, int numTerritorios) {
    printf("\n--- Territorios Atuais ---\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", (mapa + i)->nome);
        printf("  Cor: %s\n", (mapa + i)->cor);
        printf("  Tropas: %d\n", (mapa + i)->tropas);
    }
}

/**
 * @brief Simula um ataque entre dois territórios.
 * * O atacante e o defensor "rolam um dado" de 1 a 6.
 * Se o atacante vencer, o território defensor muda de dono e perde metade das tropas.
 * Se o defensor vencer (ou for empate), o atacante perde 1 tropa.
 * * @param atacante O ponteiro para o território que está atacando.
 * @param defensor O ponteiro para o território que está defendendo.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- Simulação de Ataque ---\n");
    printf("Territorio atacante: %s (%s, %d tropas)\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Territorio defensor: %s (%s, %d tropas)\n", defensor->nome, defensor->cor, defensor->tropas);

    // Simula a rolagem de dados
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nRolagem de dados:\n");
    printf("  Atacante tirou: %d\n", dadoAtacante);
    printf("  Defensor tirou: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");
        // O atacante toma o território defensor
        strcpy(defensor->cor, atacante->cor);
        // Transfere metade das tropas do defensor para o atacante
        int tropasTransferidas = defensor->tropas / 2;
        defensor->tropas -= tropasTransferidas;
        atacante->tropas += tropasTransferidas;
        printf("O territorio %s agora pertence a cor %s.\n", defensor->nome, defensor->cor);
        printf("O territorio %s perdeu %d tropas e %s ganhou %d tropas.\n", defensor->nome, tropasTransferidas, atacante->nome, tropasTransferidas);
    } else {
        printf("\nO defensor venceu ou empatou.\n");
        // O atacante perde 1 tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("O territorio atacante %s perdeu 1 tropa.\n", atacante->nome);
        } else {
            printf("O territorio atacante %s nao tinha tropas suficientes para perder.\n", atacante->nome);
        }
    }

    printf("\n--- Dados atualizados apos o ataque ---\n");
    printf("Territorio Atacante: %s (%s, %d tropas)\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Territorio Defensor: %s (%s, %d tropas)\n", defensor->nome, defensor->cor, defensor->tropas);
}

/**
 * @brief Libera a memória alocada dinamicamente para o vetor de territórios.
 * * @param mapa O ponteiro para o vetor de territórios a ser liberado.
 */
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("Memoria liberada com sucesso.\n");
    }
}