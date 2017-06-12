#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define STRINGIFY(x) #x
#define MACRO(x)     STRINGIFY(x)

#define ITER 1000000
#define RANGE 1000000000000

int gcd(unsigned long long a, unsigned long long b) {
    unsigned long long temp;
    while (b != 0)
    {
        temp = a % b;

        a = b;
        b = temp;
    }
    return a;
}

int main(int argc, char const *argv[]) {
    #ifdef DEBUG
    printf("+--------------------+\n| Build ID: %s |\n+--------------------+\n\n", MACRO(BUILDID));
    #endif

    uintmax_t Iter = ITER;
    uintmax_t Range = RANGE;
    unsigned long long RC = 0;
    unsigned long long Time;
    double pi = 0;

    if (argc > 1) {
        if (atoi(argv[1]) > 0) {
            Iter = atoi(argv[1]);
            printf("Iter set to: %lu\n", Iter);
        }
    }
    if (argc > 2) {
        if (atoi(argv[2]) > 0) {
            Range = atoi(argv[2]);
            printf("Range set to: %lu\n", Range);
        }
    }
    if (argc > 3) {
        if (atoi(argv[3]) > 0) {
            RC = atoi(argv[3]);
            printf("Randomness set to: %llu\n", RC);
        }
    }


    //Seed the randomness
    Time = time(NULL) * rand();

    srand(Time);
    printf("Seed: %llu\n\n", Time);
    for (size_t i = 0; i < (rand() % 20000); i++) {
        pi = rand();
    }

    //Calculate randomness
    if (RC == 0) {
        for (unsigned long i = 0; i < Iter; i++) {
            unsigned long long R1 = rand() % Range;
            unsigned long long R2 = rand() % Range;
            if (gcd(R1, R2) == 1) {
                RC++;
            }
        }
    }
    double randomness = (double)RC/(double)Iter;
    printf("Randomness == %llu/%lu | %f\n", RC, Iter, randomness);

    //Calculate Pi
    pi = sqrt(6/randomness);

    printf("PI: ~%.10lf\n", pi);

    return 0;
}
