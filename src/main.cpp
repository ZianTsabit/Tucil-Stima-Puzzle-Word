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


int N = 0; // jumlah baris
int M = 0; // jumlah kolom 

unordered_set<string> wordlist;		// unordered list untuk menyimpan kata yang ingin dicari	
vector<vector<char>> puzzle;       // array dua dimensi untuk menyimpan puzzle
set<string> words;

void bacaDaftarKata(string filename);
void bacaPuzzle(string filename);
void cariKata();
void printHasil();


void printPuzzles();
void printKata();


int main(){
    cout<<"***********SELAMAT DATANG DI WORD SEARCH PUZZLE GAME***********" <<endl;
    
    cout<<endl;
    
    bacaPuzzle("input_file.txt");
    printPuzzles();
    
    cout<<endl;
    
    cout<<"DAFTAR KATA YANG HARUS DICARI:" <<endl;

}

void bacaPuzzle(string filename){
    ifstream pzlReader(filename);

    string line;
    
    if (pzlReader.is_open()){
        while (getline(pzlReader, line)){
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

void printPuzzles(){
    

    for (int i=0; i< N; i++){
        vector<char> row = puzzle[i];
        for (int j = 0; j < M; j++){
            cout<< row[j] << " ";
        }
        cout << endl;

    } 
}

// bool isKata(string str){
//     int count = 0;
//     for (int i = 0; i < str.size(); i++){
//         if (str[i] < 'A' || str[i] > 'Z'){
//             return false;
//         }else{
//             count++;
//         }
//     }
// }

// void bacaDaftarKata(string filename){
//     ifstream ktReader(filename);

//     string kata;
//     if (ktReader.is_open()){
//         while (getline(ktReader, kata)){
//             if (isKata(kata)){
//                 wordlist.insert(kata);
//             }
//         }
//         ktReader.close();
//     }
// }

// void printKata(){
//     for (auto const& i: wordlist){
//         cout<< i << " ";
//     }
//     cout << endl;
// }