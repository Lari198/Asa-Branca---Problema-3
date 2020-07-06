#include <iostream>
#include <cstdlib>
#include <clocale>
#include <thread>
#include <chrono>
#include <time.h>
#include <typeinfo>
#include <functional>
#include <deque>

#include "bibliotecatransceptor.h"            //Assinatura da biblioteca do transceptor

using namespace std;
static bool s_Finished = false;
static bool cond= true;
static bool if_link=false;

deque <char*> fila;

//Conta t segundos
void timer(int t){
    while(!s_Finished){
        this_thread::sleep_for(chrono::seconds(t));
        s_Finished = true;
    }
}

//Estabelece link
int link(int time){
    char special_msgt[12]="c", special_msgr[12];
    char *pspecial_msgr=&special_msgr[12];
    int t, maxsizemsgr;
    time_t t1,t2;
    //INICIO DO LINK
    inicio:
    //In�cio transmiss�o
    inicio1:
    if(transmition(special_msgt, sizeof(special_msgt)==0)){   //Envio de mensagem especial concluida sem erros
        cout<<"Mensagem especial de transmiss�o enviada!"<<endl;
    }
    else if(transmition(special_msgt, sizeof(special_msgt))==1){      //Transceptor est� transmitindo algum dado
        ending_transf;                              //Fun��o da bibliotecatranspector.h que s� � chamada quando ocorre o t�rmino de  uma transmiss�o. Sup�e-se que ao cham�-la a transmiss�o terminar�.
        goto inicio1;                                //Quando a transmiss�o acabar, vai-se para inicio1, para verificar se o transceptor pode enviar a mensagem sem erros
    }
    else if(transmition(special_msgt, sizeof(special_msgt))==2){      //Transceptor no modo de recep��o
        goto inicio1;                                                 //Enquanto o transceptor estiver no modo recep��o volta-se para inicio1. Assim que o modo recep��o for encerrado e o transceptor n�o
    }                                                                  //estiver recebendo dados, pode-se verificar se o transceptor pode enviar a mensagem sem erros
    //Fim transmiss�o

    //In�cio modo de Recep��o
    inicio2:
    if(reception_mode(special_msgr, maxsizemsgr)==0){    //Modo recep��o ativado sem erros
        cout<<"Modo de recep��o ativado"<<endl;
    }
    else if(reception_mode(special_msgr, maxsizemsgr)==1){   //Satelite esta transmitindo algum dado
        ending_transf;                              //Fun��o da bibliotecatranspector.h que s� � chamada quando ocorre o t�rmino de  uma transmiss�o. Sup�e-se que ao cham�-la a transmiss�o terminar�.
        goto inicio2;                                //Quando a transmiss�o acabar, vai-se para inicio2, para verificar se o transceptor pode ativar o modo de recep��o sem erros
    }
    //Fim modo de recep��o

    //In�cio temporizador
    t1=time(NULL);
    std::thread temp(timer, time);                      //Conta o tempo determinado e espera a chamada da fun��o receveing_data ao mesmo tempo, por isso o uso de thread para o paralelismo
    receiving_data(pspecial_msgr,sizeof(special_msgr));      //Fun��o da bibliotecatranspector.h que s� � chamada quando do recebimento de algum dado. Sup�e-se que ao cham�-la a inicia-se o recebimento.
    t2=time(NULL);
    temp.join();                                         //Garante que a thread seja concluido
    s_Finished=false;

    if(difftime(t2,t1)>time && time==5){                 //Se tempo de resposta for maior que 5 segundos, para o estabelecimento do link, reinicia-se tentativa de link
        cout<<"Sem resposta! Reiniciando tentativa de link!"<<endl;
        goto inicio;
    }
    if(difftime(t2,t1)>time && time==10){          //Se o tempo de resposta for maior que 10s, para verifica��o do link, retorna 1 mostrando que o link foi perdido
        cout<<"Sem resposta! Link Perdido"<<endl;
        return 1;
    }
    else{                                           //Se resposta do solo for dada em menos de 5 segundos, link estabelecido!
        cout<<"Resposta do solo recebida!"<<endl;
    }
    //Fim temporizador

    //Verificando se a mensagem especial � do mesmo tipo
    if(typeid(special_msgt[0]).name()==typeid(special_msgr[0]).name()){
        cout<<"Mensagem recebida do mesmo tipo da enviada!\nSucesso!"<<endl;
    }else{
        cout<<"Mensagem recebida n�o � do mesmo tipo da enviada!! Transmitindo nova mensagem!"<<endl;
        goto inicio;
    }
    //Fim da verifica��o do tipo de mensagem
    return 0;
}


