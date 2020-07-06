#ifndef __BIBLIOTECATRANSCEPTOR_H_
#define __BIBLIOTECATRANSCEPTOR_H_

//funções de retorno imediato
int transmition(char bytearrayt[12], int sizebytearray); // o array de bytes foi substituido por um array de char pois em c++ não existe tipo byte. Como dito no problema, informações transmmitidas tem tamanho fixo de 12 bytes
                                                         // return 0 caso não ocorra erros, return 1 caso esteja transmitindo, return 2 caso esteja no modo recepção
int reception_mode(char bytearrayr[], int maxsizebar);   // return 0 caso não ocorra erros, return 1 caso esteja transmitindo

//trigger functions
void receiving_data(char *bytearrayr[], int *numbytearrayr); //é chamada quando o transceptor esta recebendo dados; não retorna nada. Cadastro feito atraves de ponteiros
                                                             //seus parametros são ponteiros que apontam para os parametro da função reception_mode
void ending_transf();                                 // é chamada quando há termino de transmissão, sinalizando que o transceptor pode aceitar nova sequencia de bytes para transmitir; não recebe parametro, nem retorna. Cadastro feito atraves de ponteiros

#endif
