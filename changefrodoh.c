#include"changefrodoh.h"


//unsigned long long t[NTESTS];

int main()
{	
	int i,j,k;
        uint32_t temp;
        uint8_t *seed;
	uint32_t *A;
        
        uint32_t kmp[l*l], WPP[l*l], WP[l*l], W[l*l], km[l*l];
        uint32_t SP[l*n]={0}, R[n*l],S[n*l]={0};
        //uint64_t BB[n*l],BP[n*l];
	uint32_t BB[n*l],BP[n*l];

        srand((unsigned)time(NULL));

	
       
	seed=(uint8_t *)OPENSSL_malloc(LWE_SEED_LENGTH* sizeof(int8_t));

        RAND_bytes(seed, LWE_SEED_LENGTH);//key->pub->param->seed是uint8_t

       
        A=(uint32_t *)OPENSSL_malloc(n* n * sizeof(uint32_t));

        if (A == NULL) 
        {
	   return 0;
	}
        
   



/*
int iterations = 0;
time_t starttime = time(NULL);
while (1) {

iterations++;	
*/
	     
        if (!gen_a(A, seed, 0))
        {
	  return 0;
	} 



 
	 for (i=0; i<l; i++)//lie
	{
		
			for(k=0;k<64;k++)
			{
                           temp=rand()%792;
			   if(temp%2==0)			                         
                           {S[temp*l+i]=1;}
			   else
			   {S[temp*l+i]=-1;}
			}		
				
	}
   
  



      keygen(BB,A,S); 


/*
if ((iterations % 100) == 0) {
				printf("Iterations: %d,  elapsed time: %ld\n",
				       iterations,  time(NULL) - starttime);
				if (iterations > (1 << 20)) break;
			    }
}
*/

/*
int iterations = 0;
time_t starttime = time(NULL);
while (1) {

iterations++;
*/




	 for (i=0; i<l; i++)
	{
		
			for(k=0;k<64;k++)
			{
                           temp=rand()%792;
			   if(temp%2==0)			                         
                           {SP[i*n+temp]=1;}
			   else
			   {SP[i*n+temp]=-1;}                    
                           
			}		
				
	}

 
   
        int mask=0;

        for(i=0;i<qm-pm;i++){mask+=(1<<i);}

	for (i=0; i<n; i++)
	{  
		for (j=0; j<l; j++)
		{
			
                        temp=rand();
			//R[i*l+j]=(temp-(temp>>(qm-pm)<<(qm-pm)));
                        R[i*l+j]=temp&mask;
		}
	} 


         sharedb(BB,A,BP,kmp,WPP,WP,SP,R);



/*
if ((iterations % 100) == 0) {
				printf("Iterations: %d,  elapsed time: %ld\n",
				       iterations,  time(NULL) - starttime);
				if (iterations > (1 << 20)) break;
			    }
}
*/





int iterations = 0;
time_t starttime = time(NULL);
while (1) {

iterations++;


	
	shareda(BP,S,W);


        rec(km,W,WPP);



if ((iterations % 100) == 0) {
				printf("Iterations: %d,  elapsed time: %ld\n",
				       iterations,  time(NULL) - starttime);
				if (iterations > (1 << 20)) break;
			    }
}





/*
for (i=0; i<l; i++)
	{  
		for (j=0; j<l; j++)
		{ 
                        printf("%u ",km[i*l+j]);
		
		}
	} 
*/




     
        SameOrNo(km,kmp);
	
if (A != NULL) {
		OPENSSL_cleanse(A, LWE_N * LWE_N * sizeof(int16_t));
		OPENSSL_free(A);
	}

	return 0;
}



