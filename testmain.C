#include <cstdint>
#include <cstdlib>
#include <string>
#include "Tools.h"
#include <inttypes.h>

int main()
{
    uint64_t test = 0x1122334455667788;
    // test = Tools::clearBits(test,8,8+8);
    // test = Tools::copyBits(0x1122334455667788, 0x8877665544332211, 0, 0, 8);
    test = Tools::setByte(0x1122334455667788, -9);
    printf("%llX\n", test);
    // printf("%X\n",0xFF >> -20);

    // uint64_t mask = 0xff;
    // uint64_t final = test;
    // int bits = 10;
    // mask = mask << (8*(bits)); // 8
    // mask = mask >> (8*(bits-1)); // 56
    // final = final | mask;
    // printf("%llX\n", mask);
    // uint64_t result; 

    // result = Tools::copyBits(0x1122334455667788,0x8877665544332211, 0, 8, 8);
    // printf("\nresult = %llX" PRIu64 "\n\n", result);
        // printf("\nresult = %llX" PRIu64 "\n, Expected: 
        // ", result);

    // // supposed to return 0x8877665544338811


//     uint64_t result;

//     result = Tools::copyBits(0x1122334455667788, 0x8877665544332211, 0, 0, 8);
//             printf("\nresult = %llX" PRIu64 ",\t Expected: 0x8877665544332288\n", result);
//     result = (Tools::copyBits(0x1122334455667788, 0x8877665544332211, 0, 8, 8));
//             printf("\nresult = %llX" PRIu64 ",\t Expected: 0x8877665544338811\n", result);
//     result = (Tools::copyBits(0x1122334455667788, 0x8877665544332211, 8, 4, 4));
//             printf("\nresult = %llX" PRIu64 ",\t Expected: 0x8877665544332271\n", result);
//     result = (Tools::copyBits(0x1122334455667788, 0x1877665544332211, 3, 0x3f, 1));
//             printf("\nresult = %llX" PRIu64 ",\t Expected: 0x9877665544332211\n", result);
//     result = (Tools::copyBits(0x1122334455667788, 0x1877665544332211, 3, 0x40, 1));
//             printf("\nresult = %llX" PRIu64 ",\t Expected: 0x1877665544332211\n", result);
//     result = Tools::copyBits(0x1122334455667788, 0x1877665544332211, 0xfffffffe, 0x3f, 1);
//             printf("\nresult = %llX" PRIu64 ",\t Expected: 0x1877665544332211\n", result);
//     result = Tools::copyBits(0x1122334455667788, 0x1877665544332211, 3, 0x3f, 2);
//             printf("\nresult = %llX" PRIu64 ",\t Expected: 0x1877665544332211\n", result);
//     result = Tools::copyBits(0x1122334455667788, 0x8877665544332211, 8, 8, 0x10);
//             printf("\nresult = %llX" PRIu64 ",\t Expected: 0x8877665544667711\n", result);
}

uint64_t Tools::setByte(uint64_t source, int32_t byteNum)
{
  uint64_t mask = 0xff;
  uint64_t final = source;
  mask = mask << (8*byteNum);

  for(int i = 0; i < 1 && (byteNum >= 8 || byteNum < 0) ; i++)
  {
    mask = 0x00;
  }

  final = final | mask;
  return final; 
}


uint64_t Tools::copyBits(uint64_t source, uint64_t dest, 
                         int32_t srclow, int32_t dstlow, int32_t length)
{
    uint32_t srchigh = srclow + (length-1);

    if(srclow < 0 || dstlow < 0 || srchigh > 63 || dstlow+(length-1) > 63)
    {
        return dest;
    }

    uint64_t getCopy = source;
    getCopy = getCopy << (63-(srchigh));
    getCopy = getCopy >> (63-(srchigh-srclow));
    getCopy = getCopy << (dstlow);
    uint64_t final = clearBits(dest, dstlow,dstlow+(length-1));
    final = final | getCopy;
    
    
    return final;
}

//                                                              srclow dstlow length
    // test = Tools::copyBits(0x1122334455667788, 0x8877665544332211, 8, 4, 4);
// 0x8877665544332271


uint64_t Tools::setBits(uint64_t source, int32_t low, int32_t high)
{
  if(high < low || low < 0 || high > 63)
  {
    return source;
  }
  
  uint64_t final = source;
  // uint64_t extra = getBits(0,low) 
  uint64_t mask = ~0;
  mask = mask << (63-(high-low));
  mask = mask >> (63-(high-low));
  mask = mask << low;
  final = final | mask;
  
  
  
  return final; 

}

uint64_t Tools::clearBits(uint64_t source, int32_t low, int32_t high)
{
  if(high < low || low < 0 || high > 63)
  {
    return source;
  }

  uint64_t final = source;
  uint64_t mask = ~0;
  mask = mask << (63-(high-low));
  mask = mask >> (63-(high-low));
  mask = mask << low;
  final = final & ~mask;
  
  return final; 

}

//