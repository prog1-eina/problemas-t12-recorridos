/******************************************************************************
 * Curso de Programación 1. Tema 12 (Algoritmos con vectores)
 * Autores: Miguel Ángel Latre
 * Última revisión: 24 de noviembre de 2020
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la 
 *          sección «Recorridos de vectores de registros» de
 *          la clase de problemas del tema 12 (recorridos de vectores).
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la clase
 *          de problemas del recorrido de vectores
 * Dependencias: módulo «permiso», ubicado en el directorio
 *               del repositorio de los problemas del tema 11 (registros).
 * Nota: El código de este programa está repartido en varios módulos. El
 *       fichero «Makefile» ha sido escrito considerando que el módulo
 *       «permiso» se encuentra en un directorio denominado «permisos-conducir»
 *       dentro de un directorio «problemas-t11-registros» ubicado en la misma
 *       carpeta que el directorio correspondiente a estas soluciones
 *       («problemas-t12-recorridos»). La ruta a este módulo puede modificarse
 *       en el propio fichero «Makefile» si fuese preciso.
 * 
 *       Para compilarlo, hay que ejecutar el comando
 *           make recorridos
 *       o ejecutar la tarea "Compilar «recorridos»" de VSC.
 * 
 *       Para ejecutarlo, una vez compilado, hay que ejecutar el comando
 *           bin/recorridos
 *       o, en Windows,
 *           bin\recorridos.exe
 *       o ejecutar la tarea "Ejecutar «recorridos»" de VSC.
 *****************************************************************************/

#include <iostream>
#include "permiso.hpp"
using namespace std;

/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Devuelve el número de permisos de conducir de las primeras «n»
 *       componentes del vector «v» con una cantidad de puntos negativa o igual
 *       a 0.
 */
unsigned contarSinPuntos(const Permiso v[], const unsigned n) {
    // Esquema de recorrido del vector, contando permisos sin puntos
    unsigned cuenta = 0;
    for (unsigned i = 0; i < n; i++) {
        if (puntos(v[i]) <= 0) {
            cuenta++;
        }
    }
    return cuenta;
}


/*
 * Pre:  «v» tiene al menos «n» componentes y «n» > 0.
 * Post: Devuelve el permiso de conducir de entre las primeras «n»
 *       componentes del vector «v» que tiene el menor saldo de puntos.
 */
