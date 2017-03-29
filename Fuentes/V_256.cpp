//////////////////////////////////////////////////////////////////////////////////////////////
// Ventana de pixeles en 256 colores                                                        //
// Revisión: 3 de Noviembre del 2003                                                        //
//                                                                                          //
//                                                                                          //
// Análisis y Diseño y Programación:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.dynamics.unam.edu                                                      //
// Página:   http://www.dynamics.unam.edu/acl                                               //
//                                                                                          //
//                                                                                          //
// Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
// bajo los términos de la Licencia Pública General de GNU según es                         //
// publicada por la Free Software Foundation, bien de la versión 2 de                       //
// dicha Licencia o bien (según su elección) de cualquier versión                           //
// posterior.                                                                               //
//                                                                                          //
// Este programa se distribuye con la esperanza de que sea útil, pero SIN                   //
// NINGUNA GARANTÍA, incluso sin la garantía MERCANTIL implícita o sin                      //
// garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. Véase la                        //
// Licencia Pública General de GNU para más detalles.                                       //
//                                                                                          //
// Debería haber recibido una copia de la Licencia Pública General junto                    //
// con este programa. Si no ha sido así, escriba a la Free Software                         //
// Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //
//                                                                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <string.h>

#include "V_256.hpp"

#ifndef __PROGRAMACION_BORLAND__
   #include <unistd.h>
   #define MAXPATH   1024



#else 
   #include <io.h>
   #define W_OK      06
   #define R_OK      04

   // Declaración de arreglo de colores a utilizar
   TColor Colores_48[] = {
      0x00000000,
      0x008080ff,   //255-ff, 192-c0, 160-a0, 128-80, 64-40
      0x000000ff,
      0x00404080,
      0x00000080,
      0x00000040,
      0x0080ffff,
      0x0000ffff,
      0x004080ff,
      0x000080ff,
      0x00004080,
      0x00008080,
      0x0080ff80,
      0x0000ff80,
      0x000080ff,
      0x00004000,
      0x00408080,
      0x0080ff00,
      0x0040ff00,
      0x00808000,
      0x00408000,
      0x00404000,
      0x00808080,
      0x00ffff80,
      0x00ffff00,
      0x00804000,
      0x00ff0000,
      0x00800000,
      0x00808040,
      0x00ff8000,
      0x00c08000,
      0x00ff8080,
      0x00a00000,
      0x00400000,
      0x00c0c0c0,
      0x00c080ff,
      0x00c08080,
      0x00400080,
      0x00800080,
      0x00400040,
      0x00400040,
      0x00ff80ff,
      0x00ff00ff,
      0x008000ff,
      0x00ff0080,
      0x00800040,
      0x00ffffff
   };

#endif

// Declaración de arreglo de colores a utilizar
TColor Colores_16[] = {
   clBlack,   // 0
   clGray,    // 1
   clSilver,  // 2
   clMaroon,  // 3
   clGreen,   // 4
   clOlive,   // 5
   clNavy,    // 6
   clPurple,  // 7
   clTeal,    // 8
   clRed,     // 9
   clLime,    // 10
   clYellow,  // 11
   clBlue,    // 12
   clFuchsia, // 13
   clAqua,    // 14
   clWhite    // 15
};


Ventana_256::Ventana_256(void)
{ 
   Activo = false, 
   Con_valores = false; 
   for (int i1 = 0; i1 < 256; i1 ++) Color[i1] = i1 == 0 ? 0 :(0x00000001 * 150) + (0x00000100 *  (i1+10)) + (0x00010000 * i1);
}


// Inicializa el arreglo de pixeles con el valor VAL
void Ventana_256::Inicializa(const int pix_x, const int pix_y, const unsigned char val, const Dimension_Ventana v_dim, const int n_colores)
{
   if (Activo) return;
   // Declara el arreglo para los renglones
   Arreglo = new unsigned char *[pix_x];
   int i1;
   for (i1 = 0; i1 < pix_x; i1 ++) Arreglo[i1] = new unsigned char [pix_y];
   if (!Arreglo) return;
   // Declara el arreglo para las columnas dentro de cada renglon
   Num_X = pix_x, Num_Y = pix_y;
   Activo = true;
   Cambia_dimension(v_dim, val);
   Con_valores = false;
   Asigna_colores(n_colores);
}


void Ventana_256::Asigna_colores(const int num_col)
{
   int i1;
   N_colores = num_col;
   // Soporte de 2, 16, 48 y 256 colores
#ifdef __PROGRAMACION_BORLAND__
////////////////////////////////////////////////////////////////////////////////////////////   
//#error Hacer corectamente la definición de los 256 colores, ya que no distinge los primeros colores
   for (i1 = 0; i1 < 256; i1 ++) Color[i1] = i1 == 0 ? 0 :(0x00000001 * 150) + (0x00000100 *  (i1+10)) + (0x00010000 * i1);
////////////////////////////////////////////////////////////////////////////////////////////   
   if (N_colores == 48) for (i1 = 0; i1 < 48; i1 ++) Color[i1] = Colores_48[i1];
   if (N_colores == 16) for (i1 = 0; i1 < 16; i1 ++) Color[i1] = Colores_16[i1];
   if (N_colores == 2) Color[0] = 0, Color[1] = 0x00ffffff;
   Color[255] = 0x00ffffff;

#endif   
}      


