/*
  territorios.c
  Programa simples para cadastrar 5 territórios usando struct em C.

  Funcionalidades:
  - Define a struct Territorio com nome, cor do exército e tropas.
  - Permite cadastrar 5 territórios com entrada amigável.
  - Exibe os dados de todos os territórios após o cadastro.
  - Código comentado e com funções auxiliares para clareza e manutenção.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define QTD_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10
#define LINHA_BUFFER 100

/* Estrutura que representa um território.
   - nome: nome do território (até 29 caracteres + terminador)
   - cor: cor do exército (até 9 caracteres + terminador)
   - tropas: número de tropas no território
*/
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

/* Remove '\n' do final da string lida por fgets, se existir */
void trim_newline(char *s) {
    size_t len = strlen(s);
    if (len == 0) return;
    if (s[len - 1] == '\n') s[len - 1] = '\0';
}

/* Lê uma linha de entrada do usuário para um campo de texto.
   - prompt: texto para mostrar ao usuário
   - dest: buffer destino
   - maxlen: tamanho máximo do buffer (inclui o terminador '\0')
*/
void ler_texto(const char *prompt, char *dest, size_t maxlen) {
    char buffer[LINHA_BUFFER];

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            /* Se ocorrer EOF ou erro, limpar e continuar */
            clearerr(stdin);
            printf("Erro de leitura. Tente novamente.\n");
            continue;
        }

        trim_newline(buffer);

        /* Se a string tiver comprimento 0, pedir novamente */
        if (strlen(buffer) == 0) {
            printf("Entrada não pode ser vazia. Tente novamente.\n");
            continue;
        }

        /* Copia para o destino respeitando o tamanho máximo */
        strncpy(dest, buffer, maxlen - 1);
        dest[maxlen - 1] = '\0';
        break;
    }
}

/* Lê um inteiro seguro do usuário (usa fgets + sscanf para validar) */
int ler_inteiro(const char *prompt) {
    char buffer[LINHA_BUFFER];
    int valor;
    char extra;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            clearerr(stdin);
            printf("Erro de leitura. Tente novamente.\n");
            continue;
        }

        /* tenta parsear um inteiro e verificar se há lixo extra na linha */
        if (sscanf(buffer, " %d %c", &valor, &extra) == 1) {
            if (valor < 0) {
                printf("Valor não pode ser negativo. Informe um número inteiro 0 ou maior.\n");
                continue;
            }
            return valor;
        } else {
            printf("Entrada inválida. Digite um número inteiro (ex: 42).\n");
        }
    }
}

/* Exibe os territórios em formato tabular simples */
void exibir_territorios(Territorio lista[], int quantidade) {
    printf("\n-----------------------------\n");
    printf("Territórios cadastrados:\n");
    printf("-----------------------------\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome : %s\n", lista[i].nome);
        printf("  Cor  : %s\n", lista[i].cor);
        printf("  Tropas: %d\n", lista[i].tropas);
        printf("-----------------------------\n");
    }
}

int main(void) {
    Territorio territorios[QTD_TERRITORIOS];

    printf("=== Cadastro de Territórios ===\n");
    printf("Você irá cadastrar %d territórios.\n", QTD_TERRITORIOS);
    printf("Por favor, informe o nome, a cor do exército e a quantidade de tropas.\n");
    printf("Observação: nomes e cores aceitam espaços. Apenas números inteiros para tropas.\n\n");

    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        char titulo[80];
        snprintf(titulo, sizeof(titulo), "---- Território %d de %d ----\n", i + 1, QTD_TERRITORIOS);
        printf("%s", titulo);

        /* Lê nome (com limite e evitando estouro) */
        char promptNome[100];
        snprintf(promptNome, sizeof(promptNome), "Digite o nome do território (%d): ", i + 1);
        ler_texto(promptNome, territorios[i].nome, sizeof(territorios[i].nome));

        /* Lê cor do exército */
        char promptCor[100];
        snprintf(promptCor, sizeof(promptCor), "Digite a cor do exército de \"%s\": ", territorios[i].nome);
        ler_texto(promptCor, territorios[i].cor, sizeof(territorios[i].cor));

        /* Lê quantidade de tropas (validação de inteiro não-negativo) */
        char promptTropas[100];
        snprintf(promptTropas, sizeof(promptTropas), "Digite o número de tropas em \"%s\": ", territorios[i].nome);
        territorios[i].tropas = ler_inteiro(promptTropas);

        printf("\n"); /* linha em branco entre cadastros para melhor usabilidade */
    }

    /* Após o cadastro de todos, exibe de forma clara */
    exibir_territorios(territorios, QTD_TERRITORIOS);

    printf("Cadastro concluído com sucesso.\n");
    return 0;
}
