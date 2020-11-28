// Nombre:Alejandro Apellidos:Borrego Megías DNI/pasaporte:26504975M (DDGG IG curso 20-21)

#ifndef MODELO_JER_H
#define MODELO_JER_H

#include "grafo-escena.h"

//Nodo Raíz
class C : public NodoGrafoEscena
{
     protected:
        Matriz4f * rotacionCuerpo  = nullptr;   // Matriz asociada al movimiento del cuerpo
        Matriz4f * giroCabeza   = nullptr;		// Matriz asociada al giro de la cabeza
        Matriz4f * movPiernas = nullptr;		// Matriz asociada al movimiento de las piernas
        Matriz4f * traslacion =nullptr;         // Matriz asociada al movimiento de R2D2
        void actualizarEstadoParametro( const unsigned iParam, const float t_sec );

    public:
        C();
        unsigned leerNumParametros() const;
        void fijarTraslacion(const float nuevaTraslacion);
        void fijarGiroCabeza(const float nuevoGiroCabeza);
        void fijarRotacionCuerpo(const float nuevaRotacionCuerpo);
        void fijarMovPiernas(const float nuevoMovPiernas);
};

//----------------------------------------------------------------------------------
// clase para el nodo del grafo etiquetado como Cabeza
class Cabeza : public NodoGrafoEscena{
    public:
        Cabeza(Matriz4f * &giroCabeza);			// constructor
};

//----------------------------------------------------------------------------------
// clases para los nodo del grafo etiquetados como Hombro1 y Hombro2
class Hombro1 : public NodoGrafoEscena
{ 
    public:
        Hombro1() ; // constructor
} ;

class Hombro2 :public NodoGrafoEscena
{
    public:
        Hombro2();
};
//----------------------------------------------------------------------------------
// clase para el nodo del grafo etiquetado como Brazo_inferior
class Brazo_inferior : public NodoGrafoEscena
{ 
    public:
        Brazo_inferior() ; // constructor
} ;

//----------------------------------------------------------------------------------
// clase para el nodo del grafo etiquetado como Brazo_superior
class Brazo_superior : public NodoGrafoEscena
{ 
    public:
        Brazo_superior() ; // constructor
} ;

//----------------------------------------------------------------------------------
// clase para el nodo del grafo etiquetado como Brazo
class Brazo : public NodoGrafoEscena
{
    public:
        Brazo();
};

//----------------------------------------------------------------------------------
// clase para el nodo del grafo etiquetado como Brazos
class Brazos : public NodoGrafoEscena
{
    public:
        Brazos();
};

//----------------------------------------------------------------------------------
// clase para el nodo del grafo etiquetado como cuerpo
class Cuerpo : public NodoGrafoEscena{
    public:
        Cuerpo(Matriz4f * &rotacionCuerpo, Matriz4f * &giroCabeza);
} ;

//----------------------------------------------------------------------------------
// clase para el nodo del grafo etiquetado como Propulsor
class Propulsor: public NodoGrafoEscena{
    public:
        Propulsor();
};

//----------------------------------------------------------------------------------
// clase para el nodo del grafo etiquetado como R2D2
class R2D2 : public NodoGrafoEscena
{
    public:
        R2D2(Matriz4f * &rotacionCuerpo, Matriz4f * &giroCabeza, Matriz4f * &movPiernas, Matriz4f * &traslacion );
};

#endif