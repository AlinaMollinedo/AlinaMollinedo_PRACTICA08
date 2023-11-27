// Materia: Programación I, Paralelo 4

// Autor: Alina Mollinedo Dávila

// Fecha creación: 25/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 4

// Problema planteado: Codifique un programa que cree un fichero para contener los datos relativos a los artículos de
// un almacén.
// Para cada artículo habrá de guardar la siguiente información:
// • Código del artículo (Numérico)
// • Nombre del artículo (Cadena de caracteres)
// • Existencias actuales (Numérico)
// • Precio (Numérico decimal).
// Se deberán pedir datos de cada artículo por teclado hasta que como código se teclee el código
// 0.
// El fichero se habrá de crear ordenado por el código del artículo.

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* file = "Articulos.txt";
const char* fileTemp = "Temp.txt";

struct Product{
    int code, existences;
    char name[50];
    float price;
};

void addProduct(int);
int countLines();
void generateList(string*);
void shellSort(int*, int);
void rewrite(string*, int);

int main(){
    int code = 1;
    // Agrega productos hasta introducir un 0
    do{
        Product a;
        cout << "\nCodigo del articulo: ";
        cin >> a.code;
        if(a.code = 0){
            break;
        }
        else{
            addProduct(a.code);
        }
    }
    while(code != 0);

    int n = countLines() - 1;
    string c[n];
    generateList(c); //Genera una lista con todos los codigos en el archivo
    
    //Transforma la lista a valores enteros
    int codes[n];
    for(int i = 0; i < n; i++){
        codes[i] = stoi(c[i]);
    }
    
    shellSort(codes, n); //Ordena la lista
    
    // Transforma la lista a caracteres
    for(int i = 0; i < n; i++){
        c[i] = to_string(codes[i]);
    }

    // Reescribe el archivo
    rewrite(c, n);

    cout << "\n---> Archivo creado y ordenado exitosamente :)." << endl;

    return 0;
}

// Agrega productos al archivo
void addProduct(int code){
    Product a;
    cout << "Nombre del articulo: ";
    cin.ignore();
    cin.getline(a.name, 50);
    cout << "Existencias actuales: ";
    cin >> a.existences;
    cout << "Precio: ";
    cin >> a.price;

    ofstream wf;
    wf.open(file, ios::app);
    wf << code << ";" << a.name << ";" << a.existences << ";" << a.price << ";" << endl;
}

// Cuenta las lineas en el archivo
int countLines(){
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

// Genera una lista con los codigos en el archivo
void generateList(string* codes){
    ifstream rf;
    rf.open(file);
    int pos = 0;
    while(!rf.eof()){
        string line, temp = "";
        getline(rf, line);
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
    rf.close();
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

// Reescribe el archivo
void rewrite(string* codes, int n){
    ifstream rf;
    ofstream wf;
    wf.open(fileTemp);
    for(int i = 0; i < n; i++){
        rf.open(file);
        while(!rf.eof()){
            string line, temp = "";
            getline(rf, line);

            int pSemi = line.find(";", 0);
            for(int i = 0; i < pSemi; i++){
                temp += line[i];
            }

            if(codes[i] == temp){
                wf << line << endl;
            }
        }
        rf.close();
    }
    wf.close();
    remove(file);
    rename(fileTemp, file);
}