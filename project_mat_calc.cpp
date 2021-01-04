#include <iostream>
using namespace std;

const int MAX_SIZE = 10000;
int m, n;

void initializeMat(int m, int n, double ** mat){
for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cin >> mat [i][j];
        }
    }

}


void printMat(int m, int n, double ** mat)
{

    for(int i=0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void sumMatrices(int m, int n, double ** mat1, double ** mat2){
    double** sum = new double* [m];
    for(int i = 0; i < m; i++){
        sum[i] = new double[n];
    }

    for(int i=0; i < m; i++){
        for(int j = 0; j < n; j++){
            sum[i][j]= mat1[i][j] + mat2[i][j];
        }
    }
    printMat(m, n, sum);

}

void scalMultiply(int m, int n, double scal, double ** mat){
    double ** multiplyScal = new double * [m];
    for(int i = 0; i < m; i++){
        multiplyScal[i] = new double[n];
    }

    for(int i=0; i < m; i++){
        for(int j = 0; j < n; j++){
            multiplyScal[i][j]= mat[i][j] * scal;
        }
    }
    printMat(m, n, multiplyScal);
}

void scalDivide(int m, int n, double scal, double ** mat){
    double ** divideScal = new double * [m];
    for(int i = 0; i < m; i++){
        divideScal[i] = new double[n];
    }

    for(int i=0; i < m; i++){
        for(int j = 0; j < n; j++){
            divideScal[i][j]= mat[i][j] / scal;
        }
    }
    printMat(m, n, divideScal);
}

int main ()
{

    return 0;
}
