//     *********************************
//     *    Matrix Multiply Project    *
//     *                               *
//     *********************************

//     ** MAIN PROGRAM  **


//     *************************************************
//     ** Any changes you make to this code must      **
//     ** maintain the correctness of the matrix      **
//     ** multiply computed by the original version.
//     **					      **
//     ** An implementation with incorrect results for**
//     ** matrix C earns zero point for this project. **
//     **
//     ** To print matrix compile with -DPRINT_MATRIX **
//     ** e.g., g++ -DPRINT_MATRIX                    **
//     **                                             **
//     ** A sample Makefile is provided.
//     ** You may assume m = n = k for your matrices  **
//     *************************************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double **dmatrix(int nrl,int nrh,int ncl,int nch);
void nerror(char *error_text);

int main(int argc, char** argv)  {

      int l,m,n,k;
      int i,j;
      double temp;
      double **A, **B, **C;


     //  ****************************************************
     //  * The following allows matrix parameters to be     *
     //  * entered on the command line to take advantage    *
     //  * of dynamically allocated memory.  You may modify *
     //  * or remove it as you wish.                        *
     //  ****************************************************

     if (argc != 4) {
       nerror("Usage:  <executable> <m-value> <n-value> <k-value>");
     }
      m = atoi(argv[1]);
      n = atoi(argv[2]);
      k = atoi(argv[3]);

      // *********************************************************
      // * Call the dmatrix() subroutine to dynamically allocate *
      // * storage for the matrix sizes specified by m, n, and k *
      // *********************************************************

      A=dmatrix(0,m-1,0,k-1);
      B=dmatrix(0,k-1,0,n-1);
      C=dmatrix(0,m-1,0,n-1);

      // *********************************************************
      //  * Initialize matrix elements so compiler does not      *
      //  * optimize out                                         *
      // *********************************************************

      for(j=0;j<k;j++) {
        for(i=0;i<m;i++) {
          A[i][j] = i+j+4.0;
        }
      }

      for(j=0;j<n;j++) {
        for(i=0;i<k;i++) {
          B[i][j] = i+j+5.0;
        }
      }

      for(j=0;j<n;j++) {
        for(i=0;i<m;i++) {
          C[i][j] = 0.0;
        }
      }

      // ******************************
      // * Start embedded timing here *
      // ******************************
      clock_t start, end;
      double cpu_time_used;
      start = clock();
      // **********************************
      // * Perform simple matrix multiply *
      // **********************************
      // for(j=0;j<n;j++) {
      //   for(l=0;l<k;l++) {
      //     for(i=0;i<m;i++) {
      //       C[i][j] = C[i][j] + B[l][j]*A[i][l];
      //     }
      //   }
      // }

      int BLOCK_SIZE = 48;
      int jj, ll;
      double a;

      for(j=0;j<m;j+= BLOCK_SIZE) {
        for(l=0;l<k;l+= BLOCK_SIZE) {
          for(jj = j; jj < j + BLOCK_SIZE; jj++){
            for(ll = l; ll < l + BLOCK_SIZE; ll++){
              a = A[jj][ll];
              for(i=0;i<n;i += 16) {
                C[jj][i] = C[jj][i] + B[ll][i]*a;
                C[jj][i+1] = C[jj][i+1] + B[ll][i+1]*a;
                C[jj][i+2] = C[jj][i+2] + B[ll][i+2]*a;
                C[jj][i+3] = C[jj][i+3] + B[ll][i+3]*a;
                C[jj][i+4] = C[jj][i+4] + B[ll][i+4]*a;
                C[jj][i+5] = C[jj][i+5] + B[ll][i+5]*a;
                C[jj][i+6] = C[jj][i+6] + B[ll][i+6]*a;
                C[jj][i+7] = C[jj][i+7] + B[ll][i+7]*a;

                C[jj][i+8] = C[jj][i+8] + B[ll][i+8]*a;
                C[jj][i+9] = C[jj][i+9] + B[ll][i+9]*a;
                C[jj][i+10] = C[jj][i+10] + B[ll][i+10]*a;
                C[jj][i+11] = C[jj][i+11] + B[ll][i+11]*a;
                C[jj][i+12] = C[jj][i+12] + B[ll][i+12]*a;
                C[jj][i+13] = C[jj][i+13] + B[ll][i+13]*a;
                C[jj][i+14] = C[jj][i+14] + B[ll][i+14]*a;
                C[jj][i+15] = C[jj][i+15] + B[ll][i+15]*a;
              }
            }
          }
        }
      }

      // ******************************
      // * Stop embedded timing here  *
      // ******************************
      end = clock();
      cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
      printf("%f seconds\n", cpu_time_used);
      // **************************************************
      // * Print out a 10 x 10 matrix for testing only    *
      // * Comment out when timing                        *
      // **************************************************

      // for (i = 0; i < m; i++) {
      //   for (j = 0; j < n; j++) {
      //     printf("%10.2f ", C[i][j]);
      //   }
      //   printf("\n");
      // }

 #ifdef PRINT_MATRIX
      fprintf(stdout, "Here is the matrix A:\n\n");
      for(i=0;i<m;i++) {
        for(j=0;j<k;j++) {
          fprintf(stdout, "%10.2f ",A[i][j]);
        }
        fprintf(stdout, "\n");
      }
      fprintf(stdout, "Here is the matrix B:\n\n");
      for(i=0;i<k;i++) {
        for(j=0;j<n;j++) {
          fprintf(stdout, "%10.2f",B[i][j]);
        }
        fprintf(stdout, "\n");
      }
      fprintf(stdout, "Here is the matrix C:\n\n");
      for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
          fprintf(stdout, "%10.2f",C[i][j]);
        }
        fprintf(stdout, "\n");
      }
#endif

}
//     **  END MAIN PROGRAM  **

//     ********************************************************
//     *******    BEGIN SUBROUTINES    ************************
//     ********************************************************

double **dmatrix(int nrl,int nrh,int ncl,int nch)
// Allocates a double matrix with range [nrl..nrh][ncl..nch]
{
  int i;
  double **m;

//    Allocate pointers to rows
  m=(double **) malloc((unsigned)(nrh-nrl+1)*sizeof(double *));
  if (!m) nerror("allocation failure in malloc in dmatrix()");
  m -= nrl;
//    Allocate rows and set pointers to them
  for(i=nrl;i<=nrh;i++) {
    m[i]=(double*) malloc((unsigned) (nch-ncl+1)*sizeof(double));
    if (!m[i]) nerror("allocaion failure in malloc in dmatrix()");
    m[i] -= ncl;
  }
  return m;
}

void nerror(char *error_text)
{
  void exit();
  fprintf(stderr, "Run-time error...\n");
  fprintf(stderr,"%s\n",error_text);
  fprintf(stderr,"Exiting...\n");
  exit(1);
}
