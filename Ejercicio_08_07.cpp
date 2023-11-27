// Materia: Programación I, Paralelo 4

// Autor: Alina Mollinedo Dávila

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 7

// Problema planteado: Escriba un programa que tenga como entrada un fichero que contenga un texto y dé como
// resultado una estadística del número de palabras.

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int wordCounter(string);

int main(){
    string file;
    cout << "Ingrese el nombre del archivo: ";
    getline(cin, file);

    int words = wordCounter(file);
    cout << "\nEl archivo tiene " << words << " palabras." << endl;

    return 0;
}

// Cuenta las palabras en el archivo
int wordCounter(string file){
    int c = 0;
    ifstream rf;
    rf.open(file);
    while(!rf.eof()){
        string line;
        getline(rf, line);
        int length = line.length();

        for(int i = 0; i < length; i++){
            if(line[i] == ' '){
                if(line[i + 1] != ' ' && i + 1 != length){ // Verifica los dobles espacios y si es el final de linea
                    c++;
                }
            }
        }
        c++;

    }
    rf.close();
    return c;
}