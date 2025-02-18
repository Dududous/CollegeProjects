Trabalho de Programação - Processador RAMSES
Este repositório contém a implementação do trabalho de programação para a disciplina Arquitetura e Organização de Computadores I da UFRGS. O objetivo é desenvolver um programa em Assembly para o processador RAMSES, capaz de criar, manipular e calcular propriedades de uma matriz quadrada.

📋 Descrição Geral
O programa realiza as seguintes etapas:

Construção da Matriz: Cria uma matriz quadrada de ordem N x N na memória, com valores calculados por uma fórmula específica.

Transformações na Matriz: Realiza operações como troca de linhas, soma ou subtração entre linhas, conforme especificado em uma lista de transformações.

Cálculo da Diagonal Principal: Calcula o somatório dos elementos da diagonal principal da matriz.

Regras e Restrições
O valor de N (ordem da matriz) será fornecido no endereço 254 da memória e pode variar entre 2 e 5.

A matriz e as variáveis devem ser armazenadas nos endereços entre 0 (H00) e 247 (HF7).

As transformações são especificadas nos endereços entre 248 (HF8) e 253 (HFD).

O resultado final (somatório da diagonal principal) deve ser escrito no endereço 255 (HFF).

Este trabalho foi desenvolvido como parte das atividades acadêmicas da disciplina Arquitetura e Organização de Computadores I da UFRGS.
