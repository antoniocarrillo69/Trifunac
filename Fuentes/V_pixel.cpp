//////////////////////////////////////////////////////////////////////////////////////////////
// Ventana de pixeles en blanco y negro                                                     //
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

#ifndef __PROGRAMACION_BORLAND__
   #include <unistd.h>
   #define MAXPATH   1024
#else 
   #include <io.h>
   #define W_OK      06
   #define R_OK      04
#endif
#include "V_pixel.hpp"


// Inicializa el arreglo de pixeles con el valor VAL
void Arreglo_pixeles::Inicializa(const int pix_x, const int pix_y, const bool val, const Dimension_Ventana v_dim)
{
   if (Activo) return;
   // Declara el arreglo para los renglones
   Arreglo = new Definicion_pixel *[pix_x];
   // Declara el arreglo para las columnas dentro de cada renglon
   for (int i1 = 0; i1 < pix_x; i1++) Arreglo[i1] = new Definicion_pixel [pix_y];
   Activo = true;
   Num_X = pix_x, Num_Y = pix_y;
   Cambia_dimension(v_dim, val);
   Con_valores = false;
}

// Destruye el contenido del arreglo
void Arreglo_pixeles::Destruye(void)
{
   if (!Activo) return;
   // Destruye el arreglo
   for (int i1 = 0; i1 < Num_X; i1++) delete []Arreglo[i1];
   delete []Arreglo;
   Activo = false;
   Con_valores = false;
}


// Cambia la cantidad de pixeles en la ventana de pixeles
void  Arreglo_pixeles::Cambia_cantidad_pixeles(const int pix_x, const int pix_y, const bool val, const Dimension_Ventana v_dim)
{
   Destruye();
   Inicializa(pix_x, pix_y, val, v_dim);
}

// Cambia la dimension de la ventana de trabajo
void Arreglo_pixeles::Cambia_dimension(const Dimension_Ventana v_dim, const bool val)
{
   // Dimensiones de la ventana de trabajo
   Dimensiones = v_dim;
   // Escala para trabajar en la ventana de pixeles
   Escala.X = (Num_X -1) / (Dimensiones.Xf - Dimensiones.Xi);
   Escala.Y = (Num_Y -1) / (Dimensiones.Yf - Dimensiones.Yi);
   Asigna_todo_array(val);
}

// Asigna linea
void Arreglo_pixeles::Asigna_linea(const int xi, const int yi, const int xf, const int yf, const bool val)
{
   if (!Activo) return;
   int min_x, max_x, min_y, max_y, xxi, xyi, xxf, xyf, py;
   ldouble m, inc;
   int i;

   xxi = xi, xxf = xf, xyi = yi, xyf = yf;
   min_x = xxi < xxf ? xxi: xxf;
   max_x = xxf > xxi ? xxf: xxi;
   min_y = xyi < xyf ? xyi: xyf;
   max_y = xyf > xyi ? xyf: xyi;
   Con_valores = true;

   // Linea vertical
   if (xxi == xxf) {
      for (i = min_y; i <= max_y; i++) if (Dentro(xi,i)) Arreglo[xi][i].pixel = val;
      return;
   }
   // Linea horizontal
   if (xyi == xyf) {
      for (i = min_x; i <= max_x; i++) if (Dentro(i,yi)) Arreglo[i][yi].pixel = val;
      return;
   }
   // Linea en general
   m = (xyf - xyi) / (ldouble) (xxf - xxi);
   for (inc = min_x; inc <= max_x; inc+=0.1) {
      py = (int)(m * (inc - xxf) + xyf);
      i = (int) inc;
      if (Dentro(i,py)) Arreglo[i][py].pixel = val;
   }
}

// Asigna linea
void Arreglo_pixeles::Asigna_linea(const ldouble xi, const ldouble yi, const ldouble xf, const ldouble yf, const bool val)
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
void Arreglo_pixeles::Graba_ventana(const char *nombre)
{
   if (!Activo) return;
   if (Con_valores) {
      FILE *ARCHIVO_TRABAJO;
      int x1, x2;
      char xcad[1280];
      Byte_pixeles pix;
      ARCHIVO_TRABAJO = fopen(nombre,"wb");
      if (ARCHIVO_TRABAJO) {
         for (x1 = 0; x1 <  Num_X; x1++) {
            for (x2 = 0; x2 < (Num_Y/8); x2++) {
               pix.pixeles.pix1 = Arreglo[x1][x2*8+0].pixel;
               pix.pixeles.pix2 = Arreglo[x1][x2*8+1].pixel;
               pix.pixeles.pix3 = Arreglo[x1][x2*8+2].pixel;
               pix.pixeles.pix4 = Arreglo[x1][x2*8+3].pixel;
               pix.pixeles.pix5 = Arreglo[x1][x2*8+4].pixel;
               pix.pixeles.pix6 = Arreglo[x1][x2*8+5].pixel;
               pix.pixeles.pix7 = Arreglo[x1][x2*8+6].pixel;
               pix.pixeles.pix8 = Arreglo[x1][x2*8+7].pixel;
               xcad[x2] = pix.byte;
            }
            fwrite(&xcad,(Num_Y/8),1,ARCHIVO_TRABAJO);
         }
         fclose(ARCHIVO_TRABAJO);
      }
   }
}


// Graba la ventana con el nombre dado
void Arreglo_pixeles::Lee_ventana(const char *nombre)
{
   if (!Activo) return;
   if (!access(nombre,R_OK)) {
      int x1, x2;
      FILE *ARCHIVO_TRABAJO;
      char xcad[1280];
      Byte_pixeles pix;
      ARCHIVO_TRABAJO = fopen(nombre,"rb");
      if (ARCHIVO_TRABAJO) {
         for (x1 = 0; x1 <  Num_X; x1++) {
            fread(&xcad,(Num_Y/8),1,ARCHIVO_TRABAJO);
            for (x2 = 0; x2 < (Num_Y/8); x2++) {
               pix.byte = xcad[x2];
               Arreglo[x1][x2*8+0].pixel = pix.pixeles.pix1;
               Arreglo[x1][x2*8+1].pixel = pix.pixeles.pix2;
               Arreglo[x1][x2*8+2].pixel = pix.pixeles.pix3;
               Arreglo[x1][x2*8+3].pixel = pix.pixeles.pix4;
               Arreglo[x1][x2*8+4].pixel = pix.pixeles.pix5;
               Arreglo[x1][x2*8+5].pixel = pix.pixeles.pix6;
               Arreglo[x1][x2*8+6].pixel = pix.pixeles.pix7;
               Arreglo[x1][x2*8+7].pixel = pix.pixeles.pix8;
            }
         }
         fclose(ARCHIVO_TRABAJO);
         Con_valores = true;
      }
   } 
}


// Visualiza la ventana en stdout como texto
void Arreglo_pixeles::Visualiza_ventana_txt(const char chr)
{
   if (!Activo) return;
   if (Con_valores) {
      
   int x1, x2, i;
   char xcad[1280];
      for (x1 = 0; x1 <  Num_X; x1++) {
         for (x2 = 0; x2 < (Num_Y/8); x2++) {
             for (i = 0; i < 8; i++) {
                 if (Arreglo[x1][x2*8+i].pixel) printf("%c",chr);
                  else printf(" ");
             } 
         }
         printf("\n");
      }
      printf("\n");
   }
}

