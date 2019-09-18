#include"changefrodoh.h"
#include<malloc.h>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
////////////////////////////////
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define NTESTS 1000

/////////////////////////////////////
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define LWE_SEED_LENGTH 16  // the seed length in bytes
#define LWE_STRIPE_STEP 8
#define LWE_N 792
//#define LWE_N 1024
///////////////////////////////////
/*
#define pm 22
#define qm 31
#define n 752
#define l 8
#define p 4194304 //2^22
#define q 2147483648 //2^31
#define B 4
*/
/*
#define pm 30
#define qm 32
#define n 752
#define l 4
#define p 1073741824 //2^30
#define q 4294967296 //2^32
#define B 16
*/
/*
#define pm 19
#define qm 21
#define n 752
#define l 8
#define p 524288 //2^29
#define q 2097152 //2^31
#define B 4
*/
/*
#define pm 14
#define qm 16
#define n 752
#define l 4
#define p 16384 //2^14
#define q 65536 //2^16
#define B 4
*/
#define bool int
#define false 0
#define true 1
long long cpucycles(void)
{
  unsigned long long result;
  asm volatile(".byte 15;.byte 49;shlq $32,%%rdx;orq %%rdx,%%rax"
    : "=a" (result) ::  "%rdx");
  return result;
}

static int cmp_llu(const void *a, const void*b)
{
  if(*(unsigned long long *)a < *(unsigned long long *)b) return -1;
  if(*(unsigned long long *)a > *(unsigned long long *)b) return 1;
  return 0;
}

static unsigned long long median(unsigned long long *lp, size_t llen)
{
  qsort(lp,llen,sizeof(unsigned long long),cmp_llu);

  if(llen%2) return lp[llen/2];
  else return (lp[llen/2-1]+lp[llen/2])/2;
}

static unsigned long long average(unsigned long long *t, size_t tlen)
{
  unsigned long long acc=0;
  size_t i;
  for(i=0;i<tlen;i++)
    acc += t[i];
  return acc/(tlen);
}

 void print_results(const char *s, unsigned long long *t, size_t tlen)
{
  size_t i;
  printf("%s", s);
  for(i=0;i<tlen-1;i++)
  {
    t[i] = t[i+1] - t[i];
  //  printf("%llu ", t[i]);
  }
  printf("\n");
  printf("median: %llu\n", median(t, tlen));
  printf("average: %llu\n", average(t, tlen-1));
  printf("\n");
}
