#include <iostream> 
#include <vector> 
#include <string> 
#include <fstream> 
#include <algorithm> 
#include <ostream>
#include <cstdlib>
#include <filesystem>
#include <stdlib.h>
#include <unordered_set>
#include <set>
#include <cstdio>
#include <chrono>

using namespace std;
using namespace std::chrono;

int N = 0; // jumlah baris
int M = 0; // jumlah kolom
int totCompare = 0;

vector<string> wordlist;		// vektor untuk menyimpan kata yang harus dicari	
vector<vector<char>> answers; // vektor dua dimensi yang menyimpan hasil dari algoritma pencarian kata
vector<vector<char>> temp;    // array dua dimensi untuk menyimpan matriks kosong
vector<vector<char>> puzzle;    // array dua dimensi untuk menyimpan puzzle      

void bacaDaftarKata(string filename);
void bacaPuzzle(string filename);
void cariKata(vector<vector<char>> puzzle, vector<string> word);
void printKata(string filename);
void printPuzzles();
void printHasil();
void printDaftarKata();
void searchAnswers();

// FUNGSI UTAMA PROGRAM

int main(int argc, char* argv[]){
    
    cout<<"                                                               " <<endl;
    cout<<"                                                               " <<endl;
    cout<<"                                                               " <<endl;
    cout<<"         ___           ___               __                    " <<endl;
    cout<<"         \\  \\    _    /  /              |  |                 " <<endl;
    cout<<"          \\  \\  / \\  /  /____  ____   __|  |                " <<endl;
    cout<<"           \\  \\/   \\/  /  _  \\/   __\\/  _  |      __      " <<endl;
    cout<<"            \\         /| (_) |   |  |  (_) |     |  |         " <<endl;
    cout<<"             \\___/\\__/ \\_____/|__|   \\_____|____ |  |__    " <<endl;
	cout<<"                  /  __|/ _ \\ / _  `|/  __\\/  __\\|     |    " <<endl;
    cout<<"                  \\__  \\  __/| (_|  |  |  |  (__ |  |  |     " <<endl;
    cout<<"           _____  \\____/\\___|\\____,_|__|   \\____/|__|__|	  " <<endl;
    cout<<"          /  _  \\      ________________   __                  " <<endl;
    cout<<"         |  (_)  |    /____   /____   /  |  |                  " <<endl;
    cout<<"         |   ___/__ __    /  /    /  /   |  |    _____         " <<endl;
    cout<<"         |  |   |  |  |  /  /    /  /    |  |   /  _  \\       " <<endl;
    cout<<"         |  |   |  |  | /  /____/  /_____|  |___   ___/        " <<endl;
    cout<<"         |__|   \\_____//_______/________/|______|\\____|      " <<endl;
    cout<<"                                                               " <<endl;
    cout<<"                                                               " <<endl;
    cout<<"                  oleh : Ghazian Tsabit Alkamil                " <<endl;
    cout<<"                                                               " <<endl;
    cout<<"                                                               " <<endl;
    cout<<endl;
    
    string filepath;
    string finalpath;
    cout<<"input path file: ";
    cin>>filepath;
    finalpath = "../test/"+filepath;
    
    if (std::filesystem::exists(finalpath)){
        bacaPuzzle(finalpath);

        cout<<endl;
        cout<<"===============PUZZLE==============="<<endl;
        cout<<endl;
        printPuzzles();
    
        
        cout<<endl;
        cout<<"==============WORD LIST=============" <<endl;
    
        bacaDaftarKata(finalpath);
        cout<<endl;
        printDaftarKata();
        cout<<endl;
        cout<<"================RESULT==============" <<endl;
        cout<<endl;
        cout<<"Loading..."<<endl;
        cout<<endl;
        
        cariKata(puzzle, wordlist);
        
        
    }else{
        cout<<"File tidak ditemukan, pastikan nama file sudah tepat !"<<endl;
    }

    //system("pause");
    char ch;
    while (cin.readsome(&ch, 1) != 0)
        ;
    cout << "Press any key to continue..."<<endl;
    getchar();
    getchar();
    return 0; 
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
            vector <char> row1;
            for (int i=0; i < line.size(); i+=2){
                row.push_back(line[i]);
                row1.push_back('-');
            }
            answers.push_back(row1);
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

void printHasil(){

    for(int i = 0; i < N; i++){
        vector <char> row1 = answers[i];
        for(int j = 0; j < M; j++){
            cout<< row1[j]<<" ";
        }
        cout<<endl;
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

// BRUTE FORCE ALGORITHM

int x[] = { -1, -1, -1, 0, 0,  1, 1, 1 }; 
int y[] = { -1,  0,  1,-1, 1, -1, 0, 1 };


bool search2D(vector<vector<char>> pzl, int row, int col, string word, int z){

    temp = answers;

    if(pzl[row][col] != word[0]){
        answers = temp;
        totCompare++;
        return false;
    }
    int len;
    if(z != wordlist.size()-1){
        len = word.length()-1;
    }else{
        len = word.length();
    }
    
    
    for (int dir = 0; dir < 8; dir++){
        int k, rd = row + x[dir], cd = col + y[dir];
        for(k = 1; k < len; k++){
            if (rd >= N || rd < 0 || cd >= M || cd < 0){
                answers = temp;
                totCompare++;
                break;
            }
            if (pzl[rd][cd] != word[k]){
                answers = temp;
                totCompare++;
                break;
            }
            answers[row][col] = pzl[row][col];
            answers[rd][cd] = pzl[rd][cd];
            rd += x[dir], cd += y[dir];
            totCompare++; 
        }
        totCompare++;
        if(k == len){
            k = 1;
            dir = 0;
            return true;
        }
    }
    return false;
}

void cariKata(vector<vector<char>> pzl, vector<string> wordlist){
    
    bool status = false;
    
    for(int i = 0; i < wordlist.size(); i++){
        auto start = high_resolution_clock::now();
        for (int row = 0; row < N; row++){
            for (int col = 0; col < M; col++){
                if (search2D(puzzle, row, col, wordlist[i], i)){
                    status = true;
                    cout<<wordlist[i]<<endl;
                    cout<<endl;
                    printHasil();
                    cout<<endl;
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "Waktu eksekusi: "<< duration.count()/1000 << " milisekon" << endl;
                    cout << "Total perbandingan huruf: "<< totCompare <<endl;
                    totCompare = 0;
                    cout<<endl;
                    answers = temp;
                }
            }              
        } 
    }
}