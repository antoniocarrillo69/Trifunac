#include <stdio.h>
#include "MVGrafica.hpp"


ldouble TS, TP, DT;



// Pulso de Ricker en el tiempo
cdouble Ric_t(const ldouble t)
{
   cdouble a, r = cdouble (0.0, 0.0);
   ldouble xa = M_PI * (DT * t - TS) / TP;
   xa = xa * xa;
   if(xa >= 30.0) return r;
   a = cdouble (xa,0.0);
   r = cdouble (xa - 0.5, 0.0) * exp (-a);
   return r;
}


// Pulso de Gab en el tiempo
cdouble Gab_t(const ldouble t)
{
   cdouble a, r = cdouble (0.0, 0.0), PI_2 = cdouble(M_PI * 2.0, 0.0);
   a = cdouble ((DT * t - TS) / TP, 0.0);
   if (real(a*a) > 30.0) return r;
   r = (cos(PI_2*a) / cdouble (4.0,0.0))* exp (cdouble (-0.8,0.0)*a*a);
   return r;
}


// Pulso de Gausiano en el tiempo
cdouble Gau_t(const ldouble t)
{
   cdouble a, r = cdouble (0.0, 0.0);
   a = cdouble (M_PI * (DT * t - TS) / TP, 0.0);
   a = a * a;
   if (real(a*a) > 20.0) return r;
   r = exp (-a);
   return r;
}


// Pulso Triangular en el tiempo
cdouble Tri_t(const ldouble t)
{
   cdouble a, b, c;
   a = cdouble (DT * t - TS + TP / 2.0,0.0);
   if (real(a) < 0.0) return cdouble (0.0,0.0);
   b = cdouble (DT * t - TS, 0.0);
   if (real(b) < 0.0) return a;
   c = cdouble (DT * t - TS - TP / 2.0, 0.0);
   if (real(c) < 0.0) return (a - b * cdouble (2.0,0.0));
   return (a - b * cdouble (2.0,0.0) + c);
}




// Norma Euclidiana
ldouble norma(cdouble z)
{
   ldouble nor = sqrt(real(z)* real(z) + imag(z) * imag(z));
   return nor;
}


// Calcula la FFT
void tff(cdouble *cx, const int n, cdouble *cy, const ldouble sgn)
{
   int i, j = 1, m, l, istep;
   cdouble sc, ctemp, carg, cw;
   sc = cdouble (sqrt(1.0/(ldouble) n), 0.0);
   for (i = 0; i < n; i++) cy[i] = cx[i];
   for (i = 1; i <= n; i++)
   {
      if (i <= j)
      {
         ctemp = cy[j-1] * sc;  
         cy[j-1] = cy[i-1] * sc;
         cy[i-1] = ctemp;
      }
      m = n / 2; 
      do {
         if (j <= m) break;
         j = j - m;
         m = m / 2;
      } while(m >= 1);
      j = j + m;
   }     
   l = 1;
   do {
      istep = 2 * l;
      for (m = 1; m <= l; m++)
      {
         carg = cdouble (0.0, M_PI * sgn * (ldouble (m-1)) / (ldouble) l);
         cw = exp(carg);
         for (i = m; i <= n; i+= istep)
         {
             ctemp = cw * cy[i+l-1];
             cy[i+l-1] = cy[i-1] - ctemp;
             cy[i-1] = cy[i-1] + ctemp;
         }
      }
      l = istep;
   } while(l < n);
}


// Genera la excitación
void Excitacion(cdouble *cx, const ldouble ini, const ldouble it, const int n, const int tp, const ldouble fac)
{
   int i = 0;
   ldouble t;
   if (tp == 0)
   {
      for (t = ini; t < (it*n); t += it)
      {
         cx[i] = cdouble (real(Ric_t(t)) * fac, 0.0);
         i++;
      }
   }
   if (tp == 1)
   {
      for (t = ini; t < (it*n); t += it)
      {
         cx[i] = cdouble (real(Gab_t(t)) * fac, 0.0);
         i++;
      }
   }
   if (tp == 2)
   {
      for (t = ini; t < (it*n); t += it)
      {
         cx[i] = cdouble (real(Gau_t(t)) * fac, 0.0);
         i++;
      }
   }
   if (tp == 3)
   {
      for (t = ini; t < (it*n); t += it)
      {
         cx[i] = cdouble (real(Tri_t(t)) * fac, 0.0);
         i++;
      }
   }
}



