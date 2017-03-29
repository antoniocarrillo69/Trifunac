//////////////////////////////////////////////////////////////////////////////////////////////
// Ventana de graficación en 2D                                                             //
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



#include "Vent_Graf_2D.hpp"


/////////////////////////////////////////////////////////////
// Clase Ventana 2D                                        //
/////////////////////////////////////////////////////////////

void Ventana_2D::Posicion_ventana(const C_3D aux, int &x, int &y)
{
   x = (int) ((aux.x - Dim_vtn.Xi) * EscalaReal.x * Escala.X);
   y = (int) ((Numero_pixeles_ventana - (((aux.y - Dim_vtn.Yi) * EscalaReal.y) + 1.0)) * Escala.Y);
}


// Dibuja un punto dentro de la ventana
void Ventana_2D::Dibuja_punto_2D(const C_3D aux, const TColor color)
{
   px = (int) ((aux.x - Dim_vtn.Xi) * EscalaReal.x);
   py = (int) (Numero_pixeles_ventana - (((aux.y - Dim_vtn.Yi) * EscalaReal.y) + 1.0));

#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pixels[px * Escala.X][py * Escala.Y] = color;
#endif
   if (Pix->Dentro(px,py)) Pix->Asigna_color(px,py,color);
}

// Dibuja una linea dentro de la ventana
void Ventana_2D::Dibuja_linea_2D(const C_3D aux1, const C_3D aux2, const TColor color)
{
   px = (int) ((aux1.x - Dim_vtn.Xi) * EscalaReal.x);
   py = (int) (Numero_pixeles_ventana - (((aux1.y - Dim_vtn.Yi) * EscalaReal.y) + 1.0));
   px1 = (int) ((aux2.x - Dim_vtn.Xi) * EscalaReal.x);
   py1 = (int) (Numero_pixeles_ventana - (((aux2.y - Dim_vtn.Yi) * EscalaReal.y) + 1.0));

#ifdef __PROGRAMACION_BORLAND__
   PtrVent->Canvas->Pen->Color = color;
   PtrVent->Canvas->MoveTo(px * Escala.X,py * Escala.Y);
   PtrVent->Canvas->LineTo(px1 * Escala.X,py1 * Escala.Y);
#endif
   Pix->Asigna_linea_color(px,py,px1,py1,color);
}


