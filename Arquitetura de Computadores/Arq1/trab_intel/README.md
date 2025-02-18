Trabalho de Programação - Processador Intel 8086
Este repositório contém a implementação do trabalho de programação para a disciplina Arquitetura e Organização de Computadores I da UFRGS. O objetivo é desenvolver um programa em Assembly para o processador Intel 8086:

Gerador de Código de Barras (Code 11)

📋 Especificações Gerais
O trabalho utiliza o padrão de código de barras Code 11, que representa os símbolos 0-9 e -. Cada sequência deve começar e terminar com o símbolo especial START/STOP (SS) e incluir um dígito verificador calculado com base nos valores dos símbolos.
🛠️ Funcionalidades
1. Gerador de Código de Barras
Lê o arquivo IN.TXT, contendo sequências de até 10 símbolos por linha.

Gera o arquivo OUT.BAR com os códigos de barras correspondentes:

Adiciona os símbolos SS no início e no final.

Calcula o dígito verificador.

Codifica os símbolos em formato binário, separando-os por uma barra branca estreita.

Trata erros:

Exibe mensagens na tela.

Escreve a causa do erro no lugar do código no arquivo OUT.BAR.

🚀 Como Executar
Compile o programa utilizando um montador compatível com Assembly para o processador Intel 8086.

Execute o programa fornecendo os arquivos necessários:

Para o gerador: IN.TXT → gera OUT.BAR.

📝 Autor
Este trabalho foi desenvolvido como parte das atividades acadêmicas da disciplina Arquitetura e Organização de Computadores I da UFRGS.
