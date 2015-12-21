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
#define CPU_TICKS_PER_SECOND 3400000000.0

#define BETWEEN(x,a,b) ((x) >= (a) && (x) <= (b)) ? true : false

#include <stdio.h>

#if EN_ARITHMETIC_COMPLEXITY_MEASURING

// ===== BLACKY ========
//const double TIME_SAD[4] = {0.9863,0.3315,0.1762,0.1170};  // IN MICROSECONDS!!!!!!
//const double TIME_SSE[4] = {8.8339,1.9178,0.4331,0.0991};
//const double TIME_SATD[4] = {5.4230,1.4477,0.4282,0.1884};
//const double TIME_TRANSF[4] = {9.8506,1.7116,0.4342,0.2539};
//const double TIME_HALF_INTER[4] = {40.9460,9.9546,3.2599,1.4155};
//const double TIME_QUART_INTER[4] = {91.6610,21.5360,6.3011,2.2778};

// ===== IMAC =======
//const double TIME_SAD[4] = {0.884, 0.227, 0.084, 0.051};  // IN MICROSECONDS!!!!!!
//const double TIME_SSE[4] = {3.165, 0.708, 0.214, 0.059};
////const double TIME_SSE[4] = {0,0,0,0};
//const double TIME_SATD[4] = {4.350, 1.103, 0.276, 0.087};
//const double TIME_TRANSF[4] = {11.701, 1.774, 0.353, 0.118};
//const double TIME_HALF_INTER[4] = {38.355, 9.938, 3.536, 1.742};
//const double TIME_QUART_INTER[4] = {80.044, 20.393, 6.731, 2.905};
//const double TIME_HALF_INTER[4] = {38.355*INTERP_ERROR, 9.938*INTERP_ERROR, 3.536*INTERP_ERROR, 1.742*INTERP_ERROR};
//const double TIME_QUART_INTER[4] = {80.044*INTERP_ERROR, 20.393*INTERP_ERROR, 6.731*INTERP_ERROR, 2.905*INTERP_ERROR};
//const double TIME_HALF_INTER[4] = {0,0,0,0};
//const double TIME_QUART_INTER[4] = {0,0,0,0};


//
// --MaxPartitionDepth=4
//const double TIME_SAD[4] = {0.870669, 0.218422, 0.077836, 0.052395};
//const double TIME_SATD[4] = {4.314265, 1.090025, 0.271185, 0.084821};
//const double TIME_SSE[4] = {3.113369, 0.701350, 0.214770, 0.061847};
//const double TIME_TRANSF[4] = {11.970484, 1.825177, 0.357812, 0.116208};
//const double TIME_HALF_INTER[4] = {37.933287, 9.808228, 3.479040, 1.702531};
//const double TIME_QUART_INTER[4] = {79.160077, 20.150851, 6.633371, 2.861608};
// --MaxPartitionDepth=3
//const double TIME_SAD[4] = {0.854727, 0.213420, 0.086328, 0.061444};
//const double TIME_SATD[4] = {4.249365, 1.086499, 0.340692, 0.148969};
//const double TIME_SSE[4] = {3.065274, 0.699989, 0.211335, 0.061782};
//const double TIME_TRANSF[4] = {11.791864, 1.805730, 0.345461, 0.119768};
//const double TIME_HALF_INTER[4] = {37.359632, 9.643600, 3.757362, 2.013447};
//const double TIME_QUART_INTER[4] = {78.059694, 19.859897, 7.127589, 3.526860};
// --MaxPartitionDepth=2
const double TIME_SAD[4] = {0.53971, 0, 0, 0, };
const double TIME_SATD[4] = {3.21357,0,0,0,};
const double TIME_SSE[4] = {0.19311,0,0,0,};
const double TIME_TRANSF[4] = {11.43051,1.61614,0.27229,0.05880,};
const double TIME_HALF_INTER[4] = {23.59637,0,0,0,};
const double TIME_QUART_INTER[4] = {49.86148,0,0,0,};
// --MaxPartitionDepth=1
//const double TIME_SAD[4] = {0.874331, 0.339831, 0.000000, 0.000000};
//const double TIME_SATD[4] = {5.002521, 1.873949, 0.000000, 0.000000};
//const double TIME_SSE[4] = {3.102756, 0.691150, 0.200879, 0.061595};
//const double TIME_TRANSF[4] = {11.928403, 1.786580, 0.347350, 0.112669};
//const double TIME_HALF_INTER[4] = {37.990816, 15.558401, 0.000000, 0.000000};
//const double TIME_QUART_INTER[4] = {79.417381, 32.208118, 0.000000, 0.000000};

