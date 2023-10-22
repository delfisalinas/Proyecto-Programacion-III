//
// Created by delfi on 22/10/2023.
//

#ifndef PROYECTO_PROGRAMACION_III_ARBOLBINARIO_H
#define PROYECTO_PROGRAMACION_III_ARBOLBINARIO_H
#include "NodoArbol.h"
#include <iostream>
using namespace std;

template <class T>
class ArbolBinario
{
protected:
    NodoArbol<T> *root;


public:
    ArbolBinario();

    void put(T data);

    T search(T data);

    void remove(T data);

    void preorder();

    void inorder();

    void postorder();

    ~ArbolBinario();

    bool esVacio();

    void print();

    void reconstruirArbolPreIn(T preorden[], T inorden[], int size);

    void reconstruirArbolInPost(T inorden[], T postorden[], int size);

    int contarPorNivel(int nivel);

    int contarPorNivel(NodoArbol<T> *r, int nivel, int nivelActual);

    void espejo();

private:
    T search(T data, NodoArbol<T> *r);
    NodoArbol<T> *put(T data, NodoArbol<T> *r);
    NodoArbol<T> *remove(T data, NodoArbol<T> *r);
    NodoArbol<int> * findMaxAndRemove(NodoArbol<T> *r, bool *found);
    void preorder(NodoArbol<T> *r);
    void inorder(NodoArbol<T> *r);
    void postorder(NodoArbol<T> *r);
    void espejo(NodoArbol<T> *r);
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el Ã¡rbol
 * @tparam T Valor guardado por el Ã¡rbol
 */
template <class T>
ArbolBinario<T>::ArbolBinario() { root = nullptr; }

/**
 * Destructor del Arbol
 */
template <class T>
ArbolBinario<T>::~ArbolBinario() {}

/**
 * Busca un dato en el Ã¡rbol. Si no esta el dato en el Ã¡rbol
 * tira una excepciÃ³n
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T>
T ArbolBinario<T>::search(T data)
{
    return search(data, root);
}

template <class T>
T ArbolBinario<T>::search(T data, NodoArbol<T> *r)
{
    if (r == nullptr)
    {
        throw 404;
    }

    if (r->getData() == data)
    {
        return r->getData();
    }

    if (r->getData() > data)
    {
        return search(data, r->getLeft());
    }
    else
    {
        return search(data, r->getRight());
    }
}

/**
 * Agrega un dato al Ã¡rbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template <class T>
void ArbolBinario<T>::put(T data) { root = put(data, root); }

template <class T>
NodoArbol<T> *ArbolBinario<T>::put(T data, NodoArbol<T> *r)
{
    if (r == nullptr)
    {
        return new NodoArbol<T>(data);
    }

    /* Si el dato ya existe, simplemente retornamos r sin hacer cambios.
    if (r->getData() == data)
    {
        return r;
    }
    */
    if (r->getData() >= data)
    {
        r->setLeft(put(data, r->getLeft()));
    }
    else{
        r->setRight(put(data, r->getRight()));
    }

    return r;
}

/**
 * Elimina un dato del Ã¡rbol
 * @param clave Clave para identificar el nodo a borrar
 */
template <class T>
void ArbolBinario<T>::remove(T data)
{
    root = remove(data, root);
}

template <class T>
NodoArbol<T> *ArbolBinario<T>::remove(T data, NodoArbol<T> *r)
{
    NodoArbol<T> *aux;

    if (r == nullptr)
    {
        throw 404;
    }

    if (r->getData() == data)
    {

        if (r->getLeft() == nullptr && r->getRight() == nullptr)
        {
            delete r;
            return nullptr;
        }
        else if (r->getLeft() != nullptr && r->getRight() == nullptr)
        {
            aux = r->getLeft();
            delete r;
            return aux;
        }
        else if (r->getLeft() == nullptr && r->getRight() != nullptr)
        {
            aux = r->getRight();
            delete r;
            return aux;
        }
        else if (r->getLeft() != nullptr && r->getRight() != nullptr)
        {

            if (r->getLeft()->getRight() != nullptr)
            {
                // Aca tenemos que buscar el valor maximo
                bool found;
                aux = findMaxAndRemove(r->getLeft(), &found);
                aux->setRight(r->getRight());
                aux->setLeft(r->getLeft());
            }
            else
            {
                aux = r->getLeft();
                r->getLeft()->setRight(r->getRight());
            }
            delete r;
            return aux;
        }
    }
    else if (r->getData() > data)
    {
        r->setLeft(remove(data, r->getLeft()));
    }
    else
    {
        r->setRight(remove(data, r->getRight()));
    }

    return r;
}

