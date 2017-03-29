//////////////////////////////////////////////////////////////////////////////////////////////
// Base de la Ventana de graficación                                                        //
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



#include "Vent_Graf_Base.hpp"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#ifdef __PROGRAMACION_BORLAND__
#include <dir.h>
#else
#include <unistd.h>
#endif



/////////////////////////////////////////////////////////////////////
//                   Ventana de Graficación                        //
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////
// Clase Base Ventana Graficacion                          //
/////////////////////////////////////////////////////////////

// Inicializa la clase
void Base_Ventana_Graficacion::Inicializa(void)
{
   // Inicializa las variables que contendran los nombres de los ejes
   Nombre_eje_X = NULL;
   Nombre_eje_Y = NULL;
   Nombre_eje_Z = NULL;
   Establece_nombre_ejes("X","Y","Z");
   // Fija la posicion dentro de los ejes (real)
   Coordenadas_reales.x = Coordenadas_reales.y = Coordenadas_reales.z = 0.0;
   // Fija la dimenciones de los ejes (real)
   Dim_vtn.Xi = Dim_vtn.Yi = Dim_vtn.Zi = -10.0;
   Dim_vtn.Xf = Dim_vtn.Yf = Dim_vtn.Zf = 10.0;
   // Indica que se visualizara el cursor
   Visualiza_cursor = false;
   // Indica que se visualizaran los nombre de los ejes
   Visualiza_nombre_eje = true;
   // Inicialización del arreglo de pixeles
   Pix = new Ventana_256;
#ifndef __PROGRAMACION_BORLAND__
   Numero_pixeles_ventana = 80;
   Pix->Inicializa(Numero_pixeles_ventana,Numero_pixeles_ventana, 255, Dim_vtn,NUMERO_COLORES_16);
#else
   Numero_pixeles_ventana = 1024;
   Pix->Inicializa(Numero_pixeles_ventana,Numero_pixeles_ventana, 255, Dim_vtn,NUMERO_COLORES_48);
#endif
   // inicializa las coordenadas dentro de la ventana
   Pos_cursor.x = 0, Pos_cursor.y = 0;
// Definicion de Colores
   Color_Eje_X = clRed;                       // Eje X
   Color_Eje_Y = clGreen;                     // Eje Y
   Color_Eje_Z = clBlue;                      // Eje Z
   Color_cursor = clFuchsia;                  // Cursor

#ifndef __PROGRAMACION_BORLAND__
   Color_fondo = clWhite;                     // Color de Fondo
   Escala.X = Numero_pixeles_ventana / (ldouble) Numero_pixeles_ventana;
   Escala.Y = Numero_pixeles_ventana / (ldouble) Numero_pixeles_ventana;
#else
   Color_fondo = 0x00ffffff;                  // Color de Fondo
   Escala.X = PtrVent->Width / (ldouble) Numero_pixeles_ventana;
   Escala.Y = PtrVent->Height / (ldouble) Numero_pixeles_ventana;
#endif
   EscalaReal.x = Numero_pixeles_ventana / (Dim_vtn.Xf - Dim_vtn.Xi);
   EscalaReal.y = Numero_pixeles_ventana / (Dim_vtn.Yf - Dim_vtn.Yi);
   EscalaReal.z = Numero_pixeles_ventana / (Dim_vtn.Zf - Dim_vtn.Zi);
   // Manipulador para grabar datos a un archivo
   MD = NULL;
}


// Muestra texto en la ventana en la posición (X,Y)
void Base_Ventana_Graficacion::Muestra_texto_ventana(const int x, const int y, const char *txt1, const char *txt2)
{
   char *xcad;
   int lg = strlen(txt1) + strlen(txt2) + 1;
   xcad = Asigna_puntero(lg);
   strcpy(xcad,txt1);
   strcat(xcad,txt2);
#ifdef __PROGRAMACION_BORLAND__
      PtrVent->Canvas->TextOut(x, y,xcad);
#endif
   delete xcad;
}

// Revisa si la cordenada esta dentro de la ventana
int Base_Ventana_Graficacion::Dentro_ventana(const C_3D aux)
{
   if (Tipo_ventana == EJES_COORDENADAS_POLARES) {
      if ((aux.x * cosl(aux.y)) < Dim_vtn.Xi || (aux.x * cosl(aux.y)) > Dim_vtn.Xf) return 0;
      if ((aux.x * sinl(aux.y)) < Dim_vtn.Yi || (aux.x * sinl(aux.y)) > Dim_vtn.Yf) return 0;
   } else {
      if (Tipo_ventana == EJES_COORDENADOS_2D ||Tipo_ventana == EJES_COORDENADOS_2DM || Tipo_ventana == EJES_COORDENADOS_3D) {
          // No verifica si esta dentro del area de trabajo
          return 1;
       } else {
         if (aux.x < Dim_vtn.Xi || aux.x > Dim_vtn.Xf) return 0;
         if (aux.y < Dim_vtn.Yi || aux.y > Dim_vtn.Yf) return 0;
         if (aux.z < Dim_vtn.Zi || aux.z > Dim_vtn.Zf) return 0;
      }
   }
   return 1;
}


