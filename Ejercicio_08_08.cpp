// Materia: Programación I, Paralelo 4

// Autor: Alina Mollinedo Dávila

// Fecha creación: 26/11/2023

// Fecha modificación: 27/11/2023

// Número de ejericio: 8

// Problema planteado: Escribir un programa que genere a partir de un fichero de entrada que contiene una tabla de
// números reales otro fichero de salida <nombre>.BIN grabado en formato binario.

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* fileTxt = "Ej8.txt";
const char* fileBin = "Ej8.BIN";

struct Num{
    double num = 0, row = 0, col = 0;
};

int numCounter();
void fillNums(Num*);
void generateBinary(Num);
void readBin(int, int);

int main(){
    int n = numCounter() - 1; // Cuenta los numeros en el archivo de texto
    Num nums[n];
    fillNums(nums); // Almacena los numeros en el archivo de texto

    // Elimina la informacion existente dentro del archivo binario
    ofstream wf;
    wf.open(fileBin, ios::binary);
    wf.close();

    // Escribe los numeros en el archivo binario
    for(int i = 0; i < n; i++){
        generateBinary(nums[i]);
    }

    cout << "\n---> Archivo binario generado a partir de " << fileTxt << "." << endl;

    int r = nums[n - 1].row, c = nums[n - 1].col; // Saca el numero de filas y columnas de la tabla
    readBin(r, c); // Imprime la tabla

    return 0;
}

// Cuenta los numeros en el archivo de texto
int numCounter(){
    int c = 0;
    ifstream rf;
    rf.open(fileTxt);
    while(!rf.eof()){
        string line;
        getline(rf, line);
        int length = line.length();

        for(int i = 0; i < length; i++){
            if(line[i] == ' '){
                if(line[i + 1] != ' ' && i + 1 != length){
                    c++;
                }
            }
        }
        c++;

    }
    rf.close();
    return c;
}

// Almacena los numeros del archivo de texto en un vector
void fillNums(Num* nums){
    int pos = 0, row = 0, col = 0;
    ifstream rf;
    rf.open(fileTxt);
    while(!rf.eof()){
        string line;
        getline(rf, line);
        int length = line.length(), ii = 0;

        for(int i = 0; i < length; i++){
            string temp = "";
            if(line[i] == ' '){
                for(int j = ii; j < i; j++){
                    temp += line[j];
                }
                nums[pos].num = stod(temp);
                nums[pos].row = row;
                nums[pos].col = col;
                ii = i + 1;
                pos++;
                col++;
            }
            else if(i + 1 == length){
                for(int j = ii; j <= i; j++){
                    temp += line[j];
                }
                nums[pos].num = stod(temp);
                nums[pos].row = row;
                nums[pos].col = col;
                ii = i + 1;
                pos++;
                col = 0;
            }
        }
        row++;
    }
    rf.close();
}

// Escribe los numeros en el archivo binario
void generateBinary(Num num){
    ofstream wf;
    wf.open(fileBin, ios::binary | ios::app);
    wf.write((char*)&num, sizeof(Num));
    wf.close();
}

// Imprime en la consola el contenido del archivo binario
void readBin(int r, int c){
    cout << "\nLEYENDO ARCHIVO" << endl;
    cout << "================" << endl;

    Num num;
    ifstream rf;
    rf.open(fileBin, ios::binary);

    for(int i = 0; i <= r; i++){
        for(int j = 0; j <= c; j++){
            rf.read((char*)&num, sizeof(Num));
            cout << num.num << "\t";
        }
        cout << endl;
    }
    rf.close();
}