// Destruye el contenido del arreglo
void Ventana_256::Destruye(void)
{
   if (!Activo) return;
   // Destruye el arreglo
   for (int i1 = 0; i1 < Num_X; i1 ++) delete []Arreglo[i1];
   delete []Arreglo;
   Activo = false;
   Con_valores = false;
}


// Cambia la cantidad de pixeles en la ventana de pixeles
void  Ventana_256::Cambia_cantidad_pixeles(const int pix_x, const int pix_y, const unsigned char val, const Dimension_Ventana v_dim)
{
   Destruye();
   Inicializa(pix_x, pix_y, val, v_dim,N_colores);
}

// Cambia la dimension de la ventana de trabajo
void Ventana_256::Cambia_dimension(const Dimension_Ventana v_dim, const unsigned char val)
{
   // Dimensiones de la ventana de trabajo
   Dimensiones = v_dim;
   // Escala para trabajar en la ventana de pixeles
   Escala.X = Num_X / (Dimensiones.Xf - Dimensiones.Xi);
   Escala.Y = Num_Y / (Dimensiones.Yf - Dimensiones.Yi);
   Asigna_todo_array(val);
}

// Asigna linea
void Ventana_256::Asigna_linea(const int xi, const int yi, const int xf, const int yf, const unsigned char val)
{
   if (!Activo) return;

   // Se obtienen los máximos y mínimos
   xxi = xi, xxf = xf, xyi = yi, xyf = yf;
   min_x = xxi < xxf ? xxi: xxf;
   max_x = xxf > xxi ? xxf: xxi;
   min_y = xyi < xyf ? xyi: xyf;
   max_y = xyf > xyi ? xyf: xyi;

   // Se validan y ajustan los máximos y los mínimos
   if (min_x < 0) min_x = 0;
   if (max_x >= Num_X) max_x = Num_X -1;
   if (min_y < 0) min_y = 0;
   if (max_y >= Num_Y) max_y = Num_Y -1;

   if (xyi < 0 || xyi >= Num_Y) return;
   if (xyf < 0 || xyf >= Num_Y) return;

   if (xxi < 0 || xxi >= Num_X) return;
   if (xxf < 0 || xxf >= Num_X) return;

   Con_valores = true;

   // Linea horizontal
   if (xyi == xyf) {
      for (i = min_x; i <= max_x; i++) Arreglo[i][xyi] = val;
      return;
   }
   // Linea vertical
   if (xxi == xxf) {
      for (i = min_y; i <= max_y; i++) Arreglo[xxi][i] = val;
      return;
   }
   // Linea en general
//#error Revisar y mejorar el algoritmo   
   m = (xyf - xyi) / (ldouble) (xxf - xxi);
   for (inc = min_x; inc <= max_x; inc+=0.01) {
      py = (int)(m * (inc - xxf) + xyf);
      i = (int) inc;
      Arreglo[i][py] = val;
   }
}

// Asigna linea
void Ventana_256::Asigna_linea_color(const int xi, const int yi, const int xf, const int yf, const TColor col)
{
   for (ind = 0; ind < N_colores; ind++) if (Colores_16[ind] == col) break;
   if (ind > N_colores) ind = N_colores;
   Asigna_linea(xi,yi,xf,yf, ind); 
}


// Asigna a un pixel del arreglo el color indicado
void Ventana_256::Asigna_color(const int pix_x, const int pix_y, const TColor col)
{
   for (ind = 0; ind < N_colores; ind++) if (Color[ind] == col) break;
   if (ind > N_colores) ind = N_colores;
   Asigna_valor(pix_x, pix_y, ind);  
}


// Asigna un recuadro apartir del centro n pixeles
void Ventana_256::Asigna_recuadro(const int pix_x, const int pix_y, const int num, const unsigned char val)
{
   if (!Activo) return;
   if (num > 1) {
      xi = pix_x - num >= 0 ? pix_x - num : 0;
      xf = pix_x + num < Num_X ? pix_x + num : Num_X -1;
      yi = pix_y - num >= 0 ? pix_y - num : 0;
      yf = pix_y + num < Num_Y ? pix_y + num : Num_Y -1;
      for (y = yi; y <= yf; y ++) {
         for (x = xi; x <= xf; x ++) {
         Arreglo[x][y] = val;
         } 
      }
   } else Arreglo[pix_x][pix_y] = val;
   Con_valores = true;
}



// Asigna a todo el array el valor especificado
void Ventana_256::Asigna_todo_array(const unsigned char val)
{
   if (Activo) {
      for (xi1 = 0; xi1 <  Num_X; xi1++) {
         prtArreglo = &Arreglo[xi1][0];
         for (xi2 = 0; xi2 <  Num_Y; xi2++) {
            *prtArreglo = val;
            prtArreglo++;
         }
      }
   }
   if (val == 255) Con_valores = false;
   else true;
}


