// Nombre:Alejandro Apellidos:Borrego Megías DNI/pasaporte:26504975M (DDGG IG curso 20-21)

// *********************************************************************
// **
// ** Gestión de una grafo de escena (implementación)
// ** Copyright (C) 2016 Carlos Ureña
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "matrices-tr.h"
#include "grafo-escena.h"
#include "malla-ind.h"
using namespace std ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != NULL );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const Matriz4f & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new Matriz4f() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != NULL );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL( ContextoVis & cv )
{
   // COMPLETAR: práctica 3: recorrer las entradas y visualizar cada nodo.
   //guardar modelview actual
      cv.cauce_act->pushMM();

   Material * material_pre = cv.iluminacion ? cv.material_act : nullptr;

   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   //recorrer todas las entradas del array que hay en el nodo
   for (unsigned i=0; i<entradas.size(); i++)
      switch( entradas[i].tipo) { 
         case TipoEntNGE::objeto : // entrada objeto:
            entradas[i].objeto->visualizarGL( cv ); // visualizar objeto
            break ;


         case TipoEntNGE::transformacion : // entrada transf.:
            cv.cauce_act->compMM( *(entradas[i].matriz)); // componer matriz
            break ;  
         
         case TipoEntNGE::material : // si la entrada es de tipo ’material’
            if ( cv.iluminacion && !cv.modo_seleccion) // y si está activada la iluminación
            { 
               cv.material_act = entradas[i].material ; // registrar material
               cv.material_act->activar( *cv.cauce_act); // activar material
            }
            break ;
      }


   glColor4fv( color_previo );
   if ( material_pre != nullptr  ){
      cv.material_act = material_pre ;
      cv.material_act->activar( *cv.cauce_act );
   }
   // restaura modelview guardada
   cv.cauce_act->popMM();
   
   // COMPLETAR: práctica 4: en la práctica 4, si 'cv.iluminacion' es 'true',
   // se deben de gestionar los materiales:
   //   1. guardar puntero al material activo al inicio (está en cv.material_act)
   //   2. si una entrada des de tipo material, activarlo y actualizar 'cv.material_act'
   //   3. al finalizar, restaurar el material activo al inicio (si es distinto del actual)
}




// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
// ignora el colo o identificador del nodo, ignora las entradas de tipo material
// (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)




// -----------------------------------------------------------------------------

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   // ........
   entradas.push_back(entrada);
   return entradas.size()-1;

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const Matriz4f & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
Matriz4f * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: devolver puntero la matriz en ese índice
   //   (debe de dar error y abortar si no hay una matriz en esa entrada)
   // ........(sustituir 'return nullptr' por lo que corresponda)
   assert(indice<entradas.size());
   assert(entradas[indice].tipo==TipoEntNGE::transformacion);
   assert(entradas[indice].matriz != nullptr);
   return entradas[indice].matriz;


}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........
   if (centro_calculado==false){
      Matriz4f mat = MAT_Ident();
      Tupla3f centro_promedio = {0,0,0};
      float num_centros = 0;
      for (unsigned i=0; i<entradas.size(); i++){
         if ( entradas[i].tipo == TipoEntNGE::objeto){
           entradas[i].objeto->calcularCentroOC();
           centro_promedio = centro_promedio + mat*leerCentroOC();
           num_centros++;
         }
         else if (entradas[i].tipo == TipoEntNGE::transformacion)
            mat = mat * (*entradas[i].matriz) ;
      }
      centro_promedio = centro_promedio / num_centros;
      ponerCentroOC(centro_promedio);
   }
   centro_calculado = true;
}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int         ident_busc, // identificador a buscar
   const Matriz4f &  mmodelado,  // matriz de modelado
   Objeto3D       ** objeto,     // (salida) puntero al puntero al objeto
   Tupla3f &         centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........
   calcularCentroOC();

   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........
   if(ident_busc == leerIdentificador()){
      centro_wc = mmodelado*leerCentroOC();
      if ( objeto == nullptr ) {
        cout << "\t Identificador encontrado con puntero asociado nulo" << endl;
      }
      *objeto = this ;
      return true;
   }

   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........
   Matriz4f mat = mmodelado;

   bool encontrado = false;
   for (unsigned i=0; i<entradas.size() && !encontrado; i++) {
      if ( entradas[i].tipo == TipoEntNGE::objeto) 
         encontrado =  entradas[i].objeto->buscarObjeto(ident_busc, mat, objeto, centro_wc );
      else if (entradas[i].tipo == TipoEntNGE::transformacion)
         mat = mat * (*entradas[i].matriz) ;
   }

   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}


CuboRejillas::CuboRejillas(){
   agregar(new Fachada());
   agregar(new Trasera());
   agregar(new RejillaY(5,5));
   agregar(new Techo());
   agregar(new Pared());
   agregar(MAT_Traslacion(1.0,0.0,0.0));
   agregar(new Pared());
   agregar(MAT_Ident());
   
   //agregar(new RejillaY(5,5));
   //agregar(new RejillaY(5,5));
}

Pared::Pared(){
   agregar(MAT_Rotacion(90,0.0,0.0,1.0));
   agregar(new RejillaY(5,5));
}

Techo::Techo(){
   agregar(MAT_Traslacion(0.0,1.0,0.0));
   agregar(new RejillaY(5,5));
}

Trasera::Trasera(){
   agregar(MAT_Rotacion(90,0.0,1.0,0.0));
   agregar(new Pared());
}
Fachada::Fachada(){
   agregar(MAT_Traslacion(0.0,0.0,1.0));
   agregar(new Trasera());
}

GrafoCubos::GrafoCubos(){
   agregar(new CuboEjeX);
   agregar(MAT_Traslacion(-0.5,-0.5,-0.5));
   agregar(new CuboRejillas());
}

CuboEjeX::CuboEjeX(){  //Habría que hacer lo mismo con el eje y y z
   agregar(MAT_Escalado(1.5,1.0,1.0));
   agregar(MAT_Escalado(0.5,0.5,0.5));
   agregar(MAT_Traslacion(-2.0,0.0,0.0));
   agregar(new Cubo());
   agregar(MAT_Traslacion(4.0,0.0,0.0));
   agregar(new Cubo());
}


NodoCubo24::NodoCubo24(){
   Textura * tex = new Textura("../recursos/imgs/window-icon.jpg");
   agregar( new Material(tex, 0.2, 0.4, 0.4, 20) );
   agregar(new Cubo24());
   ponerNombre("Cubo 24 vertices");
}