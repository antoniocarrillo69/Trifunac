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



#ifndef __VENT_GRAF_CAJA_3DM_HPP__
#define __VENT_GRAF_CAJA_3DM_HPP__


#include "Vent_Graf_Base.hpp"


/////////////////////////////////////////////////////////////
//                                                         //
//          Ventana de caja odificada en 3D                //
//                                                         //
/////////////////////////////////////////////////////////////

class Ventana_Caja_3DM: virtual public Base_Ventana_Graficacion
{

  protected:
      ldouble            Factor;                  // Factor de acercaminento dentro de la ventana
      ldouble            TETA, FI;                // Valores usados para la proyección
      ldouble            ST, SF, CT, CF;          // Valores usados para la proyección
      C_2I                   Centro;                  // Centro de la pantalla

                    // Calcula los valores necesarios 
      void          Calcula_valores(void);


   public:

                    // Inicializa la clase
      virtual void  Inicializa(void);

                    // Dibuja al ventana
      virtual void  Dibuja(void);

      virtual void  Rotar_ejes_caja(const ldouble fi, const ldouble te)
                    {
                       FI += fi;
                       TETA += te;
                       Calcula_valores();
                    }

      virtual void  Acercar_alejar_ejes(void)
                    {}
      virtual void  Graduar_ejes(void)
                    {}

};


#endif
