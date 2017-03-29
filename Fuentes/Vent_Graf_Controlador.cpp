//////////////////////////////////////////////////////////////////////////////////////////////
// Controlador de la ventana de graficación                                                 //
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


#include "Vent_Graf_Controlador.hpp"
#ifndef __PROGRAMACION_BORLAND__
   #include <unistd.h>
   #define MAXPATH   1024
#else
   #include <io.h>
#endif



/////////////////////////////////////////////////////////////
// Clase Control de Visualización                          //
/////////////////////////////////////////////////////////////

void Control_Visualizacion::Inicializa(void)
{
   // Fija el tipo de ventana a trabajar
   Tipo_ventana = EJES_COORDENADOS_3D;
   // Que se grafiquen datos como lineas
   Lin = 1;
   // Inicializa la clase base
   Base_Ventana_Graficacion::Inicializa();
   Ventana_2D::Inicializa();
   Ventana_Ejes_2D::Inicializa();
   Ventana_Ejes_2DM::Inicializa();
   Ventana_Caja_2D::Inicializa();
   Ventana_Caja_3D::Inicializa();
   Ventana_Ejes_3D::Inicializa();
   Ventana_Caja_3DM::Inicializa();
   Ventana_Coordenadas_Polares::Inicializa();
}

// Dibuja la ventana
void Control_Visualizacion::Dibuja(void)
{
   switch (Tipo_ventana) {
      case VENTANA_2D:
         Ventana_2D::Dibuja();
         break;
      case EJES_COORDENADOS_3D:
         Ventana_Ejes_3D::Dibuja();
         break;
      case EJES_COORDENADOS_2D:
         Ventana_Ejes_2D::Dibuja();
         break;
      case EJES_COORDENADOS_2DM:
         Ventana_Ejes_2DM::Dibuja();
         break;
      case EJES_CAJA_3D:
         Ventana_Caja_3D::Dibuja();
         break;
      case EJES_CAJA_3DM:
         Ventana_Caja_3DM::Dibuja();
         break;
      case EJES_CAJA_2D:
         Ventana_Caja_2D::Dibuja();
         break;
      case EJES_COORDENADAS_POLARES:
         Ventana_Coordenadas_Polares::Dibuja();
         break;
   }
}

// Dibuja un punto haciendo caso del escenario
void Control_Visualizacion::Dibuja_punto(const C_3D aux, const TColor col)
{
   switch (Tipo_ventana) {
      case VENTANA_2D:
         Ventana_2D::Dibuja_punto_2D(aux, col);
         break;
      case EJES_COORDENADOS_3D:
         Dibuja_punto_ventana_3D(aux, col);
         break;
      case EJES_COORDENADOS_2D:
      case EJES_COORDENADOS_2DM:
         Dibuja_punto_ventana_2D(aux, col);
         break;
      case EJES_CAJA_3DM:
      case EJES_CAJA_3D:
         if (!Dentro_ventana(aux)) return;
         Dibuja_punto_ventana_3D(aux, col);
         break;
      case EJES_CAJA_2D:
         if (!Dentro_ventana(aux)) return;
         Dibuja_punto_ventana_2D(aux, col);
         break;
      case EJES_COORDENADAS_POLARES:
         if (!Dentro_ventana(aux)) return;
         Dibuja_punto_ventana_coordenadas_polares(aux, col);
         break;
   }
}


