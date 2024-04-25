#include <stdio.h>

#define PESOBIT(bpos) 1<<bpos
#define CONSULTARBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)

void calcularHost(unsigned char IP[4], unsigned char mascara[4]);
void imprimirBits(unsigned char byte);

int main(int argc, char *argv[]) {

    
    //unsigned char IP[4] = {128, 255, 0, 0};
    //unsigned char IP[4] = {128, 255, 0, 0};
    //unsigned char IP[4] = {128, 255, 0, 0};
    //unsigned char IP[4] = {128, 255, 0, 0};
    //unsigned char IP[4] = {128, 255, 0, 0};
    //unsigned char IP[4] = {128, 255, 0, 0};
    //unsigned char IP[4] = {128, 255, 0, 0};
    //unsigned char IP[4] = {128, 255, 0, 0};
    unsigned char IP[4] = {4, 128, 0, 0};


    unsigned char mascara[4] = {255, 255, 255, 0};
    printf("\033[92mDirecci%cn IP: \033[0m%d.%d.%d.%d\n", 162, IP[0], IP[1], IP[2], IP[3]);
    if(!(IP[0] & 128)) {
        mascara[2] = 0;
        mascara[1] = 0;
        printf("\033[92mClase: \033[0mA\n");
        printf("\033[92mDirecci%cn de Red: \033[0m%d.%d.%d.%d\n", 162, IP[0]&mascara[0], IP[1]&mascara[1], IP[2]&mascara[2], IP[3]&mascara[3]);
        printf("\033[92mDirecci%cn de Broadcast: \033[0m%d.%d.%d.%d\n", 162, (unsigned char)(IP[0]|(~mascara[0])), (unsigned char)(IP[1]|(~mascara[1])), (unsigned char)(IP[2]|(~mascara[2])), (unsigned char)(IP[3]|(~mascara[3])));
        calcularHost(IP, mascara);
    } else if(!(IP[0] & 64)){
        mascara[2] = 0;
        printf("\033[92mClase: \033[0mB\n");
        printf("\033[92mDirecci%cn de Red: \033[0m%d.%d.%d.%d\n", 162, IP[0]&mascara[0], IP[1]&mascara[1], IP[2]&mascara[2], IP[3]&mascara[3]);
        printf("\033[92mDirecci%cn de Broadcast: \033[0m%d.%d.%d.%d\n", 162, (unsigned char)(IP[0]|(~mascara[0])), (unsigned char)(IP[1]|(~mascara[1])), (unsigned char)(IP[2]|(~mascara[2])), (unsigned char)(IP[3]|(~mascara[3])));
        calcularHost(IP, mascara);
    } else if(!(IP[0] & 32)){
        printf("\033[92mClase: \033[0mC\n");
        printf("\033[92mDirecci%cn de Red: \033[0m%d.%d.%d.%d\n", 162, IP[0]&mascara[0], IP[1]&mascara[1], IP[2]&mascara[2], IP[3]&mascara[3]);
        printf("\033[92mDirecci%cn de Broadcast: \033[0m%d.%d.%d.%d\n", 162, (unsigned char)(IP[0]|(~mascara[0])), (unsigned char)(IP[1]|(~mascara[1])), (unsigned char)(IP[2]|(~mascara[2])), (unsigned char)(IP[3]|(~mascara[3])));
        calcularHost(IP, mascara);
    } else if(!(IP[0] & 16)){
        printf("\033[92mClase: \033[0mD\n");
    } else {
        printf("\033[92mClase: \033[0mE\n");
    }
    return 0;
}

void calcularHost(unsigned char IP[4], unsigned char mascara[4]) {
    unsigned char bit = 1;
    char estado = 0;
    while(255&bit) {
        switch(estado) {
            case 0:
                if(IP[3]&bit)
                    estado = 1;
                else
                    estado = 2;
                break;
            case 1:
                if(!(IP[3]&bit)) {
                    printf("\033[92mTipo: \033[0mHost");
                    return;
                }
                break;
            case 2:
                if(IP[3]&bit) {
                    printf("\033[92mTipo: \033[0mHost");
                    return;
                }
                break;
        }
        bit = bit<<1;
    }
    // Si es tipo C y terminó de analizar la IP
    if(255&mascara[2]) {
        if(estado & 1) {
            printf("\033[92mTipo de IP: \033[0mBroadcast");
            return; 
        } else {
            printf("\033[92mTipo: \033[0mRed");
            return; 
        }
    }

    bit = 1;
    while(255&bit) {
        switch(estado) {
            case 0:
                if(IP[2]&bit)
                    estado = 1;
                else
                    estado = 2;
                break;
            case 1:
                if(!(IP[2]&bit)) {
                    printf("\033[92mTipo: \033[0mHost");
                    return;
                }
                break;
            case 2:
                if(IP[2]&bit) {
                    printf("\033[92mTipo: \033[0mHost");
                    return;
                }
                break;
        }
        bit = bit<<1;
    }
    // Si es tipo B y terminó de analizar la IP
    if(255&mascara[1]) {
        if(estado & 1) {
            printf("\033[92mTipo: \033[0mBroadcast");
            return; 
        } else {
            printf("\033[92mTipo: \033[0mRed");
            return; 
        }
    }

    bit = 1;
    while(255&bit) {
        switch(estado) {
            case 0:
                if(IP[1]&bit)
                    estado = 1;
                else
                    estado = 2;
                break;
            case 1:
                if(!(IP[1]&bit)) {
                    printf("\033[92mTipo: \033[0mHost");
                    return;
                }
                break;
            case 2:
                if(IP[1]&bit) {
                    printf("\033[92mTipo: \033[0mHost");
                    return;
                }
                break;
        }
        bit = bit<<1;
    }
    // Es tipo A y terminó de analizar la IP
    if(estado & 1) {
        printf("\033[92mTipo: \033[0mBroadcast"); 
    } else {
        printf("\033[92mTipo: \033[0mRed");
    }
    return;
}

void imprimirBits(unsigned char byte) {
    for(char i=7; i>=0; i--) {
        printf("%d", CONSULTARBIT(byte, i));
    }
    printf(" ");
}