int main(void)
{
   // Para graficar
   MVGrafica gf(150,EJES_CAJA_2D,'*');
   ldouble x[1024], y[1024];


   // Datos problema
   int Tipo_Pulso = 0;
   int N = 512;


   TS = 4.0, TP = 0.5, DT = 0.05;

   int Q = 100, NEST = 11;
   ldouble XI = 0.0, DX = 5.0, FACTOR = 4.0, BET = 4.0, F0 = 4.0;

   cdouble FDT[21][1024];
   cdouble cx[1024], cy[1024], cz[1024];
   ldouble sis[21][1024], frec[1024];
   ldouble frecuencia[1024];

/////////////////////////////////////////////////////////////////////
// Valores de preba
    TP = 3.0, TS = 5.0, N = 256, DX = 0.1, DT = 1.0;
/////////////////////////////////////////////////////////////////////


   int i, j;
   ldouble xx, w, esc, filt;
   cdouble arg;


   // Calculo de la funcion de transferencia
   for (i = 0; i < NEST; i++)
   {
      xx = XI + DX * i;
      for (j = 0; j < N/2+1; j++)
      {
         frecuencia[j] = ((1.0 / (ldouble) N)/ DT) * j;
         w = 2.0 * M_PI * frecuencia[j];
         arg = - cdouble(0.0,1.0) * (cdouble (w * xx / BET, 0.0)) * (cdouble(1.0,0.0) - cdouble(0.0, (1.0/2.0) / Q) );
         FDT[i][j] = exp(arg);

//         printf("%f %f %f %f\n",frecuencia[j], norma(FDT[i][j]),real(FDT[i][j]), imag(FDT[i][j]));
      }
   }


   // Calcula la excitación
   Excitacion(cx, 0.0, 1.0, N, Tipo_Pulso, FACTOR);

   // Grafica la excitación
   for (i = 0; i < N; i++)
   {
      x[i] = i;
      y[i] = real(cx[i]);
   }
   gf.Ajusta_dimensiones(x,y,N);
   gf.Graba_datos("Excitacion.dat");
//   gf.Interpola_grafica(x,y,N,10);
   gf.Grafica(x,y,N);
   gf.Cierra_archivo_datos();
   gf.Visualiza();



   // Calcula la transformada de Fourier
   tff(cx, N, cy, -1.0);

   // Visualiza la transformada de Fourier
   for (i = 0; i < N; i++) y[i] = norma(cy[i]);
   gf.Ajusta_dimensiones(x,y,N);
   gf.Grafica(x,y,N);
   gf.Visualiza();

   //Ajusta la transformada
   esc = DT * sqrt((ldouble) N);
   for (i = 0; i < N/2+1; i++)
   {
      frecuencia[i] = ((1.0 / (double) N)/ DT) * i;
//      printf("%f %f %f %f\n",frecuencia[i], norma(cy[i])*esc, real(cy[i])*esc, imag(cy[i])*esc);
   }

   // Visualiza la transformada ajustada
   for (i = 0; i < N/2+1;i++) y[i] = norma(cy[i])*esc;
   gf.Ajusta_dimensiones(x,y,N/2+1);
   gf.Grafica(x,y,N/2+1);
//   gf.Visualiza();



   // Se Convoluciona la excitación con la funcion de transferencia
   for (i = 0; i < NEST; i++)
   {
       cx[0] = cy[0] * FDT[i][0] * esc;
       for (j = 1; j < N/2+1; j++)
       {
          filt = 1.0 / sqrt(1.0 + pow( (((1.0 / (double) N)/ DT) * j) /F0,10.0));
          cx[j] = cy[j] * FDT[i][j] * esc * filt;
          cx[N-j] = conj(cx[j]);
       }
       tff(cx, N, cz, 1.0);
       for (j = 0; j < N; j++)
       {
          sis[i][j] = real(cz[j]) / esc;
          frec[j] = DT * j;
//          printf("%f %f\n",frec[j],sis[i][j]);
       }
   }


   ldouble FactorEscalaX = 10.0;
   // Visualiza el sismograma
   Dimension_Ventana vdim;
   ldouble max, min;
   gf.Busca_max_min(frec, N, min, max);
   vdim.Xi = min, vdim.Xf = max/FactorEscalaX;
   gf.Busca_max_min(sis[0], N, min, max);
   vdim.Yi = min+(min/2.0), vdim.Yf = (max-min)*NEST*2.0, vdim.Zi = -10.0, vdim.Zf = 10.0;
   gf.Dimensiones(vdim);
   gf.Graba_datos("Sismograma.dat");
   for (i = 0; i < NEST; i++)
   {
      for (j = 0; j < N; j++) y[j] = i*(max-min) * 2.0 + sis[i][j];
      gf.Grafica(frec,y,N);
   }
   gf.Cierra_archivo_datos();
   gf.Visualiza();

}
