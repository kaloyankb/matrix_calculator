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

void opositeMat(int m, int n, double ** mat)
{
    double ** mCopy = new double * [m];
    for(int i = 0; i < m; i++)
    {
        mCopy[i] = new double [n];
    }
    for(int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mCopy[i][j] = mat[i][j];
        }
    }
    double ** opMat = new double * [m];
    for(int i = 0; i < m; i++)
    {
        opMat[i] = new double [n];
    }
    double ** trOpMat = new double * [m];
    for(int i = 0; i < m; i++)
    {
        trOpMat[i] = new double [n];
    }
    if(m == n)
    {
        if(determinant(m, n, mat) != 0)
        {
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    if((i + j) % 2 == 0)
                    {
                        poddeterminantaUse(m, n, mCopy, i, j);
                        opMat[i][j] = determinant(m - 1, n - 1, mCopy);
                        for(int k = 0; k < m; k++)
                        {
                            for (int l = 0; l < n; l++)
                            {
                                mCopy[k][l] = mat[k][l];
                            }
                        }
                    }
                    else
                    {
                        poddeterminantaUse(m, n, mCopy, i, j);
                        opMat[i][j] = -(determinant(m - 1, n - 1, mCopy));
                        for(int k = 0; k < m; k++)
                        {
                            for (int l = 0; l < n; l++)
                            {
                                mCopy[k][l] = mat[k][l];
                            }
                        }
                    }
                }
            }
            for(int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    trOpMat[i][j] = opMat[j][i];
                    trOpMat[i][j] /= determinant(m, n, mat);
                }
            }
            cout << "The opposite matrix is: " << endl;
            printMat(m, n, trOpMat);
        }
        else cout << "the determinant is 0. Matrix opposite to to the current one doest not exist!" << endl;
    }
    else cout << "the dimensions of the matrix should be equal" << endl;
}

char endMesseges()
{
    cout << "press B to turn back to the MENU" << endl;
    cout << "press F to finish with the operations" << endl;
    char backToMenu;
    cin >> backToMenu;
    while(backToMenu != 'F' && backToMenu!= 'B')
    {
        cout << "Please enter a valid letter." << endl;
        cin >> backToMenu;
    }
    if(backToMenu == 'B')
    {
        return 'B';
    }
    if(backToMenu == 'F')
    {
        return 'F';
    }
}




int main ()
{
    while(true)
    {
        cout << "Type the number of the operation you want to use: " << endl;

        char choice [1] = {};
        cin >> choice[0];
        int m1, n1, m2, n2 = 0;
        cout << "Set the two dimensions of the matrix" << endl;
        if(choice[0] == '1') cout << "(First matrix)" << endl;
        cin >> m1 >> n1;
        if(choice[0] == '5' || choice[0] == '6'){
            while(m1 != n1){
            cout << "The dimensions of the matrix should be equal" << endl;
            cout << "Set the two dimensions of the matrix" << endl;
            cin >> m1 >> n1;
            }
        }
        double** myMat1 = new double* [m1];
        for(int i = 0; i < m1; i++)
        {
            myMat1[i] = new double[n1];
        }
        cout << "Now initialize the matrix" << endl;
        initializeMat(m1, n1, myMat1);

        if(choice[0] == '1'){
            cout << "Set the two dimensions for the matrix" << endl;
            cout << "(Second one)" << endl;
            cin >> m2 >> n2;
            while(m2 != n1){
                 cout << "the second dimension of the first matrix and the first dimension of the second matrix should be equal" << endl;
                 cout << "Set the two dimensions for the matrix" << endl;
                 cout << "(Second matrix)" << endl;
                 cin >> m2 >> n2;
            }
            cout << "Now initialize the matrix" << endl;
            double** myMat2 = new double* [m2];
            for(int i = 0; i < m2; i++)
            {
            myMat2[i] = new double[n2];
            }
            initializeMat(m2, n2, myMat2);
            cout << "The answer is: " << endl;
            multiplyMats(myMat1, myMat2, m1, n1, m2, n2);
            if(endMesseges() == 'F')
            {
                break;
            }
        }

        if(choice[0] == '2')
        {
            int scalar = 0;
            cout << "Set a scalar you want to multiply your matrix with." << endl;
            cin >> scalar;
            cout << "The result matrix is: " << endl;
            scalMultiply(m1, n1, scalar, myMat1);
            if(endMesseges() == 'F')
            {
                break;
            }

        }
        if(choice[0] == '3')
        {
            int scalar = 0;
            cout << "Set a scalar you want to divide your matrix with." << endl;
            cin >> scalar;
            cout << "The result matrix is: " << endl;
            scalDivide(m1, n1, scalar, myMat1);
            if(endMesseges() == 'F')
            {
                break;
            }
        }
        if(choice[0] == '4'){
            cout << "The transposed matrix is: " << endl;
            transp(m1, n1, myMat1);
            if(endMesseges() == 'F')
            {
                break;
            }
        }
        if(choice[0] == '5'){
            cout << "The determinant of the matrix is: " << endl;
            cout << determinant(m1, n1, myMat1) << endl;
             if(endMesseges() == 'F')
            {
                break;
            }
        }
        if(choice[0] == '6'){
            opositeMat(m1, n1, myMat1);
            if(endMesseges() == 'F')
            {
                break;
            }
        }
    }

    return 0;
}