// Asigna linea
void Ventana_256::Asigna_linea(const ldouble xi, const ldouble yi, const ldouble xf, const ldouble yf, const unsigned char val)
{
   int p1, p2, p3, p4;
///////////////////////////////////////////////////////////////////////////////
//#error Ajustar los valores para generar una linea truncada a la ventana
   if (!Calcula_punto(xi, yi, p1, p2)) return;
   if (!Calcula_punto(xf, yf, p3, p4)) return;
///////////////////////////////////////////////////////////////////////////////
   Asigna_linea(p1, p2, p3, p4, val);
}

// Graba la ventana con el nombre dado
void Ventana_256::Graba_ventana(const char *nombre)
{
   if (!Activo) return;
   if (Con_valores) {
      FILE *ARCHIVO_TRABAJO;
      unsigned char car;
      ARCHIVO_TRABAJO = fopen(nombre,"wb");
      if (ARCHIVO_TRABAJO) {
         for (int x1 = 0; x1 <  Num_X; x1++) {
            for(int y1 = 0; y1 < Num_Y; y1++) {
               car = Arreglo[x1][y1];
               fwrite(&car,sizeof(car),1,ARCHIVO_TRABAJO);
            }
         }
         fclose(ARCHIVO_TRABAJO);
      }
   }
}


// Graba la ventana con el nombre dado
void Ventana_256::Lee_ventana(const char *nombre)
{
   if (!Activo) return;
   if (!access(nombre,R_OK)) {
      FILE *ARCHIVO_TRABAJO;
      unsigned char car;
      ARCHIVO_TRABAJO = fopen(nombre,"rb");
      if (ARCHIVO_TRABAJO) {
         for (int x1 = 0; x1 <  Num_X; x1++) {
            for(int y1 = 0; y1 < Num_Y; y1++) {
               fread(&car,sizeof(car),1,ARCHIVO_TRABAJO);
               Arreglo[x1][y1] = car;
            }
         }
         fclose(ARCHIVO_TRABAJO);
         Con_valores = true;
      }
   } 
}

// Visualiza la ventana en formato texto
void Ventana_256::Visualiza_ventana_txt(const char chr)
{
   if (!Activo) return;
   if (Con_valores) {
      for (int x1 = 0; x1 <  Num_X; x1++) {
         for(int y1 = 0; y1 < Num_Y; y1++) {
            if (Arreglo[y1][x1] != 255) printf("%c",chr);
             else printf(" ");
         }
         printf("\n");
      }
      printf("\n");
   }
}



// Calcula el color a asignar
int Ventana_256::Calcula_color_a_asignar(const int ind, const int nmi, const ldouble ajus, const bool color_unico, const bool inversion_color)
{
   int color;
   if (color_unico) {
       // El color es unico (no se repite el color)
      if (N_colores <= 2) {
         if (ind) return 1;
          else return 0;
      }
      if (N_colores > 2 && N_colores <= 16) {
// #error  Falta ajuste de color
         if (ind) {
            int color = (int) (((powl(ind,ajus) * 100.0) / (ldouble) nmi)+ 1.0);
            if (color > N_colores) color = N_colores;
            return color;
         } else return 0;
      }
      if (N_colores > 16 && N_colores <= 48) {
// #error  Falta ajuste de color
         if (ind) {
            int color = (int) (((powl(ind,ajus) * 100.0) / (ldouble) nmi)+ 1.0);
            if (color > N_colores) color = N_colores;
            return color;
         } else return 0;
      }
      if (N_colores > 48) {
            if (ind >= nmi || ind == 0) return 0;
// #error  Falta ajuste de color
// #error  Falta color unico
            
//            fact = ((ind * 100.0) / (ldouble) nmi); 
//            color  = fact;   
            fact = ((1.0 / pow((ind / (ldouble) nmi), ajus)) /  (1.0 / pow(1.0 / (ldouble) nmi, ajus)));
            color  = (int) (111 * (1.0 - fact)) + 145;   
            return color;
      }
    } else {
      // El color no es unico (se repite el color)
      if (N_colores <= 2) {
         if (ind) return 1;
          else return 0;
      }
      if (N_colores > 2 && N_colores <= 16) {
         if (ind) return ((ind%15) + 1);
          else return 0;
      }
      if (N_colores > 16 && N_colores <= 48) {
         if (ind) return ((ind%47) + 1);
          else return 0;
      }
      if (N_colores > 48) {
            if (ind >= nmi || ind == 0) return 0;
            fact = ((1.0 / pow((ind / (ldouble) nmi), ajus)) /  (1.0 / pow(1.0 / (ldouble) nmi, ajus)));
            color = (int) (111 * (1.0 - fact)) + 145;   
            return color;
      }
   }
   return 0;
}                     

