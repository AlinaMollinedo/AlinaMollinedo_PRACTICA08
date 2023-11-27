// Materia: Programación I, Paralelo 4

// Autor: Alina Mollinedo Dávila

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 3

// Problema planteado: Amplíe el programa anterior que procesa clientes de una agencia matrimonial para que tome
// los datos de todos los candidatos a estudiar del fichero PERSONAS.DAT del ejercicio anterior,
// lea el cliente del teclado y finalmente genere como resultado un listado por pantalla con los
// nombres de los candidatos aceptados y un fichero llamado ACEPTADOS.DAT con toda la
// información correspondiente a los candidatos aceptados.
// Una persona del fichero PERSONAS.DAT se considerará aceptable como candidato si tiene
// diferente sexo y que haya nacido en el mes y año (El programa debe ser capaz de trabajar con
// cualquier número de personas en el fichero PERSONAS.DAT).

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* fileRead = "PERSONAS.DAT";
const char* fileWrite = "ACEPTADOS.DAT";

struct Person{
    char name[30], gender[1], birthday[11], month[2], year[2];
    int age;
};


int countLines();
void split(string, int, int, char[]);
void fillStructs(Person*);
int verifyClient(char[30], Person*, int);
void generateAccepted(char[30], Person*, int);


int main(){
    int n = countLines() - 1;
    Person p[n] = {};
    fillStructs(p);
    for(int i = 0; i < n; i++){
        cout << "nombre: " << p[i].name << endl;
        cout << "genero: " << p[i].gender << endl;
        cout << "cumple: " << p[i].birthday << endl;
        cout << "mes: " << p[i].month << endl;
        cout << "anhio: " << p[i].year << endl;
    }
    char name[30];
    cout << "Ingrese el nombre del cliente: ";
    cin.getline(name, 30);

    if(verifyClient(name, p, n) == -1){
        cout << "El cliente no ha sido registrado." << endl;
    }
    else{
        generateAccepted(name, p, n);
    }
    return 0;
}

int countLines(){
    ifstream rf;
    rf.open(fileRead);
    int c = 0;
    while(!rf.eof()){
        string str;
        getline(rf, str);
        c++;
    }
    rf.close();
    return c;
}

void split(string str, int pos1, int pos2, char c[]){
    int pos = 0;
    for(int i = pos1; i < pos2; i++){
        c[pos] = str[i];
        pos++;
    }
}

void fillStructs(Person* p){
    ifstream rf;
    rf.open(fileRead);
    int pos = 0;
    while(!rf.eof()){
        string str;
        getline(rf, str);
        if(str == ""){
            break;
        }
        else{
            int pos1 = str.find(";", 0);
            int pos2 = str.find(";", pos1 + 1);
            int pos3 = str.find(";", pos2 + 1);
            int posB = str.find(";", pos3 + 1);
            int posTemp = str.find("/", pos3 + 1);
            int pos4 = str.find("/", posTemp + 1);

            char a[3];
            split(str, 0, pos1, p[pos].name);
            split(str, pos1 + 1, pos2, a);
            //p[pos].age = stoi(a);
            split(str, pos2 + 1, pos3, p[pos].gender);
            split(str, pos3 + 1, posB, p[pos].birthday);
            split(str, posTemp + 1, pos4, p[pos].month);
            split(str, pos4 + 1, pos4 + 5, p[pos].year);
        }
        pos++;
    }
}

int verifyClient(char name[30], Person* p, int n){
    int pos = 0;
    for(int i  = 0; i < n; i++){
        if(strcmp(name, p[i].name) == 0){
            pos = i;
            return pos;
        }
    }
    return -1;
}

void generateAccepted(char name[30], Person* p, int n){
    int pos = verifyClient(name, p, n);

    ofstream wf;
    for(int i  = 0; i < n; i++){
        if(p[pos].gender != p[i].gender){
            cout << p[pos].gender << p[i].gender << endl;
            wf.open(fileWrite);
            wf << p[i].name << ";" << p[i].age << ";" << p[i].gender << ";" << p[i].birthday << ";" << endl;
            wf.close();
        }
    }
}