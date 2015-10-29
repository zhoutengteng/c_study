#include<iostream>
#include<cmath>
#include<string>

using namespace std;


struct key {
    unsigned long long first;
    unsigned long long second;
};

class RSA {
    private:
        unsigned long long  p;
        unsigned long long  q;
        unsigned long long  N;
        unsigned long long  e;
        unsigned long long  d;
        struct key* pub;
        struct key* pri;
        unsigned long long ch[128];
        unsigned long long dech[138];
        
    public:
        RSA(unsigned long long  p, unsigned long long q) {
            this->p = p;
            this->q = q;
            while (!isPrime(this->p) || !isPrime(this->q)) {
                cout << "请重新输入两个质数" << endl;
                cin >> this->p >> this->q;
            }
            this->N = this->p *  this->q;
            this->e = 7;
            while (!isMute(this->e)) {
                cout << "请输入和N：" << this->N <<"互质的数" << endl;
                cin >> this->e;

            }
            alchat();
            findd();
            cout <<  dec << "p : " << this->p << ",q: " << this->q << ", N:" << this-> N << ", e:" << this->e << ", d:" << this->d << endl;
            pub = new struct key();
            pub->first = this->e;
            pub->second = this->N;
            pri = new struct key();
            pri->first = this->d;
            pri->second = this->N;
        }
        
        RSA() {


        }
        
        void alchat() {
            unsigned long long  cc = 1;
            unsigned long long  cc2 = 1;
            for (int i = 0; i < 26; i++) {
                ch[i] = i + 'a';
            }
        }

        bool isMute(unsigned long long  e) {
            if (this->N % this->e == 0) return false;
            return true;
        }
        bool isPrime(unsigned long long x) {
            for (unsigned long long i = 2; i <= sqrt(x); i++) {
                if (x % i == 0) return false;
            }
            return true;
        }

        unsigned long long  Q() {
            return (this->p - 1) * (this->q - 1);
        }
        void findd() {
            unsigned long long  id = 1;
            unsigned long long x = Q();
            unsigned long long y = this->e % x;
            while (id++) {
                //cout << id << endl;
                if ((id * this->e) % x == 1) {
                //if (((id % x) * y) % x  == 1) {
                    this->d = id;
                    break;
                }
            }
        }        
        void print() {
            cout << "产生的公钥为("  << pub->first << "," << pub->second << "), ";
            cout << "产生的私钥为(" <<  pri->first << "," << pri->second << ")" << endl;

        }
        string encode(string source) {
            string st = "";
            for (unsigned long long  i = 0; i < source.length(); i++) {
                unsigned long long x = source[i]-'a';
                unsigned long long  re = 1;
             //   cout << x << " -> ";
                for (unsigned long long  j = 0; j < pub->first; j++) {
                    re = ((x % pub->second) * re) % pub->second; 
                }
                x = re % pub->second;
                st.push_back((char)x);

              //  cout << x << endl;
            }
            return st;
        }
        //最好还是用自己的对应表个来看好些
        string decode(string source) {
            string st = "";
            for (unsigned long long i = 0; i < source.length(); i++) {
                unsigned long long  x = source[i];
               // cout << x << " -> ";
                unsigned long long re = 1;
                for (unsigned long long j = 0; j < pri->first; j++) {
                    re = ((x % pri->second) * re) % pri->second; 
                }
                x = re % pri->second;
                st.push_back((char)ch[x]);
               // cout << x << endl;
            }
            return st;
        }
};


int main() {
    int i, j;
    cout << "请重新输入两个质数 11 3" << endl;

    cin >> i;
    cin >> j;
    RSA* rsa = new RSA (i, j);
    rsa->print();
    string str;
    cout << "要测试的字符串" << endl;
    cin >> str;
    cout << "编码后的字符串" << endl <<  rsa->encode(str) << endl;
    cout << "解码后的字符串" <<  endl << rsa->decode(rsa->encode(str)) << endl;;
}
