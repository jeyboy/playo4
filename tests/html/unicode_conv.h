#ifndef UNICODE_CONV_H
#define UNICODE_CONV_H

#include <qbytearray.h>

#define         MASKBITS                0x3F
#define         MASKBYTE                0x80
#define         MASK2BYTES              0xC0
#define         MASK3BYTES              0xE0
#define         MASK4BYTES              0xF0
#define         MASK5BYTES              0xF8
#define         MASK6BYTES              0xFC

namespace Html {
    class UnicodeConv {
        QByteArray unicodeBytes(const unsigned int unicode) {
            // 0xxxxxxx
            if (unicode < 0x80)
                return QByteArray(1, (char)unicode);
            // 110xxxxx 10xxxxxx
            else if(unicode < 0x800) {
                QByteArray()
                    << ((char)(MASK2BYTES | unicode >> 6))
                    << ((char)(MASKBYTE | unicode & MASKBITS));
            }
            // 1110xxxx 10xxxxxx 10xxxxxx
            else if(unicode < 0x10000) {
                QByteArray()
                    << ((char)(MASK3BYTES | unicode >> 12))
                    << ((char)(MASKBYTE | unicode >> 6 & MASKBITS))
                    << ((char)(MASKBYTE | unicode & MASKBITS));

            // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            } else if(unicode < 0x200000) {
                QByteArray()
                    << ((char)(MASK4BYTES | unicode >> 18))
                    << ((char)(MASKBYTE | unicode >> 12 & MASKBITS))
                    << ((char)(MASKBYTE | unicode >> 6 & MASKBITS))
                    << ((char)(MASKBYTE | unicode & MASKBITS));
            }
            // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            else if(unicode < 0x4000000) {
                QByteArray()
                    << ((char)(MASK5BYTES | unicode >> 24))
                    << ((char)(MASKBYTE | unicode >> 18 & MASKBITS))
                    << ((char)(MASKBYTE | unicode >> 12 & MASKBITS))
                    << ((char)(MASKBYTE | unicode >> 6 & MASKBITS))
                    << ((char)(MASKBYTE | unicode & MASKBITS));
            }
            // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            else if(unicode < 0x8000000) {
                QByteArray()
                    << ((char)(MASK6BYTES | unicode >> 30))
                    << ((char)(MASKBYTE | unicode >> 24 & MASKBITS))
                    << ((char)(MASKBYTE | unicode >> 18 & MASKBITS))
                    << ((char)(MASKBYTE | unicode >> 12 & MASKBITS))
                    << ((char)(MASKBYTE | unicode >> 6 & MASKBITS))
                    << ((char)(MASKBYTE | unicode & MASKBITS));
            } else {
                qDebug() << "unicode: sheet happened";
            }
        }

        QString bytesToUnicode(const QByteArray & bytes) {
           for(int i=0; i < input.size();)
           {
              Unicode4Bytes ch;

              // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
              if((input[i] & MASK6BYTES) == MASK6BYTES)
              {
                 ch = ((input[i] & 0x01) << 30) | ((input[i+1] & MASKBITS) << 24)
                      | ((input[i+2] & MASKBITS) << 18) | ((input[i+3]
                                & MASKBITS) << 12)
                      | ((input[i+4] & MASKBITS) << 6) | (input[i+5] & MASKBITS);
                 i += 6;
              }
              // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
              else if((input[i] & MASK5BYTES) == MASK5BYTES)
              {
                 ch = ((input[i] & 0x03) << 24) | ((input[i+1]
                        & MASKBITS) << 18)
                      | ((input[i+2] & MASKBITS) << 12) | ((input[i+3]
                          & MASKBITS) << 6)
                      | (input[i+4] & MASKBITS);
                 i += 5;
              }
              // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
              else if((input[i] & MASK4BYTES) == MASK4BYTES)
              {
                 ch = ((input[i] & 0x07) << 18) | ((input[i+1]
                        & MASKBITS) << 12)
                      | ((input[i+2] & MASKBITS) << 6) | (input[i+3] & MASKBITS);
                 i += 4;
              }
              // 1110xxxx 10xxxxxx 10xxxxxx
              else if((input[i] & MASK3BYTES) == MASK3BYTES)
              {
                 ch = ((input[i] & 0x0F) << 12) | ((input[i+1] & MASKBITS) << 6)
                      | (input[i+2] & MASKBITS);
                 i += 3;
              }
              // 110xxxxx 10xxxxxx
              else if((input[i] & MASK2BYTES) == MASK2BYTES)
              {
                 ch = ((input[i] & 0x1F) << 6) | (input[i+1] & MASKBITS);
                 i += 2;
              }
              // 0xxxxxxx
              else if(input[i] < MASKBYTE)
              {
                 ch = input[i];
                 i += 1;
              }
              output.push_back(ch);
           }
        }
    };
}

