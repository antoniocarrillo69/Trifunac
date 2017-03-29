#ifndef __MVGrafica__
#define __MVGrafica__


#include "Vent_Graf_Controlador.hpp"




/*  Tipos de ventana activos
#define VENTANA_2D                    0
#define EJES_COORDENADOS_2D           1
#define EJES_COORDENADOS_2DM          2
#define EJES_COORDENADOS_3D           3
#define EJES_CAJA_2D                  4
#define EJES_CAJA_3D                  5
#define EJES_COORDENADAS_POLARES      6
#define EJES_CAJA_3DM                 7
*/


// Clase que crea y controla una ventana de graficacion para visualizar en formate texto
class MVGrafica:  virtual public Control_Visualizacion
{
   private:

      int  Pixeles;
      int  Tvg;
      char Chr;

      Dimension_Ventana Vdim;

   public:
           // Constructor de la clase
           // PIX   --> Número de pixeles en la ventana
           // TVG   --> Tipo de ventana gráfica (0-7)
           // CHR   --> Caracter de graficación
           // V_DIM --> Dimensiones de la ventana
           MVGrafica(int pix, int tvg, char chr, Dimension_Ventana v_dim)
           {
              Pixeles = pix;
              Tvg = tvg;
              Chr = chr;

              Inicializa();
              Tipo_ventana_activa(Tvg);

              Base_Ventana_Graficacion::Numero_pixeles_ventana = Pixeles;
              Pix->Cambia_cantidad_pixeles(Pixeles, Pixeles, 255, v_dim);
              Dimensiones(v_dim);
              Dibuja();
           }

           // Constructor de la clase
           // PIX   --> Número de pixeles en la ventana
           // TVG   --> Tipo de ventana gráfica (0-7)
           // CHR   --> Caracter de graficación
           MVGrafica(int pix, int tvg, char chr)
           {
              Pixeles = pix;
              Tvg = tvg;
              Chr = chr;

              Inicializa();
              Tipo_ventana_activa(Tvg);
              
              Dimension_Ventana v_dim;
              Retorna_Dimensiones(v_dim);
              Base_Ventana_Graficacion::Numero_pixeles_ventana = Pixeles;
              Pix->Cambia_cantidad_pixeles(Pixeles, Pixeles, 255, v_dim);
              Dimensiones(v_dim);
              Dibuja();
           }

           // Destructor de la clase
          ~MVGrafica()
           {
              Cierra_archivo_datos();
              Destruye();
           }

           // Visualiza la ventana en formato TXT
      void Visualiza(void);


           // Ajusta la dimension de la ventana a V_DIM
      void Dimensiones(Dimension_Ventana v_dim)
           {
              Vdim = v_dim;
              Establece_Dimensiones(Vdim);
           }

           // Ajusta la dimension de la ventana con respecto a los valores de los Arreglos X vs Y
      void Ajusta_dimensiones(ldouble *x, ldouble *y, int n);

           // Ajusta la dimension de la ventana con respecto a los valores de los Arreglos X vs Y y Z
      void Ajusta_dimensiones(ldouble *x, ldouble *y, ldouble *z, int n);








      

};

#endif


/*
   Modo de uso

   // Declaración de la clase
   MVGrafica gf(80,EJES_CAJA_2D,'*');
   // Datos a graficar
   ldouble x[10], y[10];
   x[0]=-1.0; x[1]=0.0,x[2]=2.0;
   y[0]=-1.0; y[1]=1.0,y[2]=2.0;
   // Obtiene las dimensiones a partir de los datos
   gf.Ajusta_dimensiones(x,y,3);
   // Grafica datos
   gf.Grafica(x,y,3);
   // Visualiza la ventana en modo texto
   gf.Visualiza();


   Otro modo de uso

   // Se indican las dimensiones de la ventana
   Dimension_Ventana vdim;
   vdim.Xi =  0.0, vdim.Yi = -1.0, vdim.Zi = -1.0, vdim.Xf =  10.0, vdim.Yf =  1.0, vdim.Zf =  1.0;
   // Declaración de la clase
   MVGrafica gf(80,EJES_CAJA_2D,'*',vdim);
   // Datos a graficar
   gf.Grafica(0.0,0.0);
   // Visualiza la ventana en modo texto
   gf.Visualiza();



*/


/*
   Adiciones
      Revisar que opere todo 3D
      Graficar (C2D)
      Graficar (C3D)
      Grabar del formato txt a un archivo txt
      Poder poner Titulos y nombre de ejes coordenados
      Ver como meter dos renglones en uno usando puntos
      Graficar con lineas al vuelo de los puntos
*/
