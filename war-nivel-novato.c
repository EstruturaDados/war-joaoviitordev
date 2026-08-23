// ============================================================================
//         PROJETO WAR ESTRUTURADO - NIVEL NOVATO
//         Cadastro Inicial dos Territorios
// ============================================================================
//
// OBJETIVOS:
// - Criar uma struct chamada Territorio.
// - Armazenar 5 territorios em um vetor estatico.
// - Cadastrar nome, cor do exercito e numero de tropas via terminal.
// - Exibir o estado atual do mapa de forma organizada.
//
// Compilar: gcc -Wall -Wextra -std=c11 war-novato.c -o war-novato
// ============================================================================

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

// --- Constantes Globais ---
#define TERRITORIOS 5   // Quantidade fixa de territorios do mapa
#define TAM_NOME    30  // Tamanho maximo do nome do territorio
#define TAM_COR     10  // Tamanho maximo do nome da cor do exercito

// --- Estrutura de Dados ---
// Representa um territorio do mapa: quem ele e, quem o domina e com quantas tropas.
struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int  tropas;
};

// --- Prototipos das Funcoes ---
void limparBufferEntrada(void);
void lerTexto(const char *rotulo, char *destino, int tamanho);
int  lerInteiro(const char *rotulo);
void cadastrarTerritorios(struct Territorio *mapa, int total);
void exibirMapa(const struct Territorio *mapa, int total);

// --- Funcao Principal (main) ---
int main(void) {
#ifdef _WIN32
    // Garante que os acentos apareçam corretamente no terminal do Windows.
    SetConsoleOutputCP(CP_UTF8);
#endif

    // Vetor estatico: os 5 territorios vivem na pilha, sem malloc/free.
    struct Territorio mapa[TERRITORIOS];

    printf("========================================\n");
    printf("   WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("========================================\n");
    printf("Cadastre os %d territórios do mapa.\n", TERRITORIOS);

    cadastrarTerritorios(mapa, TERRITORIOS);
    exibirMapa(mapa, TERRITORIOS);

    return 0;
}

// --- Implementacao das Funcoes ---

// limparBufferEntrada():
// Descarta o que sobrou no buffer do teclado (stdin) ate o fim da linha.
// Evita que um '\n' pendente de um scanf anterior seja consumido pelo proximo fgets.
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // apenas descarta
    }
}

// lerTexto():
// Le uma linha de texto com fgets (seguro, respeita o tamanho do buffer) e
// remove o '\n' final. Se o usuario digitar mais do que cabe, o excedente
// e descartado para nao contaminar a proxima leitura.
void lerTexto(const char *rotulo, char *destino, int tamanho) {
    printf("%s", rotulo);

    if (fgets(destino, tamanho, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }

    size_t len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n') {
        destino[len - 1] = '\0';   // troca o '\n' pelo terminador nulo
    } else {
        limparBufferEntrada();     // a linha era maior que o buffer
    }
}

// lerInteiro():
// Le um numero inteiro com scanf, valida a leitura e sempre limpa o buffer
// depois - caso contrario o '\n' deixado pelo scanf quebraria o proximo fgets.
int lerInteiro(const char *rotulo) {
    int valor = 0;
    int lido  = 0;

    do {
        printf("%s", rotulo);
        lido = scanf("%d", &valor);
        limparBufferEntrada();

        if (lido != 1 || valor < 0) {
            printf("  [!] Valor inválido. Digite um número inteiro maior ou igual a 0.\n");
            lido = 0;
        }
    } while (lido != 1);

    return valor;
}

// cadastrarTerritorios():
// Preenche o vetor de territorios com os dados digitados pelo usuario.
// Recebe o mapa por referencia (ponteiro), pois precisa modifica-lo.
void cadastrarTerritorios(struct Territorio *mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\n--- Território %d de %d ---\n", i + 1, total);
        lerTexto("Nome do território: ", mapa[i].nome, TAM_NOME);
        lerTexto("Cor do exército...: ", mapa[i].cor,  TAM_COR);
        mapa[i].tropas = lerInteiro("Número de tropas..: ");
    }
}

// exibirMapa():
// Mostra o estado atual de todos os territorios em forma de tabela.
// O 'const' garante que a funcao apenas le o mapa, sem alterar nada.
void exibirMapa(const struct Territorio *mapa, int total) {
    printf("\n==================================================\n");
    printf("             ESTADO ATUAL DO MAPA\n");
    printf("==================================================\n");
    // Titulos acentuados ocupam 1 byte a mais em UTF-8 do que letras, e o printf
    // conta bytes ao preencher a largura - dai o +1 nas colunas do cabecalho.
    printf("%-4s %-21s %-13s %8s\n", "N.", "TERRITÓRIO", "EXÉRCITO", "TROPAS");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%-4d %-20s %-12s %8d\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }

    printf("==================================================\n");
}
