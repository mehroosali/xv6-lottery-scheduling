#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int processCount = 32;

//default t = 50
void spin(int t)
{
	int i = 0;
        int j = 0;
        int k = 0;
	for(i = 0; i < t; ++i)
	{
		for(j = 0; j < 100000; ++j)
		{
			k = j % 10;
      k = k + 1;
     }
	}
}

void printStats() {
   struct pstat st;
   getpinfo(&st);

   int i;
   for(i=0; i<processCount; i++) {
      if(st.inuse[i])   {
         printf(1, "Process %d \t (pid: %d)\n", i, st.pid[i]);
         printf(1, "  Tickets: %d\n  Ticks: %d\n", st.tickets[i], st.ticks[i]);
      }
   }
}

int
main(int argc, char *argv[])
{

   printf(1, "starting 3 processes\n");

   int c = 3;
   int i;
   for(i=1; i<=c; i++)   {
      int rt = fork();
      if(rt == 0) {
         //child i
         if(settickets(i*1000)!=0)   {
            printf(1, "*****set ticks %d failed*****\n", i);
         }
         //maybe make forever
         for(;;)  {
            spin(50);
         }
         exit();
      }
   }
   printf(1, "Children Spinning...");
   sleep(1000);
   if (settickets(10000000) != 0){
     printf(1,"check failed: settickets\n");
   }
   printStats();

   for (i = 1; i<=c; i++){
     kill(-1);
   }
   while(wait() > -1);

   exit();
}
