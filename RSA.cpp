#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<cmath>
#define  sp system ("pause");
using namespace std;
unsigned long long prime[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
unsigned long long random(unsigned long long m,unsigned long long n)//Generate random numbers between (m, n) in high-precision 
{
    unsigned long long ans,a;
    for(int i=0;i<4;i++){
        a=rand();
        a<<=(15*i);
        ans=ans|a;
    }
    return (ans%(n-m+1)+m);
}
unsigned long long powmod(unsigned long long x, unsigned long long n, unsigned long long p)//return value=(x^n ) mod p
{ 
    unsigned long long ans,t;
    if(n==0) return 1;
    ans=1;
    t=x%p;
    while(n){
        if(n&1){
           ans=(ans*t)%p;
        }
        n>>=1;
        t=(t*t)%p;
    }
    return ans;
}
int is_prime(unsigned long long p)//Detect whether p is a prime number
{
    long long tem=(long long)sqrt((double)p)+1;
    for (int i=2;i<tem;i++){
      if (p%i==0) {return 0;break;}
    }
    return 1;
}

unsigned long long get_prime(){//Randomly generate 14-bit primes
    unsigned long long ans;
    ans=random(8192,16383);
    while (!is_prime(ans)){
       ans=random(8192,16383);
       if (ans%2==0)ans++;
    }
    return ans;
}

unsigned long long get_d(long long a,long long b)//Calculate d 
{
    long long s[100],t[100],r[100],flag,q,q2,k,x;
    r[0]=a;r[1]=b;
    s[0]=1;s[1]=0;t[0]=0;t[1]=1;
    flag=1;
    q=r[0]/ r[1];
    r[2]=r[0]-q*r[1];
    q2=q;
    long long j;
    for (j=2;flag;j++){
        q=r[j-1] / r[j];
        r[j+1]=r[j-1]-q*r[j];
        s[j]=s[j-2]-q2*s[j-1];
        t[j]=t[j-2]-q2*t[j-1];
        q2=q;
        if (r[j+1]==0) flag=0;
    }
    j--;
    if (s[j]<0)
    {
               k=1;
               while ((k*a-b)<0) k++;
               x=k*a-b;
               s[j]=k-(x-1)*s[j];
          //    t[j]=-1-(x-1)*(t[j]);
    }
    //cout<<s[j]<<"**"<<endl;
    return (s[j]);
}

unsigned long long gcd(unsigned long long x,unsigned long long y){//Calculate the least common multiple of x and y
    unsigned long long tem,tem2;
    if(x<y){
           tem=x;x=y;y=tem;
    }
    tem2=x%y;
    while(tem2!=0){
       x=y;
       y=tem2;
       tem2=x%y;
    }
    return y;
}

void get_parameter(unsigned long long &n,unsigned long long &e,unsigned long long &d)//Generating parameters for RSA algorithm£ºn,e,d 
{
    unsigned long long p,q,t;
    long long x,y,tem;
    p=get_prime();
    q=get_prime();
    //while (p==q) q=get_prime();   
    n=p*q;
    t=(p-1)*(q-1);
    do
    {
        e=random(1,32768);
        if (e%2==0) e++;
    }while(gcd(e,t)!=1);
    x=e;y=t;
    d=get_d(x,y);   
}

void decode(vector<unsigned long long> s,unsigned long long n,unsigned long long e,unsigned long long d){//Decryption 
     unsigned long long tem;
     string ts,ans="";
     int l=s.size();
    // cout<<"Decrypted Plaintext"<<endl; 
     for(int i=0;i<l;i++){
             tem=powmod(s[i],e,n);
            // cout<<tem<<" ";
             ts="";
             while(tem!=0){
                           ts=(char)(tem%256)+ts;
                           tem>>=8;
                           }
             ans+=ts;
     }cout<<endl;
     cout<<"Decrypted Plaintext:\n"<<ans<<endl;
}

void encode(string s,unsigned long long n,unsigned long long e,unsigned long long d){ //Digitization & Encryption
    int len=s.length();
    vector<unsigned long long> ans;
    unsigned long long tem;
    cout<<"Group the plaintext in every three letters as a group, then transform groups into digitals:"<<endl; 
    for(int i=0;i<len;i+=3){
            tem=s[i];
            cout<<tem<<"()\n";
            if(i+1<len) {tem<<=8;tem+=s[i+1];}
            if(i+2<len) {tem<<=8;tem+=s[i+2];}
            cout<<tem<<" ";
            ans.push_back(powmod(tem,d,n));
    }
    cout<<endl;cout<<endl;
    cout<<"Ciphertext:\n";
    for(int i=0;i<ans.size();i++){
       cout<<ans[i]<<" ";
    };
    cout<<endl;
    decode(ans,n,e,d);
}

int main()
{    
    srand(time(0));
    unsigned long long e=0,d=0,n=0;
    get_parameter(n,e,d);
    cout<<"This is a RSA encryptor     Author£ºLilin Wang\n/****************************************************/"<<endl; 
    cout<<"Randomly generated:n="<<n<<endl;
   // cout<<endl;
    cout<<"Randomly generated:e="<<e<<endl;
   // cout<<endl;
    cout<<"Randomly generated:d="<<d<<endl;
    cout<<endl;
    string text="Mathenatical Fundation of Information Security 201202001 5101109008";
    cout<<"Plaintext:\n"<<text<<endl;
    cout<<endl;
    encode(text,n,e,d);
    sp;
}
