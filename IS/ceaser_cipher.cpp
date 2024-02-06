#include <bits/stdc++.h>
using namespace std;
string str;
void encrypt(int key);
void decrypt(int key);
int main(){
	int key;
	cout<<"Enter the String: ";
	getline(cin,str);
	cout<<"String is : "<<str<<endl;
	cout<<"Enter the key value: "<<endl;
	cin>>key;
	encrypt(key);
	cout<<str<<endl<<key<<endl;
	decrypt(key);
	return 0;
}
void encrypt(int key){

for(int i=0; str[i];i++){
		if(str[i]==' ')continue;
		else if(str[i]>= 'a' && str[i]<='z'){
			str[i]=((str[i]-'a')+key)%26+'a';
		}
		else{
		 str[i]=((str[i]-'A')+key)%26+'A';
		}
	}
	cout<<"Encrypted version: "<<str<<endl;
}
void decrypt(int key){

for(int i=0; str[i];i++){
		if(str[i]==' ')continue;
		else if(str[i]>= 'a' && str[i]<='z'){
			str[i]=((str[i]-'a' )%26)-key+'z';
		}
		else{
		str[i]=((str[i]-'A' )%26)-key+'Z';
		}
	}
	cout<<"Decrypted version: "<<str<<endl;
}