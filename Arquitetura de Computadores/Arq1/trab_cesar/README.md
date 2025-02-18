Trabalho de Programação - Processador CESAR16i
Este repositório contém a implementação do trabalho de programação para a disciplina Arquitetura e Organização de Computadores I da UFRGS. O objetivo é desenvolver um programa em Assembly para o processador CESAR16i, que gerencie um visor conforme uma sequência de operações programada.

📋 Descrição Geral
O programa será executado a partir do endereço H8000 até HFFFF, enquanto o programa fornecido pelo professor será carregado entre H0000 e H7FFF.

O programa do professor chamará o seu código com a instrução:

JSR R7, H8000
No registrador R0, será passado o endereço de memória contendo a lista de instruções que o programa deve processar.

🛠️ Funcionalidades
O programa deve interpretar e executar as seguintes instruções:

Instruções Básicas
END-OK (H0000): Finaliza o programa sem erros.

END-ERROR (H0001): Finaliza o programa com erro.

Manipulação do Visor
CLEAR (H0100): Limpa um número específico de posições no visor, a partir de uma posição inicial.

VISOR-OFF (H0200): Apaga o visor, mas mantém os dados armazenados.

VISOR-ON (H0201): Restaura os dados armazenados no visor.

Exibição de Texto
TEXT (H0300): Escreve uma string no visor, começando em uma posição específica. Caracteres com o bit 7 ativado devem piscar.

Outras Operações
DELAY (H0400): Pausa a execução por um tempo especificado (em milissegundos).

COPY (H0500): Copia um número específico de caracteres do visor, a partir de uma posição inicial.

PASTE (H0501): Cola os caracteres copiados em uma posição específica do visor.

LOOP (H0600): Reinicia a execução da lista de instruções desde o início.

🚀 Como Executar
Escreva o código em linguagem simbólica do CESAR16i.

Compile usando o montador Daedalus.

Carregue no simulador CESAR16i utilizando "carga parcial":

Primeiro, carregue o programa fornecido pelo professor.

Depois, carregue sua implementação.

Execute o programa e insira as instruções na memória conforme necessário.

Verifique os resultados no visor e no comportamento geral do sistema.

Este trabalho foi desenvolvido como parte das atividades acadêmicas da disciplina Arquitetura e Organização de Computadores I da UFRGS.
