#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

int main() {

    byte T[] = {
		0x00, 0x14, 0xd1, 0xc2, 0x38, 0xbe, 0x00, 0x18, 0xe7, 0x33, 0x3d, 0xc3, 0x08, 0x00, 0x45, 0x00, 
		0x00, 0x3c, 0x00, 0x32, 0x00, 0x00, 0x80, 0x01, 0xb5, 0x00, 0xc0, 0xa8, 0x02, 0x3c, 0xc0, 0xa8, 
		0x00, 0x01, 0x63, 0x7D, 0x81, 0x38, 0xC8, 0x01, 0x01, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    if((T[12]<<8|T[13]) != 0x0800) {
        printf("La trama no es IP");
        exit(0);
    }

    printf("\033[92mCabecera IP\033[0m\n");
    printf("\033[94mVersi%cn:\033[0m  %d\n", 162, T[14]>>4);
    printf("\033[94mInternet Header Length:\033[0m  %d\n", T[14]&0x0f);
    printf("\033[94mType of Service:\033[0m  \n");
    printf("\033[96m  Precedence =\033[0m  %d\n", T[15]>>5);
    printf("\033[96m  D =\033[0m  %d\n", (T[15]>>4)&1);
    printf("\033[96m  T =\033[0m  %d\n", (T[15]>>3)&1);
    printf("\033[96m  R =\033[0m  %d\n", (T[15]>>2)&1);
    printf("\033[96m  C =\033[0m  %d\n", (T[15]>>1)&1);
    printf("\033[96m  x =\033[0m  %d\n", T[15]&1);

    printf("\033[94mTotal Length:\033[0m  %d\n", (T[16]<<8)|T[17]);
    printf("\033[94mIdentification:\033[0m  %d\n", (T[18]<<8)|T[19]);

    printf("\033[94mFlags:\033[0m  \n");
    printf("\033[94mFragment Checksum:\033[0m  %d\n", ((T[20]&0x1f)<<8)|T[21]);

    printf("\033[94mProtocol:\033[0m  ");
    if(T[23] == 1) {
        printf("ICMP\n");
    } else if(T[23] == 2) {
        printf("IGMP\n");
    } else if(T[23] == 6) {
        printf("TCP\n");
    } else if(T[23] == 9) {
        printf("IGRP\n");
    } else if(T[23] == 17) {
        printf("UDP\n");
    } else if(T[23] == 47) {
        printf("GRE\n");
    } else if(T[23] == 50) {
        printf("ESP\n");
    } else if(T[23] == 51) {
        printf("AH\n");
    } else if(T[23] == 57) {
        printf("SKIP\n");
    } else if(T[23] == 88) {
        printf("EIGRP\n");
    } else if(T[23] == 89) {
        printf("OSPF\n");
    } else if(T[23] == 115) {
        printf("L2TP\n");
    } else {
        printf("Otro\n");
    }

    printf("\033[94mHeader Checksum:\033[0m  %.4x\n", ((short int)T[24]<<8)|T[25]);
    printf("\033[94mSource Address:\033[0m  %d.%d.%d.%d\n", T[26], T[27], T[28], T[29]);
    printf("\033[94mDestination Address:\033[0m  %d.%d.%d.%d\n", T[30], T[31], T[32], T[33]);
    /*
    printf("\033[92mProtocolo ARP\033[0m\n", 162);
    printf("\033[94mHardware Addess Type:\033[0m\n  ");
    if((T[14]<<8|T[15]) == 1) {
        printf("Ethernet\n");
    } else if((T[14]<<8|T[15]) == 6) {
        printf("IEEE 802 LAN\n");
    } else {
        printf("Otro\n");
    }

    printf("\033[94mProtocol Addess Type:\033[0m\n  ");
    if((T[16]<<8|T[17]) == 2048) {
        printf("IPv4 (0x0800)\n");
    } else {
        printf("Otro\n");
    }

    printf("\033[94mHardware Address Length:\033[0m\n  %d bytes\n", T[18]);
    printf("\033[94mProtocol Address Length:\033[0m\n  %d bytes\n", T[19]);
    printf("\033[94mProtocol Addess Type:\033[0m\n  ");
    if((T[20]<<8|T[21]) == 1) {
        printf("Solicitud\n");
    } else if ((T[20]<<8|T[21]) == 2) {
        printf("Respuesta\n");
    }
    printf("\033[94mSource Hardware Address:\033[0m\n  %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", T[22], T[23], T[24], T[25], T[26], T[27]);
    printf("\033[94mSource Protocol Address:\033[0m\n  %d.%d.%d.%d\n", T[28], T[29], T[30], T[31]);
    printf("\033[94mTarget Hardware Address:\033[0m\n  %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", T[32], T[33], T[34], T[35], T[36], T[37]);
    printf("\033[94mTarget Protocol Address:\033[0m\n  %d.%d.%d.%d\n", T[38], T[39], T[40], T[41]);
    */
    return 0;
}