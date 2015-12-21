#include "TComArithmeticComplexity.h"
#include <stdio.h>
double TComArithmeticComplexity::ac_time;
int TComArithmeticComplexity::depth;
#if EN_ARITHMETIC_COMPLEXITY_TUNING
double TComArithmeticComplexity::TIME_SAD[4];
double TComArithmeticComplexity::TIME_SATD[4];
double TComArithmeticComplexity::TIME_SSE[4];
double TComArithmeticComplexity::TIME_TRANSF[4];
double TComArithmeticComplexity::TIME_HALF_INTER[4];
double TComArithmeticComplexity::TIME_QUART_INTER[4];
#endif
unsigned long int TComArithmeticComplexity::COUNT_SAD[4];
unsigned long int TComArithmeticComplexity::COUNT_SATD[4];
unsigned long int TComArithmeticComplexity::COUNT_SSE[4];
unsigned long int TComArithmeticComplexity::COUNT_TRANSF[4];
unsigned long int TComArithmeticComplexity::COUNT_HALF_INTER[4];
unsigned long int TComArithmeticComplexity::COUNT_QUART_INTER[4];
double TComArithmeticComplexity::timeDiff;
unsigned long long int TComArithmeticComplexity::begin;

void TComArithmeticComplexity::initTimeTables(){
    for(int i = 0; i < 4; i++){
        
#if EN_ARITHMETIC_COMPLEXITY_TUNING

        TIME_SAD[i] = 0;
        TIME_SSE[i] = 0;
        TIME_SATD[i] = 0;
        TIME_TRANSF[i] = 0;
        TIME_HALF_INTER[i] = 0;
        TIME_QUART_INTER[i] = 0;
#endif        
        COUNT_SAD[i] = 0;
        COUNT_SATD[i] = 0;
        COUNT_SSE[i] = 0;
        COUNT_TRANSF[i] = 0;
        COUNT_HALF_INTER[i] = 0;
        COUNT_QUART_INTER[i] = 0;
        
    }
}

bool TComArithmeticComplexity::isSAD(int func_enum){
    if ( BETWEEN(func_enum, 8,21) or BETWEEN(func_enum, 43,48))
        return true;
    return false;
}

bool TComArithmeticComplexity::isSSE(int func_enum){
    if ( BETWEEN(func_enum, 1,7) )
        return true;
    return false;
}

bool TComArithmeticComplexity::isSATD(int func_enum){
    if ( BETWEEN(func_enum, 22,28) )
        return true;
    return false;
}

void TComArithmeticComplexity::setDepth(int d){
    depth = d;
}

void TComArithmeticComplexity::printTimeTables(){
    printf("const double TIME_SAD[4] = {");
    for(int i = 0; i < 4; i++)
        printf("%.5f, ", TIME_SAD[i]*1000000.0/COUNT_SAD[i]);
    printf("};\nconst double TIME_SATD[4] = {");
    for(int i = 0; i < 4; i++)
        printf("%.5f,", TIME_SATD[i]*1000000.0/COUNT_SATD[i]);
    printf("};\nconst double TIME_SSE[4] = {");
    for(int i = 0; i < 4; i++)
        printf("%.5f,", TIME_SSE[i]*1000000.0/COUNT_SSE[i]);
    
    printf("};\nconst double TIME_TRANSF[4] = {");
    for(int i = 0; i < 4; i++)
        printf("%.5f,", TIME_TRANSF[i]*1000000.0/COUNT_TRANSF[i]);
    
    printf("};\nconst double TIME_HALF_INTER[4] = {");
    for(int i = 0; i < 4; i++)
        printf("%.5f,", TIME_HALF_INTER[i]*1000000.0/COUNT_HALF_INTER[i]);
    printf("};\nconst double TIME_QUART_INTER[4] = {");
    for(int i = 0; i < 4; i++)
        printf("%.5f,", TIME_QUART_INTER[i]*1000000.0/COUNT_QUART_INTER[i]);
    printf("};\n");
}

//inline static void TComArithmeticComplexity::addDistTime(int func_enum, unsigned int w, unsigned int h){
//    int d;
//    d = 3 - (std::max(w,h) >> 4) // depth = 6 - int(math.log(max(w,h),2)
//    d = (d < 0) ? 0 : d;
//
/*inline void TComArithmeticComplexity::addDistTime(int func_enum){

    if (func_enum < 8)
        ac_time += TIME_SSE[depth];
    else if (func_enum < 22)
        ac_time += TIME_SAD[depth];
    else if (func_enum < 43)
        ac_time += TIME_SATD[depth];
    else
        ac_time += TIME_SAD[depth];

}
*/