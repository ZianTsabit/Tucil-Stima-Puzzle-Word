#include <iostream> //input output
#include <vector> //dynamically allocated array
#include <string> //string
#include <fstream> //file open
#include <algorithm> // hapus kata dari spasi
#include <ostream>
#include <cstdlib>

#include <unordered_set>
#include <set>

using namespace std;

const int minLength = 2;
const int maxLength = 50;

int N = 0; // jumlah baris
int M = 0; // jumlah kolom 

vector<string> wordlist;		// unordered list untuk menyimpan kata yang ingin dicari	
vector<vector<char>> puzzle;        // array dua dimensi untuk menyimpan puzzle
vector<vector<char>> jawaban;      
set<string> words;

void bacaDaftarKata(string filename);
void bacaPuzzle(string filename);
void cariKata(vector<vector<char>> puzzle);
void printKata(string filename);


void printPuzzles();
void printDaftarKata();

// FUNGSI UTAMA PROGRAM

int main(){
    cout<<"***********SELAMAT DATANG DI WORD SEARCH PUZZLE GAME***********" <<endl;
    
    cout<<endl;
    
    bacaPuzzle("../test/input_puzzle.txt");
    printPuzzles();
    
    cout<<endl;
    
    cout<<"DAFTAR KATA YANG HARUS DICARI:" <<endl;
    cout<<endl;
    
    bacaDaftarKata("../test/input_puzzle.txt");
    
    printDaftarKata();

    cout<<"Hasil...";
    cout<<endl;
    cariKata(puzzle);
    
    
    
    // cout<<endl;

    // cariKata();
    // printKata("../test/answers.txt");

}

// FUNGSI UNTUK MEMBACA PUZZLE DARI INPUT FILE

void bacaPuzzle(string filename){
    ifstream pzlReader(filename);

    string line;
    
    if (pzlReader.is_open()){
        while (getline(pzlReader, line)){
            
            
            if(line.size() == 1){
                break;
            }

            if (N == 0){
                M = (line.size()+1)/2; 
            }
            N++;

            vector <char> row;
            for (int i=0; i < line.size(); i+=2){
                row.push_back(line[i]);
            }
            puzzle.push_back(row);
        }
        pzlReader.close();
    }
}

// FUNGSI UNTUK MENAMPILKAN PUZZLE KE LAYAR

void printPuzzles(){
    
    for (int i=0; i< N; i++){
        vector<char> row = puzzle[i];
        for (int j = 0; j < M; j++){
            cout<< row[j] << " ";
        }
        cout << endl;

    } 
}

// FUNGSI UNTUK MEMBACA DAFTAR KATA YANG HARUS DICARI DARI INPUT FILE

void bacaDaftarKata(string filename){
    ifstream ktReader(filename);

    string kata;
    
    if (ktReader.is_open()){
        
        while (getline(ktReader, kata)){
            if (kata.size() == 1){
                while(getline(ktReader, kata)){
                    wordlist.push_back(kata);
                }
            }
        }
        ktReader.close();
    }
}

// FUNGSI UNTUK MENAMPILKAN DAFTAR KATA YANG HARUS DICARI KE LAYAR

void printDaftarKata(){
    for (int i=0; i< wordlist.size(); i++){
        cout<<wordlist[i]<<endl;
    } 
}

// FUNGSI MIN ANTAR DUA INTEGER

int min(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}

// FUNGSI UNTUK MENCARI KATA PADA PUZZLE SECARA HORIZONTAL

// void cariHorizontal(int r, int c){

//     string test1 = "";
//     string test2 = "";

//     for (int i= 0; i < min(M-c,maxLength); i++){
//         test1 = test1 + puzzle[r][c+i];
//         test2 = puzzle[r][c+1] + test2;
//         if ((i+1) >= minLength){
//             checkWord(test1);
//             checkWord(test2);
//         }
//     }
// }

// FUNGSI UNTUK MENCARI KATA

// void cariKata(){
//     for (int r = 0; r < N; r++){
//         for (int c = 0; c < M; c++){
//             cariHorizontal(r, c);
//         }
//     }
// }

// FUNGSI UNTUK MENAMPILKAN JAWABAN KE LAYAR

// void printKata(string filename){
//     ofstream wordprinter (filename);
//     if (wordprinter.is_open()){
//         for(auto const& i: words){
//             wordprinter << i  << endl;
//         }
//         wordprinter.close();
//     }
// }

// BRUTE FORCE ALGORITHM

int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 }; 
int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

bool search2D(vector<vector<char>> pzl, int row, int col, string word){
    
    
    if(pzl[row][col] != word[0]){
        return false;
    }

    int len = word.length();

    for (int dir = 0; dir < 8; dir++){
        
        int k, rd = row + x[dir], cd = col + y[dir];

        for(k = 1; k< len; k++){
            if (rd >= N || rd < 0 || cd >= M || cd < 0){
                break;
            }

            if (pzl[rd][cd] != word[k]){
                break;
            }
            rd += x[dir], cd += y[dir];
        }
        if(k == len){
            return true;
        }
    }
    return false;
}

void cariKata(vector<vector<char>> pzl){
    for (int row = 0; row < N; row++){
        for (int col = 0; col < M; col++){
            if (search2D(puzzle, row, col, wordlist[0])){
                cout << "text found"<<endl;
            } 
        } 
    }         
}