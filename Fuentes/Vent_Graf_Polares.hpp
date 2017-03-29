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



#ifndef __VENT_GRAF_POLARES_HPP__
#define __VENT_GRAF_POLARES_HPP__


#include "Vent_Graf_Base.hpp"


/////////////////////////////////////////////////////////////
//                                                         //
//           Ventana de coordenadas polares                //
//                                                         //
/////////////////////////////////////////////////////////////

class Ventana_Coordenadas_Polares: virtual public Base_Ventana_Graficacion
{
   private:
      ldouble            Factor;                // Factor de acercaminento dentro de la ventana


                    // Dibuja una linea dentro de la ventana
      void          Dibuja_linea_ventana_coordenadas_polares_2D(const C_3D aux1, const C_3D aux2, const TColor color);
      
   protected:

                    // Calcula la posición de un punto en coordenadas polares dentro de la ventana
      void          Posicion_ventana(const C_3D aux, int &x, int &y);

                    // Convierte una posición en coordenadas rectangulares a polares
      void          Convierte_rectangulares_polares(const ldouble x, const ldouble y, ldouble &xx, ldouble &xy);
         
   public:

                    // Inicializa la clase
      virtual void  Inicializa(void);

                    // Dibuja al ventana
      virtual void  Dibuja(void);

                    // Dibuja un punto dentro de la ventana
      void          Dibuja_punto_ventana_coordenadas_polares(const C_3D aux, const TColor color);

                    // Dibuja una linea dentro de la ventana
      void          Dibuja_linea_ventana_coordenadas_polares(const C_3D aux1, const C_3D aux2, const TColor color);
};



#endif
