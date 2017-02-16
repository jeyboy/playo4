#ifndef UNICODE_CONV_H
#define UNICODE_CONV_H

#define         MASKBITS                0x3F
#define         MASKBYTE                0x80
#define         MASK2BYTES              0xC0
#define         MASK3BYTES              0xE0
#define         MASK4BYTES              0xF0
#define         MASK5BYTES              0xF8
#define         MASK6BYTES              0xFC

namespace Html {
    class UnicodeConv {
//        char* UTF8Encode2BytesUnicode(unsigned short* input)
//        {
//           int size = 0,
//               cindex = 0;
//           while (input[size] != 0)
//             size++;
//           // Reserve enough place; The amount of
//           char* result = (char*) malloc(size);
//           for (int i=0; i<size; i++)
//           {
//              // 0xxxxxxx
//              if(input[i] < 0x80)
//              {
//                 result[cindex++] = ((char) input[i]);
//              }
//              // 110xxxxx 10xxxxxx
//              else if(input[i] < 0x800)
//              {
//                 result[cindex++] = ((char)(MASK2BYTES | input[i] >> 6));
//                 result[cindex++] = ((char)(MASKBYTE | input[i] & MASKBITS));
//              }
//              // 1110xxxx 10xxxxxx 10xxxxxx
//              else if(input[i] < 0x10000)
//              {
//                 result[cindex++] = ((char)(MASK3BYTES | input[i] >> 12));
//                 result[cindex++] = ((char)(MASKBYTE | input[i] >> 6 & MASKBITS));
//                 result[cindex++] = ((char)(MASKBYTE | input[i] & MASKBITS));
//              }
//           }
//        }

//        wchar_t* UTF8Decode2BytesUnicode(char* input)
//        {
//          int size = strlen(input);
//          wchar_t* result = (wchar_t*) malloc(size*sizeof(wchar_t));
//          int rindex = 0,
//              windex = 0;
//          while (rindex < size)
//          {
//              wchar_t ch;

//              // 1110xxxx 10xxxxxx 10xxxxxx
//              if((input[rindex] & MASK3BYTES) == MASK3BYTES)
//              {
//                 ch = ((input[rindex] & 0x0F) << 12) | (
//                       (input[rindex+1] & MASKBITS) << 6)
//                      | (input[rindex+2] & MASKBITS);
//                 rindex += 3;
//              }
//              // 110xxxxx 10xxxxxx
//              else if((input[rindex] & MASK2BYTES) == MASK2BYTES)
//              {
//                 ch = ((input[rindex] & 0x1F) << 6) | (input[rindex+1] & MASKBITS);
//                 rindex += 2;
//              }
//              // 0xxxxxxx
//              else if(input[rindex] < MASKBYTE)
//              {
//                 ch = input[rindex];
//                 rindex += 1;
//              }

//              result[windex] = ch;
//           }
//        }

//        char* getUnicodeToUTF8(wchar_t* myString) {
//          int size = sizeof(wchar_t);
//          if (size == 1)
//            return (char*) myString;
//          else if (size == 2)
//            return UTF8Encode2BytesUnicode((unsigned short*) myString);
//          else
//            return UTF8Encode4BytesUnicode((unsigned int*) myString);
//        }
    };
}

#endif // UNICODE_CONV_H
