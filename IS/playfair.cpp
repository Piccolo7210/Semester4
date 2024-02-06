#include<bits/stdc++.h>
using namespace std;
void make_Diagram(string pt,char diagram[][2],int &dg_size);
void make_grid(string key,char grid[][5]);
void print_grid(char grid[][5]);
void print_diag(char diagram[][2],int dg_size);
void cypher_text(char grid[][5],char diagram[][2],int dg_size);
int main(){
    string pt,key;
    cout<<"Plain text: ";
    cin>>pt;
    cout<<"Key: ";
    cin>>key;
    char diagram[100][2],grid[5][5];
    int dg_size=0,i,j;
    make_Diagram(pt,diagram,dg_size);
    print_diag(diagram,dg_size);
    make_grid(key,grid);
    print_grid(grid);
   cypher_text(grid,diagram,dg_size);
}
void make_Diagram(string pt,char diagram[][2],int &dg_size){
    int i,j,z;
    for(i=0,z=0;pt[i];z++){
        for(j=0;j<2;j++){
            if(pt[i+1]== '\0' && j ==0){
                diagram[z][0]=pt[i];
                diagram[z][1]='X';
                j=1;
                i++;
            }
            else if(pt[i] == pt[i+1]){
                diagram[z][j]=pt[i];
                diagram[z][j+1]='X';
                j=1;
                i++;
            }
            else{
                diagram[z][j]=pt[i];
                diagram[z][j+1]=pt[i+1];
                i=i+2;
                j=1;
            }
        }
        dg_size++;
    }  
}
void make_grid(string key,char grid[][5]){
    int i,j,arr[26];
    
    for(i=0;i<26;i++){
        arr[i]=1;
    }
    int k;
    for(j=0,i=0;j<5;j++){
        if(key[i]=='\0')break;
       for(k=0;k<5 && key[i]!='\0';k++,i++){
            if(arr[key[i]-'A'] ==1){
            if(key[i] =='I' || key[i]=='J'){
                arr['I'-'A']=0;
                arr['J'-'A']=0;
                grid[j][k]='I';
            }
            else {
                arr[key[i]-'A'] =0;
                grid[j][k]=key[i];
            }
        }
       }
       if(key[i]=='\0' && k<5)break;
    }
    if(k<5){
        for(;k<5;k++){
            for(int m=0;m<26;m++){
                if(arr[m]==1){
                    if(m == 8 || m == 9){
                        grid[j][k]='I';
                        arr[8]=0;
                        arr[9]=0;
                        break;
                    }
                    else{
                        grid[j][k]=m+'A';
                        arr[m] =0;
                        break;
                    }
                }
   }
 }
 j++;
}

 for(;j<5;j++){
    for(k=0;k<5;k++){
        for(int m=0;m<26;m++){
            if(arr[m]==1){
                if(m==8 || m== 9){
                    grid[j][k]='I';
                    arr[8]=0;
                    arr[9]=0;
                    break;
                }
                else {
                    grid[j][k]=m+'A';
                    arr[m] =0;
                    break;
            }
                
            }
        }
    }
 }
}
void print_grid(char grid[][5]){
    cout<<"GRID: "<<endl;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)cout<<grid[i][j]<<" ";
        cout<<endl;
    }
}
void print_diag(char diagram[][2],int dg_size){
    cout<<"Diagram: "<<endl;
    for(int i=0;i<dg_size;i++){
        for(int j=0;j<2;j++)cout<<diagram[i][j];
        cout<<" ";
    }
    cout<<endl;
}
void cypher_text(char grid[][5],char diagram[][2],int dg_size){
    int i,j,k;
    for(i=0;i<dg_size;i++)
        {
            int row1,col1,row2,col2;
            for(j=0;j<5;j++){
                for(k=0;k<5;k++){
                    if(diagram[i][0] == 'J' || diagram[i][0] == 'I' ){
                        if (grid[j][k]=='J' || grid[j][k]=='I' ){
                            row1=j;
                            col1=k;
                        }
                    }
                    else if (diagram[i][0] == grid[j][k]){
                            row1=j;
                            col1=k;
                    }
                    if(diagram[i][1] == 'J' || diagram[i][1] == 'I' ){
                        if (grid[j][k]=='J' || grid[j][k]=='I' ){
                            row2=j;
                            col2=k;
                        }
                    }
                    else if (diagram[i][1] == grid[j][k]){
                            row2=j;
                            col2=k;
                    }

                }
            }
            if(row1 == row2){
                cout<< grid[row1][(col1+1)%5];
                cout<< grid[row1][(col2+1)%5];
            }
            else if(col1==col2)
                {
                    cout<< grid[(row1+1)%5][col1];
                    cout<< grid[(row2+1)%5][col1];
                }
            else{
                cout<<grid[row1][col2];
                cout<<grid[row2][col1];
            }
        }
}