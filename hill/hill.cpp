
#include <cmath>
#include <fstream>
#include <iostream>
#include <locale>
#include <vector>

using namespace std;
typedef std::vector<std::vector<double> > matrix; //creating a synonym for the matrix

class hillChiper { // encyrpting text via hill's method
  matrix encryptMatrix, decryptMAtrix, a, b, message, c; // needed matrixs
  int size;              // size of the message
  int alphabetSize = 95; // size of alphabet
  int startSymbol = 32; //first symbol in the ASCII table
  std::string fileName = "cypherHill.txt"; // names of our files
  std::string fileName1 = "openHill.txt";

public:
  void getAlphabet() { // printing out our Alphabet
  	cout << "The symbols you can use for the message/key: " << endl;
    for (char i = startSymbol; i < startSymbol + alphabetSize; ++i) {
      cout << i << " ";
    }
    cout << endl;
  }
  void setSize(int key=1) { // setting size of the message
    encryptMatrix.clear(); // first we need to clear the matrix
    decryptMAtrix.clear();
    a.clear();
    b.clear();
    c.clear();
    message.clear();
    if(key){
    //cout << "Input size of your message: ";
    cin >> size;                     // then we read the inputted size
    }
    for (int i = 0; i < size; ++i) { // setting up our matrixs
      encryptMatrix.push_back(std::vector<double>(10, 0));
      decryptMAtrix.push_back(std::vector<double>(10, 0));
      a.push_back(std::vector<double>(10, 0));
      b.push_back(std::vector<double>(10, 0));
      message.push_back(std::vector<double>(10, 0));
      c.push_back(std::vector<double>(10, 0));
    }
  }
  void encrypt() { // encrypting
    for (int i = 0; i < size; ++i)
      for (int j = 0; j < 1; ++j)
        for (int k = 0; k < size; ++k)
          encryptMatrix[i][j] =
              encryptMatrix[i][j] +
              a[i][k] * message[k][j]; // adding needed elements

    cout << "\nMessage after being encyrpted: ";
    std::string result = "";
    for (int i = 0; i < size; ++i)
      result += static_cast<char>(
          (fmod(encryptMatrix[i][0], alphabetSize) + startSymbol)); // (mod 95)
    cout << result;
    std::ofstream fout(fileName.c_str()); // oppening file
    fout << result;               // writing to file
    fout.close();                 // closing file
  }

  void inverse() { //inverting our matrix to decrypt the message
    double p, q;

    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j) {
        if (i == j)
          b[i][j] = 1;
        else
          b[i][j] = 0;
      }

    for (int k = 0; k < size; ++k) {
      for (int i = 0; i < size; ++i) {
        p = c[i][k];
        q = c[k][k];

        for (int j = 0; j < size; ++j) {
          if (i != k) {
            c[i][j] = c[i][j] * q - p * c[k][j];
            b[i][j] = b[i][j] * q - p * b[k][j];
          }
        }
      }
    }

    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j)
        b[i][j] = b[i][j] / c[i][i];

    cout << "\n\nInverted Matrix:\n";
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j)
        cout << b[i][j] << " ";

      cout << "\n";
    }
  }

  void decrypt() { // Decription
    getKey(1);
    inverse();

    for (int i = 0; i < size; ++i)
      for (int j = 0; j < 1; ++j)
        for (int k = 0; k < size; ++k)
          decryptMAtrix[i][j] =
              decryptMAtrix[i][j] + b[i][k] * encryptMatrix[k][j];

    cout << "\nMessage after being decrypted : ";
    for (int i = 0; i < size; ++i){
	
      cout << static_cast<char>(
          (fmod(decryptMAtrix[i][0], alphabetSize) + startSymbol));
	std::ofstream fout(fileName1.c_str()); // oppening file
    fout << static_cast<char>(
          (fmod(decryptMAtrix[i][0], alphabetSize) + startSymbol)); //writing to file              // запис в файл
    fout.close();
}
    cout << "\n";
  }

  void getKey() { // getting decryption key
    string msg;
    string keyword;
    cout << "\nEnter the message: ";
    getline(cin, msg);
    size = msg.size();
    setSize(false);

    cout << "\nEnter the keyword (" << size<<'x'<<size << " symbols) (input only letters): ";
    getline(cin, keyword);

    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j) {
        a[i][j] = keyword[i * j + j];
        c[i][j] = a[i][j];
      }


    for (int i = 0; i < size; ++i)
      message[i][0] = msg[i] - startSymbol;
  }
  void getKey(int) { // getting decryption key (while reading from file)
    string msg;
    string keyword;

    std::ifstream fin(fileName.c_str()); // oppening file to read from
    getline(fin, msg);                 // reading the message in the file
    cout << "\nMessage from the file " + fileName + ": " + msg << endl;
    cout << "\nEnter the keyword(" << size << "x" << size << " symbols): ";
    getline(cin, keyword);

    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j) {
        a[i][j] = keyword[i * j + j];
        c[i][j] = a[i][j];
      }

    for (int i = 0; i < size; ++i)
      message[i][0] = msg[i] - startSymbol;

  }


};

int main() {
  hillChiper crypter;
  crypter.getAlphabet();
  crypter.getKey();
  crypter.encrypt();
  crypter.decrypt();
}
