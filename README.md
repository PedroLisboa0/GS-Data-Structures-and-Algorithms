# Sistema de Relatos de Desastres Naturais

Este projeto é um sistema simples em C desenvolvido para Global Solution de Data Structures and Algorithms. O sistema registra e consulta relatos de desastres naturais. Os relatos são armazenados em um arquivo de texto (`dados.txt`). O programa permite adicionar relatos e consultar relatos próximos (até 10 km) da localização informada pelo usuário.

## Funcionalidades

- **Adicionar novo relato:** O usuário informa nome, telefone, cidade, tipo e descrição do desastre, data, latitude e longitude.
- **Consultar relatos próximos:** O usuário informa sua latitude e longitude, e o programa exibe relatos cadastrados até um raio de 10 km.

## Como funciona

O programa armazena os relatos em texto, cada um com as informações completas. Para consultar, ele lê os relatos, calcula a distância geográfica e exibe apenas os relatos próximos.

## Exemplo de uso

Ao executar o programa, será exibido o menu:

```
==== MENU ====
1 - Adicionar novo relato
2 - Ver relatos ate 10km
0 - Sair
Escolha uma opcao:
```

### Exemplo de Adição de Relato

```
Digite seu nome: João Silva
Digite seu telefone: 11999999999
Digite a cidade onde ocorreu o desastre: São Paulo
Digite o tipo de desastre: Enchente
Digite a descricao do desastre: Alagamento na rua principal.
Digite a data do desastre (dd mm aaaa): 02 03 2025
Digite a latitude: -23.5505
Digite a longitude: -46.6333
Dados adicionados com sucesso em 'dados.txt'.
```

### Exemplo de Consulta de Relatos

```
Digite sua latitude: -23.5500
Digite sua longitude: -46.6300

Relatos encontrados ate 10km:

Nome: João Silva
Telefone: 11999999999
Cidade: São Paulo
Desastre: Enchente
Descricao: Alagamento na rua principal.
Data: 02/03/2025
Latitude: -23.5505
Longitude: -46.6333

Fim da listagem.
```