#include "stdio.h"
#include "stdlib.h"
#include "myAllocator.h"
#include "sys/time.h"
#include <sys/resource.h>
#include <unistd.h>

double diffTimeval(struct timeval *t1, struct timeval *t2) {
  double d = (t1->tv_sec - t2->tv_sec) + (1.0e-6 * (t1->tv_usec - t2->tv_usec));
  return d;
}

void getutime(struct timeval *t)
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  *t = usage.ru_utime;
}

int main() 
{
  void *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8;
  
  p1 = bestFitAllocRegion(254);
  p2 = bestFitAllocRegion(25400);
  p3 = bestFitAllocRegion(254);
  p3 = resizeRegion(p3,400);
  p4 = bestFitAllocRegion(13);
  p4 = resizeRegion(p4,500); /* resize p4 from 16 to 504 */
  p5 = bestFitAllocRegion(254);
  //printf("%8zx %8zx %8zx %8zx\n", p1, p2, p3, p4);
  arenaCheck();
  freeRegion(p2);
  arenaCheck();
  freeRegion(p4);
  arenaCheck();
  p6 = bestFitAllocRegion(300);  /* is fit in available region left by free p4 */
  p7 = bestFitAllocRegion(100);  
  p8 = bestFitAllocRegion(2000); /* is fit in available region left by free p2 */
  arenaCheck();
  freeRegion(p3);
  arenaCheck();
  freeRegion(p1);
  arenaCheck();
  freeRegion(p5);
  arenaCheck();
  freeRegion(p6);
  freeRegion(p7);
  arenaCheck();
  freeRegion(p8);
  arenaCheck();
  {				/* measure time for 10000 mallocs */
    struct timeval t1, t2;
    int i;
    getutime(&t1);
    for(i = 0; i < 10000; i++)
      if (firstFitAllocRegion(4) == 0) 
	break;
    getutime(&t2);
    printf("%d firstFitAllocRegion(4) required %f seconds\n", i, diffTimeval(&t2, &t1));
  }
  return 0;
}



