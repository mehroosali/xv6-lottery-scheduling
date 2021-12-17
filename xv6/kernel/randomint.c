/* The following code is added by Jonathan Perry jjp160630
    getting a random integer from min to max (and various ways)
*/

//#include "stdlib.h"

int seed = 734567;    //six digit seed
int newSeed = 2035587438;
unsigned int fancySeed = 176147161;

int
randNum (int min, int max)
{
  unsigned int next = fancySeed;
  int result;

  next *= 1103515245;
  next += 12345;
  result = (unsigned int) (next / 65536) % 2048;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  fancySeed = next;

  return ((int)result % (max - min + 1)) + min;
}

/*
int inBuiltRandNum(int min, int max)  {
    return (rand() % (max - min + 1)) + min;
}
*/

int newRandNum(int min, int max)   {

    int m = 1836788247;
    int c = 576294715;
    int a = 923874674;

    int result = (a*seed+c)%m;
    if(result<0)    {
        result -= 2*result;
    }
    seed = result;

    return (result % (max - min + 1)) + min;
}

int oldRandNum(int min, int max)   {
    //cprintf("seed-%d\n", seed);
    long result = seed * seed;
    //ensure that results is positive
    if(result<0)    {
        result = result - (2*result);
    }
    //ensure that result has at least 10 digits
    if(result<=1000000000)   {
        result+=1000000000;
    }
    //seed is middle-ish 6 digits of result
    seed = result%100000000;    //get the right most 8
    seed = result/100;   //chop off the right 2
    return (result % (max - min + 1)) + min;
}

int getSeed()   {
    return seed;
}


/* End of added code  */