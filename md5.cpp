#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>

using namespace std;
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476
#define F(x,y,z) (((x)&(y)) | ((~x) & (z)))
#define G(x,y,z) (((x)&(z)) | ((y) & (~z)))
#define H(x,y,z) ((x)^(y)^(z))
#define I(x,y,z) ((y)^((x)|(~z)))
#define shiftt(x,n) (((x) << (n)) | ((x) >> (32-n)))




class MD5 {
    private:

    int length_origin;
    int length;
    int md5_A;
    int md5_B;
    int md5_C;
    int md5_D;
    unsigned int k[64];
    unsigned int* out;
    int* addArray;

    public:

    MD5() {
        md5_A = A;
        md5_B = B;
        md5_C = C;
        md5_D = D;
        for (int i = 0; i < 64; i++) {
            k[i] = abs(sin(i+1)*(pow(2,32)));
        }
    }

    void divide(string source) {
        length = ((source.length() + 8) / 64 + 1) * 64;
        //总共有length的byte数，四个byte为一组
        out = new unsigned[length / 4];
        int rest = source.length() % 4;
        int count = 0;
        //cout << hex << (('e') + (80 << 8) + (0 << 16) + (0 << 24)) << dec <<  endl; 
        for (int i = 0; i < length / 4; i++) {
            out[i] = 0;
        }
        for (int i = 0; i < source.length(); i+=4)  {
            if (i + 3 >= source.length()) {
                break;
            }
            out[count] = 0;
            out[count] = out[count] +  (source[i]) + (source[i+3] << 24) + (source[i+2] << 16) + (source[i+1] << 8);
            count++;
        }
        int last = source.length() - 1;
                if (rest == 1) {
                    out[count] = out[count] +  (source[last]) + (128 << 8);
                } else if (rest == 2) {
                    out[count] = out[count] +  (source[last-1]) + (source[last] << 8) + (128 << 16);
                } else if (rest == 3) {
                    out[count] = out[count] +  (source[last-2]) + (source[last-1] << 8) + (source[last] << 16) + (128 << 24);
                } else if (rest == 0) {
                    out[count] = 128;
                }
        //以32来存储　　直接都是子分组，　　只要以１６个子分组来看就行了
        unsigned long long  xx = source.length() * 8;
        cout << "原来字符串的bits数" <<  xx << endl;
        //out[length-2] = ((xx & 0xff) << 24) + ((xx & 0xff00) << 16) + ((xx & 0xff0000) << 8) + (xx & 0xff000000);
        //out[length-1] = ((xx & 0xff00000000) << 24) + ((xx & 0xff0000000000) << 16) + ((xx & 0xff000000000000) << 8) + (xx & 0xff00000000000000);
        out[length / 4-2] = xx & 0xffffffff ;
        out[length / 4-1] = (xx & 0xffffffff00000000) >> 16 ;
        printByHex(out, length / 4 );
        cout  << "总共有多少个子组: " << length / 4 << endl;
    }

    

    string md5(string input) {
/*        int k[64]={
                0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
                0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,0x698098d8,
                0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,
                0xa679438e,0x49b40821,0xf61e2562,0xc040b340,0x265e5a51,
                0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
                0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,
                0xfcefa3f8,0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,
                0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,
                0xbebfbc70,0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
                0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,0xf4292244,
                0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,
                0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,
                0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391};
  */      //string addBitStr = addBit(input); 
        divide(input);
        const unsigned int s[]={7,12,17,22,7,12,17,22,7,12,17,22,7,
                                12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
                                4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,
                                15,21,6,10,15,21,6,10,15,21,6,10,15,21};

        //length 为byte的长度， output为的长度为 length / 4
   for (int j = 0; j < length / 4  / 16; j++) {
        unsigned int subarray[16];
        for (int z = 0; z <  16; z++) {
            subarray[z] = out[j*16 + z];
        }
        unsigned int f,g;
        unsigned int a = md5_A;
        unsigned int b = md5_B;
        unsigned int c = md5_C;
        unsigned int d = md5_D;
        for (int i = 0; i < 64;  i++) {
            // 每一轮完了  才加，一轮有4大组，每大组有16小组
            if (i % 64 >= 0 && i % 64 < 16 ) {
                f = F(b,c,d);
                //cout << "F"   << endl;
                //g = (i % 64) + i % 64 * 64;
                g=i;
            } else if(i % 64 >= 16&& i % 64 < 32 ) {
                f = G(b,c,d);
                //cout << 'G' << endl;
                //g=(5*(i % 64)+1)%16 + i % 64 * 64;
                g=(5*i+1)%16;
            } else if (i % 64 >= 32 && i % 64 < 48) {
                //cout << 'H' << endl;
                f = H(b,c,d);
                //g=(3* (i% 64) +5)%16 + i % 64 * 64;
                g=(3*i+5)%16;
            } else {
                //cout << 'I' << endl;
                f = I(b,c,d);
                //g=(7*(i % 64) )%16 + i % 64 * 64;
                g=(7*i)%16;
            }
            unsigned int tmp = d;
            d = c;
            c = b;
            b = b + shiftt((a + f + subarray[g] + k[i % 64]), s[i % 64]);
            a = tmp;
          //  cout << hex << subarray[g] << "  " << a << "   " <<  b  <<  "   " << c <<  "   " << d << dec << endl;
        }
        //cout << hex << md5_A << "   "  << md5_B << "   " << md5_C << "    " << md5_D << dec << endl;
        md5_A += a;
        md5_B += b;
        md5_C += c;
        md5_D += d;
        //cout << hex << md5_A << "   "  << md5_B << "   " << md5_C << "    " << md5_D << dec << endl;
   }
        return transToStr();
    }
    string transToStr() {
        string st = "";
        unsigned int num[4] = {md5_A, md5_B, md5_C, md5_D};
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int gigital = ((num[i] >> (8 * j)) & 0xff);
                int first = (gigital & 0xf0) >> 4 ;
                char x;
                if (first >= 0 && first <= 9) {
                    x = '0' + first;
                } else {
                    x = 'a' + first - 10;
                }
                st.push_back(x); 
                first = (gigital & 0xf);
                x;
                if (first >= 0 && first <= 9) {
                    x = '0' + first;
                } else {
                    x = 'a' + first - 10;
                }
                st.push_back(x); 
            }
        }
        return st;
    }


    void printByHex(string output) {
        for (int i = 0; i < output.length(); i++) {
            char x = output[i];
            cout << hex << (short)x;
        }
        cout << dec << endl;
    }
    void printByHex(unsigned output[], int length) {
        for (int i = 0; i < length; i++) {
            cout << hex << output[i] << " ";
        }
        cout << dec << endl;
    }


};


int main() {
    string input = "jklmn";
    cin >> input ;
    MD5* md = new MD5();
    string output =  md->md5(input);
    cout << input << "用md5算法处理 : " << output << endl;;
}