//ESCOLHENDO FUN��O DE ACORDO COM O TIPO DE DADO DOS DADOS
int wich_data(char data_transfer[]){
    int can;
    char d_type=(typeid(data_transfer[0]).name());    //data_transfer contem os dados para transferencia que foram gerados por outro m�dulo
                                                      //typeid retorna: i se int
    if(d_type == i){                                   //f se float
        can = data_int();                       //s se short
    }                                                  //l se long
    else if(d_type == c){                              //j se unsigned
        can = data_char();                      //t se unsigned short
    }                                                  //m se unsigned long
    else if(d_type == f){                              //d se double
        can = data_float();                     //e se long double
    }
    else if(d_type == s){
        can = data_short();
    }
    else if(d_type == l){
        can = data_long();
    }
    else if(d_type == j){
        can = data_unsigned();
    }
    else if(d_type == t){
        can = data_unsignedshort();
    }
    else if(d_type == m){
        can = data_unsignedlong();
    }
    else if(d_type == d){
        can = data_double();
    }
    else if(d_type == e){
        can = data_longdouble();
    }
    return can;
}


int data_int(){
    if(if_link==false){
        cout<<"Link ainda n�o estabelecido!"<<endl;
        return 1;
    }
    else{
        return 0;
    }
}

int data_char(){
    if(if_link==false){
        cout<<"Link ainda n�o estabelecido!"<<endl;
        return 1;
    }
    else{
        return 0;
    }
}

int data_float(){
    if(if_link==false){
        cout<<"Link ainda n�o estabelecido!"<<endl;
        return 1;
    }
    else{
        return 0;
    }
}

int data_short(){
    if(if_link==false){
        cout<<"Link ainda n�o estabelecido!"<<endl;
        return 1;
    }
    else{
        return 0;
    }
}

int data_long(){
    if(if_link==false){
        cout<<"Link ainda n�o estabelecido!"<<endl;
        return 1;
    }
    else{
        return 0;
    }
}

int data_unsigned(){
    if(if_link==false){
        cout<<"Link ainda n�o estabelecido!"<<endl;
        return 1;
    }
    else{
        return 0;
    }
}

int data_unsignedshort(){
    if(if_link==false){
        cout<<"Link ainda n�o estabelecido!"<<endl;
        return 1;
    }
    else{
        return 0;
    }
}

int data_unsignedlong(){
    if(if_link==false){
        cout<<"Link ainda n�o estabelecido!"<<endl;
        return 1;
    }
    else{
        return 0;
    }
}

int data_double(){
    if(if_link==false){
        cout<<"Link ainda n�o estabelecido!"<<endl;
        return 1;
    }
    else{
        return 0;
    }
}

int data_longdouble(){
    if(if_link==false){
        cout<<"Link ainda n�o estabelecido!"<<endl;
        return 1;
    }
    else{
        return 0;
    }
}


void timer_start(std::function<void(void)> func, unsigned int interval){
    std::thread([func, interval](){
        while(cond){
            func();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }).detach();
}

void test_link(){                //verifica link
    int a;
    a=link(10);                        //se n retornar mensagem em 10s, link perdido!!
    if (a==1){                   //se retorna 1, link perdido
       cond = false;
       if_link = false;                                  //se link perdido, dados que estavam sendo transmitidos s�o guardados em fila, e ser�o os primeiros
       fila.push_front(data_transfer);                   //a serem transmitidos quando os dados armazenados na fila forem enviados
    }else{
        if_link=true;
    }
}

int can_transfer(char data_transfer[]){

    timer_start(test_link, 90000);                                   //verifica o link de 90s em 90s
    transmition(data_transfer, sizeof(data_transfer));              //faz a transmiss�o dos dados
    if(!ending_transf){                                          //identifica quando a transmiss�o acaba para assim parar o loop
        cond=false;
    }
    while(cond);
    cond=true;
    return 0;
}

void transfer(char data_transfer[]){

    //Condi��es para transmiss�o dos dados
    if(wich_data(data_transfer)==1){                 //wich_data identifica o tipo de dado dos dados, se retorna 1 � porque n�o h� link
        fila.push_back(data_transfer);               // guardo os dados na fila para posterior envio
        link(5);                                     //estabele�o link
    }
     //Verifica se est� ocorrendo transmiss�o, caso sim, guarda dado na fila
    if(transmition(data_transfer, sizeof(data_transfer))==1){
        fila.push_back(data_transfer);
        ending_transf;                          //Fun��o da bibliotecatranspector.h que s� � chamada quando ocorre o t�rmino de  uma transmiss�o. Sup�e-se que ao cham�-la a transmiss�o terminar�.
    }
    //Trasmite dados que est�o na fila
    while(!fila.empty()){
        can_trasnfer(fila.begin());
    }
    can_transfer(data_transfer);
}

int main(){
    setlocale(LC_ALL,"portuguese");
    int can;
    cout<<"Estabelecendo link"<<endl;

    if(link(5)==0){                  //estabelecendo link
        if_link=true;
    }

    transfer(data_transfer);       //para fazer transmiss�o, chamar a fun��o transfer
                                   //data_transfer � o vetor que contem as informa��es a serem transmitidas, vetor ser� repassado atraves de outro modulo
    return 0;
}