// Dibuja un punto haciendo caso del escenario
void Control_Visualizacion::Dibuja_linea(const C_3D aux1, const C_3D aux2, const TColor col)
{
   if (!Dentro_ventana(aux1)) return;
   if (!Dentro_ventana(aux2)) return;
   switch (Tipo_ventana) {
      case VENTANA_2D:
         Ventana_2D::Dibuja_linea_2D(aux1, aux2, col);
         break;
      case EJES_COORDENADOS_3D:
         Dibuja_linea_ventana_3D(aux1, aux2, col);
         break;
      case EJES_COORDENADOS_2D:
      case EJES_COORDENADOS_2DM:
         Dibuja_linea_ventana_2D(aux1, aux2, col);
         break;
      case EJES_CAJA_3DM:
      case EJES_CAJA_3D:
         if (!Dentro_ventana(aux1)) return;
         if (!Dentro_ventana(aux2)) return;
         Dibuja_linea_ventana_3D(aux1, aux2, col);
         break;
      case EJES_CAJA_2D:
         if (!Dentro_ventana(aux1)) return;
         if (!Dentro_ventana(aux2)) return;
         Dibuja_linea_ventana_2D(aux1, aux2, col);
         break;
      case EJES_COORDENADAS_POLARES:
         if (!Dentro_ventana(aux1)) return;
         if (!Dentro_ventana(aux2)) return;
         Dibuja_linea_ventana_coordenadas_polares(aux1, aux2, col);
         break;
   }
}


// Grafica el contenido de las ventanas de pixeles
void Control_Visualizacion::Grafica(void)
{
   Grafica_ventana();
   Dibuja();
   Poner_cursor();
}

// Muestra el cursor en los ejes coordenados
void Control_Visualizacion::Poner_cursor(void)
{
#ifdef __PROGRAMACION_BORLAND__
   if (!Visualiza_cursor) return;
   int x, y;
   // Quito el cursor anterior
   PtrVent->Canvas->Pen->Color = Color_fondo;
   PtrVent->Canvas->MoveTo(Pos_cursor.x,Pos_cursor.y);
   PtrVent->Canvas->LineTo(Pos_cursor.x+10,Pos_cursor.y);
   PtrVent->Canvas->MoveTo(Pos_cursor.x,Pos_cursor.y);
   PtrVent->Canvas->LineTo(Pos_cursor.x,Pos_cursor.y+10);
   PtrVent->Canvas->MoveTo(Pos_cursor.x,Pos_cursor.y);
   PtrVent->Canvas->LineTo(Pos_cursor.x+14,Pos_cursor.y+14);
   // Grafico el contenido de la region donde estaba el cursor
   Grafica_region_ventana(Pos_cursor.x, Pos_cursor.y, 15);
   // Redibujo los ejes coordenados
   switch (Tipo_ventana) {
      case VENTANA_2D:
         Ventana_2D::Posicion_ventana(Coordenadas_reales,x,y);
         Ventana_2D::Dibuja();
         break;
      case EJES_COORDENADOS_3D:
         Posicion_ventana_3D(Coordenadas_reales,x,y);
         Ventana_Ejes_3D::Dibuja();
         break;
      case EJES_COORDENADOS_2D:
         Posicion_ventana_2D(Coordenadas_reales,x,y);
         Ventana_Ejes_2D::Dibuja();
         break;
      case EJES_COORDENADOS_2DM:
         Posicion_ventana_2D(Coordenadas_reales,x,y);
         Ventana_Ejes_2DM::Dibuja();
         break;
      case EJES_CAJA_3DM:
         Posicion_ventana_3D(Coordenadas_reales,x,y);
         Ventana_Caja_3DM::Dibuja();
         break;
      case EJES_CAJA_3D:
         Posicion_ventana_3D(Coordenadas_reales,x,y);
         Ventana_Caja_3D::Dibuja();
         break;
      case EJES_CAJA_2D:
         Posicion_ventana_2D(Coordenadas_reales,x,y);
         Ventana_Caja_2D::Dibuja();
         break;
      case EJES_COORDENADAS_POLARES:
         Ventana_Coordenadas_Polares::Posicion_ventana(Coordenadas_reales,x,y);
         Ventana_Coordenadas_Polares::Dibuja();
         break;
   }
   // Visualizo el cursor en la nueva posición
   Pos_cursor.x = x, Pos_cursor.y = y;
   PtrVent->Canvas->Pen->Color = Color_cursor;
   PtrVent->Canvas->MoveTo(x,y);
   PtrVent->Canvas->LineTo(x+10,y);
   PtrVent->Canvas->MoveTo(x,y);
   PtrVent->Canvas->LineTo(x,y+10);
   PtrVent->Canvas->MoveTo(x,y);
   PtrVent->Canvas->LineTo(x+14,y+14);
#endif
}