#endif // UNICODE_CONV_H

//typedef unsigned short   Unicode2Bytes;
//typedef unsigned int     Unicode4Bytes;

//void UTF8Encode2BytesUnicode(std::vector< Unicode2Bytes > input,
//                             std::vector< byte >& output)
//{
//   for(int i=0; i < input.size(); i++)
//   {
//      // 0xxxxxxx
//      if(input[i] < 0x80)
//      {
//         output.push_back((byte)input[i]);
//      }
//      // 110xxxxx 10xxxxxx
//      else if(input[i] < 0x800)
//      {
//         output.push_back((byte)(MASK2BYTES | input[i] >> 6));
//         output.push_back((byte)(MASKBYTE | input[i] & MASKBITS));
//      }
//      // 1110xxxx 10xxxxxx 10xxxxxx
//      else if(input[i] < 0x10000)
//      {
//         output.push_back((byte)(MASK3BYTES | input[i] >> 12));
//         output.push_back((byte)(MASKBYTE | input[i] >> 6 & MASKBITS));
//         output.push_back((byte)(MASKBYTE | input[i] & MASKBITS));
//      }
//   }
//}

//void UTF8Decode2BytesUnicode(std::vector< byte > input,
//                             std::vector< Unicode2Bytes >& output)
//{
//   for(int i=0; i < input.size();)
//   {
//      Unicode2Bytes ch;

//      // 1110xxxx 10xxxxxx 10xxxxxx
//      if((input[i] & MASK3BYTES) == MASK3BYTES)
//      {
//         ch = ((input[i] & 0x0F) << 12) | (
//               (input[i+1] & MASKBITS) << 6)
//              | (input[i+2] & MASKBITS);
//         i += 3;
//      }
//      // 110xxxxx 10xxxxxx
//      else if((input[i] & MASK2BYTES) == MASK2BYTES)
//      {
//         ch = ((input[i] & 0x1F) << 6) | (input[i+1] & MASKBITS);
//         i += 2;
//      }
//      // 0xxxxxxx
//      else if(input[i] < MASKBYTE)
//      {
//         ch = input[i];
//         i += 1;
//      }

//      output.push_back(ch);
//   }
//}

