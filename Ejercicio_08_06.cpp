// Materia: Programación I, Paralelo 4

// Autor: Alina Mollinedo Dávila

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 6

// Problema planteado: Escriba un programa que tome como entrada el fichero del ejercicio 4 y una condición sobre el
// campo Precio. La condición podrá ser:
// Precio mayo o igual a 100 o cualquier otro dato ingresado por teclado.
// Este programa debe generar como salida un fichero llamado "salida.dat" que contenga todos
// aquellos artículos para los que se cumple la condición de entrada.
// Mostrar el archivo de salida “salida.dat”

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* file = "Articulos3.txt";
const char* fileOut = "salida.dat";

int countLines(const char*);
void generateList(string*);
void write(string*, float*, int, float);

int main(){
    float cond;
    cout << "Ingrese la condicion. Se filtraran articulos con un precio mayor o igual a: ";
    cin >> cond;

    int n = countLines(file) - 1;
    string prices[n];
    float p[n];
    generateList(prices);  //Genera una lista con todos los precios en el archivo

    //Transforma la lista a valores flotantes
    for(int i = 0; i < n; i++){
        p[i] = stof(prices[i]);
    }

    write(prices, p, n, cond); // Escribe las lineas que cumplan con la condicion del precio

    cout << "\n---> Archivo creado exitosamente :)." << endl;

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

// Genera una lista con los precios en el archivo
void generateList(string* prices){
    ifstream rf;
    rf.open(file);
    int pos = 0;
    while(!rf.eof()){
        string line, temp = "";
        getline(rf, line);
        if(line != ""){
            int pSemi1 = line.find(";", 0);
            int pSemi2 = line.find(";", pSemi1 + 1);
            int pSemi3 = line.find(";", pSemi2 + 1);
            int pSemi4 = line.find(";", pSemi3 + 1);

            for(int i = pSemi3 + 1; i < pSemi4; i++){
                temp += line[i];
            }
            prices[pos] = temp;
        }
        else{
            break;
        }
        pos++;
    }
    rf.close();
}

// Escribe las lineas que cumplan con la condicion del precio
void write(string* prices, float* p, int n, float cond){
    ifstream rf;
    ofstream wf;
    wf.open(fileOut);
    for(int i = 0; i < n; i++){
        if(p[i] >= cond){
            rf.open(file);
            while(!rf.eof()){
                string line, temp = "";
                getline(rf, line);
                int pSemi1 = line.find(";", 0);
                int pSemi2 = line.find(";", pSemi1 + 1);
                int pSemi3 = line.find(";", pSemi2 + 1);
                int pSemi4 = line.find(";", pSemi3 + 1);

                for(int i = pSemi3 + 1; i < pSemi4; i++){
                    temp += line[i];
                }
                
                if(prices[i] == temp){
                    wf << line << endl;
                }
            }
            rf.close();
        }
    }
    wf.close();
}