#include<iostream>
#include<vector>
#include<string>
#include <fstream>
using namespace std;
int main(){
    int alphabetSize = 26; // size of alphabet
    int startSymbol = 65; //first symbol in the ASCII table
    std::string fileName = "cypherVigenere.txt"; // names of our files 
    std::string fileName1 = "openVigenere.txt";
   
   
    cout << "The symbols you can use for the message/key: " << endl;
    for (char i = startSymbol; i < startSymbol + alphabetSize; ++i) {
    cout << i << " ";
    }
    cout << endl;
    
    
    int i,j,k,n;
    vector<vector<char> > a(26,vector<char>(26));
    k=0;
    n=26;
    for(i=0;i<n;i++){
        k=i;
        for(j=0;j<n;j++){
            a[i][j]='A'+k;
            k++;
            if(k==26)
                k=0;
        }
    }
    cout<<"Enter the message\n";
    string s;
    cin>>s;
    
    std::ofstream fout(fileName1.c_str()); // oppening file
    fout << s;               // writing to file
    fout.close();                 // closing file
    
    cout<<"Enter the key\n";
    string key;
    cin>>key;
    k=0;
    int mod = key.size();
    for(i=key.size();i<s.size();i++){
        key+=key[k%mod];
        k++;
    }
    cout<<"Encryption via Vegenere's table: " ;
    string encrypt;
    for(i=0;i<s.size();i++){
        encrypt+= a[s[i]-'A'][key[i]-'A'];
        cout << encrypt;
    }
    cout<< '\n';
    cout<<"Encrypted message: "<<encrypt<<'\n';
    
    fout.open(fileName.c_str()); // oppening file
    fout << encrypt;      // writing to file
    fout.close();
    return 0;
}
