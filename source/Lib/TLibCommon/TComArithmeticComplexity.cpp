#include "TComArithmeticComplexity.h"
#include <stdio.h>
double TComArithmeticComplexity::ac_time;
int TComArithmeticComplexity::depth;
double TComArithmeticComplexity::factor;
#if EN_ARITHMETIC_COMPLEXITY_TUNING

double TComArithmeticComplexity::COUNT_SAD[4];
double TComArithmeticComplexity::COUNT_SATD[4];
double TComArithmeticComplexity::COUNT_SSE[4];
double TComArithmeticComplexity::COUNT_TRANSF[4];
double TComArithmeticComplexity::COUNT_HALF_INTER[4];
double TComArithmeticComplexity::COUNT_QUART_INTER[4];
#endif

std::ofstream TComArithmeticComplexity::debugFile;

void TComArithmeticComplexity::initCountTables(){
            
    debugFile.open("debug_timing.csv", std::ofstream::out);

    for(int i = 0; i < 4; i++){
#if EN_ARITHMETIC_COMPLEXITY_TUNING
        COUNT_SAD[i] = 0;
        COUNT_SATD[i] = 0;
        COUNT_SSE[i] = 0;
        COUNT_TRANSF[i] = 0;
        COUNT_HALF_INTER[i] = 0;
        COUNT_QUART_INTER[i] = 0;
#endif
    }
}

void TComArithmeticComplexity::setDepth(int d){
    depth = d;
}

void TComArithmeticComplexity::printCountTables(){
#if EN_ARITHMETIC_COMPLEXITY_TUNING
    printf("\nNCALLS \n\tSAD\tSATD\tSSE\tTransf\tHalf\tQuarter\n");
    for(int i = 0, j = 64; i < 4; i++, j >>= 1){
        printf("%dx%d\t",j,j);
        printf("%.2f\t", COUNT_SAD[i]);
        printf("%.2f\t", COUNT_SATD[i]);
        printf("%.2f\t", COUNT_SSE[i]);
        printf("%.2f\t", COUNT_TRANSF[i]);
        printf("%.2f\t", COUNT_HALF_INTER[i]);
        printf("%.2f\t\n", COUNT_QUART_INTER[i]);

    }
    printf("\n");
#endif
}
