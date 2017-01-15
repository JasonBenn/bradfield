#include <stdio.h>

int countLeadingOnes(unsigned byte) {
    int nextBitIndex = 7;
    while ((1 << nextBitIndex & byte) >> nextBitIndex == 1)
        nextBitIndex--;
    return 7 - nextBitIndex;
}

typedef enum { ASCII, UTF8_CONTINUATION, UTF8_LEAD_2, UTF8_LEAD_3, UTF8_LEAD_4, OTHER } byteType;

void printByteType(byteType type) {
    if (type == ASCII)
        printf("ASCII\n");
    else if (type == UTF8_LEAD_2 || type == UTF8_LEAD_3 || type == UTF8_LEAD_4)
        printf("UTF-8 lead byte\n");
    else if (type == UTF8_CONTINUATION)
        printf("UTF-8 continuation byte\n");
    else
        printf("Other\n");
}

int main(void) {
    printByteType((byteType) countLeadingOnes(0b11000000)); // UTF-8 first byte
    printByteType((byteType) countLeadingOnes(0b10000000)); // UTF-8 continuation byte
    printByteType((byteType) countLeadingOnes(0b01000000)); // ASCII
}
