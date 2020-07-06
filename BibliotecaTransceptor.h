#ifndef __BIBLIOTECATRANSCEPTOR_H_
#define __BIBLIOTECATRANSCEPTOR_H_

//fun��es de retorno imediato
int transmition(char bytearrayt[12], int sizebytearray); // o array de bytes foi substituido por um array de char pois em c++ n�o existe tipo byte. Como dito no problema, informa��es transmmitidas tem tamanho fixo de 12 bytes
                                                         // return 0 caso n�o ocorra erros, return 1 caso esteja transmitindo, return 2 caso esteja no modo recep��o
int reception_mode(char bytearrayr[], int maxsizebar);   // return 0 caso n�o ocorra erros, return 1 caso esteja transmitindo

//trigger functions
void receiving_data(char *bytearrayr[], int *numbytearrayr); //� chamada quando o transceptor esta recebendo dados; n�o retorna nada. Cadastro feito atraves de ponteiros
                                                             //seus parametros s�o ponteiros que apontam para os parametro da fun��o reception_mode
void ending_transf();                                 // � chamada quando h� termino de transmiss�o, sinalizando que o transceptor pode aceitar nova sequencia de bytes para transmitir; n�o recebe parametro, nem retorna. Cadastro feito atraves de ponteiros

#endif
