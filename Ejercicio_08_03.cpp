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
    char name[30], age[3] = "", gender[2], birthday[11], month[3], year[5];
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
    char name[30];
    cout << "Ingrese el nombre del cliente: ";
    cin.getline(name, 30);

    // Verifica si el cliente ha sido registrado en el archivo de lectura
    if(verifyClient(name, p, n) == -1){
        cout << "El cliente no ha sido registrado." << endl;
    }
    else{
        ofstream wf;
        wf.open(fileWrite);
        wf.close();

        generateAccepted(name, p, n);
        cout << "\n---> El archivo " << fileWrite << " con la lista de aceptados ha sido generado." << endl;
    }
    return 0;
}

// Cuenta la cantidad de lineas en el archivo de lectura
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
 
// Copia caracter por caracter el rango de una cadena de caracteres en un char ingresado
void split(string str, int pos1, int pos2, char c[]){
    int pos = 0;
    for(int i = pos1; i < pos2; i++){
        c[pos] = str[i];
        pos++;
    }
}

// Llena un vector con la informacion de cada persona en el archivo de lectura
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

            split(str, 0, pos1, p[pos].name);
            split(str, pos1 + 1, pos2, p[pos].age);
            split(str, pos2 + 1, pos3, p[pos].gender);
            split(str, pos3 + 1, posB, p[pos].birthday);
            split(str, posTemp + 1, pos4, p[pos].month);
            split(str, pos4 + 1, posB, p[pos].year);
        }
        pos++;
    }
    rf.close();
}

// Verifica si el cliente esta en el archivo de lectura
// Si se encuentra en el archivo, devuelve su posicion en el vector de personas
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

// Genera el archivo de personas aceptadas
void generateAccepted(char name[30], Person* p, int n){
    cout << "\nPERSONAS ACEPTADAS" << endl;
    cout << "==================" << endl;
    int pos = verifyClient(name, p, n), c = 0;
    ofstream wf;
    for(int i  = 0; i < n; i++){
        if(strcmp(p[pos].gender, p[i].gender) != 0 && strcmp(p[pos].month, p[i].month) == 0 && strcmp(p[pos].year, p[i].year) == 0){
            cout << "\nPersona #" << c + 1 << endl;
            cout << "\tNombre: " << p[i].name << endl;
            cout << "\tEdad: " << p[i].age << endl;
            cout << "\tGenero: " << p[i].gender << endl;
            cout << "\tFecha de nacimiento: " << p[i].birthday << endl;
            wf.open(fileWrite, ios::app);
            wf << p[i].name << ";" << p[i].age << ";" << p[i].gender << ";" << p[i].birthday << ";" << endl;
            wf.close();
            c++;
        }
    }

    if(c == 0){
        cout << "\nNinguna persona cumple los requisitos para el cliente ingreasado." << endl;

        wf.open(fileWrite);
        wf << "Ninguna persona cumple los requisitos para el cliente ingreasado." << endl;
        wf.close();
    }
}