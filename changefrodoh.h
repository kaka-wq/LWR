#ifndef HEADER_CHANGEFRODOH_H_
#define HEADER_CHANGEFRODOH_H_

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

#define pm 14
#define qm 32
#define n 792
#define l 8
#define p 16384 //2^17
#define q 4294967296 //2^32
#define B 4

/*
#define pm 30
#define qm 32
#define n 1024
#define l 4
#define p 1073741824 //2^30
#define q 4294967296 //2^32
#define B 16
*/


#define bool int
#define false 0
#define true 1
long long cpucycles(void);
//static void print_results(const char *s, unsigned long long *t, size_t tlen);
void print_results(const char *s, unsigned long long *t, size_t tlen);
int gen_a(uint32_t *a, const uint8_t *seed, const uint8_t transpose);
void keygen(uint32_t * BB,uint32_t *A,uint32_t *S);
void sharedb(uint32_t *BB, uint32_t *A, uint32_t *BP, uint32_t *kmp, uint32_t *WPP,uint32_t *WP,uint32_t *SP,uint32_t *R);
void shareda(uint32_t *BP, uint32_t *S, uint32_t *W);
//int rec(int a, int b);
void rec(uint32_t *km,uint32_t *w,uint32_t *wpp);
void SameOrNo(uint32_t *km,uint32_t *kmp);
#endif
