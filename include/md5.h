/**
 * @Author: fjk
 * @Date:   2018-01-14T11:47:01+08:00
 * @Email:  sunnyfjk@gmail.com
 * @Filename: md5.h
 * @Last modified by:   fjk
 * @Last modified time: 2018-01-14T13:24:52+08:00
 */
#ifndef __INCLUDE_MD5_H__
#define __INCLUDE_MD5_H__
struct  MD5_CTX
{
        uint32_t count[2];
        uint32_t state[4];
        uint8_t buffer[64];
};
struct CalculationStringMd5_t {
        uint32_t strlen;
        uint8_t *str;
        uint8_t md5[16];
};

#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))
#define FF(a,b,c,d,x,s,ac) \
        { \
                a += F(b,c,d) + x + ac; \
                a = ROTATE_LEFT(a,s); \
                a += b; \
        }
#define GG(a,b,c,d,x,s,ac) \
        { \
                a += G(b,c,d) + x + ac; \
                a = ROTATE_LEFT(a,s); \
                a += b; \
        }
#define HH(a,b,c,d,x,s,ac) \
        { \
                a += H(b,c,d) + x + ac; \
                a = ROTATE_LEFT(a,s); \
                a += b; \
        }
#define II(a,b,c,d,x,s,ac) \
        { \
                a += I(b,c,d) + x + ac; \
                a = ROTATE_LEFT(a,s); \
                a += b; \
        }
void MD5Init(struct MD5_CTX *context);
void MD5Update(struct MD5_CTX *context,uint8_t *input,uint32_t inputlen);
void MD5Final(struct MD5_CTX *context,uint8_t digest[16]);
void MD5Transform(uint32_t state[4],uint8_t block[64]);
void MD5Encode(uint8_t *output,uint32_t *input,uint32_t len);
void MD5Decode(uint32_t *output,uint8_t *input,uint32_t len);
#endif
