#include <cstdint>
#include <cstdlib>
#include <string>
#include "Tools.h"
#include <inttypes.h>

int main()
{
  uint64_t test;
  // uint64_t a = 0x8000000000000000; // aka 128
  // uint64_t b = 0x7fffffffffffffff; // aka 127,   127 - 128 = -1
  uint64_t a = 0x8000000000000000; // 4
  uint64_t b = 0x7fffffffffffffff; // -9223372036854775805
  // exected true;
  test = Tools::subOverflow(a, b);
  // printf("%llX\n", test);
  printf("%llX\n", test);
}

/**
 * assumes that op1 and op2 contain 64 bit two's complement values
 * and returns true if an overflow would occur from op2 - op1
 * and false otherwise
 *
 * for example, subOverflow(0x8000000000000000, 0x8000000000000000) returns 0
 *              subOverflow(0x7fffffffffffffff, 0x7fffffffffffffff) returns 0
 *              subOverflow(0x8000000000000000, 0x7fffffffffffffff) returns 1
 *
 * @param uint64_t op1 that is one of the operands of the subtraction
 * @param uint64_t op2 that is the other operand of the subtraction
 * @return true if op2 - op1 would result in an overflow assuming that op1
 *         and op2 contain 64-bit two's complement values
 *
 * RULES:
 * 1) no loops
 * 2) you can use other functions you have written, for example, sign
 * 3) you cannot use addOverflow (it doesn't work in all cases).
 * 4) no more than 10 lines of code
 */
bool Tools::subOverflow(uint64_t op1, uint64_t op2)
{
  // See hint for addOverflow
  // Note: you can not simply use addOverflow in this function.  If you negate
  // op1 in order to an add, you may get an overflow.
  // NOTE: the subtraction is op2 - op1 (not op1 - op2).
  uint64_t result = op2 - op1;

  uint64_t sign_op1 = Tools::sign(op1);
  uint64_t sign_op2 = Tools::sign(op2);
  uint64_t sign_result = Tools::sign(result);

  // 1. op1 is positive and op2 is negative, but the result is positive.
  // 2. op1 is negative and op2 is positive, but the result is negative.
  return (sign_op1 == 0 && sign_op2 == 1 && sign_result == 0) ||
         (sign_op1 == 1 && sign_op2 == 0 && sign_result == 1);
}

uint64_t Tools::sign(uint64_t source)
{
  return source >> 63;
}

uint64_t Tools::setByte(uint64_t source, int32_t byteNum)
{
  uint64_t mask = 0xff;
  uint64_t final = source;
  mask = mask << (8 * byteNum);
  mask = mask * !(byteNum > 7 || byteNum < 0);

  final = final | mask;
  return final;
}

uint64_t Tools::copyBits(uint64_t source, uint64_t dest,
                         int32_t srclow, int32_t dstlow, int32_t length)
{
  uint32_t srchigh = srclow + (length - 1);

  if (srclow < 0 || dstlow < 0 || srchigh > 63 || dstlow + (length - 1) > 63)
  {
    return dest;
  }

  uint64_t getCopy = source;
  getCopy = getCopy << (63 - (srchigh));
  getCopy = getCopy >> (63 - (srchigh - srclow));
  getCopy = getCopy << (dstlow);
  uint64_t final = clearBits(dest, dstlow, dstlow + (length - 1));
  final = final | getCopy;

  return final;
}

//                                                              srclow dstlow length
// test = Tools::copyBits(0x1122334455667788, 0x8877665544332211, 8, 4, 4);
// 0x8877665544332271

uint64_t Tools::setBits(uint64_t source, int32_t low, int32_t high)
{
  if (high < low || low < 0 || high > 63)
  {
    return source;
  }

  uint64_t final = source;
  // uint64_t extra = getBits(0,low)
  uint64_t mask = ~0;
  mask = mask << (63 - (high - low));
  mask = mask >> (63 - (high - low));
  mask = mask << low;
  final = final | mask;

  return final;
}

uint64_t Tools::clearBits(uint64_t source, int32_t low, int32_t high)
{
  if (high < low || low < 0 || high > 63)
  {
    return source;
  }

  uint64_t final = source;
  uint64_t mask = ~0;
  mask = mask << (63 - (high - low));
  mask = mask >> (63 - (high - low));
  mask = mask << low;
  final = final & ~mask;

  return final;
}

//