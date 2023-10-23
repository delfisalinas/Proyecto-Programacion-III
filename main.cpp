#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include "time.h"
#include "lista.h"
#include "cola.h"
#include "pila.h"
#include "string.h"
#include "arbolbinario.h"
#include "hashMapp.h"
#include "hashEntryy.h"
using namespace std;



/*void total_art_dif(string fileName){
    fstream fin;
    fin.open("./"+fileName,ios::in);

    string line;
    int total_art_dif=-1;

    while(getline(fin,line)){
        total_art_dif++;
    }

    cout<<"Total de articulos diferentes: "<<total_art_dif<<endl;
}

void total_art(string fileName){

}
void min_stock (string fileName, int n) {
    fstream fin;
    fin.open("./" + fileName, ios::in);

    string line, word;
    ArbolBinario<Articulo> arbol;
    int cantidad = 0;
    while (getline(fin, line)) {
        stringstream s(line);
        string nombre_articulo;
        int col = 0;
        while (getline(s, word, ',')) {
            int cantidad = 0;
            if (word.size() > 2) {
                word = word.substr(1, word.size() - 2);
            } else {
                word = "0";
            }
            if (col == 1) { // La primera columna es el nombre del artículo
                nombre_articulo = word;
            } else if (col >= 3) {
                cantidad += stoi(word);
            }

            arbolbinario.put(cantidad);
        }
    }
}


void exploreCSV(string fileName){
    fstream fin;
    fin.open("./"+fileName,ios::in);

    HashMap<string, int> hashTable(10000); // Asumiendo un tamaño máximo de 10,000 artículos diferentes
    string line,word;
    int total_art = 0;

    while(getline(fin,line)){
        stringstream s(line);
        string nombre_articulo;
        int cantidad = 0;
        int col = 0;
        while(getline(s,word,',')){
            if(word.size()>0){
                word=word.substr(1,word.size()-2);
            }else{
                word="0";
            }
            if(col == 0) { // La primera columna es el nombre del artículo
                nombre_articulo = word;
            } else if(col == 5) { // La sexta columna es la cantidad
                cantidad = stoi(word);
                total_art += cantidad;
            }
            col++;
        }
        try {
            int current_count = hashTable.get(nombre_articulo);
            hashTable.put(nombre_articulo, current_count + cantidad);
        } catch(int e) {
            if(e == 404) { // Si el artículo no está en la tabla hash
                hashTable.put(nombre_articulo, cantidad);
            }
        }
    }

    cout << "Total de articulos diferentes: " << hashTable.size() << endl; // Asumiendo que hay una función size() en la tabla hash
    cout << "Total de articulos: " << total_art << endl;
}


/*
void exploreHeaders(string fileName){
    fstream fin;
    fin.open("./"+fileName,ios::in);

    string headers,header;
    getline(fin,headers);

    stringstream s(headers);
    while(getline(s,header,',')){
        cout<<header<<endl;
    }
}
 */



struct Articulo {
    std::string grupo;
    std::string codigoBarras;
    std::string nombreArticulo;
    std::map<std::string, int> depositos; // Mapa de depósito a cantidad
};
int convertirAEntero(const std::string& str) {
    // Eliminar comillas dobles de la cadena
    std::string cadenaSinComillas = str;
    if (cadenaSinComillas.front() == '"' && cadenaSinComillas.back() == '"') {
        cadenaSinComillas = cadenaSinComillas.substr(1, cadenaSinComillas.length() - 2);
    }

    // Si la cadena está vacía después de eliminar las comillas, devolver 0
    if (cadenaSinComillas.empty()) {
        return 0;
    }

    try {
        return std::stoi(cadenaSinComillas);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error al convertir '" << cadenaSinComillas << "' a entero: " << e.what() << std::endl;
        return 0;  // o cualquier valor predeterminado que desees
    } catch (const std::out_of_range& e) {
        std::cerr << "Número fuera de rango al convertir '" << cadenaSinComillas << "' a entero: " << e.what() << std::endl;
        return 0;  // o cualquier valor predeterminado que desees
    }
}

void leerCSV(const std::string& archivo) {
    std::ifstream file(archivo);
    std::string linea;

    // Ignoramos la primera línea (encabezados)
    std::getline(file, linea);

    std::vector<Articulo> articulos;

    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string item;

        Articulo articulo;

        std::getline(ss, articulo.grupo, ',');
        std::getline(ss, articulo.codigoBarras, ',');
        std::getline(ss, articulo.nombreArticulo, ',');

        int depositoNum = 1;
        while (std::getline(ss, item, ',')) {
            if(item.size()>0){
                item=item.substr(1,item.size()-2);
            }else{
                item="0";
            }
            articulo.depositos["deposito " + std::to_string(depositoNum)] = convertirAEntero(item);
            depositoNum++;
        }

        articulos.push_back(articulo);
    }

    // Imprimir el stock individual de cada artículo según depósito
    for (const Articulo& art : articulos) {
        std::cout << "Artículo: " << art.nombreArticulo << "\n";
        for (const auto& deposito : art.depositos) {
            std::cout << deposito.first << ": " << deposito.second << "\n";
        }
        std::cout << "----------------------\n";
    }
}


int main(int argc, char **argv) {
    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();


    cout<<"Cantidad de argumentos: "<<argc<<endl;
    for(int i=0;i<argc;i++){
        cout<<"Argumento "<<i<<": "<<argv[i]<<endl;

        if(strcmp(argv[i],"-file") == 0){
            cout<<"Nombre del Archivo: "<< argv[i+1]<<endl;
            //exploreHeaders(argv[i+1]);
            //exploreCSV(argv[i+1]);
            cout<<endl;
            //total_art_dif(argv[i+1]);
            cout<<endl;
            //total_art(argv[i+1]);
            leerCSV(argv[i+1]);
            break;
        }
    }


    cout<<endl;
    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;

    return 0;
}





















/*
int main(int argc, char* argv[]) {

    // Verificar si se proporcionó el nombre del archivo como argumento
    if (argc < 2) {
        cerr << "Por favor, proporciona el nombre del archivo CSV como argumento." << endl;
        return 1;
    }

    // Abrir el archivo CSV para lectura
    ifstream fin(argv[1]);
    if (!fin.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    string line;
    vector<string> headers;
    // Leer la primera línea del archivo (generalmente contiene los nombres de las columnas)
    getline(fin, line);
    stringstream s(line);
    string word;

    // Separar los valores de la línea por comas
    while (getline(s, word, ',')) {
        // Limpiar las comillas y espacios adicionales
        if (word.size() > 2) {
            word = word.substr(1, word.size() - 2);
        }
        headers.push_back(word);
    }

    // Imprimir los nombres de las columnas
    cout << "Columnas del CSV:" << endl;
    for (const string& header : headers) {
        cout << header << endl;
    }

    // Aquí puedes continuar procesando el resto del archivo si es necesario

    // Cerrar el archivo
    fin.close();
    return 0;
}
*/