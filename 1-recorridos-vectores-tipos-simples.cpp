/******************************************************************************\
 * Curso de Programación 1. Tema 12 (Algoritmos con vectores)
 * Autores: Javier Martínez y Miguel Ángel Latre
 * Última revisión: 25 de noviembre de 2020
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la 
 *          sección «Recorridos de vectores de datos de tipos simples» de
 *          la clase de problemas del tema 12 (recorridos de vectores),
 *          planteados anteriormente en la colección de problemas del tema 9
 *          (vectores).
 * Nota: Este fichero contiene un programa completo que realiza pruebas de las
 *       funciones solicitadas. Este fichero puede compilarse y ejecutarse con
 *       la extensión Run Code de Visual Studio Code, tal y como se hacía en las
 *       prácticas 1 y 2. 
\******************************************************************************/
#include <iostream>
using namespace std;


/********************************** Problema 1 ********************************/
/*
 * Pre:  El vector «v» tiene «n» componentes.
 * Post: Ha devuelto true si y solo si los datos del vector «v» están ordenados
 *       de forma no decreciente.
 */
bool estaOrdenada(const int v[], const unsigned int n) {
    // ordenada==false cuando se tiene la CERTEZA de que no está
    // ordenada de forma no decreciente, es decir, cuando se han
    // encontrado un par de componentes consecutivas en el orden
    // incorrecto.
    bool ordenada = true;
    unsigned int i = 0;
    while (ordenada && i < n - 1) {
        ordenada = (v[i] <= v[i + 1]);
        i++;
    }
    return ordenada;
}


/********************************** Problema 2 ********************************/
/*
 * Pre:  Los vectores «v» y «p» tienen al menos «n» componentes cada uno. 
 *       El valor del parámetro «numPositivos» no está definido.   
 * Post: Tras ejecutar esta función, «numPositivos» es igual al número de datos
 *       positivos que hay en el vector «v» y las primeras «numPositivos» componentes
 *       del vector «p» almacenan los datos positivos de «v».
 */
void copiaPositivos(const int v[], const unsigned int n,
                    int p[], unsigned int& numPositivos) {
    numPositivos = 0;
    for (unsigned int i = 0; i < n; i++) {
        if (v[i] > 0) {
            p[numPositivos] = v[i];
            numPositivos++;
        }
    }
}


/********************************** Problema 3 ********************************/
/*
 * Pre:  El vector «v» tiene «n» componentes y se cumple que 0 ≤ i < n.
 * Post: Ha devuelto el número de veces que está repetido el dato
 *       «i»-ésimo del vector «v».
 */
unsigned int numeroRepeticiones(const int v[], const unsigned int i, 
                                const unsigned int n) {
    unsigned int repeticiones = 0;
    for (unsigned int j = 0; j < n; j++) {
        if (v[i] == v[j]) {
            repeticiones++;
        }
    }
    return repeticiones;
}


/*
 * Pre:  El vector «v» tiene «n» componentes.
 * Post: Ha devuelto la moda de los datos almacenados en el vector «v».
 */
int moda(const int v[], const unsigned int n) {
    int moda = v[0];
    unsigned int repeticionesDeLaModa = numeroRepeticiones(v, 0, n);

    for (unsigned int i = 1; i < n; i++) {
        unsigned int repeticionesDelDatoIesimo = numeroRepeticiones(v, i, n);
        if (repeticionesDelDatoIesimo > repeticionesDeLaModa) {
            moda = v[i];
            repeticionesDeLaModa = repeticionesDelDatoIesimo;
        }
    }
    return moda;
}


/************************** Código para las pruebas ***************************/
/*
 * Datos para las pruebas de «numPositivos», «copiar», «sonIguales» y
 * «copiaPositivos».
 */
const int VECTOR_0[] = {};
const int VECTOR_1[] = {5};
const int VECTOR_2[] = {-5};
const int VECTOR_3[] = {-1, 1};
const int VECTOR_4[] = {1, -1};
const int VECTOR_5[] = {1, -2, 3, -4, 5, -6};
const int VECTOR_6[] = {-1, 2, -3, 4, -5, 6};


/*
 * Prueba la función «estaOrdenada».
 * Si el resultado de una prueba es correcto, escribe en la pantalla true;
 * en caso contrario, escribe en la pantalla false.
 */
