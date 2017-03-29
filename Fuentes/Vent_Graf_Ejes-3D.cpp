//////////////////////////////////////////////////////////////////////////////////////////////
// Ventana de graficación de ejes en 3D                                                     //
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



#include "Vent_Graf_Ejes-3D.hpp"



/////////////////////////////////////////////////////////////
// Clase Ventana Ejes 3D                                   //
/////////////////////////////////////////////////////////////


// Inicializa la clase
void Ventana_Ejes_3D::Inicializa(void)
{
   Factor = 1.7;
   TETA = M_PI / 13.0;
   FI = M_PI * 0.45;
   Calcula_valores();
}

// Calcula valores necesarios para la visualización
void Ventana_Ejes_3D::Calcula_valores(void)
{
   ST = sinl(TETA);
   CT = cosl(TETA);
   SF = sinl(FI);
   CF = cosl(FI);
}

// Dibuja la ventana
void Ventana_Ejes_3D::Dibuja(void)
{
   int x, y;
   C_3D  aux1, aux2;
   char xcad[5];
   xcad[0] = '-';
   xcad[1] = ' ';
   xcad[2] = 0;

   // Eje horizontal
   aux1.x = Dim_vtn.Xi, aux1.y = 0.0, aux1.z = 0.0;
   aux2.x = Dim_vtn.Xf, aux2.y = 0.0, aux2.z = 0.0;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_X);
   Posicion_ventana_3D(aux1,x,y);
   if (aux1.x < 0.0) xcad[0] = '-';
    else xcad[0] = '+';
   if (Visualiza_nombre_eje) Muestra_texto_ventana(x-20,y+5,xcad,Nombre_eje_X);
   Posicion_ventana_3D(aux2,x,y);
   if (aux2.x < 0.0) xcad[0] = '-';
    else xcad[0] = '+';
   if (Visualiza_nombre_eje) Muestra_texto_ventana(x-10,y+5,xcad,Nombre_eje_X);


   //Eje vertical
   aux1.x = 0.0, aux1.y = Dim_vtn.Yi, aux1.z = 0.0;
   aux2.x = 0.0, aux2.y = Dim_vtn.Yf, aux2.z = 0.0;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_Y);
   Posicion_ventana_3D(aux1,x,y);
   if (aux1.y < 0.0) xcad[0] = '-';
    else xcad[0] = '+';
   if (Visualiza_nombre_eje) Muestra_texto_ventana(x+3,y+5,xcad,Nombre_eje_Y);
   Posicion_ventana_3D(aux2,x,y);
   if (aux2.y < 0.0) xcad[0] = '-';
    else xcad[0] = '+';
   if (Visualiza_nombre_eje) Muestra_texto_ventana(x+3,y-15,xcad,Nombre_eje_Y);


   // Tercer eje
   aux1.x = 0.0, aux1.y = 0.0, aux1.z = Dim_vtn.Zi;
   aux2.x = 0.0, aux2.y = 0.0, aux2.z = Dim_vtn.Zf;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_Z);
   Posicion_ventana_3D(aux1,x,y);
   if (aux1.z < 0.0) xcad[0] = '-';
    else xcad[0] = '+';
   if (Visualiza_nombre_eje) Muestra_texto_ventana(x+3,y+5,xcad,Nombre_eje_Z);
   Posicion_ventana_3D(aux2,x,y);
   if (aux2.z < 0.0) xcad[0] = '-';
    else xcad[0] = '+';
   if (Visualiza_nombre_eje) Muestra_texto_ventana(x+3,y-15,xcad,Nombre_eje_Z);
}






