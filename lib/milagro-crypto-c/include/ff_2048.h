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
 * @file ff_2048.h
 * @author Mike Scott
 * @brief FF Header File
 *
 */

#ifndef FF_2048_H
#define FF_2048_H

#include "big_1024_58.h"
#include "config_ff_2048.h"

#define HFLEN_2048 (FFLEN_2048/2) /**< Useful for half-size RSA private key operations */
#define P_MBITS_2048 (MODBYTES_1024_58*8) /**< Number of bits in modulus */
#define P_TBITS_2048 (P_MBITS_2048%BASEBITS_1024_58) /**< TODO  */
#define P_EXCESS_2048(a) (((a[NLEN_1024_58-1])>>(P_TBITS_2048))+1) /**< TODO */
#define P_FEXCESS_2048 ((chunk)1<<(BASEBITS_1024_58*NLEN_1024_58-P_MBITS_2048-1)) /**< TODO */


/* Finite Field Prototypes */
/**	@brief Copy one FF element of given length to another
 *
	@param x FF instance to be copied to, on exit = y
	@param y FF instance to be copied from
	@param n size of FF in BIGs

 */
extern void FF_2048_copy(BIG_1024_58 *x,BIG_1024_58 *y,int n);
/**	@brief Initialize an FF element of given length from a 32-bit integer m
 *
	@param x FF instance to be copied to, on exit = m
	@param m integer
	@param n size of FF in BIGs
 */
extern void FF_2048_init(BIG_1024_58 *x,sign32 m,int n);
/**	@brief Set FF element of given size to zero
 *
	@param x FF instance to be set to zero
	@param n size of FF in BIGs
 */
extern void FF_2048_zero(BIG_1024_58 *x,int n);
/**	@brief Tests for FF element equal to zero
 *
	@param x FF number to be tested
	@param n size of FF in BIGs
	@return 1 if zero, else returns 0
 */
extern int FF_2048_iszilch(BIG_1024_58 *x,int n);
/**	@brief  return parity of an FF, that is the least significant bit
 *
	@param x FF number
	@return 0 or 1
 */
extern int FF_2048_parity(BIG_1024_58 *x);
/**	@brief  return least significant m bits of an FF
 *
	@param x FF number
	@param m number of bits to return. Assumed to be less than BASEBITS.
	@return least significant n bits as an integer
 */
extern int FF_2048_lastbits(BIG_1024_58 *x,int m);
/**	@brief Set FF element of given size to unity
 *
	@param x FF instance to be set to unity
	@param n size of FF in BIGs
 */
extern void FF_2048_one(BIG_1024_58 *x,int n);
/**	@brief Compares two FF numbers. Inputs must be normalised externally
 *
	@param x first FF number to be compared
	@param y second FF number to be compared
	@param n size of FF in BIGs
	@return -1 is x<y, 0 if x=y, 1 if x>y
 */
extern int FF_2048_comp(BIG_1024_58 *x,BIG_1024_58 *y,int n);
/**	@brief addition of two FFs
 *
	@param x FF instance, on exit = y+z
	@param y FF instance
	@param z FF instance
	@param n size of FF in BIGs
 */
extern void FF_2048_add(BIG_1024_58 *x,BIG_1024_58 *y,BIG_1024_58 *z,int n);
/**	@brief subtraction of two FFs
 *
	@param x FF instance, on exit = y-z
	@param y FF instance
	@param z FF instance
	@param n size of FF in BIGs
 */
extern void FF_2048_sub(BIG_1024_58 *x,BIG_1024_58 *y,BIG_1024_58 *z,int n);
/**	@brief increment an FF by an integer,and normalise
 *
	@param x FF instance, on exit = x+m
	@param m an integer to be added to x
	@param n size of FF in BIGs
 */
