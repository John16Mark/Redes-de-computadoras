#include <stdio.h>
#include <stdlib.h>

#define IHL ((T[14]&0x0f)<<2)

typedef unsigned char byte;
typedef unsigned short int nibble;

void Ethernet(byte *T);
void IP(byte * T);
void ICMP(byte * T, byte ihl);

int main() {
    byte T[][2000] = {
        {
            0x00, 0x01, 0xf4, 0x43, 0xc9, 0x19, 0x00, 0x50, 0xba, 0xb2, 0xf3, 0x7b, 0x08, 0x00, 0x45, 0x00, 
            0x00, 0x3c, 0x09, 0x0d, 0x00, 0x00, 0x80, 0x01, 0x7b, 0xfe, 0x94, 0xcc, 0x19, 0x1b, 0x94, 0xcc, 
            0x73, 0x02, 0x08, 0x00, 0x58, 0x5a, 0x02, 0x00, 0xf3, 0x01, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 
            0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 
            0x77, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69
        }, {
            0x00, 0x50, 0xba, 0xb2, 0xf3, 0x7b, 0x00, 0x01, 0xf4, 0x43, 0xc9, 0x19, 0x08, 0x00, 0x45, 0x00, 
            0x00, 0x3c, 0xdf, 0x5c, 0x00, 0x00, 0x7c, 0x01, 0xa9, 0xae, 0x94, 0xcc, 0x73, 0x02, 0x94, 0xcc, 
            0x19, 0x1b, 0x00, 0x00, 0x60, 0x5a, 0x02, 0x00, 0xf3, 0x01, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 
            0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 
            0x77, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69
        }
    };

    printf("  \033[93m.:: Trama 1 ::.\n");
    Ethernet(T[0]);
    printf("  \033[93m.:: Trama 2 ::.\n");
    Ethernet(T[1]);
    return 0;
}

void Ethernet(byte *T) {
    if((T[12]<<8|T[13]) == 0x0800)
        IP(T);
}

void IP(byte * T) {
    if(T[23] == 1)
        ICMP(T, IHL);
}

void ICMP(byte * T, byte ihl) {
    printf("\033[94mTipo:\033[0m  %d", T[14+ihl]);
    if(!T[15+ihl]) {
        if(T[14+ihl] == 8)
            printf("\t\033[96mSolicitud\n");
        else if(!T[14+ihl])
            printf("\t\033[95mRespuesta\n");
    }
    printf("\033[94mC%cdigo:\033[0m  %d\n", 162, T[15+ihl]);
    printf("\033[94mChecksum:\033[0m  %.2x%.2x\n\n", T[16+ihl], T[17+ihl]);
    return;
}