// Nombre:Alejandro Apellidos:Borrego Megías DNI/pasaporte:26504975M (DDGG IG curso 20-21)

// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar 
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
 
      std::vector<Tupla3f> normalesAristas, vertsAux;
      Tupla3f normal, aux;
      for(unsigned i = 0; i<perfil.size()-1; i++){

         aux = (perfil[i+1]-perfil[i]);
         normal(0)=aux(1);
         normal(1)=-aux(0);
         normal(2)=0;
         if(normal.lengthSq()>0)
            normalesAristas.push_back(normal.normalized());
         else
            normalesAristas.push_back(normal);
         
      }

      nor_ver.insert(nor_ver.begin(), perfil.size(), {0.0, 0.0 , 0.0});
      if(normalesAristas[0].lengthSq()!=0)
         nor_ver[0]=normalesAristas[0].normalized();
      
      for(unsigned i=1; i<perfil.size()-1; i++){
         nor_ver[i]=normalesAristas[i]+normalesAristas[i-1];
         if(nor_ver[i].lengthSq()!=0)
            nor_ver[i]=nor_ver[i].normalized();
      }

      if(normalesAristas[perfil.size()-2].lengthSq()!=0)
         nor_ver[perfil.size()-1]=normalesAristas[perfil.size()-2];


   //Calculamos coordenadas de textura
   std::vector<float> d, t;
   float den=0;
   for(unsigned int i = 0; i<perfil.size()-1; i++){
      d.push_back(sqrt((perfil[i+1]-perfil[i]).lengthSq()));
      den += d[i];
   }
   t.push_back(0);
   for(unsigned int i = 1; i<perfil.size(); i++)
      t.push_back(t[i-1]+d[i-1]/den);

   // COMPLETAR: Práctica 2: completar: creación de la malla....
   
   Tupla3f vertice_rotado;
   Matriz4f rotacion;
   int k;
   int m=perfil.size();
   Tupla2f textura;
   float t_x,t_y;

   for (int i=0; i<num_copias; i++){
      rotacion=MAT_Rotacion((360.0*i)/(num_copias-1), 0.0, 1.0, 0.0);
      for (int j=0; j<m; j++){
         vertice_rotado=rotacion*perfil[j];
         nor_ver.push_back(rotacion*nor_ver[j]);
         t_x=(float)i/(num_copias-1);
         t_y=1.0-t[j];
         textura={t_x,t_y};
         vertices.push_back(vertice_rotado);
         cc_tt_ver.push_back(textura);

      }
   }

   for (int i=0; i<num_copias-1; i++){
      for (int j=0; j<m-1; j++){
         k=i*m+j;
         triangulos.push_back({k,k+m,k+m+1});
         triangulos.push_back({k,k+m+1,k+1});
      }
   }

}

void MallaRevolParam::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias,  // número de copias del perfil
   const double angulo
)
{
   
   Tupla3f vertice_rotado;
   Matriz4f rotacion;
   int k;
   int m=perfil.size();
   for (int i=0; i<num_copias; i++){
      rotacion=MAT_Rotacion((angulo*i)/(num_copias-1), 0.0, 1.0, 0.0);
      for (int j=0; j<m; j++){
         vertice_rotado=rotacion*perfil[j];
         vertices.push_back(vertice_rotado);

      }
   }

   for (int i=0; i<num_copias-1; i++){
      for (int j=0; j<m-1; j++){
         k=i*m+j;
         triangulos.push_back({k,k+m,k+m+1});
         triangulos.push_back({k,k+m+1,k+1});
      }
   }



}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   vector<Tupla3f> perfil;
   LeerVerticesPLY(nombre_arch,perfil);
   inicializar(perfil,nperfiles);
}

Cilindro::Cilindro (const int num_verts_per, const unsigned nperfiles){
   ponerNombre(std::string("Cilindro generado por revolución"));
   assert(num_verts_per >= 4);
   
   ponerNombre( std::string("Cilindro generado por revolución" ));

   vector<Tupla3f> perfil;
   float coord_y;

   perfil.push_back({0.0, -1.0, 0.0}); //Cerrar el cilindro por abajo

   for (int i=0; i<num_verts_per-2; i++){
      coord_y=-1.0 + (2.0*(float)i/(num_verts_per-3));
      perfil.push_back({1.0, coord_y, 0.0});
   }

   perfil.push_back({0.0, 1.0, 0.0}); //cerrar el cilindro por arriba
   inicializar(perfil,nperfiles);

}