Permiso peorConductor(const Permiso v[], const unsigned n) {
    // Esquema de búsqueda de un mínimo en el vector, buscando un mínimo
    unsigned indPeor = 0;
    int puntosPeor = puntos(v[0]);
    for (unsigned i = 1; i < n; i++) {
        int puntosI = puntos(v[i]);
        if (puntosI < puntosPeor) {
            indPeor = i;
            puntosPeor = puntosI;
        }
    }
    return v[indPeor];
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Devuelve el índice de una componente de entre las primeras «n»
 *       componentes del vector «v» que contiene un permiso con
 *       «puntosBuscados» puntos, o un valor negativo si no existe ninguno en
 *       el vector.
 */
int buscarPorPuntos(const Permiso v[], const unsigned n,
                    const int puntosBuscados) {
    // Esquema de búsqueda sin garantía de éxito
    bool encontrado = false;
    unsigned i = 0;
    while (!encontrado && i < n) {
        if (puntos(v[i]) == puntosBuscados) {
            encontrado = true;
        } else {
            i++;
        }
    }
    // Se cumple: encontrado || i >= n

    // Determinación del éxito de la búsqueda y devolución de resultado
    if (encontrado) {
        return i;
    } else {
        return -1;
    }
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Recorre las primeras «n» componentes del vector «v», aumentando la
 *       antigüedad de todos los permisos en un mes.
 */
void actualizarMes(Permiso v[], const unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        v[i].antiguedadMeses++;
    }
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Recorre las primeras «n» componentes del vector «v» y, cuando
 *       encuentra  permisos en ellas correspondientes a conductores que han
 *       dejado de ser noveles (conductores con exactamente 12 meses de
 *       antigüedad), les bonifica con 4 puntos. Devuelve el número de permisos
 *       de conductores a los que se bonifica por dejar de ser noveles.
 */
unsigned bonificarPorDejarDeSerNovel(Permiso v[], const unsigned n) {
    unsigned cuenta = 0;

    // Recorrido del vector buscando conductores con exactamente 24 meses de
    // antigüedad, bonificándolos con 4 puntos y contándolos.
    for (unsigned i = 0; i < n; i++) {
        if (v[i].antiguedadMeses == MESES_NOVEL) {
            registrarBonificacion(v[i], 4);
            cuenta++;
        }
    }
    return cuenta;
}


/*
 * Pre:  Los vectores «v» y  «resultado» tienen al menos «nV» componentes cada
 *       uno.
 * Post: El vector «resultado» contiene, en sus primeras «nR»
 *       componentes, únicamente aquellos permisos de las primeras «nV»
 *       componentes del vector «v» que tienen un saldo de puntos estrictamente
 *       positivo.
 */
void purgar(const Permiso v[], const unsigned nV, Permiso resultado[],
            unsigned &nR) {
    nR = 0; // Cuenta el número de permisos con puntos positivos y va a servir
            // como cursor para indexar el vector «resultado».

    // Recorrido del vector «v», copiando los permisos con puntos
    // positivos a el vector «resultado».
    for (unsigned i = 0; i < nV; i++) {
        if (puntos(v[i]) > 0) {
            resultado[nR] = v[i];
            nR++;
        }
    }
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Devuelve «true» si y solo si las primeras «n» componentes del vector
 *       «v» están ordenadas de forma que los permisos de sus componentes
 *       tienen valores de puntos no decrecientes.
 */
bool estaOrdenadoPorPuntos(const Permiso v[], const unsigned n) {
    if (n == 0) {
        // Hay cero componentes y está trivialmente ordenado
        return true;
    } else {
        /*
        * Resolución del problema como la búsqueda de un par de componentes
        * consecutivas en las que la primera corresponde a un conductor con
        * más puntos que el de la componente siguiente. Si se encuentra tal
        * par, no esta ordenado. En caso contrario, sí está ordenado.
        */
        unsigned i = 0;
        int puntosActual = puntos(v[0]);
        bool ordenado = true;
        while (ordenado && i < n - 1) {
            int puntosSiguiente = puntos(v[i + 1]);
            ordenado = puntosActual <= puntosSiguiente;
            puntosActual = puntosSiguiente;
            i++;
        }
        return ordenado;
    }
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Devuelve true si y solo si las primeras «n» componentes del vector
 *       «v» están distribuidas de forma tal que todos los permisos
 *       correspondientes a conductores noveles aparecen primero (en las
 *       componentes de índices más bajos) y todos los correspondientes a
 *       conductores experimentados, después (en las componentes de índices más
 *       altos).
 */
bool estaDistribuidoPorNovel(const Permiso v[], const unsigned n) {
    /*
     * Resolución del problema como la búsqueda de un par de componentes
     * consecutivas en las que la primera corresponde a un conductor
     * experimentado y la segunda a un conductor novel. Si se encuentra tal
     * par, no esta ordenado. En caso contrario, sí está ordenado.
     */
    unsigned i = 0;
    bool distribuido = true;
    while (distribuido && i < n - 1) {
        distribuido = !(!esNovel(v[i]) && esNovel(v[i + 1]));
        i++; 
    }
    // !distribuido || i >= n - 1
    return distribuido;
}


/*
 * Pre:  uno = A y otro = B
 * Post: uno = B y otro = A
 */
void permutar(Permiso &uno, Permiso &otro) {
    Permiso aux = uno;
    uno = otro;
    otro = aux;
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Las primeras «n» componentes del vector «v» son una permutación de los
 *       permisos que había inicialmente en esas mismas primeras «n»
 *       componentes del vector «v» y están clasificadas de forma que todos los
 *       permisos correspondientes a conductores noveles aparecen primero (en
 *       las componentes de índices más bajos) y todos los correspondientes a
 *       conductores experimentados, después (en las componentes de índices más
 *       altos).
 */
void clasificarPorNovel(Permiso v[], const unsigned n) {
    /*
     * INV1: Todas las componentes de índice menor que «inferior» corresponden
     *       a conductores noveles.
     */
    int inferior = 0;

    /*
     * INV2: Todas las componentes de índice mayor que «superior» corresponden
     *       a conductores experimentados.
     */
    int superior = n - 1;

    /*
     * INV3: Las componentes de índices en el intervalo [inferior, superior]
     *       pueden tener permisos noveles o experimentados.
     */
    while (inferior < superior) {
        // Se cumplen INV1, INV2 e INV3.

        if (esNovel(v[inferior])) {
            /*
             * Como v[inferior] corresponde a un conductor novel, se puede
             * incrementar en 1 el valor de «inferior» y se seguirá cumpliendo
             * INV1.
             */
            inferior++;
        } else if (!esNovel(v[superior])) {
            /*
             * Como v[superior] corresponde a un conductor experimentado, se
             * puede decrementar en 1 el valor de «superior» y se seguirá
             * cumpliendo INV2.
             */
            superior--;
        } else {
            /*
             * Se cumple !esNovel(v[inferior]) && esNovel(v[superior])
             *
             * En la componente de índice «inferior» hay un experimentado y en
             * la de índice «superior» hay un novel. Podemos intercambiarlos,
             * incrementar «inferior», decrementar «superior» y se seguirá
             * cumpliendo INV1 e INV2.
             */
            permutar(v[inferior], v[superior]);
            inferior++;
            superior--;
        }
    }
    /*
     * Al acabar el bucle, se siguen cumpliendo INV1, INV2, INV3.
     * Además, inferior >= superior, con lo que el intervalo
     * [inferior, superior] que se menciona en INV3 se refiere a uno o ningún
     * índice: "Todas las componentes de índice menor que «inferior»
     * corresponden a conductores noveles; todas las componentes de índice
     * mayor que «superior» corresponden a conductores experimentados y en
     * v[inferior] hay un conductor novel o experimentado".
     *
     * Esto quiere decir que se cumple la postcondición: "Todos los permisos
     * correspondientes a conductores noveles aparecen primero (en las
     * componentes de índices más bajas) y todos los correspondientes a
     * conductores experimentados, después (en las componentes de índices más
     * altas)".
     */
}

/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Las primeras «n» componentes del vector «v» son una permutación de los
 *       permisos que había inicialmente en esas mismas primeras «n»
 *       componentes del vector «v» y están ordenadas de forma que tienen
 *       valores de puntos no decrecientes.
 */
void ordenarPorPuntos(Permiso v[], const unsigned n) {
    if (n != 0) {
        // Aplica el método de ordenación de vectores por selección directa.
        for (unsigned i = 0; i < n - 1; i++) {
            // Determina el índice «iMenor» del menor de los datos almacenados
            //  en el subvector v[i, n - 1].
            unsigned iMenor = i;
            for (unsigned j = i + 1; j < n; j++) {
                if (puntos(v[j]) < puntos(v[iMenor])) {
                    iMenor = j;
                }
            }

            // Permuta los valores de v[i] y v[iMenor]
            permutar(v[i], v[iMenor]);
        }
    }
}


/*
 * Función main para que el proyecto compile sin errores. Puede utilizarse para
 * escribir un programa de prueba de las funciones anteriores.
 */
int main() {
    cout << "Puedes escribir un programa de prueba." << endl;
    return 0;
}