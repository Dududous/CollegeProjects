Este repositório contém a implementação do trabalho de programação para o computador Ahmes, desenvolvido como parte da disciplina Arquitetura e Organização de Computadores I da UFRGS. O objetivo é criar um programa em Assembly que realize cálculos matemáticos específicos utilizando variáveis alocadas em endereços de memória predefinidos.

📋 Especificações Gerais
O programa realiza os seguintes cálculos:

• A = (x+y)*z 
• B = inteiro(A/2n) 
• Se z ≠ 0, então C = inteiro((x-y)/z). Se z = 0, então C = 1 
• Se z ≠ 0, então D = resto((x-y)/z). Se z = 0, então D = 0 Sendo: • x, y, z, n, C, D: variáveis de 1 byte 

Variáveis e Endereços
Variáveis de entrada:

x (1 byte): endereço 128

y (1 byte): endereço 130

z (1 byte): endereço 131

n (1 byte): endereço 132

Variáveis de saída:

A (2 bytes): endereços 133 (a1) e 134 (a0)

B (2 bytes): endereços 135 (b1) e 136 (b0)

C (1 byte): endereço 137

D (1 byte): endereço 138

Regras Importantes
O programa deve iniciar no endereço 0 da memória.

As variáveis de entrada não podem ser alteradas diretamente.

Variáveis temporárias ou constantes devem ser alocadas a partir do endereço 138.

Todas as variáveis alteradas durante o programa devem ser inicializadas pelo próprio código.

🚀 Como Executar
Escreva o programa em Assembly utilizando o editor/montador Daedalus.

Compile o programa para gerar o arquivo .mem.

Carregue o arquivo .mem no simulador do computador Ahmes.

Insira os valores de entrada nos endereços especificados.

Execute o programa e verifique os resultados nos endereços de saída.

Este trabalho foi desenvolvido como parte das atividades acadêmicas da disciplina Introdução à Arquitetura e Organização de Computadores da UFRGS.

