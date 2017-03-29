//////////////////////////////////////////////////////////////////////////////////////////////
// Ventana de graficación de caja en 3D modificada                                          //
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


#include "Vent_Graf_Caja-3DM.hpp"


/////////////////////////////////////////////////////////////
// Clase Ventana Caja Modificada 3D                        //
/////////////////////////////////////////////////////////////

void Ventana_Caja_3DM::Inicializa(void)
{
   Factor = 1.1;
   TETA = M_PI / 5.5;
   FI = M_PI / 2.0;
   Calcula_valores();
}

void Ventana_Caja_3DM::Calcula_valores(void)
{
   ST = sinl(TETA);
   CT = cosl(TETA);
   SF = sinl(FI);
   CF = cosl(FI);
}

// Dibuja al ventana
void Ventana_Caja_3DM::Dibuja(void)
{
   int x, y;
   C_3D  aux1, aux2;
   aux1.x = Dim_vtn.Xi, aux1.y = Dim_vtn.Yi, aux1.z = Dim_vtn.Zi;
   aux2.x = Dim_vtn.Xf, aux2.y = Dim_vtn.Yi, aux2.z = Dim_vtn.Zi;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_X);
   Posicion_ventana_3D(aux1,x,y);
   if (Visualiza_nombre_eje) Muestra_texto_ventana(x-20,y," ",Nombre_eje_Z);
   aux1.x = Dim_vtn.Xi, aux1.y = Dim_vtn.Yi, aux1.z = Dim_vtn.Zf;
   aux2.x = Dim_vtn.Xf, aux2.y = Dim_vtn.Yi, aux2.z = Dim_vtn.Zf;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_X);
   aux1.x = Dim_vtn.Xi, aux1.y = Dim_vtn.Yf, aux1.z = Dim_vtn.Zf;
   aux2.x = Dim_vtn.Xf, aux2.y = Dim_vtn.Yf, aux2.z = Dim_vtn.Zf;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_X);
   Posicion_ventana_3D(aux1,x,y);
   if (Visualiza_nombre_eje) Muestra_texto_ventana(x,y-20," ",Nombre_eje_Y);
   aux1.x = Dim_vtn.Xi, aux1.y = Dim_vtn.Yi, aux1.z = Dim_vtn.Zi;
   aux2.x = Dim_vtn.Xi, aux2.y = Dim_vtn.Yf, aux2.z = Dim_vtn.Zi;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_Y);
   aux1.x = Dim_vtn.Xi, aux1.y = Dim_vtn.Yi, aux1.z = Dim_vtn.Zf;
   aux2.x = Dim_vtn.Xi, aux2.y = Dim_vtn.Yf, aux2.z = Dim_vtn.Zf;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_Y);
   aux1.x = Dim_vtn.Xf, aux1.y = Dim_vtn.Yi, aux1.z = Dim_vtn.Zf;
   aux2.x = Dim_vtn.Xf, aux2.y = Dim_vtn.Yf, aux2.z = Dim_vtn.Zf;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_Y);
   Posicion_ventana_3D(aux1,x,y);
   if (Visualiza_nombre_eje) Muestra_texto_ventana(x+3,y+5," ",Nombre_eje_X);
   aux1.x = Dim_vtn.Xi, aux1.y = Dim_vtn.Yi, aux1.z = Dim_vtn.Zi;
   aux2.x = Dim_vtn.Xi, aux2.y = Dim_vtn.Yi, aux2.z = Dim_vtn.Zf;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_Z);
   aux1.x = Dim_vtn.Xi, aux1.y = Dim_vtn.Yf, aux1.z = Dim_vtn.Zi;
   aux2.x = Dim_vtn.Xi, aux2.y = Dim_vtn.Yf, aux2.z = Dim_vtn.Zf;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_Z);
   aux1.x = Dim_vtn.Xf, aux1.y = Dim_vtn.Yi, aux1.z = Dim_vtn.Zi;
   aux2.x = Dim_vtn.Xf, aux2.y = Dim_vtn.Yi, aux2.z = Dim_vtn.Zf;
   Dibuja_linea_ventana_3D(aux1, aux2, Color_Eje_Z);
}