// Graba la ventana de pixeles
void Control_Visualizacion::Graba_ventana_pixeles(const char *nombre)
{
   Pix->Graba_ventana(nombre);
}

// Lee la ventana de pixeles
void Control_Visualizacion::Lee_ventana_pixeles(const char *nombre)
{
   Pix->Lee_ventana(nombre);
   Grafica();
}

// Borra los archivos de las ventanas de pixeles grabados
void Control_Visualizacion::Borra_archivo_ventana_pixeles(const char *nombre)
{
   unlink(nombre);
}


// Rota los ejes coordenados
void Control_Visualizacion::Rotar_ejes_3D(const ldouble fi, const ldouble te)
{
  switch (Tipo_ventana) {
     case EJES_COORDENADOS_3D:
       Ventana_Ejes_3D::Rotar_ejes_coordenados(fi, te);
       break;
     case EJES_CAJA_3DM:
       Ventana_Caja_3DM::Rotar_ejes_caja(fi, te);
       break;
     case EJES_CAJA_3D:
       Ventana_Caja_3D::Rotar_ejes_caja(fi, te);
       break;
  }
  Limpiar();
  Dibuja();
}


// Acerca o aleja los ejes coordenados
void Control_Visualizacion::Acercar_alejar_ejes(void)
{
  switch (Tipo_ventana) {
     case EJES_COORDENADOS_3D:
        Ventana_Ejes_3D::Acercar_alejar_ejes();
        break;
     case EJES_COORDENADOS_2D:
        Ventana_Ejes_2D::Acercar_alejar_ejes();
        break;
     case EJES_COORDENADOS_2DM:
        Ventana_Ejes_2DM::Acercar_alejar_ejes();
        break;
     case EJES_CAJA_3DM:
       Ventana_Caja_3DM::Acercar_alejar_ejes();
       break;
     case EJES_CAJA_3D:
       Ventana_Caja_3D::Acercar_alejar_ejes();
       break;
  }
}

// Gradua los ejes
void Control_Visualizacion::Graduar_ejes(void)
{
  switch (Tipo_ventana) {
     case EJES_COORDENADOS_3D:
        Ventana_Ejes_3D::Graduar_ejes();
        break;
     case EJES_COORDENADOS_2D:
        Ventana_Ejes_2D::Graduar_ejes();
        break;
     case EJES_COORDENADOS_2DM:
        Ventana_Ejes_2DM::Graduar_ejes();
        break;
     case EJES_CAJA_3D:
        Ventana_Caja_3D::Graduar_ejes();
        break;
     case EJES_CAJA_3DM:
        Ventana_Caja_3DM::Graduar_ejes();
        break;
  }
}

// Ajusta las dimensiones de la ventana real a la escala que se usa en la ventana de visualización
void Control_Visualizacion::Ajusta_dimension_escala(Dimension_Ventana &aux)
{
  switch (Tipo_ventana) {
      case EJES_COORDENADOS_2DM:
      case EJES_CAJA_2D:
      case EJES_COORDENADAS_POLARES:
      case EJES_COORDENADOS_2D:
         aux.Xi = aux.Xi / Base_Ventana_Graficacion::Factor;
         aux.Xf = aux.Xf / Base_Ventana_Graficacion::Factor;
         aux.Yi = aux.Yi / Base_Ventana_Graficacion::Factor;
         aux.Yf = aux.Yf / Base_Ventana_Graficacion::Factor;
         break;
      case VENTANA_2D:
         break;
      case EJES_COORDENADOS_3D:
         break;
      case EJES_CAJA_3DM:
         break;
      case EJES_CAJA_3D:
         break;
   }
}

