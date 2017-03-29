// Clase que crea y controla una ventana de graficacion para visualizar en formate texto

#include "MVGrafica.hpp"
#include <stdio.h>



// Visualiza la ventana en formato TXT
void MVGrafica::Visualiza(void)
{
   Control_Visualizacion::Grafica();
   Pix->Visualiza_ventana_txt(Chr);
   if (Tvg == EJES_COORDENADOS_3D || Tvg == EJES_CAJA_3D || Tvg == EJES_CAJA_3DM)
   {
#ifdef __Double__
            printf("Dimensiones Xi=%1.6lf, Xf=%1.6lf, Yi=%1.6lf, Yf=%1.6lf, Zi=%1.6lf, Zf=%1.6lf\n", Vdim.Xi,Vdim.Xf,Vdim.Yi,Vdim.Yf,Vdim.Zi,Vdim.Zf);
#else
            printf("Dimensiones Xi=%1.6Lf, Xf=%1.6Lf, Yi=%1.6Lf, Yf=%1.6Lf, Zi=%1.6Lf, Zf=%1.6Lf\n", Vdim.Xi,Vdim.Xf,Vdim.Yi,Vdim.Yf,Vdim.Zi,Vdim.Zf);
#endif
   } else {
#ifdef __Double__
      printf("Dimensiones Xi=%1.6lf, Xf=%1.6lf, Yi=%1.6lf, Yf=%1.6lf\n", Vdim.Xi,Vdim.Xf,Vdim.Yi,Vdim.Yf);
#else
      printf("Dimensiones Xi=%1.6Lf, Xf=%1.6Lf, Yi=%1.6Lf, Yf=%1.6Lf\n", Vdim.Xi,Vdim.Xf,Vdim.Yi,Vdim.Yf);
#endif
   }
}

// Ajusta la dimension de la ventana con respecto a los valores de los Arreglos X vs Y
void MVGrafica::Ajusta_dimensiones(ldouble *x, ldouble *y, const int n)
{
   Dimension_Ventana v_dim;
   Busca_max_min( x, n, v_dim.Xi, v_dim.Xf);
   Busca_max_min( y, n, v_dim.Yi, v_dim.Yf);
   // Ajusta para que los extremos sean visibles en ejes coordenados con marco
   if (Tvg == EJES_COORDENADOS_2DM || Tvg == EJES_CAJA_2D)
   {
      ldouble xinc = (v_dim.Xf - v_dim.Xi) / 30.0;
      ldouble yinc = (v_dim.Yf - v_dim.Yi) / 30.0;
      v_dim.Xi -= xinc;
      v_dim.Xf += xinc;
      v_dim.Yi -= yinc;
      v_dim.Yf += yinc;
   }
   v_dim.Zi = Vdim.Zi;
   v_dim.Zf = Vdim.Zf;
   Dimensiones(v_dim);
}


// Ajusta la dimension de la ventana con respecto a los valores de los Arreglos X vs Y y Z
void MVGrafica::Ajusta_dimensiones(ldouble *x, ldouble *y, ldouble *z, const int n)
{
   Dimension_Ventana v_dim;
   Busca_max_min( x, n, v_dim.Xi, v_dim.Xf);
   Busca_max_min( y, n, v_dim.Yi, v_dim.Yf);
   Busca_max_min( z, n, v_dim.Zi, v_dim.Zf);
   // Ajusta para que los extremos sean visibles en ejes coordenados con marco
   if (Tvg == EJES_COORDENADOS_2DM || Tvg == EJES_CAJA_2D)
   {
      ldouble xinc = (v_dim.Xf - v_dim.Xi) / 30.0;
      ldouble yinc = (v_dim.Yf - v_dim.Yi) / 30.0;
      ldouble zinc = (v_dim.Zf - v_dim.Zi) / 30.0;
      v_dim.Xi -= xinc;
      v_dim.Xf += xinc;
      v_dim.Yi -= yinc;
      v_dim.Yf += yinc;
      v_dim.Zi += zinc;
      v_dim.Zf += zinc;
   }
   Dimensiones(v_dim);
}





