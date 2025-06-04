#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM_NOME 100
#define TAM_TELEFONE 20
#define TAM_DESCRICAO 200
#define TAM_TIPO 50
#define TAM_CIDADE 200
#define TAM_DATA 3
#define TAM_ANO 5
#define TAM_COORDENADA 30
#define ARQUIVO "dados.txt"
#define RAIO_MAX_KM 10.0
#define PI 3.14159265358979323846
#define R_EARTH_KM 6371.0

typedef struct {
    char nome[TAM_NOME];
    char telefone[TAM_TELEFONE];
    char descricao[TAM_DESCRICAO];
    char tipo[TAM_TIPO];
    char cidade[TAM_CIDADE];
    char dia[TAM_DATA];
    char mes[TAM_DATA];
    char ano[TAM_ANO];
    char latitude[TAM_COORDENADA];
    char longitude[TAM_COORDENADA];
} Entrada;

void remover_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

double graus_para_radianos(double grau) {
    return grau * PI / 180.0;
}

double calcular_distancia(double lat1, double lon1, double lat2, double lon2) {
    lat1 = graus_para_radianos(lat1);
    lon1 = graus_para_radianos(lon1);
    lat2 = graus_para_radianos(lat2);
    lon2 = graus_para_radianos(lon2);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = pow(sin(dlat / 2), 2) +
               cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R_EARTH_KM * c;
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
        "Data: %s/%s/%s\n"
        "Latitude: %s\n"
        "Longitude: %s\n"
        "---\n",
        relato.nome,
        relato.telefone,
        relato.cidade,
        relato.tipo,
        relato.descricao,
        relato.dia,
        relato.mes,
        relato.ano,
        relato.latitude,
        relato.longitude
    );

    fclose(arquivo);
    printf("Dados adicionados com sucesso em '%s'.\n\n", ARQUIVO);
    return 0;
}

void ler_relatos_com_filtro() {
    double user_lat, user_lon;
    printf("Digite sua latitude: ");
    scanf("%lf", &user_lat);
    printf("Digite sua longitude: ");
    scanf("%lf", &user_lon);
    getchar();  // limpa o \n do buffer

    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Nenhum relato encontrado.\n");
        return;
    }

    char linha[512];
    Entrada relato;
    int dentro_do_bloco = 0;
    int mostrar = 0;
    double lat_relato, lon_relato;

    printf("\nRelatos encontrados ate 10km:\n\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strncmp(linha, "Nome: ", 6) == 0) {
            strcpy(relato.nome, linha + 6);
            remover_newline(relato.nome);
            dentro_do_bloco = 1;
        } else if (strncmp(linha, "Telefone: ", 10) == 0) {
            strcpy(relato.telefone, linha + 10);
            remover_newline(relato.telefone);
        } else if (strncmp(linha, "Cidade: ", 8) == 0) {
            strcpy(relato.cidade, linha + 8);
            remover_newline(relato.cidade);
        } else if (strncmp(linha, "Desastre: ", 10) == 0) {
            strcpy(relato.tipo, linha + 10);
            remover_newline(relato.tipo);
        } else if (strncmp(linha, "Descricao: ", 11) == 0) {
            strcpy(relato.descricao, linha + 11);
            remover_newline(relato.descricao);
        } else if (strncmp(linha, "Data: ", 6) == 0) {
            sscanf(linha + 6, "%2s/%2s/%4s", relato.dia, relato.mes, relato.ano);
        } else if (strncmp(linha, "Latitude: ", 10) == 0) {
            strcpy(relato.latitude, linha + 10);
            remover_newline(relato.latitude);
        } else if (strncmp(linha, "Longitude: ", 11) == 0) {
            strcpy(relato.longitude, linha + 11);
            remover_newline(relato.longitude);
        } else if (strncmp(linha, "---", 3) == 0 && dentro_do_bloco) {
            lat_relato = atof(relato.latitude);
            lon_relato = atof(relato.longitude);
            double distancia = calcular_distancia(user_lat, user_lon, lat_relato, lon_relato);

            if (distancia <= RAIO_MAX_KM) {
                mostrar = 1;
            }

            if (mostrar) {
                printf("Nome: %s\nTelefone: %s\nCidade: %s\nDesastre: %s\nDescricao: %s\nData: %s/%s/%s\nLatitude: %s\nLongitude: %s\n\n",
                    relato.nome, relato.telefone, relato.cidade, relato.tipo, relato.descricao,
                    relato.dia, relato.mes, relato.ano, relato.latitude, relato.longitude);
            }

            mostrar = 0;
            dentro_do_bloco = 0;
        }
    }

    fclose(arquivo);
    printf("Fim da listagem.\n\n");
}

void adicionar_relato() {
    Entrada relato;

    printf("Digite seu nome: ");
    fgets(relato.nome, sizeof(relato.nome), stdin);
    remover_newline(relato.nome);

    printf("Digite seu telefone: ");
    fgets(relato.telefone, sizeof(relato.telefone), stdin);
    remover_newline(relato.telefone);

    printf("Digite a cidade onde ocorreu o desastre: ");
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
    getchar();

    printf("Digite a latitude: ");
    fgets(relato.latitude, sizeof(relato.latitude), stdin);
    remover_newline(relato.latitude);

    printf("Digite a longitude: ");
    fgets(relato.longitude, sizeof(relato.longitude), stdin);
    remover_newline(relato.longitude);

    salvar_relatos(relato);
}

int main() {
    int opcao;

    do {
        printf("==== MENU ====\n");
        printf("1 - Adicionar novo relato\n");
        printf("2 - Ver relatos ate 10km\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // consome \n

        switch (opcao) {
            case 1:
                adicionar_relato();
                break;
            case 2:
                ler_relatos_com_filtro();
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
