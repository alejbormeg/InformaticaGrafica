// Nombre:Alejandro Apellidos:Borrego Megías DNI/pasaporte:26504975M (DDGG IG curso 20-21)

// *********************************************************************
// **
// ** Informática Gráfica, curso 2020-21
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

//#include <set>   // std::set
#include "ig-aux.h"
#include "tuplasg.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

   Tupla3f p,q,r,a,b, n_c;
   for(unsigned int i = 0; i<triangulos.size(); i++){
      p = vertices[triangulos[i](0)];
      q = vertices[triangulos[i](1)];
      r = vertices[triangulos[i](2)];

      a = q-p;
      b = r-p;

      n_c = a.cross(b);
      if(n_c.lengthSq()>0)
         nor_tri.push_back(n_c.normalized());
      else
         nor_tri.push_back({0,0,0});  
   }
}



// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   calcularNormalesTriangulos();
   nor_ver.insert(nor_ver.begin(), vertices.size(), {0.0, 0.0, 0.0});

   for(int i = 0; i<triangulos.size(); i++){ //Recorremos las caras
      nor_ver[triangulos[i](0)]=nor_ver[triangulos[i](0)]+nor_tri[i];
      nor_ver[triangulos[i](1)]=nor_ver[triangulos[i](1)]+nor_tri[i];
      nor_ver[triangulos[i](2)]=nor_ver[triangulos[i](2)]+nor_tri[i];
   }

   for(int i = 0; i<vertices.size(); i++){
      if(nor_ver[i].lengthSq()>0)
         nor_ver[i]=nor_ver[i].normalized();
   }
}





// ----------------------------------------------------------------------------
void MallaInd::visualizarNormales()
{
   using namespace std ;

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  
   if ( array_verts_normales == nullptr )
   {  
      for( unsigned i = 0 ; i < vertices.size() ; i++ )
      {  
         segmentos_normales.push_back( vertices[i] );
         segmentos_normales.push_back( vertices[i]+ 0.35f*(nor_ver[i]) );
      }
      array_verts_normales = new ArrayVertices( GL_FLOAT, 3, segmentos_normales.size(), segmentos_normales.data() );
   }

   array_verts_normales->visualizarGL_MI_DAE( GL_LINES );
   CError();
}

void MallaInd::visualizarGL( ContextoVis & cv )
{

   using namespace std ;
   assert( cv.cauce_act != nullptr );

   if (cv.visualizando_normales==true)
      visualizarNormales();

   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // guardar el color previamente fijado
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   // COMPLETAR: práctica 1: si el puntero 'array_verts' es nulo, crear el objeto ArrayVerts
   //   * en el constructor se dan los datos de la tabla de coordenadas de vértices (tabla 'vertices')
   //   * después hay que invocar a 'fijarIndices', usando el formato y datos de la tabla de triángulos ('triangulos')
   //   * si las tablas 'col_ver', 'cc_tt_ver' o 'nor_ver' no están vacías, hay que invocar los métodos 
   //     'fijarColores', 'fijarCoordText' y 'fijarNormales', como corresponda.
   if (array_verts == nullptr){
      array_verts= new ArrayVertices(GL_FLOAT,3,vertices.size(),vertices.data());

      array_verts->fijarIndices(GL_UNSIGNED_INT,3*triangulos.size(),triangulos.data());
      if(!col_ver.empty())
         array_verts->fijarColores(GL_FLOAT,3,col_ver.data());
      
      if(!cc_tt_ver.empty())
         array_verts->fijarCoordText(GL_FLOAT,2,cc_tt_ver.data());

      if(!nor_ver.empty())
         array_verts->fijarNormales(GL_FLOAT, nor_ver.data());


   }


   // COMPLETAR: práctica 1: visualizar según el modo (en 'cv.modo_envio')
   //   ** inmediato begin/end       : usar método 'visualizarGL_MI_BVE' de 'ArrayVerts'
   //   ** inmediato con una llamada : usar método 'visualizarGL_MI_DAE' de 'ArrayVerts'
   //   ** diferido (con un VAO)     : usar método 'visualizarGL_MD_VAO' de 'ArrayVerts'
   // (en cualquier caso hay que pasar como parámetro el tipo de primitiva adecuada a una malla de triángulos).
   // .....
   switch (cv.modo_envio)
   {
      case (ModosEnvio::inmediato_begin_end):
         array_verts->visualizarGL_MI_BVE(GL_TRIANGLES);
      break;

      case (ModosEnvio::inmediato_drawelements):
         array_verts->visualizarGL_MI_DAE(GL_TRIANGLES);
      break;

      case (ModosEnvio::diferido_vao):
         array_verts->visualizarGL_MD_VAO(GL_TRIANGLES);
      break;

   }

   // restaurar el color previamente fijado
   glColor4fv( color_previo );
}






