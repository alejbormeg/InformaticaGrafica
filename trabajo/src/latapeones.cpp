
#include "malla-ind.h"
#include "malla-revol.h"
#include "matrices-tr.h"
#include "latapeones.h"
//#include "funciones-aux.h"


ParteInferiorLata :: ParteInferiorLata(){
    agregar( new Material(0.1,0.6,0.3,20) );
    agregar( new MallaRevolPLY("../recursos/plys/lata-pinf.ply",100) );
    ponerIdentificador(-1);
    ponerNombre("Parte Inferior Lata");
}
ParteSuperiorLata :: ParteSuperiorLata(){
    agregar( new Material(0.1,0.6,0.3,20) );
    agregar( new MallaRevolPLY("../recursos/plys/lata-psup.ply",100) );
    ponerIdentificador(-1);
    ponerNombre("Parte Superior Lata");
}

CuerpoLata :: CuerpoLata(const std::string & fichero){
    Textura * tex = new Textura(fichero);
    agregar( new Material(tex, 0.5,0.1,0.3,20) );
    agregar(new MallaRevolPLY("../recursos/plys/lata-pcue.ply",50));
    ponerIdentificador(-1);
    ponerNombre("Cuerpo de la lata");
}

Lata :: Lata(const std::string & textura){
    agregar(MAT_Escalado(4.0,4.0,4.0));
    agregar(new ParteInferiorLata() );
    agregar(new ParteSuperiorLata());
    agregar(new CuerpoLata(textura));

    ponerIdentificador(-1);
    ponerNombre("Lata");
}

PeonMadera :: PeonMadera(){
    Textura * tex = new Textura("../recursos/imgs/text-madera.jpg");
    agregar( MAT_Escalado(0.8, 0.8, 0.8) );
    agregar( MAT_Traslacion(0.0,1.35,0.0));
    agregar( new Material(tex, 0.2, 0.4, 0.4, 20) );
    agregar(new MallaRevolPLY("../recursos/plys/peon.ply",50));

    ponerNombre("Peon de Madera");
    ponerIdentificador(0);
}


PeonBlanco :: PeonBlanco(){
    ponerColor({1.0,1.0,1.0});
    agregar( MAT_Escalado(0.8, 0.8, 0.8) );
    agregar( MAT_Traslacion(0.0,1.35,0.0));
    agregar( new Material(0.1, 0.8, 0.1, 15 ) );
    agregar(new MallaRevolPLY("../recursos/plys/peon.ply",50));

    ponerNombre("Peon Blanco");
    ponerIdentificador(1);
}

PeonNegro :: PeonNegro(){
    ponerColor({0.0,0.0,0.0});
    agregar( MAT_Escalado(0.8, 0.8, 0.8) );
    agregar( MAT_Traslacion(0.0,1.35,0.0));
    agregar( new Material(0.1, 0.1, 0.8, 20) );
    agregar(new MallaRevolPLY("../recursos/plys/peon.ply",50));

    ponerNombre("Peon Negro");
    ponerIdentificador(2);
}

LataPeones :: LataPeones(){

    agregar(new Lata("../recursos/imgs/lata-coke.jpg"));
    agregar(MAT_Traslacion(0.0, 0.0, 3.0));
    agregar(new PeonNegro());
    agregar(MAT_Traslacion(2.0, 0.0, 0.0));
    agregar(new PeonBlanco());
    agregar(MAT_Traslacion(2.0, 0.0, 0.0));
    agregar(new PeonMadera());

    ponerNombre("Lata y Peones");
}


LataPepsi :: LataPepsi(){
    agregar(new Lata("../recursos/imgs/lata-pepsi.jpg"));

    ponerNombre("Lata de Pepsi");
    ponerIdentificador(3);
}

LataCocaCola :: LataCocaCola(){
    agregar(new Lata("../recursos/imgs/lata-coke.jpg"));

    ponerNombre("Lata de Coca-Cola");
    ponerIdentificador(4);
}

LataUGR :: LataUGR(){
    agregar(new Lata("../recursos/imgs/window-icon.jpg"));

    ponerNombre("Lata de la UGR");
    ponerIdentificador(5);
}

Latas :: Latas(){
    agregar(new LataPepsi());
    agregar(MAT_Traslacion(3.0,0.0,0.0));
    agregar(new LataCocaCola());
    agregar(MAT_Traslacion(3.0,0.0,0.0));
    agregar(new LataUGR());

    ponerIdentificador(0);
    ponerNombre("Latas");
}

Peones :: Peones(){
    agregar(new PeonMadera());
    agregar(MAT_Traslacion(2.0, 0.0, 0.0));
    agregar(new PeonBlanco());
    agregar(MAT_Traslacion(2.0, 0.0, 0.0));
    agregar(new PeonNegro());
    ponerIdentificador(0);

    ponerNombre("Peones");
}

VariasLatasPeones :: VariasLatasPeones(){
    agregar(new Latas());
    agregar(MAT_Traslacion(0.0,0.0,3.0));
    agregar(new Peones());

    ponerIdentificador(0);
    ponerNombre("Latas y Peones");
}