// Grafica el contenido de las ventanas de pixeles
void Base_Ventana_Graficacion::Grafica_ventana(void)
{
   unsigned int x, y, i;

   if (!Pix->Ventana_activa()) return;
   Limpiar_fondo();
   // Calcula la escala de la ventana de visualización con respecto a la ventana de pixeles
#ifdef __PROGRAMACION_BORLAND__
   Escala.X = PtrVent->Width / (ldouble) Numero_pixeles_ventana;
   Escala.Y = PtrVent->Height / (ldouble) Numero_pixeles_ventana;
   for (y = 0; y < Numero_pixeles_ventana; y++) {
       for (x = 0; x < Numero_pixeles_ventana; x++) {
           i = (int) Pix->Retorna_valor(x,y);
           if (i!= 255) PtrVent->Canvas->Pixels[x * Escala.X][y * Escala.Y] = Pix->Retorna_color(i);
       }
   }
#endif
}

// Grafica una región de la ventana de pixeles
void Base_Ventana_Graficacion::Grafica_region_ventana(const int xx, const int xy, const int tm)
{
   unsigned int x, y;
   int posX, posY;
   int i;
#ifdef __PROGRAMACION_BORLAND__
   Escala.X = PtrVent->Width / (ldouble) Numero_pixeles_ventana;
   Escala.Y = PtrVent->Height / (ldouble) Numero_pixeles_ventana;
   for (y = 0; y < Numero_pixeles_ventana; y++) {
       posY = y * Escala.Y;
       if (posY <  xy) continue;
       for (x = 0; x < Numero_pixeles_ventana; x++) {
           posX = x * Escala.X;
           if (posX < xx) continue;
           i = (int) Pix->Retorna_valor(x, y);
           if (i != 255) PtrVent->Canvas->Pixels[posX][posY] = Pix->Retorna_color(i);
           if(posX >= (xx+tm)) break;
       }
       if (posY >= (xy+tm)) break;
   }
#endif
}



// Limpia la ventana de trabajo
void Base_Ventana_Graficacion::Limpiar(void)
{
   Limpia_todos_arreglos();
   Limpiar_fondo();
}

// Limpia el fondo de la ventana
void Base_Ventana_Graficacion::Limpiar_fondo(void)
{
#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pen->Color = Color_fondo;
   PtrVent->Canvas->Brush->Color = Color_fondo;
   PtrVent->Canvas->Rectangle(0, 0, PtrVent->Width, PtrVent->Height);
#endif
}

