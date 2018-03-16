//#include <QCoreApplication>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const uint8_t size = 5 ;


class Lato {
public:
    Lato(const uint16_t val) {
        static const uint16_t max = 255 >> ( 8 - size);
        static const uint16_t maxBit = size - 1;
        static const uint16_t minBit = 2;
        auto bit = __builtin_popcount(val);
        if(bit > maxBit || val > max){
            printf("%i is too big (more than %i)!\n", val, max);
            exit(1);
        }
        if(bit < minBit){
            printf("%i is too small!\n", val);
            exit(1);
        }
    }
};

class Quad {
public:
    Quad () {}
};

int main(int argc, char *argv[]) {
    Lato a(24);
    return 0;
}
