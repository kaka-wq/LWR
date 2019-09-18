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
*/

#define bool int
#define false 0
#define true 1

/*
void rec(uint32_t *km,uint32_t *w,uint32_t *wpp)
{
   uint32_t i;
   uint32_t j,k,t;
   for(k=0;k<l;k++)
   {
    for(t=0;t<l;t++)
    {
     for(i=0;i<(q/2);i++)
     {
       j=w[k*l+t]+i;
     
       //if(((j*4)>>qm)-(((j*4)>>qm)>>1<<1)==wpp[k])
       if(((j>>(qm-B-1))&1)==wpp[k*l+t])
       //if((j>>(qm-B-1))-((j>>(qm-B-1))>>1<<1)==wpp[k*l+t])
       {         
           
           km[k*l+t]=(j>>(qm-B))&15;
           //km[k*l+t]=(j>>(qm-B))-((j>>(qm-B))>>4<<4);
           break;      
       }
           j=w[k*l+t]-i;
     

       //if(((j*4)>>qm)-((((j*4)>>qm))>>1<<1)==wpp[k])
       if(((j>>(qm-B-1))&1)==wpp[k*l+t])
       //if((j>>(qm-B-1))-((j>>(qm-B-1))>>1<<1)==wpp[k*l+t])
       {     
          
           km[k*l+t]=(j>>(qm-B))&15;
           //km[k*l+t]=(j>>(qm-B))-((j>>(qm-B))>>4<<4);
           break;       
       }
      }
     }
       
   }
}
*/
void rec(uint32_t *km,uint32_t *w,uint32_t *wpp)
{
uint32_t f[64]={0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,14,14,14,14,15,15,15,15};
uint32_t j[64]={0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
int32_t k,t,s,z;
uint64_t ww;

for(k=0;k<l;k++)
   {
    for(t=0;t<l;t++)
    {
	//ww=w[k*l+t];
	ww=w[k*l+t]%q;
        s=ww>>(qm-B-2);
	
		if(j[s]==wpp[k*l+t]){km[k*l+t]=f[s];continue;}

		if(s+1>=64){
                z=s+1-64;

		if(j[z]==wpp[k*l+t]){
		km[k*l+t]=f[z];
		continue;}}
		if(j[s+1]==wpp[k*l+t]){km[k*l+t]=f[s+1];continue;}

		if(s-1<0){
                z=s-1+64;
		if(j[z]==wpp[k*l+t]){km[k*l+t]=f[z];
		continue;}}
		if(j[s-1]==wpp[k*l+t]){km[k*l+t]=f[s-1];continue;}
      }
     }
}

void SameOrNo(uint32_t *km,uint32_t *kmp)
{
	int i,j;
	bool flag = true;

	for (i=0; i<l; i++)
	{
		for (j=0; j<l; j++)
		{
	 	   if(km[i*l+j]!=kmp[i*l+j])
		   {
		    	flag = false;
                        break;
		   }
		   
		} 
	}
    
	if(flag) 
	{
		printf("successful\n");
	}
	else
	{
		printf("fail\n");
	}

}