#endif // #if EN_ARITHMETIC_COMPLEXITY_MEASURING



#if defined(__i386__)

static __inline__ unsigned long long rdtsc(void)
{
  unsigned long long int x;
     __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
     return x;
}
#elif defined(__x86_64__)


//static __inline__ unsigned long long rdtsc(void)
//{
//  unsigned hi, lo;
//  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
//  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
//}

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
 __asm__ __volatile__("CPUID\n\t"
                    "RDTSC\n\t"
                    "mov %%edx, %0\n\t"
                    "mov %%eax, %1\n\t": "=r" (hi), "=r" (lo)::
                    "%rax", "%rbx", "%rcx", "%rdx");
 return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

static __inline__ unsigned long long rdtsc_end(void)
{
        unsigned hi, lo;

   __asm__ __volatile__("RDTSCP\n\t"
     "mov %%edx, %0\n\t"
     "mov %%eax, %1\n\t"
     "CPUID\n\t": "=r" (hi), "=r" (lo)::
    "%rax", "%rbx", "%rcx", "%rdx");
   return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );

}
#elif defined(__powerpc__)


static __inline__ unsigned long long rdtsc(void)
{
  unsigned long long int result=0;
  unsigned long int upper, lower,tmp;
  __asm__ volatile(
                "0:                  \n"
                "\tmftbu   %0           \n"
                "\tmftb    %1           \n"
                "\tmftbu   %2           \n"
                "\tcmpw    %2,%0        \n"
                "\tbne     0b         \n"
                : "=r"(upper),"=r"(lower),"=r"(tmp)
                );
  result = upper;
  result = result<<32;
  result = result|lower;

  return(result);
}

#endif

class TComArithmeticComplexity{

public:
    static double ac_time;
    static int depth;
    static unsigned long long begin;
    static double timeDiff;
    
#if EN_ARITHMETIC_COMPLEXITY_TUNING
    static double TIME_SAD[4], TIME_SATD[4], TIME_SSE[4], TIME_TRANSF[4], TIME_HALF_INTER[4], TIME_QUART_INTER[4];
#endif
        
    static unsigned long int COUNT_SAD[4], COUNT_SATD[4], COUNT_SSE[4], COUNT_TRANSF[4], COUNT_HALF_INTER[4], COUNT_QUART_INTER[4];

    static bool isSAD(int func_enum);
    static bool isSSE(int func_enum);
    static bool isSATD(int func_enum);
    static void setDepth(int d);
    static void initTimeTables();

    
    
    
    static void printTimeTables();
    
    static inline void addDistTime(int func_enum){

        if (func_enum < 8)
            ac_time += TIME_SSE[depth];
        else if (func_enum < 22)
            ac_time += TIME_SAD[depth];
        else if (func_enum < 43)
            ac_time += TIME_SATD[depth];
        else
            ac_time += TIME_SAD[depth];

    }
        
    static inline void setDistTime(int func_enum){
#if EN_ARITHMETIC_COMPLEXITY_TUNING
        if (func_enum < 8){
            TIME_SSE[depth] += timeDiff;
            COUNT_SSE[depth] ++;
        }
        else if (func_enum < 22){
            TIME_SAD[depth] += timeDiff;
            COUNT_SAD[depth] ++;
        }        
        else if (func_enum < 43){
            TIME_SATD[depth] += timeDiff;
            COUNT_SATD[depth] ++;
        }        
        else{
            TIME_SAD[depth] += timeDiff;
            COUNT_SAD[depth] ++;
        }
#endif
    }
    
    static inline void initTimer(){
        begin = rdtsc();
    }
    static inline void endTimer(){
        timeDiff = (rdtsc_end() - begin)/CPU_TICKS_PER_SECOND;
    }

    
    
    
};



#endif	/* TCOMARITHMETICCOMPLEXITY_H */