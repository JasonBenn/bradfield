#include <stdio.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

void printBinary(unsigned byte) {
    printf(""BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(byte));
    printf("\n");
}


unsigned getBits(unsigned bitfield, int start, int length) {
    bitfield >>= start;
    unsigned mask = (1 << length) - 1;
    return bitfield & mask;
}

unsigned setBits(unsigned bitfield, int start, int length, int value) {
    printf("bitfield: ");
    printBinary(bitfield);
    unsigned mask = ((1 << length) - 1) << length;
    printf("mask: ");
    printBinary(mask);
    printf("negative mask: ");
    printBinary(~mask);
    bitfield &= ~mask;
    printf("negative mask'd bitfield: ");
    printBinary(bitfield);
    printf("value to insert: ");
    printBinary(value);
    printf("value to insert, moved into position: ");
    printBinary(value << (start + 1));
    printf("answer: ");

    return bitfield | (value << (start + 1));
}

//int main(void) {
//    printBinary(setBits(0b11111111, 2, 3, 0b101)); // 101 010 10
//}