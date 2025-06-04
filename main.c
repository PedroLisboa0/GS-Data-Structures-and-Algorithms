#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 100
#define TAM_TELEFONE 20
#define TAM_DESCRICAO 200
#define TAM_TIPO 50
#define TAM_CIDADE 200
#define TAM_DATA 3
#define TAM_ANO 5
#define ARQUIVO "dados.txt"

typedef struct {
    char nome[TAM_NOME];
    char telefone[TAM_TELEFONE];      
    char descricao[TAM_DESCRICAO];
    char tipo[TAM_TIPO];       
    char cidade[TAM_CIDADE];
    char dia[TAM_DATA];          
    char mes[TAM_DATA];          
    char ano[TAM_ANO];          
} Entrada;

void remover_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int salvar_relatos(Entrada relato) {
    FILE *arquivo = fopen(ARQUIVO, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo,
        "Nome: %s\n"
        "Telefone: %s\n"
        "Cidade: %s\n"
        "Desastre: %s\n"
        "Descricao: %s\n"
        "Data: %s/%s/%s\n\n",
        relato.nome,
        relato.telefone,
        relato.cidade,
        relato.tipo,
        relato.descricao,
        relato.dia,
        relato.mes,
        relato.ano
    );

    fclose(arquivo);
    printf("Dados adicionados com sucesso em %s!\n", ARQUIVO);
    return 0;
}

int main() {
    Entrada relato;

    printf("Digite seu nome: ");
    fgets(relato.nome, sizeof(relato.nome), stdin);
    remover_newline(relato.nome);

    printf("Digite seu telefone: ");
    fgets(relato.telefone, sizeof(relato.telefone), stdin);
    remover_newline(relato.telefone);

    printf("Digite a cidade em que o desastre ocorreu: ");
    fgets(relato.cidade, sizeof(relato.cidade), stdin);
    remover_newline(relato.cidade);

    printf("Digite o tipo de desastre: ");
    fgets(relato.tipo, sizeof(relato.tipo), stdin);
    remover_newline(relato.tipo);

    printf("Digite a descricao do desastre: ");
    fgets(relato.descricao, sizeof(relato.descricao), stdin);
    remover_newline(relato.descricao);

    printf("Digite a data do desastre (dd mm aaaa): ");
    scanf("%2s %2s %4s", relato.dia, relato.mes, relato.ano);

    salvar_relatos(relato);
    return 0;
}
