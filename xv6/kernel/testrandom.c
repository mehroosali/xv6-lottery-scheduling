#include "stdio.h"
#include "randomint.c"


void main() {

    int i;
    long result;

    //USER VARIABLES
    long numberToGenerate = 3000;
    long maxValue = 6000;
    int minValue = 1;
    int binCount = 2;
    
    float split = (float)maxValue/(float)binCount;
    float binSize = numberToGenerate/binCount;
    long count = 0;
    long bin[binCount];
    for(i=0; i<binCount; i++)   {
        bin[i] = 0;
    }

    for(i=0; i<numberToGenerate; i++) {
        result = randNum(minValue,maxValue);

        if(numberToGenerate<=25)    {
           printf("Result: %d\n",result);
        }

        count+=result;
        int q;
        for(q = 0; q<binCount; q++) {
            if((float)result>=(float)q*split+minValue && (float)result<((float)q+1)*split+minValue)    {
                bin[q]++;
            }
        }
        if(i/100000==0) {
            //printf("Result: %d\n",result);
            //printf("Seed: %d\n", getSeed());
        }

    }

    for(i=0; i<binCount; i++)   {
        printf("bin: %d\tcount: %d\terror:%f\%\n", i+1, bin[i], ((float)bin[i]/(binSize)-1)*100);
    }

    int meanOff = count/numberToGenerate - maxValue/2;
    printf("Mean-Off: %d\n",meanOff);
}