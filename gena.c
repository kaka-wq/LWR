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
int gen_a(uint32_t *a, const uint8_t *seed, const uint8_t transpose) //transpose///
{
	int i, j;
	int ret = 0;
	/* We generate A using 128 bytes of memory at a time. */
	EVP_CIPHER_CTX *aes_ctx = EVP_CIPHER_CTX_new();
	if (aes_ctx == NULL) {
		goto err;
	}

	if (1 != EVP_EncryptInit_ex(aes_ctx, EVP_aes_128_ecb(), NULL, seed, NULL)) {
		goto err;
	}

	EVP_CIPHER_CTX_set_padding(aes_ctx, 0);  // no padding in the ECB mode

	size_t a_len = LWE_N * LWE_N * sizeof(uint32_t);

	memset(a, 0, a_len);

	for (i = 0; i < LWE_N; i++)
		for (j = 0; j < LWE_N; j += LWE_STRIPE_STEP) {
			a[i * LWE_N + j] = i;
			a[i * LWE_N + j + 1] = j;
		}

	int outlen;

	if (1 != EVP_EncryptUpdate(aes_ctx, (unsigned char *)a, &outlen,
	                           (unsigned char *)a, a_len) ||
	        ((size_t) outlen != a_len)) {
		goto err;
	}

	if (1 != EVP_EncryptFinal_ex(aes_ctx, (unsigned char *)a, &outlen)) {
		// not necessary since padding is disabled
		goto err;
	}

	if (transpose) // in-situ transpose of the square matrix
		for (i = 0; i < LWE_N; i++)
			for (j = i + 1; j < LWE_N; j++) {
				uint32_t tmp = a[i * LWE_N + j];
				a[i * LWE_N + j] = a[j * LWE_N + i];
				a[j * LWE_N + i] = tmp;
			}

	ret = 1;

err:
	if (aes_ctx != NULL) EVP_CIPHER_CTX_free(aes_ctx);
	return ret;
}
