// Materia: Programación I, Paralelo 4

// Autor: Alina Mollinedo Dávila

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 5

// Problema planteado: Escriba un programa que dados dos ficheros generados por el programa anterior y ordenados
// genere un tercer fichero que sea el resultado de mezclar de formar ordenada los dos primeros.

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* file1 = "Articulos1.txt";
const char* file2 = "Articulos2.txt";
const char* file3 = "Articulos3.txt";

int countLines(const char*);
void generateList(string*);
void shellSort(int*, int);
void rewrite(string*, int);

int main(){
    int n = countLines(file1) + countLines(file2) - 2; // Numero de lineas total entre los dos archivos

    string c[n];
    int codes[n];

    generateList(c); // Genera una lista con los codigos de ambos archivos

    //Transforma la lista a valores enteros
    for(int i = 0; i < n; i++){
        codes[i] = stoi(c[i]);
    }

    shellSort(codes, n); //Ordena la lista
    cout << endl;
    // Transforma la lista a caracteres
    for(int i = 0; i < n; i++){
        c[i] = to_string(codes[i]);
    }

    // Escribe el tercer archivo
    rewrite(c, n);

    cout << "\n---> Archivo creado y ordenado exitosamente :)." << endl;

    return 0;
}

// Cuenta las lineas en el archivo
int countLines(const char* file){
    ifstream rf;
    rf.open(file);
    int c = 0;
    while(!rf.eof()){
        string str;
        getline(rf, str);
        c++;
    }
    rf.close();
    return c;
}

// Genera una lista con los codigos en los archivos
void generateList(string* codes){
    ifstream rf1, rf2;
    rf1.open(file1);
    rf2.open(file2);
    int pos = 0;
    while(!rf1.eof()){
        string line, temp = "";
        getline(rf1, line);
        if(line != ""){
            int pSemi = line.find(";", 0);
            for(int i = 0; i < pSemi; i++){
                temp += line[i];
            }
            codes[pos] = temp;
        }
        else{
            break;
        }
        pos++;
    }
    rf1.close();
    while(!rf2.eof()){
        string line, temp = "";
        getline(rf2, line);
        if(line != ""){
            int pSemi = line.find(";", 0);
            for(int i = 0; i < pSemi; i++){
                temp += line[i];
            }
            codes[pos] = temp;
        }
        else{
            break;
        }
        pos++;
    }
    rf2.close();
}

// Ordena la lista mediante shell sort
void shellSort(int* codes, int n){
    int piv = n / 2;
    while(piv != 1){
        for(int i = 0; i < n; i++){
            if(i + piv < n){
                if(codes[i] > codes[i + piv]){
                    swap(codes[i], codes[i + piv]);
                }
            }
        }
        piv /= 2;
    }
    bool flag = true;
    while(flag){
        flag = false;
        for(int i = 0; i < n - 1; i++){
            if(codes[i] > codes[i + piv]){
                swap(codes[i], codes[i + piv]);
                flag = true;
            }
        }
    }
}

// Escribe el tercer archivo
void rewrite(string* codes, int n){
    ifstream rf1, rf2;
    ofstream wf;
    wf.open(file3);
    for(int i = 0; i < n; i++){
        rf1.open(file1);
        while(!rf1.eof()){
            string line, temp = "";
            getline(rf1, line);

            int pSemi = line.find(";", 0);
            for(int i = 0; i < pSemi; i++){
                temp += line[i];
            }

            if(codes[i] == temp){
                wf << line << endl;
            }
        }
        rf1.close();

        rf2.open(file2);
        while(!rf2.eof()){
            string line, temp = "";
            getline(rf2, line);

            int pSemi = line.find(";", 0);
            for(int i = 0; i < pSemi; i++){
                temp += line[i];
            }

            if(codes[i] == temp){
                wf << line << endl;
            }
        }
        rf2.close();
    }
    wf.close();
}