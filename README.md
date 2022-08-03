# 42 Labs 3º Edição
Este projeto foi desenvolvido para o desafio técnico do processo seletivo da 3º
Edição do 42 Labs. O objetivo do desafio é desenvolver uma aplicação de
monitoramento de serviços web em **C**.

## Índice

- [Features](#features)
- [Requerimentos](#requerimentos)
- [Como rodar](#como-rodar)
- [Como usar](#como-usar)
	- [monitoring.db](#monitoringdb)
	- [monitoring](#monitoring)

## Features

- Analisa o arquivo `monitoring.db` e realiza o monitoramento com bases nas
informações continas nesse arquivo
- Monitora os serviços web utilizando 3 protocolos: **HTTP**, **PING** e **DNS**
- Escreve no arquivo `monitoring.log` o log do monitoramento realizado
- Mostra uma versão simplificada do log na saída padrão do terminal
- Apresenta uma visão geral do log na saída padrão do terminal

## Requerimentos

Possuir instalado as seguintes dependências:
```txt
libcurl, dig, ping
```

## Como rodar

- Clone este repositório
- Compile o projeto com `make`
- Execute o programa `monitoring`

## Como usar

### monitoring.db

O arquivo `monitoring.db` define o que será monitorado pela aplicação, através
de uma estrutura estrita.

A estrutura é definida por linhas e colunas, onde cada linha terá as
configurações separadas por um **TAB**, que definem as colunas. Para cada
monitoramento, as configurações até a 3º coluna serão as mesmas, já a partir da
4º a configuração é específica, baseando-se no protocolo escolhido na 2º coluna.

As configurações para cada protocolo são:

| Protocolo   | Configurações                                                           |
|-------------|-------------------------------------------------------------------------|
| HTTP        | nome, protocolo, endereço, método HTTP, código HTTP esperado, intervalo |
| PING        | nome, protocolo, endereço, intervalo                                    |
| DNS         | nome, protocolo, endereço, intervalo, servidor DNS                      |

O intervalo do monitoramento é medido em **minutos**, só aceitando números
inteiros.

Abaixo, exemplo do arquivo descrito acima:

```txt
# monitoring.db

intra	HTTP	intra.42.fr	GET	200	120
game ping test	PING	game.42sp.org.br	60
workspaces monitoring	PING	workspaces.42sp.org.br	60
```

### monitoring

Ao iniciar o programa `monitoring`, ele irá ler o arquivo de configuração e
começará a monitorar os serviços.

As informações dos serviços monitorados serão armazenadas no arquivo
`monitoring.log` da seguinte maneira:

| Protocolo   | Estrutura do log                                                                                            |
|-------------|-------------------------------------------------------------------------------------------------------------|
| HTTP        | data, nome, protocolo, endereço, método HTTP, código HTTP retornado, código HTTP esperado, latência, status |
| PING        | data, nome, protocolo, endereço, latência, status                                                           |
| DNS         | data, nome, protocolo, endereçom, servidor DNS, resposta retornada, latência, status                        |

Todas as informações são separadas por um **|** entre elas.

O status será apresentado da seguinte maneira:

- **HEALTHY**: quando o serviço está saudável.
- **UNHEALTHY**: quando o serviço não está saudável.

Um serviço saudável é aquele que consegue responder a requisição do
monitoramento de forma esperada, em contrapartida ao serviço não saudável, que
não responde de forma esperada.

Será mostrado na saída padrão do terminal um breve resumo dos resultados do
monitoramento, conforme eles forem ocorrendo. Caso queria recuperar essas
informações após o término do programa, basta iniciar o programa `monitoring`
com a flag `--simplify` que ele irá mostrar novamente as informações no arquivo
`monitoring.log` de forma resumida.

Caso queria ver uma visão geral do resultado de todos os monitoramentos
realizados, inicie o programa `monitoring` com a flag `--overview`, e ele irá
mostrá-la na saída padrão do terminal, seguindo o seguinte padrão:

- Nome da requisição
- Quantidade de retornos saudáveis
- Quantidade de retornos não saudáveis
