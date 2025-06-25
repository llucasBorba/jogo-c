#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_LINHA 300
#define NUM_NIVEIS 5
#define VIDAS_INICIAIS 3

typedef enum {
    JOGAR = 1,
    SAIR = 0
} OpcaoMenu;

typedef struct {
    char *texto;
} Alternativa;

typedef struct {
    char *pergunta;
    Alternativa *alternativas;
    int qtdAlternativas;
    int indiceCorreta;
} Pergunta;

typedef struct {
    Pergunta *perguntas;
    int qtdPerguntas;
} BancoPerguntas;

// Função para converter string para minúscula
void strMinuscula(char *str) {
    for (int i = 0; str[i]; i++) str[i] = tolower(str[i]);
}

// Função para ler perguntas de um arquivo
BancoPerguntas carregarPerguntas(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    BancoPerguntas banco = {NULL, 0};
    Pergunta perguntaTemp;
    char linha[MAX_LINHA];
    perguntaTemp.pergunta = NULL;
    perguntaTemp.alternativas = NULL;
    perguntaTemp.qtdAlternativas = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strncmp(linha, "PERGUNTA:", 9) == 0) {
            if (perguntaTemp.pergunta != NULL) {
                banco.perguntas = realloc(banco.perguntas, (banco.qtdPerguntas + 1) * sizeof(Pergunta));
                banco.perguntas[banco.qtdPerguntas++] = perguntaTemp;
                perguntaTemp.alternativas = NULL;
                perguntaTemp.qtdAlternativas = 0;
            }
            perguntaTemp.pergunta = strdup(linha + 10);
            perguntaTemp.pergunta[strcspn(perguntaTemp.pergunta, "\n")] = '\0';
        } else if (strncmp(linha, "ALTERNATIVA:", 12) == 0) {
            perguntaTemp.alternativas = realloc(perguntaTemp.alternativas, (perguntaTemp.qtdAlternativas + 1) * sizeof(Alternativa));
            perguntaTemp.alternativas[perguntaTemp.qtdAlternativas].texto = strdup(linha + 13);
            perguntaTemp.alternativas[perguntaTemp.qtdAlternativas].texto[strcspn(perguntaTemp.alternativas[perguntaTemp.qtdAlternativas].texto, "\n")] = '\0';
            perguntaTemp.qtdAlternativas++;
        } else if (strncmp(linha, "CORRETA:", 8) == 0) {
            perguntaTemp.indiceCorreta = atoi(linha + 9);
        }
    }

    if (perguntaTemp.pergunta != NULL) {
        banco.perguntas = realloc(banco.perguntas, (banco.qtdPerguntas + 1) * sizeof(Pergunta));
        banco.perguntas[banco.qtdPerguntas++] = perguntaTemp;
    }

    fclose(arquivo);
    return banco;
}

void liberarBanco(BancoPerguntas banco) {
    for (int i = 0; i < banco.qtdPerguntas; i++) {
        free(banco.perguntas[i].pergunta);
        for (int j = 0; j < banco.perguntas[i].qtdAlternativas; j++) {
            free(banco.perguntas[i].alternativas[j].texto);
        }
        free(banco.perguntas[i].alternativas);
    }
    free(banco.perguntas);
}

void jogar() {
    int nivelAtual = 1;
    int pontos = 0;
    int vidas = VIDAS_INICIAIS;
    srand(time(NULL));

    while (nivelAtual <= NUM_NIVEIS && vidas > 0) {
        char nomeArquivo[20];
        sprintf(nomeArquivo, "nivel%d.txt", nivelAtual);
        BancoPerguntas banco = carregarPerguntas(nomeArquivo);

        printf("\n=== NÍVEL %d ===\n", nivelAtual);

        int indicePergunta = rand() % banco.qtdPerguntas;
        Pergunta p = banco.perguntas[indicePergunta];

        printf("\n%s\n", p.pergunta);
        for (int i = 0; i < p.qtdAlternativas; i++) {
            printf("  [%d] %s\n", i, p.alternativas[i].texto);
        }

        printf("Sua resposta (digite o número): ");
        int resposta;
        scanf("%d", &resposta);
        getchar(); // limpa o \n do buffer

        if (resposta == p.indiceCorreta) {
            printf("✅ Resposta correta!\n");
            pontos += nivelAtual * 10;
            nivelAtual++;
        } else {
            printf("❌ Resposta incorreta. Resposta certa: [%d] %s\n", p.indiceCorreta, p.alternativas[p.indiceCorreta].texto);
            vidas--;
        }

        printf("Pontos: %d | Vidas restantes: %d\n", pontos, vidas);
        liberarBanco(banco);
    }

    if (vidas <= 0) {
        printf("\n💀 Game Over! Você perdeu todas as vidas. Pontos finais: %d\n", pontos);
    } else {
        printf("\n🎉 Parabéns! Você venceu o jogo com %d pontos!\n", pontos);
    }
}

int main() {
    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("[1] Jogar\n");
        printf("[0] Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch ((OpcaoMenu)opcao) {
            case JOGAR:
                jogar();
                break;
            case SAIR:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != SAIR);

    return 0;
}