void pruebaEstaOrdenada() {
    const int ORDENADA[] = {1, 2, 3, 4, 5, 6};
    cout << endl;
    cout << "Pruebas de la función «estaOrdenada»: " << endl;    
    cout << boolalpha;

    cout <<  estaOrdenada(VECTOR_0, 0) << endl;
    cout <<  estaOrdenada(VECTOR_1, 1) << endl;
    cout <<  estaOrdenada(VECTOR_2, 1) << endl;
    cout <<  estaOrdenada(VECTOR_3, 2) << endl;
    cout << !estaOrdenada(VECTOR_4, 2) << endl;
    cout << !estaOrdenada(VECTOR_5, 6) << endl;
    cout << !estaOrdenada(VECTOR_6, 6) << endl;
    cout <<  estaOrdenada(ORDENADA, 6) << endl;
    
}


/*
 * Pre:  Los vectores «v» y «w» tienen al menos «n» componentes cada uno.
 * Post: Ha devuelto true si y solo si los datos de las primeras «n» componentes 
 *       de los vectores «v» y «w» son iguales.
 * Nota: Función para la función de prueba de la función «copiaPositivos».
 */
bool sonIguales(const int v[], const int w[], const unsigned int n) {
    bool deMomentoSonIguales = true;
    unsigned int i = 0;
    while (deMomentoSonIguales && i < n) {
        deMomentoSonIguales = (v[i] == w[i]);
        i++;
    }
    // !deMomentoSonIguales || i >= n
    return deMomentoSonIguales;
}


/*
 * Prueba la función «copiaPositivos».
 * Si el resultado de una prueba es correcto, escribe en la pantalla true;
 * en caso contrario, escribe en la pantalla false.
 * Utiliza la función «sonIguales», que es también objeto de otras pruebas.
 */
void pruebaCopiaPositivos() {
    const int RESULTADO_3_Y_4[] = {1};
    const int RESULTADO_5[] = {1, 3, 5};
    const int RESULTADO_6[] = {2, 4, 6};
    
    cout << endl;
    cout << "Pruebas de la función «copiaPositivos»: " << endl;
    cout << boolalpha;

    int positivos[6];
    unsigned int nPos;

    copiaPositivos(VECTOR_0, 0, positivos, nPos);
    cout << ((nPos == 0) && sonIguales(positivos, VECTOR_0, nPos)) << endl;

    copiaPositivos(VECTOR_1, 1, positivos, nPos);
    cout << ((nPos == 1) && sonIguales(positivos, VECTOR_1, nPos)) << endl;

    copiaPositivos(VECTOR_2, 1, positivos, nPos);
    cout << ((nPos == 0) && sonIguales(positivos, VECTOR_0, nPos)) << endl;

    copiaPositivos(VECTOR_3, 2, positivos, nPos);
    cout << ((nPos == 1) && sonIguales(positivos, RESULTADO_3_Y_4, nPos)) << endl;

    copiaPositivos(VECTOR_4, 2, positivos, nPos);
    cout << ((nPos == 1) && sonIguales(positivos, RESULTADO_3_Y_4, nPos)) << endl;

    copiaPositivos(VECTOR_5, 6, positivos, nPos);
    cout << ((nPos == 3) && sonIguales(positivos, RESULTADO_5, nPos)) << endl;

    copiaPositivos(VECTOR_6, 6, positivos, nPos);
    cout << ((nPos == 3) && sonIguales(positivos, RESULTADO_6, nPos)) << endl;
}


/*
 * Prueba la función «moda».
 * Si el resultado de una prueba es correcto, escribe en la pantalla true;
 * en caso contrario, escribe en la pantalla false.
 * Utiliza los vectores de ejemplo del enunciado.
 */
void pruebaModa() {
    cout << endl;
    cout << "Pruebas de la función «moda»: " << endl;    
    cout << boolalpha;

    const int T1[] = {4, 7, 5, 5, 1, 7, 6, 9, 2, 2, 5, 0, 7, 9, 5, 6, 5, 0, 8, 0, 2};
    cout << (moda(T1, 21) == 5) << endl;

    const int T2[] = {1, 5, 8, 6, 8, 3, 4, 6, 6, 1, 5, 8, 1, 9, 5, 9, 5, 8, 9, 2, 9};
    int m = moda(T2, 21);
    cout << (m == 5 || m == 8 || m == 9) << endl;
}


/*
 * Programa que realiza pruebas de las funciones «numPositivos», «copiar»,
 * «sonIguales», «moda», «esta», «estaOrdenada», «copiaPositivos» y «kolakoski».
 */
int main() {
    pruebaEstaOrdenada();
    pruebaCopiaPositivos();
    pruebaModa();
    return 0;
}
