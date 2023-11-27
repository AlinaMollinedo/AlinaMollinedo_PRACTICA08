// Materia: Programación I, Paralelo 4

// Autor: Alina Mollinedo Dávila

// Fecha creación: 27/11/2023

// Fecha modificación: 27/11/2023

// Número de ejericio: 9

// Problema planteado: Dado una tabla grabada en un fichero en formato binario <nombre>.BIN hallar la suma
// horizontal y vertical y grabar la tabla y los resultados en otro fichero de texto o binario según se
// introduzca por pantalla. 

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* fileTxt = "Ej9.txt";
const char* fileBin = "Ej8.BIN";
const char* fileBin1 = "Ej9.BIN";

struct Num{
    double num, row, col;
};

int numCounter();
void fillStruct(Num*);
void calSums(Num*, Num*, int);
void writeText(Num*, int);
void writeBin(Num);
void readText();
void readBin(int, int);

int main(){
    int n = numCounter() - 1, N = n * 2;
    Num numsTemp[n];
    fillStruct(numsTemp);
    Num nums[N];
    calSums(numsTemp, nums, n);
    
    int op;
    cout << "\nDesea escribir la tabla en un archivo de texto o binario?" << endl;
    do{
        cout << "[1] Archivo de texto\t[2] Archivo binario" << endl;
        cin >> op;
    }
    while(op != 1 && op != 2); 

    switch (op){
    case 1:
        writeText(nums, N);
        cout << "\n---> Archivo de texto generado a partir de " << fileBin << "." << endl;
        readText();
        break;
    case 2:
        // Elimina la informacion existente en el archivo binario
        ofstream wf;
        wf.open(fileBin1, ios::binary);
        wf.close();

        int r = nums[N - 1].row, c = nums[N - 1].col; // Saca el numero de filas y columnas de la tabla
        for(int i = 0; i < N; i++){
            writeBin(nums[i]);
        }
        cout << "\n---> Archivo binario generado a partir de " << fileBin << "." << endl;
        readBin(r, c);
        break;
    }

    return 0;
}

// Cuenta los numeros en el archivo binario
int numCounter(){
    Num num;
    int c = 0;
    ifstream rf;
    rf.open(fileBin, ios::binary);
    while(rf.read((char*)&num, sizeof(Num))){
        c++;
    }
    rf.close();
    return c;
}

// Almacena los numeros del archivo binario en un vector
void fillStruct(Num* nums){
    Num num;
    int pos = 0;
    ifstream rf;
    rf.open(fileBin, ios::binary);
    while(rf.read((char*)&num, sizeof(Num))){
        nums[pos].num = num.num;
        nums[pos].row = num.row;
        nums[pos].col = num.col;
        pos++;
    }
    rf.close();
}

// Calcula las sumas necesarias y guarda todos los numeros ordenados en un vector
void calSums(Num* numsTemp, Num* nums, int n){
    int r = numsTemp[n - 1].row + 1;
    int c = numsTemp[n - 1].col + 1;
    int pos = 0, pos1 = 0;

    // Ordena las posiciones de los numeros en el vector
    for(int i = 0; i <= r; i++){
        for(int j = 0; j <= c; j++){
            if(i == r){
                nums[pos].num = 100;
                nums[pos].row = r;
                nums[pos].col = j;
            }
            else{
                if(j == c){
                    nums[pos].num = 100;
                    nums[pos].row = i;
                    nums[pos].col = c;
                }
                else{
                    nums[pos].num = numsTemp[pos1].num;
                    nums[pos].row = numsTemp[pos1].row;
                    nums[pos].col = numsTemp[pos1].col;
                    pos1++;
                }
            }
            pos++;
        }
    }

    // Realiza las sumas necesarias
    for(int i = 0; i < 2 * n; i++){
        if(nums[i].num == 100.0){
            if(nums[i].col == c){
                if(nums[i].row != r){
                    double temp = 0;
                    for(int j = i - 1; j >= i - c; j--){
                        temp += nums[j].num;
                    }
                    nums[i].num = temp;
                }
            }
            else{
                if(nums[i].row == r){
                    double temp = 0;
                    for(int j = i - c - 1; j >= 0; j = j - c - 1){
                        temp += nums[j].num;
                    }
                    nums[i].num = temp;
                }
            }
        }
    }

    // Calcula la suma total
    double temp = 0;
    for(int i = (2 * n) - 2; i >= (2 * n) - 2 - r; i--){
        temp += nums[i].num;
    }
    nums[2 * n - 1].num = temp;
}

// Escribe la tabla en un archivo de texto
void writeText(Num* nums, int N){
    int r = nums[N - 1].row;
    int c = nums[N - 1].col;
    int pos = 0;

    ofstream wf;
    wf.open(fileTxt);
    for(int i = 0; i <= r; i++){
        for(int j = 0; j <= c; j++){
            wf << nums[pos].num << "\t";
            pos++;
        }
        wf << endl;
    }
    wf.close();
}

// Escribe la tabla en un archivo binario
void writeBin(Num num){
    ofstream wf;
    wf.open(fileBin1, ios::binary | ios::app);
    wf.write((char*)&num, sizeof(Num));
    wf.close();
}

// Imprime en consola el archivo de texto
void readText(){
    cout << "\nLEYENDO ARCHIVO" << endl;
    cout << "================" << endl;

    ifstream rf;
    rf.open(fileTxt);
    while(!rf.eof()){
        string line;
        getline(rf, line);
        cout << line << endl;
    }
    rf.close();
}

// Imprime en consola el archivo binario
void readBin(int r, int c){
    cout << "\nLEYENDO ARCHIVO" << endl;
    cout << "================" << endl;

    Num num;
    ifstream rf;
    rf.open(fileBin1, ios::binary);

    for(int i = 0; i <= r; i++){
        for(int j = 0; j <= c; j++){
            rf.read((char*)&num, sizeof(Num));
            cout << num.num << "\t";
        }
        cout << endl;
    }
    rf.close();
}
