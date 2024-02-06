#include<bits/stdc++.h>
using namespace std;
void keyset(char keyword[],string key, int size);
void encrypted(char keyword[],string str,char encrypt[]);
void decrypted(char keyword[],char encrypt[],char decrypt[]);
int main(){
    string key , str;
    cin>> key;
    cin>>str;
    char keyword[str.size()],encrypt[str.size()],decrypt[str.size()];
    keyset(keyword,key,str.size());
    cout<<"Crypted text:"<<endl;
    encrypted(keyword,str,encrypt);
     cout<<encrypt<<endl;
    cout<<"Decrtpyted: ";
    decrypted(keyword,encrypt,decrypt);
     cout<<decrypt<<endl;
    
}
void keyset(char keyword[] ,string key, int size){
    if(strlen(keyword) < size){
        int i;
        for( i=0;i<size;i++){
            keyword[i]=key[i%key.size()];
        }
        keyword[i]='\0';
    }
}
void encrypted(char keyword[],string str,char encrypt[]){
    
    int i;
    for(i=0;str[i];i++){
         encrypt[i]=((str[i]-'A')+(keyword[i]-'A'))%26 +'A';
    }
    encrypt[i]='\0';
   
    
}
void decrypted(char keyword[],char encrypt[],char decrypt[]){
    int i;
    for(i=0;encrypt[i];i++){
        char x =(encrypt[i]-keyword[i]+26)%26 +'A';
        decrypt[i]=x; 
    }
    decrypt[i]='\0';
}
