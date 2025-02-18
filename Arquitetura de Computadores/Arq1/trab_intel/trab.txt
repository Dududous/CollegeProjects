.MODEL SMALL
.STACK 100h
.DATA
    FileName DB 'IN.TXT', 0              ; Nome do arquivo
    MsgErroOpenFile DB 'Erro na abertura do arquivo.', 13, 10, '$' ; Mensagem de erro
    MsgErroReadLine DB 'Erro ao ler linha do arquivo.', 13, 10, '$' ; Mensagem de erro de leitura
    MsgSucesso DB 'Arquivo processado com sucesso!', 13, 10, '$'   ; Mensagem de sucesso
    FileHandle DW ?                      ; Variável para armazenar o handle do arquivo
    Buffer DB 128 DUP(0)                 ; Buffer para armazenar uma linha lida (128 bytes)
    LineBuffer DB 128 DUP('$')           ; Buffer para armazenar a linha processada
    StartFlag DB 0                       ; Flag para identificar "START"
    StopFlag DB 0                        ; Flag para identificar "STOP"

.CODE
MAIN PROC
    MOV AX, @DATA                        ; Configura segmento de dados
    MOV DS, AX

    ; Tenta abrir o arquivo no modo leitura (ah=0x3d)
    MOV AL, 0                            ; Modo leitura
    LEA DX, FileName                     ; Carrega o nome do arquivo em DX
    MOV AH, 3Dh                          ; Função para abrir arquivo (INT 21h)
    INT 21h                              ; Chamada de interrupção

    JNC Continua1                        ; Se não houve erro (Carry Flag limpa), continua

    ; Caso contrário, exibe mensagem de erro e encerra o programa
    LEA DX, MsgErroOpenFile              ; Carrega mensagem de erro em DX
    CALL printf_s                        ; Exibe mensagem usando printf_s (simulação)
    
    MOV AH, 4Ch                          ; Termina o programa (INT 21h)
    INT 21h                              ;

Continua1:
    MOV FileHandle, AX                   ; Armazena o handle do arquivo retornado em AX

ReadLoop:
    LEA DX, Buffer                       ; Endereço do buffer em DX
    MOV BX, FileHandle                   ; Handle do arquivo em BX
    MOV CX, 128                          ; Tamanho máximo da leitura (128 bytes)
    MOV AH, 3Fh                          ; Função para ler do arquivo (INT 21h)
    INT 21h                              ; Chamada de interrupção

    JC ReadError                         ; Salta se houver erro na leitura

    CMP AX, 0                            ; Verifica EOF (AX = número de bytes lidos)
    JE EndRead                           ; Se EOF (AX = 0), termina a leitura

    CALL PrintLine
    CALL ProcessLine                     ; Processa a linha lida no buffer
    CALL PrintBarCode                    ; Imprime o BarCode gerado no terminal

    JMP ReadLoop                         ; Continua lendo as próximas linhas
                                         ; Continua lendo as próximas linhas

ReadError:
    LEA DX, MsgErroReadLine              ; Carrega mensagem de erro em DX
    CALL printf_s                        ; Exibe mensagem usando printf_s (simulação)
    JMP EndProgram                       ;

EndRead:
    LEA DX, MsgSucesso                   ; Mensagem de sucesso ao processar o arquivo
    CALL printf_s                        ;

EndProgram:
    MOV AH, 3Eh                          ; Função para fechar o arquivo (INT 21h)
    MOV BX, FileHandle                   ;
    INT 21h                              ;

EXIT:
    MOV AH, 4Ch                          ; Termina o programa (INT 21h)
    INT 21h                              ;

MAIN ENDP

; Subrotina: Processa uma linha lida do buffer
ProcessLine PROC
    LEA SI, Buffer                       ; Ponteiro para o buffer lido

CheckStartStop:
    CMP StartFlag, 1                     ; Verifica se já encontrou "START"
    JE CheckStop                         ;

FindStart:
    MOV CX, 5                            ;
    REPE CMPSB                           ; Compara os primeiros caracteres com "START"
    JZ SetStartFlag                      ;
    
CheckStop:
FindStop:
    MOV CX, 4                            ;
    REPE CMPSB                           ; Compara os primeiros caracteres com "STOP"
    JZ SetStopFlag                       ;