extern void FF_2048_inc(BIG_1024_58 *x,int m,int n);
/**	@brief Decrement an FF by an integer,and normalise
 *
	@param x FF instance, on exit = x-m
	@param m an integer to be subtracted from x
	@param n size of FF in BIGs
 */
extern void FF_2048_dec(BIG_1024_58 *x,int m,int n);
/**	@brief Normalises the components of an FF
 *
	@param x FF instance to be normalised
	@param n size of FF in BIGs
 */
extern void FF_2048_norm(BIG_1024_58 *x,int n);
/**	@brief Shift left an FF by 1 bit
 *
	@param x FF instance to be shifted left
	@param n size of FF in BIGs
 */
extern void FF_2048_shl(BIG_1024_58 *x,int n);
/**	@brief Shift right an FF by 1 bit
 *
	@param x FF instance to be shifted right
	@param n size of FF in BIGs
 */
extern void FF_2048_shr(BIG_1024_58 *x,int n);
/**	@brief Formats and outputs an FF to the console
 *
	@param x FF instance to be printed
	@param n size of FF in BIGs
 */
extern void FF_2048_output(BIG_1024_58 *x,int n);
/**	@brief Formats and outputs an FF to the console, in raw form
 *
 	@param x FF instance to be printed
 	@param n size of FF in BIGs
 */
extern void FF_2048_rawoutput(BIG_1024_58 *x,int n);
/**	@brief Formats and outputs an FF instance to an octet string
 *
	Converts an FF to big-endian base 256 form.
	@param S output octet string
	@param x FF instance to be converted to an octet string
	@param n size of FF in BIGs
 */
extern void FF_2048_toOctet(octet *S,BIG_1024_58 *x,int n);
/**	@brief Populates an FF instance from an octet string
 *
	Creates FF from big-endian base 256 form.
	@param x FF instance to be created from an octet string
	@param S input octet string
	@param n size of FF in BIGs
 */
extern void FF_2048_fromOctet(BIG_1024_58 *x,octet *S,int n);
/**	@brief Multiplication of two FFs
 *
	Uses Karatsuba method internally
	@param x FF instance, on exit = y*z
	@param y FF instance
	@param z FF instance
	@param n size of FF in BIGs
 */
extern void FF_2048_mul(BIG_1024_58 *x,BIG_1024_58 *y,BIG_1024_58 *z,int n);
/**	@brief Reduce FF mod a modulus
 *
	This is slow
	@param x FF instance to be reduced mod p - on exit = x mod p
	@param p FF modulus
	@param n size of FF in BIGs
 */
extern void FF_2048_mod(BIG_1024_58 *x,BIG_1024_58 *p,int n);
/**	@brief Square an FF
 *
	Uses Karatsuba method internally
	@param x FF instance, on exit = y^2
	@param y FF instance to be squared
	@param n size of FF in BIGs
 */
extern void FF_2048_sqr(BIG_1024_58 *x,BIG_1024_58 *y,int n);
/**	@brief Reduces a double-length FF with respect to a given modulus
 *
	This is slow
	@param x FF instance, on exit = y mod z
	@param y FF instance, of double length 2*n
	@param z FF modulus
	@param n size of FF in BIGs
 */
extern void FF_2048_dmod(BIG_1024_58 *x,BIG_1024_58 *y,BIG_1024_58 *z,int n);
/**	@brief Invert an FF mod a prime modulus
 *
	@param x FF instance, on exit = 1/y mod z
	@param y FF instance
	@param z FF prime modulus
	@param n size of FF in BIGs
 */
extern void FF_2048_invmodp(BIG_1024_58 *x,BIG_1024_58 *y,BIG_1024_58 *z,int n);
/** @brief Invert an FF mod 2^(n*BIGBITS)
 *
 * @param U FF instance, on exit 1/a mod 2^(n*BIGBITS)
 * @param a FF instance
 * @param n size of FF in BIGs
 */
