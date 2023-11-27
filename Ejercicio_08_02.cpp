// Materia: Programación I, Paralelo 4

// Autor: Alina Mollinedo Dávila

// Fecha creación: 25/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 2

// Problema planteado: Escriba un programa que cree un fichero de texto llamado "PERSONAS.BIN" en el que se
// guarde la información de un número indeterminado de personas.
// La información que se guardará por cada persona será:
// • Nombre: De 1 a 30 caracteres.
// • Edad numérico (>= 1 y <=100)
// • Sexo CHAR (M/F).
// • FechaNacimiento CHAR(10) (formato dd/mm/yyyy)
// La información correspondiente a cada persona se leerá del teclado.
// El proceso finalizará cuando se teclee un campo "Nombre" que esté solamente con el carácter
// de espacio.

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* file = "PERSONAS.BIN";

void addFile(char[30]);

int main(){
    char name[30], n[30] = " ";
    // Agrega personas hasta que se introduzca un espacio
    do{
        cout << "\nNombre: ";
        cin.getline(name, 31);
        if(strcmp(name, n) == 0){
            break;
        }
        addFile(name);
    }
    while(name != n);
    return 0;
}

// Agrega una persona al archivo
void addFile(char name[30]){
    ofstream wf;
    wf.open(file, ios::app);
    char gender, birthday[10];
    int age;

    wf << name << ";";
    cout << "Edad: ";
    cin >> age;
    wf << age << ";";
    cin.ignore(256, '\n');
    cout << "Sexo: ";
    cin >> gender;
    wf << gender << ";";
    cin.ignore(256, '\n');
    cout << "Fecha de nacimiento (dd/mm/yyyy): ";
    cin.getline(birthday, 11);
    wf << birthday << ";" << endl;

    wf.close();
}