ProcessContent:
    CMP StartFlag, 1                     ;
    JNE SkipLine                         ;
    
ProcessValidLine PROC
    ; Inicializa ponteiros e variáveis
    LEA SI, Buffer                       ; Ponteiro para a linha lida no Buffer
    LEA DI, LineBuffer                   ; Ponteiro para o buffer de saída (BarCode)
    MOV CX, 0                            ; Contador de caracteres processados

    ; Escreve o símbolo START/STOP no início do BarCode
    CALL WriteStartStop                  ; Adiciona o símbolo SS ao início do BarCode

ProcessSymbols:
    LODSB                                ; Carrega o próximo caractere da linha no registrador AL
    CMP AL, 0                            ; Verifica se é o final da string (NULL terminator)
    JE CalculateCheckDigit               ; Se for o final, calcula o dígito verificador

    ; Verifica se o caractere é válido (0-9 ou '-')
    CMP AL, '0'                          ;
    JB InvalidSymbol                     ; Se menor que '0', é inválido
    CMP AL, '9'                          ;
    JA CheckDash                         ; Se maior que '9', verifica se é '-'

CheckDash:
    CMP AL, '-'                          ;
    JE EncodeSymbol                      ; Se for '-', continua para codificação
    JMP InvalidSymbol                    ; Caso contrário, é inválido

EncodeSymbol:
    ; Converte o caractere em código binário com base na tabela (ver especificação)
    CALL GetBarCode                      ; Obtém o BarCode do caractere em AL
    CALL WriteBarCode                    ; Escreve o BarCode no buffer de saída
    INC CX                               ; Incrementa o contador de símbolos processados
    JMP ProcessSymbols                   ; Continua processando os próximos símbolos

InvalidSymbol:
    ; Caso um símbolo inválido seja encontrado, exibe erro e termina processamento
    LEA DX, MsgErroReadLine              ; Mensagem de erro para símbolo inválido
    CALL printf_s                        ;
    RET                                  ;

CalculateCheckDigit:
    ; Calcula o dígito verificador com base nos símbolos processados
    CALL ComputeCheckDigit               ; Calcula e armazena o dígito verificador em AL
    CALL GetBarCode                      ; Obtém o BarCode do dígito verificador
    CALL WriteBarCode                    ; Escreve no buffer de saída

    ; Escreve o símbolo START/STOP no final do BarCode
    CALL WriteStartStop                  ;

RET                                      ;

ProcessValidLine ENDP

; Subrotina: Obtém o BarCode correspondente ao caractere em AL
GetBarCode PROC
    CMP AL, '0'
    JE Code0                             ;
    CMP AL, '1'
    JE Code1                             ;
    CMP AL, '2'
    JE Code2                             ;
    CMP AL, '3'
    JE Code3                             ;
    CMP AL, '4'
    JE Code4                             ;
    CMP AL, '5'
    JE Code5                             ;
    CMP AL, '6'
    JE Code6                             ;
    CMP AL, '7'
    JE Code7                             ;
    CMP AL, '8'
    JE Code8                             ;
    CMP AL, '9'
    JE Code9                             ;
    CMP AL, '-'                          ;
    JE CodeDash                          ;

RET                                      ;

Code0: MOV AX, 00001b                    ; Código binário para '0'
       RET                              ;
Code1: MOV AX, 10001b                    ; Código binário para '1'
       RET                              ;
Code2: MOV AX, 01001b                    ; Código binário para '2'
       RET                              ;
Code3: MOV AX, 11000b                    ; Código binário para '3'
       RET                              ;
Code4: MOV AX, 00101b                    ; Código binário para '4'
       RET                              ;
Code5: MOV AX, 10100b                    ; Código binário para '5'
       RET                              ;
Code6: MOV AX, 01100b                    ; Código binário para '6'
       RET                              ;
Code7: MOV AX, 00011b                    ; Código binário para '7'
       RET                              ;
Code8: MOV AX, 10010b                    ; Código binário para '8'
       RET                              ;
Code9: MOV AX, 10000b                    ; Código binário para '9'
       RET                              ;
CodeDash: MOV AX, 00100b                 ; Código binário para '-'
      RET                               ;

GetBarCode ENDP

