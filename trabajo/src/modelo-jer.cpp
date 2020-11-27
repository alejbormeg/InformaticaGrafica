
#include "modelo-jer.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "matrices-tr.h"
#include <cmath>

C :: C(){
    agregar(new R2D2(rotacionCuerpo, giroCabeza, movPiernas, traslacion));
}

unsigned C:: leerNumParametros() const {
    return 4;
}

void C::fijarTraslacion(const float nuevaTraslacion){
    *traslacion=MAT_Traslacion(0.0,0.0,nuevaTraslacion);
}

void C::fijarRotacionCuerpo(const float nuevaRotacionCuerpo){
    *rotacionCuerpo=MAT_Rotacion(nuevaRotacionCuerpo,1.0,0.0,0.0);
}

void C::fijarGiroCabeza(const float nuevoGiroCabeza){
    *giroCabeza=MAT_Rotacion(nuevoGiroCabeza,0.0,1.0,0.0);
}

void C::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
    assert(iParam<leerNumParametros());

    switch (iParam)
    {
    case 0:
        fijarTraslacion(5*sin(0.5*M_PI*t_sec));
        break;
    case 1:
        fijarRotacionCuerpo(10.0*sin(0.5*M_PI*t_sec));
        break;
    
    case 2:
        fijarGiroCabeza(60.0*sin(0.5*M_PI*t_sec));
        break;
    
    default:
        break;
    }
}

Cabeza :: Cabeza(Matriz4f * &giroCabeza){
    unsigned ind=agregar(MAT_Rotacion(0.0, 0.0, 1.0, 0.0));
    agregar(MAT_Traslacion(0.0,1.0,0.0));
    SemiEsfera * cabeza= new SemiEsfera(30,30);
    cabeza->ponerColor({0.035, 0.2588, 0.5765});
    agregar(cabeza);
    agregar(MAT_Traslacion(0.0,0.45,0.75));  
    agregar(MAT_Escalado(0.2,0.2,0.2));
    agregar( MAT_Rotacion(90,1.0,0.0,0.0));
    SemiEsfera * pantalla= new SemiEsfera(30,30);
    pantalla->ponerColor({0.0, 0.0, 0.0});
    agregar(pantalla);

    giroCabeza=leerPtrMatriz(ind);
    ponerNombre("Cabeza");
}

Propulsor::Propulsor(){
    agregar(MAT_Traslacion(0.0,-1.0,0.0));
    agregar(MAT_Escalado(1.0,-1.0,1.0));
    agregar(MAT_Escalado(0.90,0.90,0.90));
    SemiCono *propulsor = new SemiCono(30,30,20);
    propulsor->ponerColor({0.6078,0.6078,0.6078});
    agregar(propulsor);
    ponerNombre("Propulsor");
}

Cuerpo:: Cuerpo(Matriz4f * &rotacionCuerpo, Matriz4f * &giroCabeza){
    unsigned ind=agregar(MAT_Rotacion(0.0, 1.0, 0.0, 0.0));
    agregar(MAT_Traslacion(0.0,2.0,0.0));
    agregar(new Cabeza(giroCabeza));
    Cilindro *cilindro = new Cilindro(30,30);
    cilindro->ponerColor({0.7608,0.7608,0.7608});
    agregar(cilindro);
    agregar(new Propulsor);
    rotacionCuerpo=leerPtrMatriz(ind);
    ponerNombre("Cuerpo");
}

Brazo_inferior:: Brazo_inferior(){
    agregar(MAT_Rotacion(90, 0.0, 0.0, 1.0));
    Piramide_sinPico *pie = new Piramide_sinPico ();
    pie->ponerColor({0.035, 0.2588, 0.5765});
    agregar(pie);
    agregar(MAT_Traslacion(1.5,0.0,0.0));
    agregar(MAT_Escalado(2.0,0.5,0.5));
    Cubo * conector= new Cubo;
    conector->ponerColor({0.6078,0.6078,0.6078});
    agregar(conector);
    
    ponerNombre("Brazo Izquierdo Inferior");
}

Hombro1 :: Hombro1(){
    agregar(MAT_Traslacion(0.0,3.5,0.0));
    agregar(MAT_Rotacion(90,1.0,0.0,0.0));
    CilindroParam *hombro= new CilindroParam(30,30,180.0);
    hombro->ponerColor({0.035, 0.2588, 0.5765});
    agregar(hombro);
    ponerNombre("hombro1");
}

Hombro2 :: Hombro2(){
    agregar(MAT_Traslacion(0.0,3.0,0.0));
    agregar(MAT_Escalado(1.0,0.5,1.0));
    Cubo * cubo= new Cubo;
    cubo->ponerColor({0.035, 0.2588, 0.5765});
    agregar(cubo);
    ponerNombre("hombro2");
}

Brazo_superior:: Brazo_superior(){
    agregar(new Hombro1);
    agregar(new Hombro2);
    ponerNombre("Brazosuperior");
}

Brazo :: Brazo(){
    agregar(MAT_Rotacion(90,0.0,1.0,0.0));
    agregar(MAT_Escalado(0.5,0.5,0.5));
    agregar(MAT_Traslacion(0.0,1.0,0.0));
    agregar(new Brazo_inferior);
    agregar(MAT_Traslacion(0.0,0.0,0.5));
    agregar(new Brazo_superior);
    ponerNombre("brazo");
}

Brazos :: Brazos(){
    agregar(MAT_Traslacion(-1.25,0.0,0.0));
    agregar(new Brazo);
    agregar(MAT_Traslacion(2.5,0.0,0.0));
    agregar(MAT_Escalado(-1.0,1.0,1.0));
    agregar(new Brazo);
}

R2D2 :: R2D2(Matriz4f * &rotacionCuerpo, Matriz4f * &giroCabeza, Matriz4f * &movPiernas, Matriz4f * &traslacion ){
    unsigned ind=agregar(MAT_Traslacion(0.0,0.0,0.0));
    agregar(new Cuerpo(rotacionCuerpo, giroCabeza));
    agregar(new Brazos);
    traslacion=leerPtrMatriz(ind);
    ponerIdentificador(0);
    ponerNombre("R2D2");
}