#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Definição de Estruturas e Constantes ---
#define NUM_TERRITORIOS 10
#define NUM_MISSOES 5
#define NUM_JOGADORES 2

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
void inicializarJogo(Territorio* mapa, char** missoesJogadores);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
void exibirMissao(const char* missao);
int verificarMissao(const char* missao, Territorio* mapa, int tamanho, const char* corJogador);
void exibirMapa(const Territorio* mapa, int tamanho);
void atacar(Territorio* atacante, Territorio* defensor);
void exibirVencedor(const char* corVencedor, const char* missao);
void liberarMemoria(Territorio* mapa, char** missoesJogadores);

// --- Função Principal ---
int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Alocação de memória para o mapa
    Territorio* mapa = (Territorio*)calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria para o mapa!\n");
        return 1;
    }

    // Vetor de ponteiros para as missões dos jogadores
    // Cada jogador terá sua missão armazenada dinamicamente
    char** missoesJogadores = (char**)malloc(NUM_JOGADORES * sizeof(char*));
    if (missoesJogadores == NULL) {
        printf("Erro ao alocar memoria para as missoes dos jogadores!\n");
        free(mapa);
        return 1;
    }
    
    // Aloca a memória para as strings das missões
    for (int i = 0; i < NUM_JOGADORES; i++) {
        missoesJogadores[i] = (char*)malloc(100 * sizeof(char)); // Tamanho suficiente para a missão
        if (missoesJogadores[i] == NULL) {
            printf("Erro ao alocar memoria para a missao do jogador %d!\n", i);
            liberarMemoria(mapa, missoesJogadores);
            return 1;
        }
    }

    // Inicializa o jogo e atribui as missões
    inicializarJogo(mapa, missoesJogadores);

    // Exibe as missões para cada jogador
    printf("--- MISSAO DOS JOGADORES ---\n");
    printf("Jogador 1 (Azul): ");
    exibirMissao(missoesJogadores[0]);
    printf("Jogador 2 (Vermelho): ");
    exibirMissao(missoesJogadores[1]);
    printf("---------------------------\n\n");

    int jogadorAtual = 0;
    int vencedor = -1;

    // Loop principal do jogo
    while (vencedor == -1) {
        // Exibe o mapa no início do turno
        printf("--- TURNO DO JOGADOR %d (%s) ---\n", jogadorAtual + 1, (jogadorAtual == 0) ? "Azul" : "Vermelho");
        exibirMapa(mapa, NUM_TERRITORIOS);

        // Simula um ataque
        // A lógica de ataque é simplificada para este exemplo.
        // O jogador 1 sempre ataca o território 5 a partir do 0.
        // O jogador 2 sempre ataca o território 4 a partir do 9.
        int indiceAtacante, indiceDefensor;
        
        if (jogadorAtual == 0) { // Jogador Azul
            indiceAtacante = 0;
            indiceDefensor = 5;
            printf("Jogador Azul ataca de %s (%d tropas) contra %s (%d tropas).\n", 
                   mapa[indiceAtacante].nome, mapa[indiceAtacante].tropas, 
                   mapa[indiceDefensor].nome, mapa[indiceDefensor].tropas);
        } else { // Jogador Vermelho
            indiceAtacante = 9;
            indiceDefensor = 4;
            printf("Jogador Vermelho ataca de %s (%d tropas) contra %s (%d tropas).\n",
                   mapa[indiceAtacante].nome, mapa[indiceAtacante].tropas,
                   mapa[indiceDefensor].nome, mapa[indiceDefensor].tropas);
        }
        
        // Valida se o ataque é contra um território inimigo
        if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) != 0) {
            atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
        } else {
            printf("Ataque invalido: nao e possivel atacar um territorio aliado.\n");
        }
        
        printf("\n--- RESULTADO DO ATAQUE ---\n");
        exibirMapa(mapa, NUM_TERRITORIOS);
        printf("---------------------------\n\n");

        // Verifica silenciosamente se a missão do jogador atual foi cumprida
        if (verificarMissao(missoesJogadores[jogadorAtual], mapa, NUM_TERRITORIOS, (jogadorAtual == 0) ? "Azul" : "Vermelho")) {
            vencedor = jogadorAtual;
            printf("--- MISSAO CUMPRIDA! ---\n");
            exibirVencedor((jogadorAtual == 0) ? "Azul" : "Vermelho", missoesJogadores[jogadorAtual]);
        }

        // Troca de jogador
        jogadorAtual = (jogadorAtual + 1) % NUM_JOGADORES;
        printf("Pressione Enter para continuar...\n");
        getchar();
        printf("\n\n");
    }

    // Libera a memória alocada dinamicamente
    liberarMemoria(mapa, missoesJogadores);

    return 0;
}

// --- Implementação das Funções ---

/**
 * @brief Inicializa o mapa com territórios e atribui as missões aos jogadores.
 * * @param mapa Ponteiro para o vetor de territórios.
 * @param missoesJogadores Vetor de ponteiros para as missões dos jogadores.
 */