extern void FF_2048_invmod2m(BIG_1024_58 U[],BIG_1024_58 a[],int n);
/**	@brief Create an FF from a random number generator
 *
	@param x FF instance, on exit x is a random number of length n BIGs with most significant bit a 1
	@param R an instance of a Cryptographically Secure Random Number Generator
	@param n size of FF in BIGs
 */
extern void FF_2048_random(BIG_1024_58 *x,csprng *R,int n);
/**	@brief Create a random FF less than a given modulus from a random number generator
 *
	@param x FF instance, on exit x is a random number < y
	@param y FF instance, the modulus
	@param R an instance of a Cryptographically Secure Random Number Generator
	@param n size of FF in BIGs
 */
extern void FF_2048_randomnum(BIG_1024_58 *x,BIG_1024_58 *y,csprng *R,int n);
/**	@brief Calculate r=x^e mod p, side channel resistant
 *
	@param r FF instance, on exit = x^e mod p
	@param x FF instance
	@param e FF exponent
	@param p FF modulus
	@param n size of FF in BIGs
	@param en size of the exponent in BIGs
 */
extern void FF_2048_skpow(BIG_1024_58 *r,BIG_1024_58 *x,BIG_1024_58 * e,BIG_1024_58 *p,int n, int en);
/**	@brief Calculate r=x^e mod p, side channel resistant
 *
	For short BIG exponent
	@param r FF instance, on exit = x^e mod p
	@param x FF instance
	@param e BIG exponent
	@param p FF modulus
	@param n size of FF in BIGs
 */
extern void FF_2048_skspow(BIG_1024_58 *r,BIG_1024_58 *x,BIG_1024_58 e,BIG_1024_58 *p,int n);
/**	@brief Calculate r=x^e.y^f mod p for FF e and f, side channel resistant
 *
	@param r  FF instance, on exit = x^e.y^f mod p
	@param x  FF instance
	@param e  FF exponent
	@param y  FF instance
	@param f  FF exponent
	@param p  FF modulus
	@param n  size of FF in BIGs
	@param en size of the exponent in BIGs
 */
extern void FF_2048_skpow2(BIG_1024_58 *r,BIG_1024_58 *x, BIG_1024_58 *e, BIG_1024_58 *y, BIG_1024_58 *f, BIG_1024_58 *p, int n, int en);
/**	@brief Calculate r=x^e.y^f.z^g mod p for FF e, f and g, side channel resistant
 *
	@param r  FF instance, on exit = x^e.y^f.z^g mod p
	@param x  FF instance
	@param e  FF exponent
	@param y  FF instance
	@param f  FF exponent
	@param z  FF instance
	@param g  FF exponent
	@param p  FF modulus
	@param n  size of FF in BIGs
	@param en size of the exponent in BIGs
 */
extern void FF_2048_skpow3(BIG_1024_58 *r,BIG_1024_58 *x, BIG_1024_58 *e, BIG_1024_58 *y, BIG_1024_58 *f, BIG_1024_58 *z, BIG_1024_58 *g, BIG_1024_58 *p, int n, int en);
/**	@brief Calculate r=x^e mod p
 *
	For very short integer exponent
	@param r  FF instance, on exit = x^e mod p
	@param x  FF instance
	@param e  integer exponent
	@param p  FF modulus
	@param n  size of FF in BIGs
 */
extern void FF_2048_power(BIG_1024_58 *r,BIG_1024_58 *x,int e,BIG_1024_58 *p,int n);
/**	@brief Calculate r=x^e mod p
 *
	@param r FF instance, on exit = x^e mod p
	@param x FF instance
	@param e FF exponent
	@param p FF modulus
	@param n size of FF in BIGs
 */
extern void FF_2048_pow(BIG_1024_58 *r,BIG_1024_58 *x,BIG_1024_58 *e,BIG_1024_58 *p,int n);
/**	@brief Calculate r=x^e.y^f mod m
 *
	@param r FF instance, on exit = x^e.y^f mod p
	@param x FF instance
	@param e BIG exponent
	@param y FF instance
	@param f BIG exponent
	@param m FF modulus
	@param n size of FF in BIGs
 */
