//////////////////////////////////////////////////////////////////////////////////////////////
// Ventana de graficación en coordenadas polares                                            //
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


#include "Vent_Graf_Polares.hpp"


/////////////////////////////////////////////////////////////
// Clase Ventana Coordenadas Polares                       //
/////////////////////////////////////////////////////////////

void Ventana_Coordenadas_Polares::Inicializa(void)
{
#ifndef __PROGRAMACION_BORLAND__
   Factor = 0.99;
#else
   Factor = 0.8;
#endif
}

// Dibuja la ventana
void Ventana_Coordenadas_Polares::Dibuja(void)
{
   C_3D  aux1, aux2;
   aux1.x = Dim_vtn.Xi, aux1.y = Dim_vtn.Yi, aux1.z = 0.0;
   aux2.x = Dim_vtn.Xf, aux2.y = Dim_vtn.Yi, aux2.z = 0.0;
   Dibuja_linea_ventana_coordenadas_polares_2D(aux1, aux2, Color_Eje_X);
   aux1.x = Dim_vtn.Xi, aux1.y = Dim_vtn.Yf, aux1.z = 0.0;
   aux2.x = Dim_vtn.Xf, aux2.y = Dim_vtn.Yf, aux2.z = 0.0;
   Dibuja_linea_ventana_coordenadas_polares_2D(aux1, aux2, Color_Eje_X);
   aux1.x = Dim_vtn.Xi, aux1.y = Dim_vtn.Yi, aux1.z = 0.0;
   aux2.x = Dim_vtn.Xi, aux2.y = Dim_vtn.Yf, aux2.z = 0.0;
   Dibuja_linea_ventana_coordenadas_polares_2D(aux1, aux2, Color_Eje_Y);
   aux1.x = Dim_vtn.Xf, aux1.y = Dim_vtn.Yi, aux1.z = 0.0;
   aux2.x = Dim_vtn.Xf, aux2.y = Dim_vtn.Yf, aux2.z = 0.0;
   Dibuja_linea_ventana_coordenadas_polares_2D(aux1, aux2, Color_Eje_Y);
}

// Posición dentro de la ventana
void Ventana_Coordenadas_Polares::Posicion_ventana(const C_3D aux, int &x, int &y)
{
   x = (int) (((aux.x * Factor) - Dim_vtn.Xi) * EscalaReal.x * Escala.X);
   y = (int) ((Numero_pixeles_ventana - ((((aux.y * Factor) - Dim_vtn.Yi) * EscalaReal.y) + 1.0)) * Escala.Y);
}

// Convierte una posición en coordenadas rectangulares a polares
void Ventana_Coordenadas_Polares::Convierte_rectangulares_polares(const ldouble x, const ldouble y, ldouble &xx, ldouble &xy)
{
   xx = sqrtl((x * x)+(y * y));
   if (x != 0) xy = atanl(fabsl(y) / fabsl(x));
    else xy = 0.0;
   if (x == 0 && y  > 0) xy = M_PI_2;
   if (x == 0 && y  < 0) xy = M_PI_2*3;
   if (x  < 0 && y == 0) xy = M_PI;

   if (x < 0 && y > 0) xy = (M_PI_2 - xy) + M_PI_2;
   if (x < 0 && y < 0) xy = -((M_PI_2 - xy) + M_PI_2);
   if (x > 0 && y < 0) xy = - xy;
}


// Dibuja un punto dentro de la ventana
void Ventana_Coordenadas_Polares::Dibuja_punto_ventana_coordenadas_polares(const C_3D aux, const TColor color)
{
   px = (int) (((aux.x * Factor * cosl(aux.y))- Dim_vtn.Xi) * EscalaReal.x);
   py = (int) ((Numero_pixeles_ventana - ((((aux.x * Factor * sinl(aux.y))- Dim_vtn.Yi) * EscalaReal.y) + 1.0)));

#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pixels[px * Escala.X][py * Escala.Y] = color;
#endif
   if (Pix->Dentro(px,py)) Pix->Asigna_color(px,py,color);
}

// Dibuja una linea dentro de la ventana
void Ventana_Coordenadas_Polares::Dibuja_linea_ventana_coordenadas_polares(const C_3D aux1, const C_3D aux2, const TColor color)
{
   px = (int) (((aux1.x * Factor * cosl(aux1.y)) - Dim_vtn.Xi) * EscalaReal.x);
   py = (int) ((Numero_pixeles_ventana - ((((aux1.x * Factor * sinl(aux1.y)) - Dim_vtn.Yi) * EscalaReal.y) + 1.0)));
   px1 = (int) (((aux2.x * Factor * cosl(aux2.y)) - Dim_vtn.Xi) * EscalaReal.x);
   py1 = (int) ((Numero_pixeles_ventana - ((((aux2.x * Factor * sinl(aux2.y)) - Dim_vtn.Yi ) * EscalaReal.y ) + 1.0)));

#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pen->Color = color;
   PtrVent->Canvas->MoveTo(px * Escala.X,py * Escala.Y);
   PtrVent->Canvas->LineTo(px1 * Escala.X,py1 * Escala.Y);
#endif
   Pix->Asigna_linea_color(px,py,px1,py1,color);
}

// Dibuja una linea dentro de la ventana
void Ventana_Coordenadas_Polares::Dibuja_linea_ventana_coordenadas_polares_2D(const C_3D aux1, const C_3D aux2, const TColor color)
{
   px = (int) ((((aux1.x * Factor) - Dim_vtn.Xi) * EscalaReal.x));
   py = (int) ((Numero_pixeles_ventana - ((((aux1.y * Factor) - Dim_vtn.Yi) * EscalaReal.y) + 1.0)));
   px1 = (int) ((((aux2.x * Factor) - Dim_vtn.Xi) * EscalaReal.x));
   py1 = (int) ((Numero_pixeles_ventana - ((((aux2.y * Factor)- Dim_vtn.Yi ) * EscalaReal.y ) + 1.0)));

#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pen->Color = color;
   PtrVent->Canvas->MoveTo(px * Escala.X,py * Escala.Y);
   PtrVent->Canvas->LineTo(px1 * Escala.X,py1 * Escala.Y);
#endif
   Pix->Asigna_linea_color(px,py,px1,py1,color);
}


