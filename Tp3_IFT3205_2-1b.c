/*------------------------------------------------------*/
/* Prog    : Tp3_IFT3205-2-2.c                          */
/* Auteur  : Kevin Laurent et Dennis Orozko             */
/* Date    : --/--/2010                                 */
/* version :                                            */ 
/* langage : C                                          */
/* labo    : DIRO                                       */
/*------------------------------------------------------*/

/*------------------------------------------------*/
/* FICHIERS INCLUS -------------------------------*/
/*------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "FonctionDemo3.h"

/*------------------------------------------------*/
/* DEFINITIONS -----------------------------------*/   
/*------------------------------------------------*/
#define NAME_VISUALISER "display "
#define NAME_IMG_IN  "lena128"
#define NAME_IMG_OUT "image-TpIFT3205-2-1b"

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/   
/*------------------------------------------------*/


/*------------------------------------------------*/
/* PROGRAMME PRINCIPAL   -------------------------*/                     
/*------------------------------------------------*/
void InterpolBilineaire(float** Mat,float** MatI,int length,int width)
 {
   float a;
   float b;
   float c;
   float d;
   int x;
   int y;
   float w; // width inter-point
   float l; // length inter-point
   for (int i=0; i<(length*4)-4; i++)
     for (int j=0; j<(width*4)-4; j++)
       {
         x = (int) i/4;
         y = (int) j/4;
         a = Mat[x][y];
         b = Mat[x][y+1];
         c = Mat[x+1][y];
         d = Mat[x+1][y+1];

         w = ((float)j-(float)y*4.0)/4.0;
         l = ((float)i-(float)x*4.0)/4.0;

         MatI[i][j] = a*(1-w)*(1-l) + b*(w)*(1-l) + c*(l)*(1-w) + d*(w*l);
       }
 }

int main(int argc,char **argv)
 {
  int i,j;
  int length,width;
  char BufSystVisuImg[100];

  //Lecture Image 
  float** MatriceImg1=LoadImagePgm(NAME_IMG_IN,&length,&width);
  float** MatriceImg2=fmatrix_allocate_2d(length*4,width*4);

  //Interpolation PPV
  InterpolBilineaire(MatriceImg1,MatriceImg2,length,width);
 
  //Sauvegarde
  SaveImagePgm(NAME_IMG_OUT,MatriceImg2,length*4,width*4);

  //Commande systeme: VISU
  strcpy(BufSystVisuImg,NAME_VISUALISER);
  strcat(BufSystVisuImg,NAME_IMG_OUT);
  strcat(BufSystVisuImg,".pgm&");
  printf(" %s",BufSystVisuImg);
  system(BufSystVisuImg);
 


  //==End=========================================================

  //Liberation memoire 
  free_fmatrix_2d(MatriceImg1);
  free_fmatrix_2d(MatriceImg2);  
 
  //retour sans probleme
  printf("\n C'est fini ... \n\n");
  return 0; 	 
}