; Subrotina: Escreve um BarCode no buffer de saída
WriteBarCode PROC
   MOV [DI], AX                          ; Escreve os bits do BarCode no buffer de saída
   ADD DI, 5                             ; Avança 5 posições (tamanho de cada símbolo)
   MOV BYTE PTR [DI], 0                  ; Adiciona barra branca estreita como separador
   INC DI                                ;
RET                                      ;

WriteBarCode ENDP

; Subrotina: Escreve o símbolo START/STOP no buffer de saída
WriteStartStop PROC
   MOV AX, 00110b                        ; Código binário do símbolo SS
   CALL WriteBarCode                     ;
RET                                      ;

WriteStartStop ENDP

; Subrotina: Calcula o dígito verificador com base na soma ponderada dos símbolos processados
ComputeCheckDigit PROC
    XOR BX, BX                            ; Zera BX (acumulador da soma ponderada)
    XOR DX, DX                            ; Zera DX (peso atual)
    LEA SI, Buffer                        ; Carrega o endereço do Buffer no SI

ComputeLoop:
    LODSB                                 ; Carrega próximo símbolo em AL
    CMP AL, 0                             ; Verifica fim da string (NULL terminator)
    JE ComputeEnd                         ; Se for o final da string, termina o loop

    SUB AL, '0'                           ; Converte caractere ASCII em valor numérico
    INC DX                                ; Incrementa peso atual (DX)
    MUL DX                                ; Multiplica valor pelo peso atual
    ADD BX, AX                            ; Soma ao acumulador BX

    JMP ComputeLoop                       ; Continua processando os próximos símbolos

ComputeEnd:
    MOV AX, BX                            ; Move a soma ponderada para AX
    MOV CX, 11                            ; Carrega o divisor (11) no registrador CX
    XOR DX, DX                            ; Zera DX antes da divisão
    DIV CX                                ; Divide AX por 11 (resultado em AX, resto em DX)
    MOV AL, DL                            ; O resto da divisão é o dígito verificador

RET                                       ;
ComputeCheckDigit ENDP

SkipLine:
RET                                      ;

SetStartFlag:
    MOV StartFlag, 1                     ;
RET                                      ;

SetStopFlag:
    MOV StopFlag, 1                      ;
RET                                      ;

ProcessLine ENDP

; Subrotina: Imprime uma linha lida no terminal
PrintLine PROC
    LEA SI, Buffer                       ; Ponteiro para o buffer lido
PrintLoop:
    LODSB                                ; Carrega um byte da linha no registrador AL
    CMP AL, 0                            ; Verifica se é o final da string (NULL terminator)
    JE PrintEnd                          ;
    
WriteChar:
    MOV DL, AL                           ; Move o caractere atual para DL (registro usado pelo DOS)
    MOV AH, 02h                          ; Função para imprimir um caractere (INT 21h)
    INT 21h                              ;
    
JMP PrintLoop                            ;

PrintEnd:
RET                                      ;
PrintLine ENDP

; Simulação da função printf_s para exibir mensagens na tela
printf_s PROC
    MOV AH, 09h                          ; Função para imprimir string (INT 21h)
    INT 21h                              ;
RET                                      ;
printf_s ENDP

; Subrotina: Imprime o BarCode gerado no terminal
PrintBarCode PROC
    LEA SI, LineBuffer                  ; Ponteiro para o buffer do BarCode gerado
PrintLoop1:
    LODSB                               ; Carrega o próximo byte do buffer em AL
    CMP AL, 0                           ; Verifica se é o final da string (NULL terminator)
    JE PrintEnd1                         ; Se for, termina a impressão

    MOV DL, AL                          ; Move o caractere atual para DL (registro usado pelo DOS)
    MOV AH, 02h                         ; Função para imprimir um caractere (INT 21h)
    INT 21h                             ; Exibe o caractere no terminal

    JMP PrintLoop1                       ; Continua imprimindo os próximos caracteres

PrintEnd1:
    MOV DL, 13                          ; Caractere de retorno de carro (CR)
    MOV AH, 02h                         ; Função para imprimir um caractere
    INT 21h                             ;

    MOV DL, 10                          ; Caractere de nova linha (LF)
    MOV AH, 02h                         ;
    INT 21h                             ;

RET                                    ;
PrintBarCode ENDP


END MAIN                                 ;
