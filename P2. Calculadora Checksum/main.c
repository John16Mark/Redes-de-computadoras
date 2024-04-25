#include <stdio.h>

unsigned short int checksum(unsigned char T[], unsigned char inicio, unsigned char final);

int main() {
    //unsigned char T[] = {0x52, 0x65, 0x64, 0x65, 0x73, 0x20, 0x64, 0x65, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x75, 0x74, 0x61, 0x64, 0x6f, 0x72, 0x61, 0x73, 0x2e};
    //unsigned char T[] = {'H', 'o', 'l', 'a'};
    unsigned char T[] = {0xaa, 0xaa, 0xaa};
    
    printf("\033[93mMensaje: \033[0m");
    for(unsigned char i=0; i<sizeof(T); i++) {
        printf("%c", T[i]);
    }
    printf("\n");
    printf("\033[92mChecksum: \033[0m0x%x", checksum(T, 0, sizeof(T)));
}

unsigned short int checksum(unsigned char T[], unsigned char inicio, unsigned char final) {
    int suma = 0;
    for(unsigned char i=0; i<final; i+=2) {
        if(i == final-1) {
            T[i+1] = 0;
        }
        suma += T[i]<<8 | T[i+1];
    }
    suma += suma>>16;
    suma = suma&0x0000FFFF;
    return ~suma;
}