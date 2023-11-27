// Materia: Programación I, Paralelo 4

// Autor: Alina Mollinedo Dávila

// Fecha creación: 25/11/2023

// Fecha modificación: 25/11/2023

// Número de ejericio: 1

// Problema planteado: Escribir un programa con la opción de encriptar y de desencriptar un fichero de texto.
// La encriptación consiste en que dado un fichero de texto de entrada genere otro fichero de
// salida de extensión <nombre>.COD donde el texto estará codificado (encriptado).
// Esta codificación consiste en reemplazar cada carácter por el tercero siguiente según la tabla
// ASCII.
// La opción de desencriptado consiste en leer un fichero <nombre>.COD y recuperar la
// información original.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char* fileNormal = "Data.txt";
const char* fileEncrypted = "Data.COD";

void generateFile();
void encryptFile();
void decryptFile();
void readEncryption();

int main(){
    ifstream rf;
    rf.open(fileNormal);
    // Verifica si el archivo ya ha sido creado
    if(rf.good()){
        int op;
        cout << "Desea agregar informacion al archivo?" << endl;
        cout << "[1] SI\t[2] NO\t>> ";
        cin >> op;

        if(op == 1){
            generateFile();
        }
    }
    else{
        generateFile();
    }
    rf.close();

    int op;
    cout << "\nDesea encriptar el archivo o desencriptar el archivo?" << endl;
    cout << "\n[1] ENCRIPTAR\t[2] DESENCRIPTAR\t>> ";
    cin >> op;

    if(op == 1){
        encryptFile();
        readEncryption();
    }
    else{
        decryptFile();
    }
    return 0;
}

// Agrega informacion al archivo
void generateFile(){
    ofstream wf;
    string str;

    wf.open(fileNormal, ios::app);
    cout << "\nIngrese la informacion a guardar en el archivo: " << endl;
    cin.ignore();
    getline(cin, str);
    wf << str << endl;
    wf.close();
}

// Encripta la informacion del archivo
void encryptFile(){
    ofstream wf;
    ifstream rf;
    wf.open(fileEncrypted);
    rf.open(fileNormal);

    string str;
    while(!rf.eof()){
        getline(rf, str);
        int sizeofline = str.length();
        for(int i = 0; i < sizeofline; i++){
            int s = int(str[i]) + 3;
            wf << static_cast<char>(s);
        }
        wf << endl;
    }
    rf.close();
    wf.close();
}

// Desencripta la informacion del archivo
void decryptFile(){

    ifstream rf;
    rf.open(fileEncrypted);

    if(rf.good()){
        cout << "\n\nARCHIVO DESENCRIPTADO: " << endl;
        cout << "=======================\n" << endl;
        string str;
        while(!rf.eof()){
            getline(rf, str);
            int sizeofline = str.length();
            for(int i = 0; i < sizeofline; i++){
                int s = int(str[i]) - 3;
                cout << static_cast<char>(s);
            }
            cout << endl;
        }
        rf.close();
    }
    else{
        cout << "\nNo se ha encriptado nada todavia." << endl;
    }
    
}

// Lee el archivo encriptado
void readEncryption(){
    cout << "\n\nARCHIVO ENCRIPTADO: " << endl;
    cout << "==================\n" << endl;
    ifstream rf;
    rf.open(fileEncrypted);
    while(!rf.eof()){
        string str;
        getline(rf, str);
        cout << str << endl;
    }
}