template <class T>
NodoArbol<int> * ArbolBinario<T>::findMaxAndRemove(NodoArbol<T> *r, bool *found)
{
    NodoArbol<T> ret;
    *found = false;

    if (r->getRight() == nullptr)
    {
        *found = true;
        return r;
    }

    ret = findMaxAndRemove(r->getRight(), found);
    if (*found)
    {
        r->setRight(nullptr);
        *found = false;
    }

    return ret;
}

/**
 * Informa si un Ã¡rbol esta vacÃ­o
 * @return
 */
template <class T>
bool ArbolBinario<T>::esVacio() { return root == nullptr; }

/**
 * Recorre un Ã¡rbol en preorden
 */
template <class T>
void ArbolBinario<T>::preorder()
{
    preorder(root);
    std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::preorder(NodoArbol<T> *r)
{
    if (r == nullptr)
    {
        return;
    }

    std::cout << r->getData() << " ";
    preorder(r->getLeft());
    preorder(r->getRight());
}

/**
 * Recorre un Ã¡rbol en orden
 */
template <class T>
void ArbolBinario<T>::inorder()
{
    inorder(root);
    std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::inorder(NodoArbol<T> *r)
{
    if (r == nullptr)
    {
        return;
    }

    inorder(r->getLeft());
    std::cout << r->getData() << " ";
    inorder(r->getRight());
}

/**
 * Recorre un Ã¡rbol en postorden
 */
template <class T>
void ArbolBinario<T>::postorder()
{
    postorder(root);
    std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::postorder(NodoArbol<T> *r)
{
    if (r == nullptr)
    {
        return;
    }

    postorder(r->getLeft());
    postorder(r->getRight());
    std::cout << r->getData() << " ";
}

/**
 * Muestra un Ã¡rbol por consola
 */
template <class T>
void ArbolBinario<T>::print()
{
    if (root != NULL)
        root->print(false, "");
}
/**
 * Reconstruye un Ã¡rbol binario a partir de los recorridos en preorden e inorden.
 * @param preorden Arreglo con el recorrido en preorden.
 * @param inorden Arreglo con el recorrido en inorden.
 * @param preIndex Ãndice para rastrear la posiciÃ³n actual en el recorrido en preorden.
 * @param inStart Inicio del rango en el recorrido en inorden.
 * @param inEnd Fin del rango en el recorrido en inorden.
 * @return Puntero al nodo raÃ­z del Ã¡rbol reconstruido.
 */
template <class T>
NodoArbol<T> *reconstruirPreIn(T preorden[], T inorden[], int &preIndex, int inStart, int inEnd)
{
    // Si el rango de inorden estÃ¡ vacÃ­o, retorna nullptr
    if (inStart > inEnd)
        return nullptr;

    // Crea un nuevo nodo con el prÃ³ximo elemento del preorden
    NodoArbol<T> *nuevoNodo = new NodoArbol<T>(preorden[preIndex++]);

    // Si solo hay un elemento en el rango, retorna el nodo
    if (inStart == inEnd)
        return nuevoNodo;

    // Busca la posiciÃ³n del nodo en el inorden
    int inIndex = 0;
    for (int i = inStart; i <= inEnd; i++)
    {
        if (inorden[i] == nuevoNodo->getData())
        {
            inIndex = i;
            break;
        }
    }

    // Construye el subÃ¡rbol izquierdo y derecho recursivamente
    nuevoNodo->setLeft(reconstruirPreIn(preorden, inorden, preIndex, inStart, inIndex - 1));
    nuevoNodo->setRight(reconstruirPreIn(preorden, inorden, preIndex, inIndex + 1, inEnd));

    // Retorna el nuevo nodo construido
    return nuevoNodo;
}

/**
 * Inicia la reconstrucciÃ³n del Ã¡rbol binario a partir de los recorridos en preorden e inorden.
 * @param preorden Arreglo con el recorrido en preorden.
 * @param inorden Arreglo con el recorrido en inorden.
 * @param size TamaÃ±o de los arreglos.
 */
template <class T>
void ArbolBinario<T>::reconstruirArbolPreIn(T preorden[], T inorden[], int size)
{
    int preIndex = 0;
    // Inicia la reconstrucciÃ³n llamando a la funciÃ³n recursiva
    root = reconstruirPreIn(preorden, inorden, preIndex, 0, size - 1);
}
/**
 * Reconstruye un Ã¡rbol binario a partir de los recorridos en inorden y postorden.
 * @param inorden Arreglo con el recorrido en inorden.
 * @param postorden Arreglo con el recorrido en postorden.
 * @param postIndex Ãndice para rastrear la posiciÃ³n actual en el recorrido en postorden.
 * @param inStart Inicio del rango en el recorrido en inorden.
 * @param inEnd Fin del rango en el recorrido en inorden.
 * @return Puntero al nodo raÃ­z del Ã¡rbol reconstruido.
 */
template <class T>
NodoArbol<T> *reconstruirInPost(T inorden[], T postorden[], int &postIndex, int inStart, int inEnd)
{
    // Si el rango de inorden estÃ¡ vacÃ­o, retorna nullptr
    if (inStart > inEnd)
        return nullptr;

    // Crea un nuevo nodo con el prÃ³ximo elemento del postorden
    NodoArbol<T> *nuevoNodo = new NodoArbol<T>(postorden[postIndex--]);

    // Si solo hay un elemento en el rango, retorna el nodo
    if (inStart == inEnd)
        return nuevoNodo;

    // Busca la posiciÃ³n del nodo en el inorden
    int inIndex = 0;
    for (int i = inStart; i <= inEnd; i++)
    {
        if (inorden[i] == nuevoNodo->getData())
        {
            inIndex = i;
            break;
        }
    }

    // Construye el subÃ¡rbol derecho e izquierdo recursivamente
    nuevoNodo->setRight(reconstruirInPost(inorden, postorden, postIndex, inIndex + 1, inEnd));
    nuevoNodo->setLeft(reconstruirInPost(inorden, postorden, postIndex, inStart, inIndex - 1));

    // Retorna el nuevo nodo construido
    return nuevoNodo;
}

/**
 * Inicia la reconstrucciÃ³n del Ã¡rbol binario a partir de los recorridos en inorden y postorden.
 * @param inorden Arreglo con el recorrido en inorden.
 * @param postorden Arreglo con el recorrido en postorden.
 * @param size TamaÃ±o de los arreglos.
 */
template <class T>
void ArbolBinario<T>::reconstruirArbolInPost(T inorden[], T postorden[], int size)
{
    int postIndex = size - 1;
    // Inicia la reconstrucciÃ³n llamando a la funciÃ³n recursiva
    root = reconstruirInPost(inorden, postorden, postIndex, 0, size - 1);
}

/**
 * @brief Devuelve el nÃºmero de nodos en el nivel especificado del Ã¡rbol.
 * @param nivel El nivel para contar los nodos.
 * @return El nÃºmero de nodos en el nivel especificado.
 */
template <class T>
int ArbolBinario<T>::contarPorNivel(int nivel)
{
    return contarPorNivel(root, nivel, 1); // Comienza con nivel 1
}

template <class T>
int ArbolBinario<T>::contarPorNivel(NodoArbol<T> *r, int nivel, int nivelActual)
{
    if (r == nullptr)
    {
        return 0;
    }

    if (nivel == nivelActual)
    {
        return 1;
    }

    return contarPorNivel(r->getLeft(), nivel, nivelActual + 1) +
           contarPorNivel(r->getRight(), nivel, nivelActual + 1);
}

template <class T>
void ArbolBinario<T>::espejo()
{
    espejo(root);
}

template <class T>
void ArbolBinario<T>::espejo(NodoArbol<T> *r)
{
    if (r == nullptr)
    {
        return;
    }

    // Intercambiar los subÃ¡rboles izquierdo y derecho del nodo actual
    NodoArbol<T> *temp = r->getLeft();
    r->setLeft(r->getRight());
    r->setRight(temp);

    // Aplicar la operaciÃ³n espejo recursivamente a los subÃ¡rboles izquierdo y derecho
    espejo(r->getLeft());
    espejo(r->getRight());
}


#endif //PROYECTO_PROGRAMACION_III_ARBOLBINARIO_H
