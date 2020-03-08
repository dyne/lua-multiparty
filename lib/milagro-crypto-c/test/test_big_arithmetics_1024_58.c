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
 * @author Alessandro Budroni
 * @brief Test for aritmetics with BIG_1024_58
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arch.h"
#include "amcl.h"
#include "utils.h"
#include "big_1024_58.h"

#define LINE_LEN 10000
#define MAX_STRING 300

void read_BIG_1024_58(BIG_1024_58 A, char* string)
{
    int len;
    char support[LINE_LEN];
    BIG_1024_58_zero(A);
    len = strlen(string)+1;
    amcl_hex2bin(string,support,len);
    len = (len-1)/2;;
    BIG_1024_58_fromBytesLen(A,support,len);
    BIG_1024_58_norm(A);
}

void read_DBIG_1024_58(DBIG_1024_58 A, char* string)
{
    int len;
    char support[LINE_LEN];
    BIG_1024_58_dzero(A);
    len = strlen(string)+1;
    amcl_hex2bin(string,support,len);
    len = (len-1)/2;
    BIG_1024_58_dfromBytesLen(A,support,len);
    BIG_1024_58_dnorm(A);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("usage: ./test_BIG_1024_58_arithmetics [path to test vector file]\n");
        exit(EXIT_FAILURE);
    }

    int i=0, len=0, bitlen=0;

    FILE *fp;

    char line[LINE_LEN];
    char * linePtr = NULL;

    BIG_1024_58 supp,mod,div;
    DBIG_1024_58 dsupp;

    BIG_1024_58 BIG1;
    const char* BIG1line = "BIG1 = ";
    BIG_1024_58 BIG2;
    const char* BIG2line = "BIG2 = ";
    BIG_1024_58 BIGsum;
    const char* BIGsumline = "BIGsum = ";
    BIG_1024_58 BIGsub;
    const char* BIGsubline = "BIGsub = ";
    BIG_1024_58 BIG1mod2;
    const char* BIG1mod2line = "BIG1mod2 = ";
    BIG_1024_58 BIG2mod1;
    const char* BIG2mod1line = "BIG2mod1 = ";
    DBIG_1024_58 BIGmul;
    const char* BIGmulline = "BIGmul = ";
    DBIG_1024_58 BIG1sqr;
    const char* BIG1sqrline = "BIG1sqr = ";
    DBIG_1024_58 BIG2sqr;
    const char* BIG2sqrline = "BIG2sqr = ";
    BIG_1024_58 BIG1sqrmod2;
    const char* BIG1sqrmod2line = "BIG1sqrmod2 = ";
    BIG_1024_58 BIG1modneg2;
    const char* BIG1modneg2line = "BIG1modneg2 = ";
    int nbitBIG = 0;
    const char* nbitBIGline = "nbitBIG = ";
    int nbitDBIG = 0;
    const char* nbitDBIGline = "nbitDBIG = ";
    BIG_1024_58 BIGdiv;
    const char* BIGdivline = "BIGdiv = ";
    BIG_1024_58 BIGdivmod;
    const char* BIGdivmodline = "BIGdivmod = ";
    DBIG_1024_58 BIGpxmul;
    const char* BIGpxmulline = "BIGpxmul = ";

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("ERROR opening test vector file\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, LINE_LEN, fp) != NULL)
    {
        i++;
        if (!strncmp(line,  BIG1line, strlen(BIG1line)))
        {
            len = strlen(BIG1line);
            linePtr = line + len;
            read_BIG_1024_58(BIG1,linePtr);
        }
// test comparison
        if (!strncmp(line,BIG2line, strlen(BIG2line)))
        {
            len = strlen(BIG2line);
            linePtr = line + len;
            read_BIG_1024_58(BIG2,linePtr);
            if (BIG_1024_58_comp(BIG1,BIG2) < 0)
            {
                printf("ERROR comparing two BIGs, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test addition
        if (!strncmp(line,BIGsumline, strlen(BIGsumline)))
        {
            BIG_1024_58_zero(supp);
            BIG_1024_58_add(supp,BIG1,BIG2);
            len = strlen(BIGsumline);
            linePtr = line + len;
            read_BIG_1024_58(BIGsum,linePtr);
            BIG_1024_58_norm(supp);
            if (BIG_1024_58_comp(BIGsum,supp) != 0)
            {
                printf("ERROR adding two BIGs, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test subtraction
        if (!strncmp(line,BIGsubline, strlen(BIGsubline)))
        {
            BIG_1024_58_zero(supp);
            BIG_1024_58_sub(supp,BIG1,BIG2);
            len = strlen(BIGsubline);
            linePtr = line + len;
            read_BIG_1024_58(BIGsub,linePtr);
            BIG_1024_58_norm(supp);
            if (BIG_1024_58_comp(BIGsub,supp) != 0)
            {
                printf("ERROR subtracting two BIGs, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test modulo 1
        if (!strncmp(line,BIG1mod2line, strlen(BIG1mod2line)))
        {
            BIG_1024_58_zero(supp);
            BIG_1024_58_copy(supp,BIG1);
            BIG_1024_58_mod(supp,BIG2);
            len = strlen(BIG1mod2line);
            linePtr = line + len;
            read_BIG_1024_58(BIG1mod2,linePtr);
            BIG_1024_58_norm(supp);
            if (BIG_1024_58_comp(BIG1mod2,supp) != 0)
            {
                printf("ERROR reducing modulo BIG, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test modulo 2
        if (!strncmp(line,BIG2mod1line, strlen(BIG2mod1line)))
        {
            BIG_1024_58_zero(supp);
            BIG_1024_58_copy(supp,BIG2);
            BIG_1024_58_mod(supp,BIG1);
            len = strlen(BIG2mod1line);
            linePtr = line + len;
            read_BIG_1024_58(BIG2mod1,linePtr);
            BIG_1024_58_norm(supp);
            if (BIG_1024_58_comp(BIG2mod1,supp) != 0)
            {
                printf("ERROR reducing modulo BIG, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test multiplication
        if (!strncmp(line,BIGmulline, strlen(BIGmulline)))
        {
            BIG_1024_58_dzero(dsupp);
            BIG_1024_58_mul(dsupp,BIG1,BIG2);
            len = strlen(BIGmulline);
            linePtr = line + len;
            read_DBIG_1024_58(BIGmul,linePtr);
            BIG_1024_58_dnorm(dsupp);
            if (BIG_1024_58_dcomp(BIGmul,dsupp) != 0)
            {
                printf("ERROR multiplication BIG, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test square 1
        if (!strncmp(line,BIG1sqrline, strlen(BIG1sqrline)))
        {
            BIG_1024_58_dzero(dsupp);
            BIG_1024_58_sqr(dsupp,BIG1);
            len = strlen(BIG1sqrline);
            linePtr = line + len;
            read_DBIG_1024_58(BIG1sqr,linePtr);
            BIG_1024_58_dnorm(dsupp);
            if (BIG_1024_58_dcomp(BIG1sqr,dsupp) != 0)
            {
                printf("ERROR squaring BIG 1, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test square 2
        if (!strncmp(line,BIG2sqrline, strlen(BIG2sqrline)))
        {
            BIG_1024_58_dzero(dsupp);
            BIG_1024_58_sqr(dsupp,BIG2);
            len = strlen(BIG2sqrline);
            linePtr = line + len;
            read_DBIG_1024_58(BIG2sqr,linePtr);
            BIG_1024_58_dnorm(dsupp);
            if (BIG_1024_58_dcomp(BIG2sqr,dsupp) != 0)
            {
                printf("ERROR squaring BIG 2, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test square mod
        if (!strncmp(line,BIG1sqrmod2line, strlen(BIG1sqrmod2line)))
        {
            BIG_1024_58_zero(supp);
            BIG_1024_58_copy(supp,BIG1);
            BIG_1024_58_modsqr(supp,supp,BIG2);
            len = strlen(BIG1sqrmod2line);
            linePtr = line + len;
            read_BIG_1024_58(BIG1sqrmod2,linePtr);
            BIG_1024_58_norm(supp);
            if (BIG_1024_58_comp(BIG1sqrmod2,supp) != 0)
            {
                printf("ERROR reducing squaring modulo BIG, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test negative and modulo
        if (!strncmp(line,BIG1modneg2line, strlen(BIG1modneg2line)))
        {
            BIG_1024_58_zero(supp);
            BIG_1024_58_copy(supp,BIG1);
            BIG_1024_58_modneg(supp,supp,BIG2);
            BIG_1024_58_mod(supp,BIG2); // Account for case BIG1 = BIG2
            len = strlen(BIG1modneg2line);
            linePtr = line + len;
            read_BIG_1024_58(BIG1modneg2,linePtr);
            BIG_1024_58_norm(supp);
            if (BIG_1024_58_comp(BIG1modneg2,supp) != 0)
            {
                printf("ERROR negative reduced modulo BIG, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test counting bit BIG
        if (!strncmp(line,nbitBIGline, strlen(nbitBIGline)))
        {
            len = strlen(nbitBIGline);
            nbitBIG = BIG_1024_58_nbits(BIG1);
            linePtr = line + len;
            sscanf(linePtr,"%d\n",&bitlen);
            if (nbitBIG != bitlen)
            {
                printf("ERROR counting bit BIG, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test counting bit DBIG
        if (!strncmp(line,nbitDBIGline, strlen(nbitDBIGline)))
        {
            len = strlen(nbitDBIGline);
            nbitDBIG = BIG_1024_58_dnbits(BIGmul);
            linePtr = line + len;
            sscanf(linePtr,"%d\n",&bitlen);
            if (nbitDBIG != bitlen)
            {
                printf("ERROR counting bit DBIG, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test division
        if (!strncmp(line,BIGdivline, strlen(BIGdivline)))
        {
            BIG_1024_58_dzero(dsupp);
            BIG_1024_58_zero(supp);
            BIG_1024_58_dcopy(dsupp,BIGmul);
            BIG_1024_58_ddiv(supp,dsupp,BIGsum);
            len = strlen(BIGdivline);
            linePtr = line + len;
            read_BIG_1024_58(BIGdiv,linePtr);
            BIG_1024_58_norm(supp);
            if (BIG_1024_58_comp(BIGdiv,supp) != 0)
            {
                printf("ERROR division BIG, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test division with modulo
        if (!strncmp(line,BIGdivmodline, strlen(BIGdivmodline)))
        {
            read_BIG_1024_58(mod,"E186EB30EF");
            read_BIG_1024_58(div,"0ED5066C6815047425DF");
            BIG_1024_58_zero(supp);
            BIG_1024_58_copy(supp,BIG1);
            BIG_1024_58_moddiv(supp,supp,div,mod);
            len = strlen(BIGdivmodline);
            linePtr = line + len;
            read_BIG_1024_58(BIGdivmod,linePtr);
            BIG_1024_58_norm(supp);
            if (BIG_1024_58_comp(BIGdivmod,supp) != 0)
            {
                printf("ERROR division modulo BIG, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
// test small multiplication
        if (!strncmp(line,BIGpxmulline, strlen(BIGpxmulline)))
        {
            BIG_1024_58_dzero(dsupp);
            BIG_1024_58_pxmul(dsupp,BIG1,nbitDBIG);
            len = strlen(BIGpxmulline);
            linePtr = line + len;
            read_DBIG_1024_58(BIGpxmul,linePtr);
            BIG_1024_58_dnorm(dsupp);
            if (BIG_1024_58_dcomp(BIGpxmul,dsupp) != 0)
            {
                printf("ERROR small multiplication BIG, line %d\n",i);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(fp);
    printf("SUCCESS TEST ARITMETIC OF BIG_1024_58 PASSED\n");
    exit(EXIT_SUCCESS);
}
