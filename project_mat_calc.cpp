#include <iostream>
using namespace std;


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

void poddeterminantaUse (int m, int n, double ** mat, int removedElementI, int removedElementJ)
{
    int pdI = 0;
    int pdJ = 0;
    for(int i = 0; i < m; i++)
    {
        if(i != removedElementI)
        {
            for(int j = 0; j < n; j++)
            {
                if(j != removedElementJ)
                {
                    mat[pdI][pdJ] = mat[i][j];
                    pdJ++;
                    if(pdJ == n - 1)
                    {
                        pdJ = 0;
                        pdI++;
                    }
                }
            }
        }
    }
}

void transp(int m, int n, double ** mat){
    double ** matTr = new double * [m];
    for(int i = 0; i < m; i++)
    {
        matTr[i] = new double [n];
    }
    for(int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++){
        matTr[i][j] = mat[j][i];
        }
    }
    printMat(m, n, matTr);
}

int determinant (int m, int n, double ** mat, double det = 0){
    double detForReturn = 0;
    double ** mCopy = new double * [m];
    for(int i = 0; i < m; i++)
    {
        mCopy[i] = new double [n];
    }
    for(int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++){
        mCopy[i][j] = mat[i][j];
        }
    }
    if(m == n){
        if(m == 1){
            det = mat[0][0];
            return det;
        }
        if(m == 2){
            det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
            return det;
        }
        if(m == 3){
            det = mat[0][0] * mat[1][1] * mat[2][2] + mat[0][1] * mat[1][2] * mat[2][0] + mat[0][2] * mat[1][0] * mat[2][1];
            det -= (mat[0][2] * mat[1][1] * mat[2][0] + mat[0][0] * mat[1][2] * mat[2][1] + mat[0][1] * mat[1][0] * mat[2][2]);
            return det;
        }
        if(m == 4){
                for(int j = 0; j < n; j++){
                      //  cout << "j: " << j << endl;
                    if(j % 2 == 0){
                        int elRem = mat[0][j];
                        poddeterminantaUse(m, n, mCopy, 0, j);
                       // printMat(m - 1, n - 1, mCopy);
                        //cout << endl;
                        //cout << "here" << endl;
                        det += elRem * determinant(m - 1, n - 1, mCopy);

                        for(int i = 0; i < m; i++) {
                            for (int j = 0; j < n; j++){
                                mCopy[i][j] = mat[i][j];
                            }
                        }

                       // cout << "yaaa, the det is: " << det;
                    }
                    else {
                        int elRem = mat [0][j];
                        poddeterminantaUse(m, n, mCopy, 0, j);
                        det += -(elRem * determinant(m - 1, n - 1, mCopy));

                        for(int i = 0; i < m; i++) {
                            for (int j = 0; j < n; j++){
                                mCopy[i][j] = mat[i][j];
                            }
                        }
                        detForReturn = det;
                    }
                }
                return detForReturn;
        }
    }
    else cout << "the dimensions of the matrix should be equal" << endl;
}

void multiplyMats(double ** mat1, double ** mat2, int m1, int n1, int m2, int n2)
{
    int mulI = 0;
    int mulJ = 0;
    int currentValue = 0;
    double ** multiply = new double * [m1];
    for(int i = 0; i < m1; i++)
    {
        multiply[i] = new double [n2];
    }
    if(n1 != m2)
    {
        cout << "the second dimension of the first matrix and the first dimension of the second matrix should be equal" << endl;
    }
    else
    {

        for(int i = 0; i < m1; i++){
            for(int j = 0; j < n2; j++){
                for(int k = 0; k < m2; k++){
                   multiply[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
    printMat(m1, n2, multiply);
    }
}

int main ()
{

    return 0;
}
