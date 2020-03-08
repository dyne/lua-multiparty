/*
    Licensed to the Apache Software Foundation (ASF) under one
    or more contributor license agreements.  See the NOTICE file
    distributed with this work for additional information
    regarding copyright ownership.  The ASF licenses this file
    to you under the Apache License, Version 2.0 (the
    "License"); you may not use this file except in compliance
    with the License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing,
    software distributed under the License is distributed on an
    "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
    KIND, either express or implied.  See the License for the
    specific language governing permissions and limitations
    under the License.
*/
/**
 * @file test_big_consistency.c
 * @author Samuele Andreoli
 * @brief Test for consistency of FF_4096
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arch.h"
#include "amcl.h"
#include "utils.h"
#include "ff_4096.h"

#define FS_4096  MODBYTES_512_60*FFLEN_4096
#define HFS_4096 MODBYTES_512_60*HFLEN_4096

#if 4096 == 2048
char *Phex = "cc44dc413faedf280f429f57881d48047e6041b16774b3074e81c6d2b2753269e61db41fb6a1bddc43f4257c49724f1d2678df0fc4d05032d228037c6580ed4b35001f1c01d788c1a5e2dfd3f676b25646d7df23d62bff478c5875327ca47b0145153fb316ad2289687fbc6fc113dca2d592e9761dd0d60577a1551c1cd37c29";
char *Qhex = "f68a619af0db4e19ed9c32569b25650e4cd9d9b3949bad18ce58c77770413e823c92dea3eb0a0a41425b2a0ba4e329c42d89bba26548ec3544a9798c887a0e1bb419e73374202505ada6b63c63ba9af2b10ab7c80efe4bf752cb951e6c8a763d6fa6430c23547f2e671303bc3e9591f45696f25c2da64939ff2346f636581e0d";
#elif 4096 == 3072
char *Phex = "e80f3579282159380cd9a7923b90d5565795bc46a3ef5fcaec8769886a6e59499db17e8eb9163f714bf481d100c7ed66e2ec6f45389d74146ed02e7c9e0bfadb0e9625c3eaf55ce460c812ef04cb83213dc136212c88c16afc43d1b1dc53f5326804b853b60165c913740f127e7649778993852d3b46517ce75eed668976fdd9b8bb4b548a9012465b60aa5215c9fff7b4b3d270e0892add878d5fc97124b66094b358e68ced76a1d75db07804b7b0986eef123175f30a6e7530aa14c0c3cd41";
char *Qhex = "e01b5c4cc562898d5dda3a71699b9bbde49d89f25868f6806a484c660cacfac59c2d42550960245c509dbfdec01dc980d2c50f3074fc188291ef4e4345850875eb150b7eb1d9d1f4354dd462ffaca772900b5c915ad4e17ec286343913bf3650b34c32fe240305f61c4c57ae3012027d987a84a33087990365f5ac7d1c6ea53e62af477e3fbda86b22c1c80ebcece950627b981052a7e7ca0789eee7b14df7c174660799e583d8d5284cb97821fbb02d00be90fad65e6a9d231b1fac04ef69b9";
#else
char *Phex = "e94f422c81696ed652102bb6dfa96e2977f6b0e16188b89319f00c2aad1e5d9617fe5d5126ce31e8a6f957caa56102f4863452bf901d53d8595c3fa4dc6ca6bfb76ec4ebed2f46e508bb6501a35cda8fde7caec29b3dd09b540a24019fc6bb1d28975a0946f01b226bd81d1a2c8d92287b22a4bb55c894caa4a7b35071b4e261b5cf3d10706eb4ca3dfe75181c356aa8bfc3d4ce03dda4a58149d9a6489e06b79db9390ea97e6e498047518ab32e5151ecb644342ec750da99f08fab040f7a02506d5b603b69ee3efdb403a90361a9ff307e6c55b20759ef0907d03aa8190813a522a340accc1a2f520098f2b56c8f9d977a3922a8d4eba1b0219697a91f8eb1";
char *Qhex = "ec0a7fd563b3e58212e3ce6437a07df1294c8cb44ed3f66af0e5145db048db2e02de30e08e3c9ee8ecc6335ed8d4ba2bbbd699fbcd599f0db98e1433a071a7e331fba574926ca61131f35cf7b7b770a5fd7ccd2ac60054ddfc79fe9b587c28bf2ab3350aef850bc74b9508af2bc291c13823369d38c79a1b86539d52d3d4bf4a1ffe07274cef610660ea936bce4c9eaab4334b5e28a61703860fec1898c83d97439be945c8e782430a13428d3fe5d6ebc9d03baf027c4c1822a092c58120fc2180ad61d568c124401ab2ff12148a1a434d2832d971a113d5577fda4245e139a971336b10b5d83f1a74511a89cca229f6c89bb447b2dfcb8ecbfbb623b504252f";
#endif

int main()
{

    int i;
    char seed[256];
    csprng RNG;

    char oct[FS_4096];
    octet OCT = {0,FS_4096,oct};

    BIG_512_60 A[HFLEN_4096], B[HFLEN_4096], C[HFLEN_4096], D[HFLEN_4096];
    BIG_512_60 E[FFLEN_4096], F[FFLEN_4096], G[FFLEN_4096], H[FFLEN_4096], L[FFLEN_4096], P[FFLEN_4096], Q[FFLEN_4096], N[FFLEN_4096];

    /* Fake random source */
    RAND_clean(&RNG);
    for (i=0; i<256; i++) seed[i]=(char)i;
    RAND_seed(&RNG,256,seed);

    /* Testing general equality and equality to zero */
    FF_4096_zero(A, HFLEN_4096);
    FF_4096_zero(B, HFLEN_4096);

    if(FF_4096_comp(A,B,HFLEN_4096) || !FF_4096_iszilch(A, HFLEN_4096))
    {
        printf("ERROR comparing or setting to zero\n");
        exit(EXIT_FAILURE);
    }

    /* Test parity */
    FF_4096_one(A,HFLEN_4096);
    if (!FF_4096_parity(A) || FF_4096_parity(B))
    {
        printf("ERROR checking parity\n");
        exit(EXIT_FAILURE);
    }

    /* Test last bits */
    FF_4096_init(A,0xF8,HFLEN_4096);
    if(FF_4096_lastbits(A,8) != 0xF8 || FF_4096_lastbits(A,12) != 0xF8)
    {
        printf("ERROR checking last bits\n");
        exit(EXIT_FAILURE);
    }

    /* Testing copy*/
    FF_4096_random(F,&RNG,FFLEN_4096);
    FF_4096_copy(G,F,FFLEN_4096);
    if(FF_4096_comp(G,F,FFLEN_4096))
    {
        printf("ERROR testing copy\n");
        exit(EXIT_FAILURE);
    }

    /* Testing addition, subtraction */
    for (i=0; i<10; i++)
    {
        FF_4096_random(F,&RNG,FFLEN_4096);
        FF_4096_random(G,&RNG,FFLEN_4096);
        FF_4096_copy(H,G,FFLEN_4096);

        FF_4096_add(G,G,F,FFLEN_4096);
        FF_4096_sub(G,G,F,FFLEN_4096);
        FF_4096_sub(F,F,F,FFLEN_4096);
        if(FF_4096_comp(G,H,FFLEN_4096) || !FF_4096_iszilch(F,FFLEN_4096))
        {
            printf("ERROR testing addition/subtraction\n");
            exit(EXIT_FAILURE);
        }
    }

    FF_4096_one(A,HFLEN_4096);
    FF_4096_zero(B,HFLEN_4096);

    FF_4096_add(C,A,B,HFLEN_4096);
    FF_4096_add(B,B,B,HFLEN_4096);
    if(FF_4096_comp(A,C,HFLEN_4096) || !FF_4096_iszilch(B,HFLEN_4096))
    {
        printf("ERROR testing addition/subtraction\n");
        exit(EXIT_FAILURE);
    }

    /* Testing increment/decrement */
    for (i=0; i<10; i++)
    {
        FF_4096_random(F,&RNG,FFLEN_4096);
        FF_4096_copy(H,F,FFLEN_4096);

        FF_4096_inc(F,10,FFLEN_4096);
        FF_4096_dec(F,10,FFLEN_4096);
        if(FF_4096_comp(F,H,FFLEN_4096))
        {
            printf("ERROR testing addition/subtraction\n");
            exit(EXIT_FAILURE);
        }
    }

    FF_4096_zero(A,HFLEN_4096);

    FF_4096_inc(A,0,HFLEN_4096);
    if(!FF_4096_iszilch(A,HFLEN_4096))
    {
        printf("ERROR testing addition/subtraction\n");
        exit(EXIT_FAILURE);
    }

    FF_4096_dec(A,0,HFLEN_4096);
    if(!FF_4096_iszilch(A,HFLEN_4096))
    {
        printf("ERROR testing addition/subtraction\n");
        exit(EXIT_FAILURE);
    }

    /* Testing shifts */
    FF_4096_one(A,HFLEN_4096);
    FF_4096_init(B,2,HFLEN_4096);
    FF_4096_one(C,HFLEN_4096);

    FF_4096_shl(A,HFLEN_4096);
    if(FF_4096_comp(A,B,HFLEN_4096))
    {
        printf("ERROR testing shifts\n");
        exit(EXIT_FAILURE);
    }

    FF_4096_shr(A,HFLEN_4096);
    if(FF_4096_comp(A,C,HFLEN_4096))
    {
        printf("ERROR testing shifts\n");
        exit(EXIT_FAILURE);
    }

    /* Testing octet conversions */
    for (i=0; i<10; i++)
    {
        OCT_clear(&OCT);

        FF_4096_random(F,&RNG,FFLEN_4096);
        FF_4096_copy(H,F,FFLEN_4096);

        FF_4096_toOctet(&OCT,F,FFLEN_4096);
        FF_4096_zero(F,FFLEN_4096);
        FF_4096_fromOctet(F,&OCT,FFLEN_4096);

        if(FF_4096_comp(F,H,FFLEN_4096))
        {
            printf("ERROR testing octet conversion\n");
            exit(EXIT_FAILURE);
        }

        OCT_clear(&OCT);

        FF_4096_random(A,&RNG,HFLEN_4096);
        FF_4096_copy(C,A,HFLEN_4096);

        FF_4096_toOctet(&OCT,A,HFLEN_4096);
        FF_4096_zero(A,HFLEN_4096);
        FF_4096_fromOctet(A,&OCT,HFLEN_4096);

        if(FF_4096_comp(A,C,HFLEN_4096))
        {
            printf("ERROR testing octet conversion\n");
            exit(EXIT_FAILURE);
        }
    }

    /* Testing multiplication/square */
    for (i=0; i<10; i++)
    {
        FF_4096_random(A,&RNG,HFLEN_4096);

        FF_4096_mul(F,A,A,HFLEN_4096);
        FF_4096_sqr(G,A,HFLEN_4096);

        // Normalise for comparison
        FF_4096_norm(F,FFLEN_4096);
        FF_4096_norm(G,FFLEN_4096);

        if(FF_4096_comp(F,G,FFLEN_4096))
        {
            printf("ERROR testing multiplication/square");
            exit(EXIT_FAILURE);
        }
    }

    /* Read P and Q primes from hex */
    OCT_fromHex(&OCT, Phex);
    OCT_pad(&OCT,FS_4096);
    FF_4096_fromOctet(P,&OCT,FFLEN_4096);

    OCT_fromHex(&OCT, Qhex);
    OCT_pad(&OCT,FS_4096);
    FF_4096_fromOctet(Q,&OCT,FFLEN_4096);

    /* Testing inverse modulo P */
    FF_4096_one(C,HFLEN_4096);
    for (i=0; i< 10; i++)
    {
        FF_4096_random(A,&RNG, HFLEN_4096);
        FF_4096_mod(A,P,HFLEN_4096);
        FF_4096_copy(B,A,HFLEN_4096);

        FF_4096_invmodp(B,B,P,HFLEN_4096);
        FF_4096_mul(F,A,B,HFLEN_4096);
        FF_4096_mod(F,P,FFLEN_4096);

        if(FF_4096_comp(C,F,HFLEN_4096))
        {
            printf("ERROR testing inverse modulo p");
            exit(EXIT_FAILURE);
        }
    }

    /* Testing CRT */
    FF_4096_mul(N,P,Q,HFLEN_4096);

    for (i=0; i<10; i++)
    {
        FF_4096_random(A,&RNG,HFLEN_4096);
        FF_4096_random(B,&RNG,HFLEN_4096);

        FF_4096_mul(H,A,B,HFLEN_4096);
        FF_4096_mod(H,N,FFLEN_4096);

        FF_4096_copy(C,A,HFLEN_4096);
        FF_4096_copy(D,B,HFLEN_4096);
        FF_4096_mod(A,P,HFLEN_4096);
        FF_4096_mod(B,P,HFLEN_4096);
        FF_4096_mod(C,Q,HFLEN_4096);
        FF_4096_mod(D,Q,HFLEN_4096);

        FF_4096_mul(F,A,B,HFLEN_4096);
        FF_4096_mod(F,P,FFLEN_4096);

        FF_4096_mul(G,C,D,HFLEN_4096);
        FF_4096_mod(G,Q,FFLEN_4096);

        FF_4096_crt(L,F,G,P,Q,HFLEN_4096);

        if(FF_4096_comp(L,H,HFLEN_4096))
        {
            printf("ERROR testing crt");
            exit(EXIT_FAILURE);
        }
    }

    /* Testing multiple power */
    FF_4096_random(A, &RNG, HFLEN_4096);
    FF_4096_random(B, &RNG, HFLEN_4096);
    FF_4096_random(C, &RNG, HFLEN_4096);
    FF_4096_random(D, &RNG, HFLEN_4096);

    FF_4096_random(E, &RNG, HFLEN_4096);
    FF_4096_random(F, &RNG, HFLEN_4096);
    FF_4096_random(G, &RNG, HFLEN_4096);
    FF_4096_random(H, &RNG, HFLEN_4096);

    FF_4096_pow(L, A, E, P, HFLEN_4096);
    FF_4096_pow(N, B, F, P, HFLEN_4096);
    FF_4096_mul(Q, L, N, HFLEN_4096);
    FF_4096_dmod(L, Q, P, HFLEN_4096);

    FF_4096_bpow2(N, A, E, B, F, P, HFLEN_4096, HFLEN_4096);

    if(FF_4096_comp(N, L, HFLEN_4096))
    {
        printf("ERROR testing bpow2");
        exit(EXIT_FAILURE);
    }

    // Test triple exponent
    FF_4096_pow(N, C, G, P, HFLEN_4096);
    FF_4096_mul(Q, L, N, HFLEN_4096);
    FF_4096_dmod(L, Q, P, HFLEN_4096);

    FF_4096_pow3(N, A, E, B, F, C, G, P, HFLEN_4096, HFLEN_4096);

    if(FF_4096_comp(N, L, HFLEN_4096))
    {
        printf("ERROR testing pow3");
        exit(EXIT_FAILURE);
    }

    // Test triple exponent for secret key
    FF_4096_zero(N, HFLEN_4096);
    FF_4096_skpow3(N, A, E, B, F, C, G, P, HFLEN_4096, HFLEN_4096);

    if(FF_4096_comp(N, L, HFLEN_4096))
    {
        printf("ERROR testing pow3");
        exit(EXIT_FAILURE);
    }

    // Test quadruple exponent
    FF_4096_pow(N, D, H, P, HFLEN_4096);
    FF_4096_mul(Q, L, N, HFLEN_4096);
    FF_4096_dmod(L, Q, P, HFLEN_4096);

    FF_4096_pow4(N, A, E, B, F, C, G, D, H, P, HFLEN_4096, HFLEN_4096);

    if(FF_4096_comp(N, L, HFLEN_4096))
    {
        printf("ERROR testing pow4");
        exit(EXIT_FAILURE);
    }

    printf("SUCCESS TEST CONSISTENCY OF FF_4096 PASSED\n");
    exit(EXIT_SUCCESS);
}