// Retorna la posición de un punto en 3D
void Control_Visualizacion::Posicion_3D(const C_3D aux, int &x, int &y)
{
   ldouble factor;
   int mx = 0, my = 0;
   aux3 = aux;
   aux3.x = (aux3.x - (Dim_vtn.Xi + ((Dim_vtn.Xf - Dim_vtn.Xi)/2.0))) * EscalaReal.x;
   aux3.y = (aux3.y - (Dim_vtn.Yi + ((Dim_vtn.Yf - Dim_vtn.Yi)/2.0))) * EscalaReal.y;
   aux3.z = (aux3.z - (Dim_vtn.Zi + ((Dim_vtn.Zf - Dim_vtn.Zi)/2.0))) * EscalaReal.z;
   // Rota segun las especificaciones del escenario
   switch (Tipo_ventana)
   {
      case EJES_COORDENADOS_3D:
         aux4.x = (aux3.z * Ventana_Ejes_3D::ST) + (aux3.x * Ventana_Ejes_3D::CT);
         aux4.y = (aux3.z * Ventana_Ejes_3D::CT * Ventana_Ejes_3D::CF) - (aux3.x * Ventana_Ejes_3D::ST * Ventana_Ejes_3D::CF) + (aux3.y * Ventana_Ejes_3D::SF);
         aux4.z = (aux3.z * Ventana_Ejes_3D::CT * Ventana_Ejes_3D::SF) - (aux3.x * Ventana_Ejes_3D::ST * Ventana_Ejes_3D::SF) - (aux3.y * Ventana_Ejes_3D::CF);
         factor = Ventana_Ejes_3D::Factor;
         break;
      case EJES_CAJA_3D:
         aux4.x = (aux3.z * Ventana_Caja_3D::ST) + (aux3.x * Ventana_Caja_3D::CT);
         aux4.y = (aux3.z * Ventana_Caja_3D::CT * Ventana_Caja_3D::CF) - (aux3.x * Ventana_Caja_3D::ST * Ventana_Caja_3D::CF) + (aux3.y * Ventana_Caja_3D::SF);
         aux4.z = (aux3.z * Ventana_Caja_3D::CT * Ventana_Caja_3D::SF) - (aux3.x * Ventana_Caja_3D::ST * Ventana_Caja_3D::SF) - (aux3.y * Ventana_Caja_3D::CF);
         factor = Ventana_Caja_3D::Factor;
         break;
      case EJES_CAJA_3DM:
         aux4.x = (aux3.z * Ventana_Caja_3DM::ST) + (aux3.x * Ventana_Caja_3DM::CT);
         aux4.y = (aux3.z * Ventana_Caja_3DM::CT * Ventana_Caja_3DM::CF) - (aux3.x * Ventana_Caja_3DM::ST * Ventana_Caja_3DM::CF) + (aux3.y * Ventana_Caja_3DM::SF);
         aux4.z = (aux3.z * Ventana_Caja_3DM::CT * Ventana_Caja_3DM::SF) - (aux3.x * Ventana_Caja_3DM::ST * Ventana_Caja_3DM::SF) - (aux3.y * Ventana_Caja_3DM::CF);
         factor = Ventana_Caja_3DM::Factor;
   }
   // Proyecta al plano y centra en la ventana
   x = (int) (((aux4.x * Numero_pixeles_ventana) / (aux4.z + Numero_pixeles_ventana * 2.0)) * factor + ((Numero_pixeles_ventana - mx) / 2.0));
   y = (int) (((Numero_pixeles_ventana - my) / 2.0) - ((aux4.y * Numero_pixeles_ventana) / (aux4.z + Numero_pixeles_ventana * 2.0)) * factor);
}


// Busca el maximo y el mínimo de los valores del arreglo X
void Control_Visualizacion::Busca_max_min(ldouble *x, const int n, ldouble &min, ldouble &max)
{
   max = min = x[0];
   for (int i = 0; i < n; i++)
   {
      if (x[i] > max) max = x[i];
      if (x[i] < min) min = x[i];
   }
}


