#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#define  sp system ("pause");
using namespace std;
unsigned long long prime[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

unsigned long long random(unsigned long long m,unsigned long long n)////Generate random numbers between (m, n) in high-precision 
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

int is_prime(unsigned long long p)//Use Rabin-Miller algorithm to detect whether p is a prime number.Repeated nine times to ensure the correctness
{
    int len=sizeof(prime)/sizeof(unsigned long long);
    int s=0;
    unsigned long long u=p-1;
    while((u&1)==0 && u!=0){
       u>>=1;s++;
    }
    for(int i=0;i<10;i++){
       unsigned long long a=random(2,p-2),x=powmod(a,u,p);
       if(x==1 || x==p-1)continue;
       int flag=0;
       for(int r=1;r<s;r++){
           x=(x*x)%p;
           if(x==1)return 0;
           if(x==p-1){
              flag=1;break;
           }
       }
       if(!flag) return 0;
    }
    return 1;
}

int main(){
  srand(time(0));
  int x,f,tem=1;
  cout<<"Input -1 to exit.\n";  
  while (tem){
    cout<<"Please input a integer:";
    cin>>x;
    if (x==-1) break;
    f=is_prime(x);
    if (f==1) {cout<<"The integer is a prime."<<endl;} else
    {cout<<"The integer is not a prime."<<endl;}
  }
  sp;
}
