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

// --- Estrutura de Dados ---
// Definição da estrutura Territorio
typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
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

// Função para exibir os territórios
void exibirTerritorios(Territorio* mapa, int quantidade) {
    printf("\n--- Territórios ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n\n", mapa[i].tropas);
    }
}

// Função de ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não é possível atacar um território da mesma cor.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1; //gera um número inteiro aleatório entre 1 e 6
    int dadoDefensor = rand() % 6 + 1; //gera um número inteiro aleatório entre 1 e 6

    printf("\nAtaque de %s (%s) contra %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: Vitória do atacante!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Resultado: Defesa bem sucedida! O atacante perdeu 1 tropa.\n");
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

// Funções de setup e gerenciamento de memória:
// Função para liberar a memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}
// Função para efetuar limpeza do buffer
void limparBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    
    //DESAFIO NÍVEL AVENTUREIRO

    srand(time(NULL)); // inicializa o gerador de números aleatórios

    int quantidade;
    printf("Qual o número de territórios a serem cadastrados? ");
    scanf("%d", &quantidade);

    // Alocação dinâmica de memória para os territórios
    Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));

   //Verifica se a alocação de memória deu certo 
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);
    exibirTerritorios(mapa, quantidade);

    char continuar;
    do {
        int iAtacante, iDefensor;

        printf("\nEscolha o número do território atacante (1 a %d): ", quantidade);
        scanf("%d", &iAtacante);
        printf("Escolha o número do território defensor (1 a %d): ", quantidade);
        scanf("%d", &iDefensor);

        if (iAtacante < 1 || iAtacante > quantidade || iDefensor < 1 || iDefensor > quantidade) {
            printf("Numero do território inválido.\n");
        } else {
            atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
            exibirTerritorios(mapa, quantidade);
        }        
            printf("Deseja realizar outro ataque? (s/n): ");
            scanf(" %c", &continuar);
        
    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa);
    limparBufferEntrada();
    return 0;


}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.


// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
