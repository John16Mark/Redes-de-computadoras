#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream archivo("input.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    vector<string> palabras;
    string linea;
    while (getline(archivo, linea)) {
        istringstream stream(linea);
        string palabra;

        while (stream >> palabra) {
            palabras.push_back(palabra);
        }
    }

    archivo.close();
    for(int i=0; i<palabras.size(); i++) {
        if(i%16 == 0)
            cout << "\t\t";
        cout << "0x"<< palabras[i];
        if(i != palabras.size()-1)
            cout << ", ";
        if(i%16 == 15)
            cout << endl;
    }
    return 0;
}
