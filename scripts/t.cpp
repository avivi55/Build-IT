#include <iostream>
#include <algorithm>
#include <cstdint>

using namespace std;

// constexpr static uint8_t processBitsInBufferForScreen(uint8_t e1, uint8_t e2, uint8_t e3, uint8_t e4, uint8_t e5, uint8_t e6, uint8_t e7, uint8_t e8)
// {
//   uint8_t res = 0;

//   res |= (e1 & 0b1);
//   res |= (e2 & 0b10);
//   res |= (e3 & 0b100);
//   res |= (e4 & 0b1000);
//   res |= (e5 & 0b10000);
//   res |= (e6 & 0b100000);
//   res |= (e7 & 0b1000000);
//   res |= (e8 & 0b10000000);
  
//   return ~res;
// }

bool getPixel(uint8_t x, uint8_t y, uint8_t *pixels)
{
  x %= 84;
  y %= 48;

  return (bool) (pixels[(y * 11) + x/8] & (0b10000000 >> (x%8)));
}

void setPixel(uint8_t x, uint8_t y, uint8_t *pixels, bool state)
{
  x %= 84;
  y %= 48;

  uint8_t maskNoConcernedBit = ~(0b10000000 >> (x%8));

  pixels[(y * 11) + x/8] = (uint8_t) ((pixels[(y * 11) + x/8] & maskNoConcernedBit) | ((state << 7) >> (x%8)));
}

uint8_t bitsToByte(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7, uint8_t b8)
{
  return (b1 << 7)
        | (b2 << 6)
        | (b3 << 5)
        | (b4 << 4)
        | (b5 << 3)
        | (b6 << 2)
        | (b7 << 1)
        | b8;
}
int main(){
  u_int8_t *pixels = (u_int8_t*)calloc(48*(84/8 + 1) , 1);

  // pixels[11] = 0b01100001;

  setPixel(0, 1, pixels, 1);
  setPixel(0, 2, pixels, 1);
  setPixel(0, 3, pixels, 1);
  setPixel(0, 4, pixels, 1);
  setPixel(0, 5, pixels, 1);
  setPixel(0, 6, pixels, 1);




  for (int j = 0; j < 48; j++)
  {    
    for (int i = 0; i < 8; i++)
    {
      printf("%d", getPixel(i, j, pixels));
    }
    printf("\n"); 
  }



  printf("%d\n", bitsToByte(1,0,0,0,0,0,1,0));

  free(pixels);

  return 0;
}