// *****************************************************************************


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch,vertices,triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................
   calcularNormales();


}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   calcularNormales();

}
// -----------------------------------------------------------------------------------------------

Tetraedro::Tetraedro()
:  MallaInd( "tetraedro 4 vértices" )
{

   vertices =
      {  { -2.0, 0.0 , 0.0 }, // 0
         { +2.0, 0.0, 0.0 }, // 1
         { 0.0, +2.0, 0.0 }, // 2
         { 0.0, +1.0, +2.0 }, // 3
      } ;



   triangulos =
      {  {0,1,2},{0,1,3},{0,2,3},{1,2,3}
      } ;

   calcularNormales();
   ponerColor({0.0,+0.255,+0.6});

}

CuboColores::CuboColores()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   col_ver=
   {  
      { -1.0, -1.0, -1.0 }, // 0
      { -1.0, -1.0, +1.0 }, // 1
      { -1.0, +1.0, -1.0 }, // 2
      { -1.0, +1.0, +1.0 }, // 3
      { +1.0, -1.0, -1.0 }, // 4
      { +1.0, -1.0, +1.0 }, // 5
      { +1.0, +1.0, -1.0 }, // 6
      { +1.0, +1.0, +1.0 }, // 7
   } ;

}

Piramide_sinPico:: Piramide_sinPico() :MallaInd  ("Piramide sin pico")
{
   vertices=
   {     { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +0.5, -0.5, -0.5 }, // 4
         { +0.5, -0.5, +0.5 }, // 5
         { +0.5, +0.5, -0.5 }, // 6
         { +0.5, +0.5, +0.5 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;
}

CasaZ:: CasaZ(){
vertices =
      {  { 0.0, 0.0, 0.0 }, // 0
         { 0.0, 0.0, 1.0 }, // 1
         { 0.0, +0.5, 0.0 }, // 2
         { 0.0, +0.5, +1.0 }, // 3
         { +0.5, 0.0, 0.0 }, // 4
         { +0.5, 0.0, +1.0 }, // 5
         { +0.5, +0.5, 0.0 }, // 6
         { +0.5, +0.5, +1.0 }, // 7
         {0.25, 1.0, 1.0}, //8
         {0.25, 1.0, 0.0}  //9
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         //{0,5,1}, {0,4,5}, // Y-
         //{2,3,7}, {2,7,6}, // Y+ (+2)
         {3,8,7}, {2,6,9},
         {7,8,6}, {6,9,8},
         {3,8,2}, {2,8,9},

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   col_ver=
   {  
         { 0.0, 0.0, 0.0 }, // 0
         { 0.0, 0.0, 1.0 }, // 1
         { 0.0, +0.5, 0.0 }, // 2
         { 0.0, +0.5, +1.0 }, // 3
         { +0.5, 0.0, 0.0 }, // 4
         { +0.5, 0.0, +1.0 }, // 5
         { +0.5, +0.5, 0.0 }, // 6
         { +0.5, +0.5, +1.0 }, // 7
         {0.25, 1.0, 1.0}, //8
         {0.25, 1.0, 0.0}  //9
   } ;  
}

RejillaY ::RejillaY(const unsigned m, const unsigned n){
   assert(m>1 && n>1);

   double ancho=1.0/m;
   double largo=1.0/n;
   //vertices.push_back({0,0,0});
   for ( int i=0; i<= m; i++){
      for (int j=0; j<=n; j++){
         vertices.push_back({ancho*i,0.0,largo*j});
         col_ver.push_back({ancho*i,0.0,largo*j});
      }
   }

   for( int i = 0; i< m; i++) {
      for (int j = 0; j < n; j++){

      int a = j+i*n;
      int b = j+i*n +n;
      triangulos.push_back({a,b+1,b});
      triangulos.push_back({a,a+1,b+1}); 
      }
  
   }
}