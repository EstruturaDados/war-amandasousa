// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---

// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define TAM_STRING 30

// Definição da estrutura Territorio
typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
} Territorio;

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int tamanho);
void atacar(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
void exibirMissao(char* missao);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void liberarMemoria(Territorio* mapa, char* missao);


// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    
    //DESAFIO NÍVEL MESTRE
    srand(time(NULL));

    int qtdTerritorios;
    printf("Digite o número de territórios: ");
    scanf("%d", &qtdTerritorios);

    Territorio* mapa = malloc(qtdTerritorios * sizeof(Territorio));
    if (!mapa) {
        printf("Erro de alocação.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtdTerritorios);

    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar pelo menos 4 territórios",
        "Ter mais de 10 tropas no total",
        "Conquistar o território chamado Fortaleza"
    };

    char* missaoJogador = malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, 5);
    exibirMissao(missaoJogador);

    char continuar;
    do {
        int iA, iD;
        printf("\nEscolha o território atacante (1 a %d): ", qtdTerritorios);
        scanf("%d", &iA);
        printf("Escolha o território defensor (1 a %d): ", qtdTerritorios);
        scanf("%d", &iD);

        if (iA >= 1 && iA <= qtdTerritorios && iD >= 1 && iD <= qtdTerritorios) {
            atacar(&mapa[iA - 1], &mapa[iD - 1]);
            exibirMapa(mapa, qtdTerritorios);

            if (verificarMissao(missaoJogador, mapa, qtdTerritorios)) {
                printf("\n Missão cumprida! Você venceu!\n");
                break;
            }
        } else {
            printf("Indices inválidos.\n");
        }

        printf("Deseja continuar? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa, missaoJogador);
    return 0;

}

// Função que cadastra os territórios
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\nCadastro do território %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função que exibe os dados dos territórios
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n--- Territórios ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Território %d: %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função que realiza o ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não pode atacar território da mesma cor.\n");
        return;
    }

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\nAtaque de %s contra %s\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        printf("Vitória do atacante!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Defesa bem-sucedida. Atacante perde 1 tropa.\n");
        if (atacante->tropas > 0) atacante->tropas--;
    }
}

// Função que atribui uma missão aleatória ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Função que exibe a missão do jogador
void exibirMissao(char* missao) {
    printf("\nMissão do jogador: %s\n", missao);
}

// Função que verifica se a missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strstr(missao, "vermelha") != NULL || strstr(missao, "vermelho") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if ((strcmp(mapa[i].cor, "vermelha") == 0 || strcmp(mapa[i].cor, "vermelho") == 0 ) && mapa[i].tropas > 0) {
                return 0; // Missão não cumprida
            }
        }
        return 1; // Missão cumprida - Eliminar todas as tropas da cor vermelha
    }
    if (strstr(missao, "3 territórios") != NULL) {
        int cont = 0;
        for (int i = 0; i < tamanho - 2; i++) {
            if (strcmp(mapa[i].cor, mapa[i + 1].cor) == 0 &&
                strcmp(mapa[i].cor, mapa[i + 2].cor) == 0) {
                cont++;
            }
        }
        return cont > 0;
    }
    return 0;
}

// Função que libera memória alocada
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}


// Função para efetuar limpeza do buffer
void limparBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}