// Establece el nombre de los ejes coordenado
void Base_Ventana_Graficacion::Establece_nombre_ejes(const char *eje_x, const char *eje_y, const char *eje_z)
{
   if(Nombre_eje_X) delete [] Nombre_eje_X;
   if(Nombre_eje_Y) delete [] Nombre_eje_Y;
   if(Nombre_eje_Z) delete [] Nombre_eje_Z;
   Nombre_eje_X = Asigna_puntero(eje_x);
   Nombre_eje_Y = Asigna_puntero(eje_y);
   Nombre_eje_Z = Asigna_puntero(eje_z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// El contenido de estas dos rutinas ponerlo en donde se requiera para optimizar velocidad

/*
// Dibuja un punto en la ventana de trabajo
void Base_Ventana_Graficacion::Dibuja_punto_ventana(const int x, const int y, const TColor color)
{
#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pixels[x * Escala.X][y * Escala.Y] = color;
#endif
   if (Pix->Dentro(x,y)) Pix->Asigna_color(x,y,color);

}
*/

/*
// Dibuja un punto en la ventana de trabajo
void Base_Ventana_Graficacion::Dibuja_linea_ventana(const int x1, const int y1, const int x2, const int y2, const TColor color)
{
#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pen->Color = color;
   PtrVent->Canvas->MoveTo(x1 * Escala.X,y1 * Escala.Y);
   PtrVent->Canvas->LineTo(x2 * Escala.X,y2 * Escala.Y);
#endif
   Pix->Asigna_linea_color(x1,y1,x2,y2,color);
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////




// Posición deltro de la ventana 2D
void Base_Ventana_Graficacion::Posicion_ventana_2D(const C_3D aux, int &x, int &y)
{
   x = (int) ((((aux.x - Dim_vtn.Xi) * EscalaReal.x) * Factor + (Numero_pixeles_ventana * ((1.0 - Factor)/2.0)))* Escala.X);
   y = (int) (((Numero_pixeles_ventana - (((aux.y - Dim_vtn.Yi) * EscalaReal.y) + 1.0)) * Factor + (Numero_pixeles_ventana * ((1.0 - Factor)/2.0))) * Escala.Y);
}



// Dibuja un punto dentro de la ventana
void Base_Ventana_Graficacion::Dibuja_punto_ventana_2D(const C_3D aux, const TColor color)
{
   px = (int) (((aux.x - Dim_vtn.Xi) * EscalaReal.x) * Factor + (Numero_pixeles_ventana * ((1.0 - Factor)/2.0)));
   py = (int) ((Numero_pixeles_ventana - (((aux.y - Dim_vtn.Yi) * EscalaReal.y) + 1.0)) * Factor + (Numero_pixeles_ventana * ((1.0 - Factor)/2.0)));

#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pixels[px * Escala.X][py * Escala.Y] = color;
#endif
   if (Pix->Dentro(px,py)) Pix->Asigna_color(px,py,color);
}

// Dibuja una linea dentro de la ventana
void Base_Ventana_Graficacion::Dibuja_linea_ventana_2D(const C_3D aux1, const C_3D aux2, const TColor color)
{
   px = (int) (((aux1.x - Dim_vtn.Xi) * EscalaReal.x) * Factor + (Numero_pixeles_ventana * ((1.0 - Factor)/2.0)));
   py = (int) ((Numero_pixeles_ventana - (((aux1.y - Dim_vtn.Yi) * EscalaReal.y) + 1.0)) * Factor + (Numero_pixeles_ventana * ((1.0 - Factor)/2.0)));
   px1 = (int) (((aux2.x - Dim_vtn.Xi) * EscalaReal.x) * Factor + (Numero_pixeles_ventana * ((1.0 - Factor)/2.0)));
   py1 = (int) ((Numero_pixeles_ventana - (((aux2.y - Dim_vtn.Yi) * EscalaReal.y) + 1.0)) * Factor + (Numero_pixeles_ventana * ((1.0 - Factor)/2.0)));

#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pen->Color = color;
   PtrVent->Canvas->MoveTo(px * Escala.X, py * Escala.Y);
   PtrVent->Canvas->LineTo(px1 * Escala.X, py1 * Escala.Y);
#endif
   Pix->Asigna_linea_color(px,py,px1,py1,color);
}

// Posición deltro de la ventana 3D
void Base_Ventana_Graficacion::Posicion_ventana_3D(const C_3D aux, int &x, int &y)
{
   Posicion_3D(aux,px,py);
   x = (int) (px * Escala.X);
   y = (int) (py * Escala.Y);
}

// Dibuja un punto dentro de la ventana
void Base_Ventana_Graficacion::Dibuja_punto_ventana_3D(const C_3D aux, const TColor color)
{
   Posicion_3D(aux,px,py);

#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pixels[px * Escala.X][py * Escala.Y] = color;
#endif
   if (Pix->Dentro(px,py)) Pix->Asigna_color(px,py,color);
}

// Dibuja una linea dentro de la ventana
void Base_Ventana_Graficacion::Dibuja_linea_ventana_3D(const C_3D aux1, const C_3D aux2, const TColor color)
{
   Posicion_3D(aux1,px,py);
   Posicion_3D(aux2,px1,py1);

#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pen->Color = color;
   PtrVent->Canvas->MoveTo(px * Escala.X,py * Escala.Y);
   PtrVent->Canvas->LineTo(px1 * Escala.X,py1 * Escala.Y);
#endif
   Pix->Asigna_linea_color(px,py,px1,py1,color);
}

// Graba datos graficados en el archivo de datos indicado
void Base_Ventana_Graficacion::Graba_datos(const char *arc)
{
   if (MD) Cierra_archivo_datos(); 
   MD = new Manipulador_archivos();
   MD->Parametros(arc, GRABA_ARCHIVO, 1000, "MVGrafica");
}


// Cierra el archivo de datos graficados
void Base_Ventana_Graficacion::Cierra_archivo_datos(void)
{
   if (MD) MD->Cerrar();
   delete MD;
   MD = NULL;  
}