extern void FF_2048_pow2(BIG_1024_58 *r,BIG_1024_58 *x,BIG_1024_58 e,BIG_1024_58 *y,BIG_1024_58 f,BIG_1024_58 *m,int n);
/**	@brief Calculate r=x^e.y^f mod p. Faster but non constant time
 *
	@param r  FF instance, on exit = x^e.y^f mod p
	@param x  FF instance
	@param e  BIG exponent
	@param y  FF instance
	@param f  BIG exponent
	@param p  FF modulus
	@param n   size of FF in BIGs
	@param en size of exponent in BIGs
 */
void FF_2048_bpow2(BIG_1024_58 *r,BIG_1024_58 *x,BIG_1024_58 *e, BIG_1024_58 *y, BIG_1024_58 *f, BIG_1024_58 *p,int n, int en);
/**	@brief Calculate r=x^e.y^f.z^g mod p. Faster but non constant time
 *
	@param r  FF instance, on exit = x^e.y^f.z^g mod p
	@param x  FF instance
	@param e  BIG exponent
	@param y  FF instance
	@param f  BIG exponent
	@param z  FF instance
	@param g  BIG exponent
	@param p  FF modulus
	@param n  size of FF in BIGs
	@param en size of exponent in BIGs
 */
void FF_2048_pow3(BIG_1024_58 *r,BIG_1024_58 *x,BIG_1024_58 *e, BIG_1024_58 *y, BIG_1024_58 *f, BIG_1024_58 *z, BIG_1024_58 *g, BIG_1024_58 *p, int n, int en);
/**	@brief Calculate r=x^e.y^f.z^g.w^h mod p. Faster but non constant time
 *
	@param r  FF instance, on exit = x^e.y^f.z^g.w^h mod p
	@param x  FF instance
	@param e  BIG exponent
	@param y  FF instance
	@param f  BIG exponent
	@param z  FF instance
	@param g  BIG exponent
	@param w  FF instance
	@param h  BIG exponent
	@param p  FF modulus
	@param n  size of FF in BIGs
	@param en size of exponent in BIGs
 */
extern void FF_2048_pow4(BIG_1024_58 *r,BIG_1024_58 *x,BIG_1024_58 *e, BIG_1024_58 *y, BIG_1024_58 *f, BIG_1024_58 *z, BIG_1024_58 *g, BIG_1024_58 *w, BIG_1024_58 *h, BIG_1024_58 *p, int n, int en);
/**	@brief Test if an FF has factor in common with integer s
 *
	@param x FF instance to be tested
	@param s the supplied integer
	@param n size of FF in BIGs
	@return 1 if gcd(x,s)!=1, else return 0
 */
extern int FF_2048_cfactor(BIG_1024_58 *x,sign32 s,int n);
/**	@brief Test if an FF is prime
 *
	Uses Miller-Rabin Method
	@param x FF instance to be tested
	@param R an instance of a Cryptographically Secure Random Number Generator
	@param n size of FF in BIGs
	@return 1 if x is (almost certainly) prime, else return 0
 */
extern int FF_2048_prime(BIG_1024_58 *x,csprng *R,int n);
/**	@brief Combine rp and rq using the Chinese Remainder Theorem
 *
	@param r  FF instance, on exit the solution of the system
	@param rp FF instance, solution modulo p
	@param rq FF instance, solution modulo q
	@param p  FF instance, MUST be coprime with q
	@param q  FF instance, MUST be coprime with p
	@param n size of p and q in BIGs
 */
extern void FF_2048_crt(BIG_1024_58 *r, BIG_1024_58 *rp, BIG_1024_58 *rq, BIG_1024_58 *p, BIG_1024_58 *q, int n);

#endif
