#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;
typedef unsigned short int nibble;

void TCP(byte * T, byte IHL);

int main() {
    byte T[][2000] = {
        {       // t2
            0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x00, 0x23,  0x8b, 0x46, 0xe9, 0xad, 0x08, 0x00, 0x46, 0x00, 
            0x80, 0x42, 0x04, 0x55, 0x34, 0x11, 0x80, 0x06,  0x6b, 0xf0, 0x94, 0xcc, 0x39, 0xcb, 0x94, 0xcc, 
            0x67, 0x02, 0xaa, 0xbb, 0xcc, 0xdd, 0x04, 0x0c,  0x00, 0x35, 0x80, 0x2e, 0x85, 0x7c, 0xe2, 0x1a, 
            0x01, 0x00, 0x50, 0x01, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x03, 0x77, 0x77, 0x77, 0x03, 0x69, 
            0x73, 0x63, 0x05, 0x65, 0x73, 0x63, 0x6f, 0x6d,  0x03, 0x69, 0x70, 0x6e, 0x02, 0x6d, 0x78, 0x00, 
            0x00, 0x1c, 0x00, 0x01
        }, {   // t9
            0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x08, 0x00, 0x45, 0x10, 
            0x00, 0x3c, 0x04, 0x57, 0x00, 0x00, 0x64, 0x01, 0x98, 0x25, 0x94, 0xcc, 0x39, 0xcb, 0x94, 0xcc, 
            0x3a, 0xe1, 0x08, 0x00, 0x49, 0x5c, 0x03, 0x00, 0x01, 0x00, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 
            0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 
            0x77, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69
        }
    };

    if((( (T[0][12]<<8)|T[0][13] ) == 0x0800) && (T[0][23] == 6) )
        TCP(T[0], (T[0][14]&0x0f)<<2);
    return 0;
}

void TCP(byte * T, byte IHL) {
    printf("\033[92m  .:: TCP Header ::.\033[0m\n");
    printf("\033[94mSource Port:\033[0m  %u\n", (T[14+IHL]<<8)|T[15+IHL]);
    printf("\033[94mDestination Port:\033[0m  %u\n", (T[16+IHL]<<8)|T[17+IHL]);
    printf("\033[94mSequence Number:\033[0m  %u\n", (T[18+IHL]<<24)|(T[19+IHL]<<16)|(T[20+IHL]<<8)|(T[21+IHL]));
    printf("\033[94mAcknowledgement Number:\033[0m  %u\n", (T[22+IHL]<<24)|(T[23+IHL]<<16)|(T[24+IHL]<<8)|(T[25+IHL]));
    printf("\033[94mOffset:\033[0m  %u\n", T[26+IHL]>>4);
    printf("\033[94mHeader Length:\033[0m  %u\n", (T[26+IHL]>>4)<<2);
    printf("\033[94mFlags:\033[0m  \n");
    if(T[27+IHL]&1)
        printf("\033[96m  URG Consult urgent pointer\n");
    if(T[27+IHL]&2)
        printf("\033[96m  ACK Consult acknowledgement field\n");
    if(T[27+IHL]&4)
        printf("\033[96m  PSH Push data\n");
    if(T[27+IHL]&8)
        printf("\033[96m  RST Reset connection\n");
    if(T[27+IHL]&16)
        printf("\033[96m  SYN Synchronize sequence numbers\n");
    if(T[27+IHL]&32)
        printf("\033[96m  FIN Finish connection\n");
    printf("\033[94mWindow:\033[0m  %u\n", (T[28+IHL]<<8)|T[29+IHL]);
    printf("\033[94mChecksum\033[0m  %u\n", (T[30+IHL]<<8)|T[31+IHL]);
    printf("\033[94mUrgent Pointer:\033[0m  %u\n", (T[32+IHL]<<8)|T[33+IHL]);
    return;
}