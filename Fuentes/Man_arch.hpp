//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para manipulación de archivos                                                      //
// Revisión: 3 de Noviembre del 2003                                                        //
//                                                                                          //
//                                                                                          //
// Análisis y Diseño y Programación:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.igeofcu.unam.mx                                                    //
// Página:   http://www.mmc.igeofcu.unam.mx/acl                                             //
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



#ifndef __man_arch_hpp__
#define __man_arch_hpp__

#include <stdio.h>
#include "Cadenas.hpp"
#include "Definiciones.hpp"


#define LEE_ARCHIVO       0
#define GRABA_ARCHIVO     1
#define ADICIONA_ARCHIVO  2


/// Clase manipuladora del manipulador de archivos
class Manipulador_archivos: virtual public Cadenas   
{
  private:

  // Guarda el modo de apertura del archivo
   unsigned int     MODO:              2;
   // Variable que indica el Estado del objeto
   int              Estado;                      
   // Variable de caracter temporal
   char             car;                         
   // Indica la longitud maxima de la cadena a trabajar
   unsigned int     LG_MAX;                      
   // Variables temporal
   int              inttmp;                      
   long             longtmp;
   unsigned int     uinttmp;
   unsigned char    cartmp;
   char             xcad[1000];

   /// Puntero al archivo generado como reporte
   FILE            *ARCHIVO_TRABAJO;
   /// Nombre del archivo a trabajar
   char            *ARCHIVO; 
   /// Nombre de la rutina que llama al manipulador de archivos
   char            *RUTINA; 
   /// Contiene el delimitador entre lineas
   char            *DELIMITADOR;


  public:

         /// Costructor de la clase
         Manipulador_archivos(void);
         /// Destructor de la clase
        ~Manipulador_archivos();

         /// Parametros para el manipulador de archivos
    void Parametros(const char *archivo, const int modo, const unsigned int lg_max, const char *rutina = "");
         /// Cierra el acceso al puntero del archivo
    void Cerrar(void);
         /// Longitud máxima del texto
    void Cambia_longitud_maxima_texto(const int lg)
         {LG_MAX = lg;}
         /// Cuenta el numero de caracteres y lineas dentro del archivo si T_P es (1) combierte tabuladores en TABULADOR espacios y no tome en cuenta el caracter 13, si T_P es (0) cuenta la cantidad de caracteres reales
    void Longitud_archivo(long &lg_archivo, long &nm_lineas, const int t_p);
         /// Actualiza la longitud máxima de la cadena a trabajar
    unsigned int Longitud_maxima_linea(void);
         /// Lee la siguiente linea del archivo, retornando la longitud de la linea
    unsigned int Lee_linea(char *cadena);
         /// Graba una cadena como una linea del archivo, retornando la longitud de esta
    unsigned int Graba_linea(const char *cadena);
         /// Se posiciona en la linea indicada por LINEA
    unsigned int Busca_linea(const unsigned int linea);
         /// Lee el numero de caracteres indicados en N_C y los deja en la cadena CADENA, retornando  el numero de caracteres leidos
    unsigned int Lee_caracteres(char *cadena, const unsigned int n_c);
         /// Graba una una cadena de caracteres, retornando el numero de caracteres grabados
    unsigned int Graba_caracteres(const char *cadena, const unsigned int n_c);
         /// Lee un entero
    void Lee_entero(int &num);
         /// Lee un entero sin signo
    void Lee_entero(unsigned int &num);
         /// Lee un carcater sin signo
    void Lee_caracter(char &num);
         /// Lee un entero largo
    void Lee_entero_largo(long &num);
         /// Lee un flotante double
    void Lee_double(double &num);
         /// Lee un flotante long double
    void Lee_ldouble(long double &num);
         /// Graba un entero
    void Graba_entero(const int ent);
         /// Graba un entero sin signo
    void Graba_entero(const unsigned int ent);
         /// Graba un caracter sin signo
    void Graba_caracter(const char car);
         /// Graba un entero largo
    void Graba_entero_largo(const long ent);
         /// Graba un flotante double
    void Graba_double(const double num);
         /// Graba un flotante long double
    void Graba_ldouble(const long double num);
         /// Debuelve el Estado del manipulador de archivos
    int  Retorna_estado(void) const
         {return Estado;}
         /// Posiciona al indicador del archivo en el inicio de este
    void Inicio_archivo(void)
         {Estado = 0; rewind(ARCHIVO_TRABAJO);}


         /// Copia el archivo indicado como fuente al archivo objeto
    int  Copia_archivo(const char *archivo_fuente, const char *archivo_objeto);
         /// Concatena el archivo indicado como fuente al archivo objeto
    int  Concatena_archivo(const char *archivo_fuente, const char *archivo_objeto);
         /// Remueve el archivo especificado en el path, en caso de tener permisos de solo lectura y/o oculto son cambiados a archivo normal. Despues de borra el archivo, si tp es (1) reescribe este para evitar su recuperación.
    int  Remueve_archivo(const char *arch, const int tp);
         /// Renombra el archivo indicado como fuente al archivo objeto
    int  Renombra_archivo(const char *archivo_fuente, const char *archivo_objeto);
         /// Retorna un nombre de archivo con extención EXT
    void Cambia_ext_path(const char *path, const char *ext, char *pathmod);
         /// Retorna un nombre de archivo con extención EXT
    void Cambia_ext_path(char *path, const char *ext);
         /// Construye una trayectoria
    void Construye_trayectoria(const char *tray, const char *arch, const char *ext, char *xpath);
         /// Adiciona a una cadena con terminador nulo los caracteres LF y LN
    void Construye_trayectoria(const char *tray, const char *arch, char *xpath);
         /// Adiciona a una cadena con terminador nulo los caracteres LF y LN
    void Convierte_linea(char *xcad);
         /// Ajusta el nombre de archivo para visualizacion a la longitud indicada
    void AjustaNombreArchivo(const char *cad, char *xcad, unsigned int lg);
    
    
         /// Graba el contenido de los arreglos X vs Y
    void Graba(ldouble *x, ldouble *y, int n);

         /// Graba el contenido de los arreglos X vs Y y Z
    void Graba(ldouble *x, ldouble *y, ldouble *z, int n);

         /// Graba X vs Y
    void Graba(ldouble x, ldouble y);

         /// Graba X vs Y y Z
    void Graba(ldouble x, ldouble y, ldouble z);
    
         /// Graba el punto x con los n valores del vector y en una misma linea
    void Graba(ldouble x, ldouble *y, int n);

         /// Interpola num valores con los dados
    void Interpola_graba(ldouble *x, ldouble *y,  int n, int num);

         /// Interpola num valores con los dados
    void Interpola_graba(ldouble x1, ldouble y1, ldouble x2, ldouble y2, int num);
      
         /// Busca el maximo y el mínimo de los valores del arreglo X
    void Busca_max_min(ldouble *x, int n, ldouble &min, ldouble &max);
    
};

#endif


