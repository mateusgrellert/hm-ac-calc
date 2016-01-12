/* 
 * File:   TComArithmeticComplexity.h
 * Author: grellert
 *
 * Created on December 19, 2015, 10:43 AM
 */

#ifndef TCOMARITHMETICCOMPLEXITY_H
#define	TCOMARITHMETICCOMPLEXITY_H

#define EN_ARITHMETIC_COMPLEXITY_MEASURING 0
#define EN_ARITHMETIC_COMPLEXITY_TUNING 1


#include <stdio.h>
#include <fstream>

#if EN_ARITHMETIC_COMPLEXITY_MEASURING

// ===== BLACKY ========
//const double TIME_SAD[5] = {0.9863,0.3315,0.1762,0.1170};  // IN MICROSECONDS!!!!!!
//const double TIME_SSE[5] = {8.8339,1.9178,0.4331,0.0991};
//const double TIME_SATD[5] = {5.4230,1.4477,0.4282,0.1884};
//const double TIME_TRANSF[5] = {9.8506,1.7116,0.4342,0.2539};
//const double TIME_HALF_INTER[5] = {40.9460,9.9546,3.2599,1.4155};
//const double TIME_QUART_INTER[5] = {91.6610,21.5360,6.3011,2.2778};




// === IMAC =========
const double TIME_SAD[5] = {1.19751, 0.31412, 0.09382, 0.05736, 0};
const double TIME_SATD[5] = {7.21264,1.81197,0.46692,0.12916, 0};
const double TIME_SSE[5] = {2.96286,0.66671,0.19061,0.06339, 0};
const double TIME_TRANSF[5] = {11.41940,1.61500,0.27588,0.05912, 0};
const double TIME_HALF_INTER[5] = {53.44381,15.16350,4.84652,1.88722, 0};
const double TIME_QUART_INTER[5] = {112.13131,31.16828,9.46509,3.41669, 0};

#endif // #if EN_ARITHMETIC_COMPLEXITY_MEASURING



class TComArithmeticComplexity{

public:
    static double ac_time, factor;
    static int depth;
    static unsigned long long begin;
    static std::ofstream debugFile;
    
#if EN_ARITHMETIC_COMPLEXITY_TUNING
    static double COUNT_SAD[4], COUNT_SATD[4], COUNT_SSE[4], COUNT_TRANSF[4], COUNT_HALF_INTER[4], COUNT_QUART_INTER[4];
#endif
    
    static bool isSAD(int func_enum);
    static bool isSSE(int func_enum);
    static bool isSATD(int func_enum);
    static void setDepth(int d);
    static void initCountTables();

    
    
    
    static void printCountTables();
    
    static inline void addDistTime(int func_enum,int width, int height){
        
#if EN_ARITHMETIC_COMPLEXITY_MEASURING
        setDepth(width, height);
        setAdjustFactor(width,height);
        if (func_enum < 8)
            ac_time += TIME_SSE[depth]*factor;
        else if (func_enum < 22)
            ac_time += TIME_SAD[depth]*factor;
        else if (func_enum < 43)
            ac_time += TIME_SATD[depth]*factor;
        else
            ac_time += TIME_SAD[depth]*factor;
#endif
    }
        
    static inline void incDistCount(int func_enum, int width, int height){
#if EN_ARITHMETIC_COMPLEXITY_TUNING
        setDepth(width, height);
        setAdjustFactor(width,height);

        if (func_enum < 8){
            COUNT_SSE[depth] += factor;
        }
        else if (func_enum < 22){
            COUNT_SAD[depth] += factor;
        }        
        else if (func_enum < 43){
            COUNT_SATD[depth] += factor;
        }        
        else{
            COUNT_SAD[depth] += factor;
        }
#endif
    }
    
    static inline void setDepth(int w, int h){
        int max = (w > h) ? w : h;
        if(max == 64)
            depth = 0;
        else if(max == 32)
            depth = 1;
        else if(max == 16)
            depth = 2;
        else if(max == 8)
            depth = 3;
        else
            depth = -1;
    }
        
    static inline void setAdjustFactor(int w, int h){
        int max = (w > h) ? w : h;
        factor = ((w*h)*1.0)/(max*max*1.0);
    }
    
    
};



#endif	/* TCOMARITHMETICCOMPLEXITY_H */