void inicializarJogo(Territorio* mapa, char** missoesJogadores) {
    // Vetor de strings com as descrições das missões
    char* missoes[] = {
        "Conquistar 5 territorios seguidos.",
        "Eliminar todas as tropas da cor vermelha.",
        "Ter um total de 10 tropas em seus territorios.",
        "Conquistar todos os territorios do norte (0, 1, 2).",
        "Conquistar o territorio 'Siberia'."
    };

    // Vetores com nomes de territórios e cores
    char* nomesTerritorios[] = {"Brasil", "Argentina", "Espanha", "Franca", "Alemanha", 
                               "Canada", "Siberia", "Japao", "Australia", "Egito"};
    char* cores[] = {"Azul", "Vermelho"};

    // Inicializa o mapa com cores e tropas
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        strcpy(mapa[i].nome, nomesTerritorios[i]);
        strcpy(mapa[i].cor, cores[i % 2]); // Alterna as cores entre Azul e Vermelho
        mapa[i].tropas = rand() % 5 + 1;    // Tropas aleatórias entre 1 e 5
    }

    // Atribui uma missão aleatória para cada jogador
    atribuirMissao(missoesJogadores[0], missoes, NUM_MISSOES);
    atribuirMissao(missoesJogadores[1], missoes, NUM_MISSOES);
}

/**
 * @brief Sorteia uma missão e a copia para a variável do jogador.
 * * @param destino Ponteiro para a string de destino (missão do jogador).
 * @param missoes Vetor de strings com todas as missões.
 * @param totalMissoes Tamanho do vetor de missões.
 */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indiceSorteado]);
}

/**
 * @brief Exibe a missão de um jogador.
 * * @param missao Ponteiro para a string da missão a ser exibida.
 */
void exibirMissao(const char* missao) {
    printf("%s\n", missao);
}

/**
 * @brief Avalia se a missão do jogador foi cumprida.
 * * @param missao Ponteiro para a string da missão.
 * @param mapa Ponteiro para o vetor de territórios.
 * @param tamanho Tamanho do vetor de territórios.
 * @param corJogador Cor do jogador atual.
 * @return 1 se a missão foi cumprida, 0 caso contrário.
 */
int verificarMissao(const char* missao, Territorio* mapa, int tamanho, const char* corJogador) {
    // Lógica simplificada de verificação de missões
    if (strstr(missao, "Conquistar 5 territorios seguidos.") != NULL) {
        int contador = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contador++;
                if (contador >= 5) {
                    return 1;
                }
            } else {
                contador = 0;
            }
        }
    } else if (strstr(missao, "Eliminar todas as tropas da cor vermelha.") != NULL) {
        if (strcmp(corJogador, "Azul") == 0) {
            for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0) {
                    return 0; // Ainda existem tropas vermelhas
                }
            }
            return 1; // Todas as tropas vermelhas foram eliminadas
        } else { // Missão não aplicável ao jogador vermelho
            return 0;
        }
    } else if (strstr(missao, "Ter um total de 10 tropas em seus territorios.") != NULL) {
        int totalTropas = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                totalTropas += mapa[i].tropas;
            }
        }
        return (totalTropas >= 10);
    } else if (strstr(missao, "Conquistar todos os territorios do norte (0, 1, 2).") != NULL) {
        return (strcmp(mapa[0].cor, corJogador) == 0 &&
                strcmp(mapa[1].cor, corJogador) == 0 &&
                strcmp(mapa[2].cor, corJogador) == 0);
    } else if (strstr(missao, "Conquistar o territorio 'Siberia'.") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].nome, "Siberia") == 0) {
                return (strcmp(mapa[i].cor, corJogador) == 0);
            }
        }
    }
    
    return 0;
}

/**
 * @brief Exibe o mapa, mostrando os territórios, suas cores e tropas.
 * * @param mapa Ponteiro para o vetor de territórios.
 * @param tamanho Tamanho do vetor de territórios.
 */
void exibirMapa(const Territorio* mapa, int tamanho) {
    printf("--- MAPA ATUAL ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] %-10s | Cor: %-8s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/**
 * @brief Simula um ataque entre dois territórios.
 * * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    // Simulação de rolagem de dados
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dados - Atacante: %d, Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Ataque bem-sucedido! %s conquistou %s.\n", atacante->nome, defensor->nome);
        // Transfere a cor e metade das tropas
        strcpy(defensor->cor, atacante->cor);
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

        // Garante que o atacante tenha no mínimo 1 tropa após a conquista
        if (atacante->tropas == 0) {
            atacante->tropas = 1;
        }

    } else {
        printf("Ataque falhou! %s perdeu uma tropa.\n", atacante->nome);
        atacante->tropas--;
        if (atacante->tropas <= 0) {
            printf("%s foi eliminado da partida por falta de tropas.\n", atacante->nome);
            // Lógica para eliminar o jogador... (simplificado neste exemplo)
        }
    }
}

/**
 * @brief Exibe a mensagem de vitória.
 * * @param corVencedor A cor do jogador vencedor.
 * @param missao A missão cumprida.
 */
void exibirVencedor(const char* corVencedor, const char* missao) {
    printf("\n--- FIM DE JOGO ---\n");
    printf("O jogador de cor %s venceu a partida!\n", corVencedor);
    printf("Ele cumpriu a seguinte missao: %s\n", missao);
    printf("-------------------\n");
}

/**
 * @brief Libera toda a memória alocada dinamicamente.
 * * @param mapa Ponteiro para o vetor de territórios.
 * @param missoesJogadores Vetor de ponteiros para as missões dos jogadores.
 */
void liberarMemoria(Territorio* mapa, char** missoesJogadores) {
    // Libera a memória de cada missão individualmente
    if (missoesJogadores != NULL) {
        for (int i = 0; i < NUM_JOGADORES; i++) {
            free(missoesJogadores[i]);
        }
        // Libera o vetor de ponteiros
        free(missoesJogadores);
    }
    // Libera a memória do mapa
    free(mapa);
    printf("Memoria liberada com sucesso.\n");
}