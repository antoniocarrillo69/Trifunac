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



#ifndef __V_256_HPP__
#define __V_256_HPP__

#include <math.h>
#include "Definiciones.hpp"

#ifndef __PROGRAMACION_BORLAND__
   #define clBlack     0
   #define clGray      1 
   #define clSilver    2
   #define clMaroon    3
   #define clGreen     4
   #define clOlive     5
   #define clNavy      6
   #define clPurple    7
   #define clTeal      8
   #define clRed       9
   #define clLime      10
   #define clYellow    11
   #define clBlue      12
   #define clFuchsia   13
   #define clAqua      14
   #define clWhite     15

#else 
   #include <Graphics.hpp>
#endif

#define NUMERO_COLORES_2     2
#define NUMERO_COLORES_16   16 
#define NUMERO_COLORES_48   48
#define NUMERO_COLORES_255 255 




// Clase Ventana de 256 colores que manipula y controla un array de pixeles
class Ventana_256
{
   private:
      int                Color[256];    // Almacena el color correspondiente
      int                N_colores;     // Indica el numero de colores activo
      bool               Activo;        // Indica si esta activo el objeto
      int                Num_Y;         // Longitud de la matriz en Y
      int                Num_X;         // Longitud de la matrix en X
      C_2D               Escala;        // Escala usada dentro de la ventana de pixeles
      Dimension_Ventana  Dimensiones;   // Dimensiones de la ventana de trabajo
      int                pxx, pyx;      // Valores temporales
      int                p_x, p_y;
      int                xi1, xi2;
      int                xi, xf, yi, yf, x, y, ind;
      bool               st;
      int min_x, max_x, min_y, max_y, xxi, xyi, xxf, xyf, py;
      int i;
      ldouble m, inc;
      
      bool               Con_valores;   // Indica si ya tiene datos

      unsigned char    **Arreglo;       // Puntero al arreglo de pixeles
      unsigned char     *prtArreglo;    // Puntero al arreglo de pixeles

      ldouble        fact; // Valores temporales

      
   public:
                     // Constructor de la clase
                     Ventana_256(void);

                     // Destructor de la clase
                    ~Ventana_256(void)
                     {Destruye();}

                     // Inicializa la clase
               void  Inicializa(const int pix_x, const int pix_y, const unsigned char val, const Dimension_Ventana v_dim, const int n_colores);

                     // Destruye el contenido del arreglo
               void  Destruye(void);

                     // Calcula la posición de un punto dentro de la ventana de pixeles
               bool  Calcula_punto(const ldouble x, const ldouble y, int &px, int &py)
                     {
                        st = true;
                        if ((y >= Dimensiones.Yi && y <= Dimensiones.Yf) && (x >= Dimensiones.Xi && x <= Dimensiones.Xf)) {
                           py = (int)(Num_Y - (((y - Dimensiones.Yi) * Escala.Y) + 1.0));
                           px = (int)((x - Dimensiones.Xi) * Escala.X);
                        } else st = false;
                        return st;
                     }


                     // Asigna a un pixel del arreglo el valor indicado
               void  Asigna_valor(const int pix_x, const int pix_y, const unsigned char val)
                     {
                        if (Activo && pix_x >= 0 && pix_x < Num_X && pix_y >= 0 && pix_y < Num_Y) Arreglo[pix_x][pix_y] = val;
                        Con_valores = true;
                     }

                     // Asigna a un pixel del arreglo el color indicado
               void  Asigna_color(const int pix_x, const int pix_y, const TColor col);
                     
                     // Asigna a un pixel del arreglo el valor indicado
               void  Asigna_valor(const ldouble x, const ldouble y, const unsigned char val)
                     {
                        if (Calcula_punto(x, y, pxx, pyx)) 
                        if (pxx >= 0 && pxx < Num_X && pyx >= 0 && pyx < Num_Y) Arreglo[pxx][pyx] = val;
                     }

                     // Retorna el valor del pixel indicado dentro del arreglo
      unsigned char  Retorna_valor(const int pix_x, const int pix_y) const
                     {
                        if (pix_x >= 0 && pix_x < Num_X && pix_y >= 0 && pix_y < Num_Y) return (Arreglo[pix_x][pix_y]);
                        return (Arreglo[pix_x][pix_y]);
                     }

                     // Asigna a todo el array el valor especificado
               void  Asigna_todo_array(const unsigned char val);

                     // Asigna linea
               void  Asigna_linea(const int xi, const int yi, const int xf, const int yf, const unsigned char val);
                     // Asigna linea
               void  Asigna_linea_color(const int xi, const int yi, const int xf, const int yf, const TColor col);
                     // Asigna linea
               void  Asigna_linea(const ldouble xi, const ldouble yi, const ldouble xf, const ldouble yf, const unsigned char val);

                     // Asigna un recuadro apartir del centro n pixeles
               void  Asigna_recuadro(const int pix_x, const int pix_y, const int num, const unsigned char val);

                     // Asigna un recuadro apartir del centro n pixeles
               void  Asigna_recuadro(const ldouble x, const ldouble y, const int num, const unsigned char val)
                     {
                        if (Calcula_punto(x, y, p_x, p_y)) Asigna_recuadro(p_x, p_y, num, val);
                     }
                     
                     // Cambia la dimension del al ventana
               void  Cambia_dimension(const Dimension_Ventana v_dim, const unsigned char val);

                     // Cambia la cantidad de pixeles en la ventana
               void  Cambia_cantidad_pixeles(const int pix_x, const int pix_y, const unsigned char val, const Dimension_Ventana v_dim);

                     // Graba la ventana con el nombre dado
               void  Graba_ventana(const char *nombre);

                     // Lee la ventana con el nombre dado
               void  Lee_ventana(const char *nombre);

                     // Visualiza la ventana en formato texto
               void  Visualiza_ventana_txt(const char chr);

                     // Retorna si tiene datos
               bool  Tiene_datos(void)
                     {
                        return Con_valores;
                     }
                     // Revisa si el punto esta dentro de la ventana
               bool  Dentro(const int pix_x, const int pix_y)
                     {
                        if (Activo && pix_x >= 0 && pix_x < Num_X && pix_y >= 0 && pix_y < Num_Y) return true;
                        return false;
                     }   
                     // Retorna el color correspondiente al indice

              TColor Retorna_color(const int i)
                     {
                        if (i < 256) return (Color[i]);
                        return (Color[255]);
                     }

                     // Retorna el valor del pixel indicado dentro del arreglo
              TColor Retorna_color(const int pix_x, const int pix_y) const
                     {
                        if (pix_x >= 0 && pix_x < Num_X && pix_y >= 0 && pix_y < Num_Y) return (Color[Arreglo[pix_x][pix_y]]);
                        return (Color[Arreglo[pix_x][pix_y]]);
                     }

                     
                     // Asigna el color COL al indice IND
               void  Asigna_color(const int col, const int ind)
                     {
                        if (ind < 256) Color[ind] = col;
                     }       

                     // Asigna los colores a la paleta de 256 colores
               void  Asigna_colores(const int num_col);

                     // Calcula el color a asignar
               int   Calcula_color_a_asignar(const int ind, const int nmi, const ldouble ajus, bool color_unico, bool inversion_color);

               bool  Ventana_activa(void)
                     {
                        return (Activo);
                     }      
};


// Notas:
//   (1) El array empieza en cero para los pixeles Y y X
//   (2) El numero maximo de elemetos depende de la memoria de la maquina

#endif