// Grafica el contenido de los arreglos X vs Y
void Control_Visualizacion::Grafica(ldouble *x, ldouble *y, int n, TColor col)
{
   int i;
   C_3D a1, a2;
   // Se grafica con lineas
   if (Lin)
   {
      // Se graba archivo de datos
      if  (MD) {
         for (i = 0; i < n-1; i++)
         {
            a1.x = x[i];
            a1.y = y[i];
            a1.z = 0.0;
            a2.x = x[i+1];
            a2.y = y[i+1];
            a2.z = 0.0;
            Dibuja_linea(a1,a2,col);
#ifdef __Double__
            sprintf(xcad,"%+10.10lf  %+10.10lf",a1.x,a1.y);

#else
            sprintf(xcad,"%+10.10Lf  %+10.10Lf",a1.x,a1.y);

#endif
            MD->Graba_linea(xcad);
         }
#ifdef __Double__
         sprintf(xcad,"%+10.10lf  %+10.10lf",a2.x,a2.y);
#else
         sprintf(xcad,"%+10.10Lf  %+10.10Lf",a2.x,a2.y);
#endif
         MD->Graba_linea(xcad);
      } else {
         // Se grafica con lineas
         for (i = 0; i < n-1; i++)
         {
            a1.x = x[i];
            a1.y = y[i];
            a1.z = 0.0;
            a2.x = x[i+1];
            a2.y = y[i+1];
            a2.z = 0.0;
            Dibuja_linea(a1,a2,col);
         }
      }
    } else {
      if (MD)
      {
         for (i = 0; i < n; i++)
         {
            a1.x = x[i];
            a1.y = y[i];
            a1.z = 0.0;
            Dibuja_punto(a1,col);
#ifdef __Double__
            sprintf(xcad,"%+10.10lf  %+10.10lf",a1.x,a1.y);
#else            
            sprintf(xcad,"%+10.10Lf  %+10.10Lf",a1.x,a1.y);
#endif

            MD->Graba_linea(xcad);
         }
       } else {
         for (i = 0; i < n; i++)
         {
            a1.x = x[i];
            a1.y = y[i];
            a1.z = 0.0;
            Dibuja_punto(a1,col);
         }
      }
   }
}

// Grafica el contenido de los arreglos X vs Y y Z
void Control_Visualizacion::Grafica(ldouble *x, ldouble *y, ldouble *z, int n, TColor col)
{
   int i;
   C_3D a1, a2;
   if (Lin)
   {
      if  (MD) {
         for (i = 0; i < n-1; i++)
         {
            a1.x = x[i];
            a1.y = y[i];
            a1.z = z[i];
            a2.x = x[i+1];
            a2.y = y[i+1];
            a2.z = z[i+1];
            Dibuja_linea(a1,a2,col);
#ifdef __Double__
            sprintf(xcad,"%+10.10lf  %+10.10lf  %+10.10lf",a1.x,a1.y,a1.z);
#else
            sprintf(xcad,"%+10.10Lf  %+10.10Lf  %+10.10Lf",a1.x,a1.y,a1.z);
#endif
            MD->Graba_linea(xcad);
         }
#ifdef __Double__
         sprintf(xcad,"%+10.10lf  %+10.10lf  %+10.10lf",a2.x,a2.y,a2.z);
#else
         sprintf(xcad,"%+10.10Lf  %+10.10Lf  %+10.10Lf",a2.x,a2.y,a2.z);
#endif

         
         MD->Graba_linea(xcad);
      } else {
         for (i = 0; i < n-1; i++)
         {
            a1.x = x[i];
            a1.y = y[i];
            a1.z = z[i];
            a2.x = x[i+1];
            a2.y = y[i+1];
            a2.z = z[i+1];
            Dibuja_linea(a1,a2,col);
         }
      }
    } else {
      if (MD)
      {
         for (i = 0; i < n; i++)
         {
            a1.x = x[i];
            a1.y = y[i];
            a1.z = z[i];
            Dibuja_punto(a1,col);
#ifdef __Double__
            sprintf(xcad,"%+10.10lf  %+10.10lf  %+10.10lf",a1.x,a1.y,a1.z);
#else
            sprintf(xcad,"%+10.10Lf  %+10.10Lf  %+10.10Lf",a1.x,a1.y,a1.z);
#endif
            MD->Graba_linea(xcad);
         }
       } else {
         for (i = 0; i < n; i++)
         {
            a1.x = x[i];
            a1.y = y[i];
            a1.z = z[i];
            Dibuja_punto(a1,col);
         }
      }
   }
}

