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

#define Bm 65536//2^16
*/

#define bool int
#define false 0
#define true 1
void keygen(uint32_t *BB,uint32_t *A,uint32_t *S)
{
	int i,j,k;
        uint32_t temp;
	//uint64_t BBB[n*l];
	for (i=0; i<n; i++)
	{  
		for (j=0; j<l; j++)
		{
			temp=0;
		    for (k=0; k<n; k++)
			{
			
			temp += A[i*n+k]*S[k*l+j] ;
                        
			
			}
						 
                         
                         BB[i*l+j]=temp&(-262144);//divide 2^18,qu xia zheng multi 2^18
                         //BB[i*l+j]=temp>>(qm-pm);//2^18
			
            
		} 
	}
        //memcpy(BB,BBB,sizeof(uint64_t)*n*l);
     
        
}

void sharedb(uint32_t *BB, uint32_t *A, uint32_t *BP, uint32_t *kmp, uint32_t *WPP,uint32_t *WP,uint32_t *SP,uint32_t *R)//l,n
{
	int i,j,k;
        uint32_t temp;
       


	for (i=0; i<l; i++)
	{  
		for (j=0; j<l; j++)
		{
			temp=0;
		    for (k=0; k<n; k++)
			{
			
                        temp += SP[i*n+k]*(BB[k*l+j]+R[k*l+j]);
			}
                        WP[i*l+j]=temp;
                      
		} 
	}
	


uint32_t AT[n*n],SPT[n*l];
uint32_t BPT[n*l];
for (i=0; i<n; i++)
	{  
		for (j=0; j<n; j++)
		{
			AT[i*n+j]=A[j*n+i];
		}
	}

for (i=0; i<n; i++)
	{
		for (j=0; j<l; j++)
		{
			
			SPT[i*l+j]=SP[j*n+i];
		}
	}

keygen(BPT,AT,SPT);



for (i=0; i<l; i++)
	{
	for (j=0; j<n; j++)
		{ 
			BP[i*n+j]=BPT[j*l+i];
		}
	}


	
	for (i=0; i<l; i++)
	{  
		for (j=0; j<l; j++)
		{
			kmp[i*l+j] = WP[i*l+j]>>(qm-B);
                        //kmp[i][j] = WP[i][j]*Bm/q; 
                        kmp[i*l+j] = kmp[i*l+j]&15; 
                        //kmp[i*l+j] = kmp[i*l+j]-(kmp[i*l+j]>>4<<4);     
		} 
	}
    
	for (i=0; i<l; i++)
	{  
		for (j=0; j<l; j++)
		{
			//(WPP[i][j]) = (WP[i][j]+q)>>(qm-B-1);
                         WPP[i*l+j] = WP[i*l+j]>>(qm-B-1);
                         //WPP[i][j] = WP[i][j]*2*Bm/q;

                    WPP[i*l+j] =WPP[i*l+j]&1;
                     // WPP[i*l+j] =WPP[i*l+j]-(WPP[i*l+j]>>1<<1);
                    
		} 
	}
        
       
        
}

void shareda(uint32_t *BP, uint32_t *S, uint32_t *W)
{
	int i,j,k;
        uint32_t temp;

	for (i=0; i<l; i++)
	{  
		for (j=0; j<l; j++)
		{
			temp=0;
		    for (k=0; k<n; k++)
			{
			temp += BP[i*n+k]*S[k*l+j];
			}
                        W[i*l+j] = temp;
                       
		} 
	}
	

}
