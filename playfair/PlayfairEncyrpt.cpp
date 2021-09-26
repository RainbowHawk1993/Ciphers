#include<iostream>
#include<string>
#include<vector>
#include<map>
#include <locale>
#include <fstream>
using namespace std;
int main(){
   
    int alphabetSize = 95; // size of alphabet
    int startSymbol = 32; //first symbol in the ASCII table
    std::string fileName = "cypherPlayfair.txt"; // names of our files 
    std::string fileName1 = "openPlayfair.txt";
   
    cout << "Symbols you can use for the message/key: " << endl;
	for (char i = startSymbol; i < startSymbol + alphabetSize; ++i) {
    cout << i << " ";
    }
    cout << endl;
   
    int i,j,k,n;
    cout<<"Enter the message"<<endl;
    string s,origin;
    getline(cin,origin);
    
    std::ofstream fout(fileName1.c_str()); // oppening file
    fout << origin;               // writing to file
    fout.close();                 // closing file
    
    cout<<"Enter the key"<<endl;
    string key;
    cin>>key;
    for(i=0;i<origin.size();i++){
        if(origin[i]!=' ')
            s+= origin[i];
    }
    vector<vector<char> > a(5,vector<char>(5,' '));
    n=5;
    map<char,int> mp;
    k=0;
    int pi,pj;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            while(mp[key[k]]>0&&k<key.size()){
                k++;
            }
            if(k<key.size()){
                a[i][j]=key[k];
                mp[key[k]]++;
                pi=i;
                pj=j;
            }
            if(k==key.size())
            break;
        }
        if(k==key.size())
            break;
    }
    k=0;
    for(;i<n;i++){
        for(;j<n;j++){
            while(mp[char(k+'a')]>0&&k<26){
                k++;
            }
            if(char(k+'a')=='j'){
                j--;
                k++;
                continue;
            }
            if(k<26){
                a[i][j]=char(k+'a');
                mp[char(k+'a')]++;
            }
        }
        j=0;
    }

    string ans;
    if(s.size()%2==1)
        s+="x";
    for(i=0;i<s.size()-1;i++){
        if(s[i]==s[i+1])
            s[i+1]='x';
    }

    map<char,pair<int,int> > mp2;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            mp2[a[i][j]] = make_pair(i,j);
        }
    }
    
    for(i=0;i<s.size()-1;i+=2){
        int y1 = mp2[s[i]].first;
        int x1 = mp2[s[i]].second;
        int y2 = mp2[s[i+1]].first;
        int x2 = mp2[s[i+1]].second;
        if(y1==y2){
            ans+=a[y1][(x1+1)%5];
            ans+=a[y1][(x2+1)%5];
        }
        else if(x1==x2){
            ans+=a[(y1+1)%5][x1];
            ans+=a[(y2+1)%5][x2];    
        }
        else {
            ans+=a[y1][x2];
            ans+=a[y2][x1];
        }
    }
    cout<<ans<<'\n';
    fout.open(fileName.c_str()); // oppening file
    fout << ans;               // writing to file
    fout.close();
    return 0;
}