//void UTF8Encode4BytesUnicode(std::vector< Unicode4Bytes > input,
//                             std::vector< byte >& output)
//{
//   for(int i=0; i < input.size(); i++)
//   {
//      // 0xxxxxxx
//      if(input[i] < 0x80)
//      {
//         output.push_back((byte)input[i]);
//      }
//      // 110xxxxx 10xxxxxx
//      else if(input[i] < 0x800)
//      {
//         output.push_back((byte)(MASK2BYTES | input[i] > 6));
//         output.push_back((byte)(MASKBYTE | input[i] & MASKBITS));
//      }
//      // 1110xxxx 10xxxxxx 10xxxxxx
//      else if(input[i] < 0x10000)
//      {
//         output.push_back((byte)(MASK3BYTES | input[i] >> 12));
//         output.push_back((byte)(MASKBYTE | input[i] >> 6 & MASKBITS));
//         output.push_back((byte)(MASKBYTE | input[i] & MASKBITS));
//      }
//      // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
//      else if(input[i] < 0x200000)
//      {
//         output.push_back((byte)(MASK4BYTES | input[i] >> 18));
//         output.push_back((byte)(MASKBYTE | input[i] >> 12 & MASKBITS));
//         output.push_back((byte)(MASKBYTE | input[i] >> 6 & MASKBITS));
//         output.push_back((byte)(MASKBYTE | input[i] & MASKBITS));
//      }
//      // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//      else if(input[i] < 0x4000000)
//      {
//         output.push_back((byte)(MASK5BYTES | input[i] >> 24));
//         output.push_back((byte)(MASKBYTE | input[i] >> 18 & MASKBITS));
//         output.push_back((byte)(MASKBYTE | input[i] >> 12 & MASKBITS));
//         output.push_back((byte)(MASKBYTE | input[i] >> 6 & MASKBITS));
//         output.push_back((byte)(MASKBYTE | input[i] & MASKBITS));
//      }
//      // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//      else if(input[i] < 0x8000000)
//      {
//         output.push_back((byte)(MASK6BYTES | input[i] >> 30));
//         output.push_back((byte)(MASKBYTE | input[i] >> 18 & MASKBITS));
//         output.push_back((byte)(MASKBYTE | input[i] >> 12 & MASKBITS));
//         output.push_back((byte)(MASKBYTE | input[i] >> 6 & MASKBITS));
//         output.push_back((byte)(MASKBYTE | input[i] & MASKBITS));
//      }
//   }
//}

//void UTF8Decode4BytesUnicode(std::vector< byte > input,
//                             std::vector< Unicode4Bytes >& output)
//{
//   for(int i=0; i < input.size();)
//   {
//      Unicode4Bytes ch;

//      // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//      if((input[i] & MASK6BYTES) == MASK6BYTES)
//      {
//         ch = ((input[i] & 0x01) << 30) | ((input[i+1] & MASKBITS) << 24)
//              | ((input[i+2] & MASKBITS) << 18) | ((input[i+3]
//                        & MASKBITS) << 12)
//              | ((input[i+4] & MASKBITS) << 6) | (input[i+5] & MASKBITS);
//         i += 6;
//      }
//      // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//      else if((input[i] & MASK5BYTES) == MASK5BYTES)
//      {
//         ch = ((input[i] & 0x03) << 24) | ((input[i+1]
//                & MASKBITS) << 18)
//              | ((input[i+2] & MASKBITS) << 12) | ((input[i+3]
//                  & MASKBITS) << 6)
//              | (input[i+4] & MASKBITS);
//         i += 5;
//      }
//      // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
//      else if((input[i] & MASK4BYTES) == MASK4BYTES)
//      {
//         ch = ((input[i] & 0x07) << 18) | ((input[i+1]
//                & MASKBITS) << 12)
//              | ((input[i+2] & MASKBITS) << 6) | (input[i+3] & MASKBITS);
//         i += 4;
//      }
//      // 1110xxxx 10xxxxxx 10xxxxxx
//      else if((input[i] & MASK3BYTES) == MASK3BYTES)
//      {
//         ch = ((input[i] & 0x0F) << 12) | ((input[i+1] & MASKBITS) << 6)
//              | (input[i+2] & MASKBITS);
//         i += 3;
//      }
//      // 110xxxxx 10xxxxxx
//      else if((input[i] & MASK2BYTES) == MASK2BYTES)
//      {
//         ch = ((input[i] & 0x1F) << 6) | (input[i+1] & MASKBITS);
//         i += 2;
//      }
//      // 0xxxxxxx
//      else if(input[i] < MASKBYTE)
//      {
//         ch = input[i];
//         i += 1;
//      }
//      output.push_back(ch);
//   }
//}