Cono::Cono (const int num_verts_per, const unsigned nperfiles){
   ponerNombre(std::string("Cono generado por revolucion"));
   assert (num_verts_per>=3); //necesito minimo 3 vertices
   vector<Tupla3f> perfil;
   float coord_x;
   float coord_y;

   perfil.push_back({0.0, 1.0, 0.0});
   for (int i=0; i<num_verts_per-2; i++){
      coord_x=0.0 + (1.0*(float)i/(num_verts_per-3));
      coord_y=-coord_x + 1;  // y=-x+1
      perfil.push_back({coord_x, coord_y, 0.0});
   }

   perfil.push_back({1.0, 0.0, 0.0});
   perfil.push_back({0.0, 0.0, 0.0}); //Cerramos por abajo el cono
   inicializar(perfil, num_verts_per);
}

Esfera::Esfera (const int num_verts_per, const unsigned nperfiles){
   ponerNombre(std::string("Esfera generado por revolucion"));
   assert(num_verts_per >= 3); // Al menos se necesitan 3 vértices para generar la esfera

   vector<Tupla3f> perfil;
   Tupla3f punto_inicio={0.0, 1.0, 0.0};
   Tupla3f punto_rotado;
   Matriz4f rotacion;

   for (int i=0; i< num_verts_per; i++){
      rotacion=MAT_Rotacion(180*i/(num_verts_per-1),0.0, 0.0, 1.0);
      punto_rotado=rotacion*punto_inicio; //en cada rotación giramos el punto de inicio un ángulo que llega hasta 180º con respecto al eje z
      perfil.push_back(punto_rotado);
   }

   inicializar(perfil,nperfiles);

}

SemiEsfera::SemiEsfera(const int num_verts_per, const unsigned nperfiles){
   ponerNombre(std::string("Semiesfera generado por revolucion"));
   assert(num_verts_per>=3);

   vector<Tupla3f> perfil;
   Tupla3f punto_inicio={0.0, 1.0, 0.0};
   Tupla3f punto_rotado;
   Matriz4f rotacion;

   for (int i=0; i< num_verts_per; i++){
      rotacion=MAT_Rotacion(90*i/(num_verts_per-1),0.0, 0.0, 1.0);
      punto_rotado=rotacion*punto_inicio; //en cada rotación giramos el punto de inicio un ángulo que llega hasta 90º con respecto al eje z
      perfil.push_back(punto_rotado);
   }

   inicializar(perfil,nperfiles);
}

SemiCono::SemiCono (const int num_verts_per, const unsigned nperfiles, const int n){
   //n es el número de vértices que se salta para que no acabe en punta el cono
   ponerNombre(std::string("SemiCono generado por revolucion"));
   assert (num_verts_per>=3 && n<=num_verts_per); //necesito minimo 3 vertices
   vector<Tupla3f> perfil;
   float coord_x;
   float coord_y;

   for (int i=0; i<num_verts_per-1; i++){
      if(i>=n){
         coord_x=0.0 + (1.0*(float)i/(num_verts_per-3));
         coord_y=-coord_x + 1;  // y=-x+1
         perfil.push_back({coord_x, coord_y, 0.0});
      }
   }

   perfil.push_back({1.0, 0.0, 0.0});
   perfil.push_back({0.0,0.0,0.0});
   inicializar(perfil, num_verts_per);
}

CilindroParam::CilindroParam (const int num_verts_per, const unsigned nperfiles, double angulo){
   ponerNombre(std::string("Cilindro Paramétrico generado por revolución"));
   assert(num_verts_per >= 4);
   vector<Tupla3f> perfil;
   float coord_y;

   perfil.push_back({0.0, -1.0, 0.0}); //Cerrar el cilindro por abajo

   for (int i=0; i<num_verts_per-2; i++){
      coord_y=-1.0 + (2.0*(float)i/(num_verts_per-3));
      perfil.push_back({1.0, coord_y, 0.0});
   }

   perfil.push_back({0.0, 1.0, 0.0}); //cerrar el cilindro por arriba
   inicializar(perfil,nperfiles, angulo);

}