// Grafica X vs Y
void Control_Visualizacion::Grafica(ldouble x, ldouble y, TColor col)
{
   C_3D a1;
   a1.x = x;
   a1.y = y;
   a1.z = 0.0;
   Dibuja_punto(a1,col);
   if (MD)
   {
#ifdef __Double__
      sprintf(xcad,"%+10.10lf  %+10.10lf",a1.x,a1.y);
#else
      sprintf(xcad,"%+10.10Lf  %+10.10Lf",a1.x,a1.y);
#endif
      MD->Graba_linea(xcad);
   }
}

// Grafica X vs Y y Z
void Control_Visualizacion::Grafica(ldouble x, ldouble y, ldouble z, TColor col)
{
   C_3D a1;
   a1.x = x;
   a1.y = y;
   a1.z = z;
   Dibuja_punto(a1,col);
   if (MD)
   {
#ifdef __Double__
      sprintf(xcad,"%+10.10lf  %+10.10lf  %+10.10lf",a1.x,a1.y,a1.z);
#else
      sprintf(xcad,"%+10.10Lf  %+10.10Lf  %+10.10Lf",a1.x,a1.y,a1.z);
#endif
      MD->Graba_linea(xcad);
   }
}


// Interpola num valores con los dados
void Control_Visualizacion::Interpola_grafica(ldouble x1, ldouble y1, ldouble x2, ldouble y2, int num, TColor col)
{
   ldouble inc = (x2 - x1) / (ldouble) num;
   ldouble x, y;
   C_3D a1;
   if (MD)
   {
      for (x = x1; x <= x2; x+= inc)
      {
         y = y1 * ((x - x2) / (x1 - x2)) + y2 * ((x - x1) / (x2 - x1));
         a1.x = x;
         a1.y = y;
         a1.z = 0.0;
         Dibuja_punto(a1,col);
#ifdef __Double__
         sprintf(xcad,"%+10.10lf  %+10.10lf",a1.x,a1.y);
#else
         sprintf(xcad,"%+10.10Lf  %+10.10Lf",a1.x,a1.y);
#endif
         MD->Graba_linea(xcad);
      }
   } else {
      for (x = x1; x <= x2; x+= inc)
      {
         y = y1 * ((x - x2) / (x1 - x2)) + y2 * ((x - x1) / (x2 - x1));
         a1.x = x;
         a1.y = y;
         a1.z = 0.0;
         Dibuja_punto(a1,col);
      }
   }
}


// Interpola num valores con los dados
void Control_Visualizacion::Interpola_grafica(ldouble *x, ldouble *y, int n, int num, TColor col)
{
   ldouble inc;
   ldouble xi, yi;

   int i;
   C_3D a1, a2;
   // Se graba archivo de datos
   if  (MD)
   {
      for (i = 0; i < n-1; i++)
      {
         a1.x = x[i];
         a1.y = y[i];
         a1.z = 0.0;
         a2.x = x[i+1];
         a2.y = y[i+1];
         a2.z = 0.0;
         Dibuja_linea(a1,a2,col);
         inc = (a2.x - a1.x) / (ldouble) num;
         for (xi = a1.x; xi < a2.x; xi+= inc)
         {
            yi = a1.y * ((xi - a2.x) / (a1.x - a2.x)) + a2.y * ((xi - a1.x) / (a2.x - a1.x));
#ifdef __Double__
            sprintf(xcad,"%+10.10lf  %+10.10lf",xi,yi);
#else
            sprintf(xcad,"%+10.10Lf  %+10.10Lf",xi,yi);
#endif
            MD->Graba_linea(xcad);
         }
      }
   } else {
      // Se grafica con lineas
      for (i = 0; i < n-1; i++)
      {
         a1.x = x[i];
         a1.y = y[i];
         a1.z = 0.0;
         a2.x = x[i+1];
         a2.y = y[i+1];
         a2.z = 0.0;


         Dibuja_linea(a1,a2,col);
      }
   }
}
