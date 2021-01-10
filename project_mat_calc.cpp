#include <iostream>
#include <fstream>
using namespace std;


void initializeMat(int m, int n, double ** mat) //function for initializing a matrix
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> mat [i][j];
        }
    }

}

void printMat(int m, int n, double ** mat) //function for printing a matrix
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


void scalMultiply(int m, int n, double scal, double ** mat)
{
    double ** multiplyScal = new double * [m]; //creating a new matrix
    for(int i = 0; i < m; i++)
    {
        multiplyScal[i] = new double[n];
    }

    for(int i=0; i < m; i++) // in which we fill the multiplied one
    {
        for(int j = 0; j < n; j++)
        {
            multiplyScal[i][j]= mat[i][j] * scal; //multiplying each element with a scalar
        }
    }
    printMat(m, n, multiplyScal);//printing that matrix
}

void scalDivide(int m, int n, double scal, double ** mat)
{
    double ** divideScal = new double * [m]; //creating a new matrix
    for(int i = 0; i < m; i++)
    {
        divideScal[i] = new double[n];
    }

    for(int i=0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            divideScal[i][j]= mat[i][j] / scal; //dividing each element with a scalar
        }
    }
    printMat(m, n, divideScal); //print
}

void subDeterminant (int m, int n, double ** mat, int removedElementI, int removedElementJ) //we need a subdeterminant to find the determinant
{       //removed element is the element which column and row we remove from the determinant
        //removedI is the row we remove
        //removeJ is the column we remove
    int pdI = 0;//new coordinates for the matrix
    int pdJ = 0;
    for(int i = 0; i < m; i++)// we start two cycles (for the columns and the rows)
    {
        if(i != removedElementI)//if the current row is not the row we have to remove
        {
            for(int j = 0; j < n; j++)//then we start a cycle for the collumns
            {
                if(j != removedElementJ)//if the current column is not the column we have to remove
                {
                    mat[pdI][pdJ] = mat[i][j];//we set the new element of the matrix to that element from the old matrix
                    pdJ++;
                    if(pdJ == n - 1)//when the column ends we go on the next row
                    {
                        pdJ = 0;
                        pdI++;
                    }
                }
            }
        }
    }
    //in the end we have skipped the row and the collumn that we don't want so we have the subdeterminant
}

void transp(int m, int n, double ** mat)//function that finds the transposed matrix
{
    double ** matTr = new double * [n];//new matrix with the opposite dimensions (m is n and n is m)
    for(int i = 0; i < n; i++)
    {
        matTr[i] = new double [m];
    }
    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matTr[i][j] = mat[j][i]; //every element of the new matrix is with opposite coordinates of the old matrix
        }
    }
    printMat(n, m, matTr);//printing the new one
}

int determinant (int m, int n, double ** mat, double det = 0)
{
    double detForReturn = 0;
    double ** mCopy = new double * [m]; //creating a copy of the argument matrix
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
    if(m == n) //we check if the argument matrix is with equal dimensions
    {
        if(m == 1) //if the matrix is 1 x 1
        {
            det = mat[0][0];// we print it's element
            return det;
        }
        if(m == 2)// if the matrix is 2 x 2
        {
            det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]; //using the formula for determinant 2 x 2
            return det;
        }
        if(m == 3) // if the matrix is 3 x 3
        {    //using the formula for determinant 3 x 3
            det = mat[0][0] * mat[1][1] * mat[2][2] + mat[0][1] * mat[1][2] * mat[2][0] + mat[0][2] * mat[1][0] * mat[2][1];
            det -= (mat[0][2] * mat[1][1] * mat[2][0] + mat[0][0] * mat[1][2] * mat[2][1] + mat[0][1] * mat[1][0] * mat[2][2]);
            return det;
        }
        if(m == 4)// if the matrix is 4 x 4
        {
            //developing the determinant of the first row (that means i is fixated = 0 and we move the collumns
            for(int j = 0; j < n; j++)
            {

                if(j % 2 == 0)// if j is even that means (-1) is on even degree and it's equal to 1
                {
                    int elRem = mat[0][j];
                    subDeterminant(m, n, mCopy, 0, j); //making a subdeterminant of the copy of the matrix
                    det += elRem * determinant(m - 1, n - 1, mCopy);//the determinant formula where we recursively call the same determinant function but now with
                                                                    //dimensions 3 by 3 and the subbdeterminant of the determinant of the argument matrix

                    for(int i = 0; i < m; i++)
                    {
                        for (int j = 0; j < n; j++)
                        {
                            mCopy[i][j] = mat[i][j]; //setting the matrix copy again as a copy of the argument matrix to use it again after the the for cycle makes new iteration
                        }
                    }
                }
                else //same thing when j is odd. In this case (-1)^(i+j) equals to -1, so the determinant is the same as in in the last case but with a minus sign
                {
                    int elRem = mat [0][j];
                    subDeterminant(m, n, mCopy, 0, j);
                    det += -(elRem * determinant(m - 1, n - 1, mCopy));

                    for(int i = 0; i < m; i++)
                    {
                        for (int j = 0; j < n; j++)
                        {
                            mCopy[i][j] = mat[i][j];
                        }
                    }
                    detForReturn = det;//we return this value
                }
            }
            return detForReturn;
        }
    }
    else cout << "the dimensions of the matrix should be equal" << endl;//when the dimensions are not equal
}

void multiplyMats(double ** mat1, double ** mat2, int m1, int n1, int m2, int n2)//function for multiplying matrices
{
    int mulI = 0;
    int mulJ = 0;
    int currentValue = 0;
    double ** multiply = new double * [m1];// creating a new matrix where we put result
    for(int i = 0; i < m1; i++)
    {
        multiply[i] = new double [n2];
    }
    if(n1 != m2)//if the second dimension of the first matrix and the first dimension of the second matrix are not equal
    {
        cout << "the second dimension of the first matrix and the first dimension of the second matrix should be equal" << endl;
    }
    else
    {

        for(int i = 0; i < m1; i++)
        {
            for(int j = 0; j < n2; j++)
            {
                for(int k = 0; k < m2; k++)
                {
                    multiply[i][j] += mat1[i][k] * mat2[k][j]; //using the multiply formula for matrices
                }
            }
        }
        printMat(m1, n2, multiply);//printing that matrix
    }
}

void opositeMat(int m, int n, double ** mat)//function that finds the opposite matrix of a given one (works only for 4 x 4 matrices because the determinant function works only for 4 x 4 matrices
{
    double ** mCopy = new double * [m];//creating a copy of the argument matrix
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
    double ** opMat = new double * [m];//creating a new matrix which will contain the opposite matrix before transposing
    for(int i = 0; i < m; i++)
    {
        opMat[i] = new double [n];
    }
    double ** trOpMat = new double * [m];//creating a new matrix which will contain the opposite matrix after transposing
    for(int i = 0; i < m; i++)
    {
        trOpMat[i] = new double [n];
    }
    if(m == n)//if the dimensions of the matrix are equal
    {
        if(determinant(m, n, mat) != 0)//if the determinant of the matrix is not zero
        {
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {       //using the formula for fing an opposite matrix
                        //every element of the matrix is ((-1) ^ (i + j)) * (the subbdeterminant ij)
                    if((i + j) % 2 == 0)//if (-1) ^ (i + j) equals 1
                    {
                        subDeterminant(m, n, mCopy, i, j);//making the copy of the matrix a subdeterminant ij
                        opMat[i][j] = determinant(m - 1, n - 1, mCopy);//finding it's determinant
                        for(int k = 0; k < m; k++)
                        {
                            for (int l = 0; l < n; l++)
                            {
                                mCopy[k][l] = mat[k][l];//setting the matrix copy again as a copy of the argument matrix to use it again after the the for cycle makes new iteration
                            }
                        }
                    }
                    else //the same thing but (-1) ^ (i + j) equals -1
                    {
                        subDeterminant(m, n, mCopy, i, j);
                        opMat[i][j] = -(determinant(m - 1, n - 1, mCopy));
                        for(int k = 0; k < m; k++)
                        {
                            for (int l = 0; l < n; l++)
                            {
                                mCopy[k][l] = mat[k][l]; //setting the matrix copy again as a copy of the argument matrix to use it again after the the for cycle makes new iteration
                            }
                        }
                    }
                }
            }
            for(int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    trOpMat[i][j] = opMat[j][i];//transposing that matrix (according to the formula for opposite matrices)
                    trOpMat[i][j] /= determinant(m, n, mat); //deviding each elemt with the determinant of the argument matrix according to the formula for opposite matrices)
                }
            }
            cout << "The opposite matrix is: " << endl;
            printMat(m, n, trOpMat);//printing that matrix
        }
        else cout << "the determinant is 0. Matrix opposite to to the current one doest not exist!" << endl;//when the determinant of the argument matrix is 0
    }
    else cout << "the dimensions of the matrix should be equal" << endl;//when the dimensions of the argument matrix are not equal
}

char endMesseges() //function that prints messages and asks what we want to do with the program when an operation is finished
{
    cout << "press B to turn back to the MENU" << endl;//back to menu option
    cout << "press F to finish with the operations" << endl;//end the program option
    char backToMenu;
    cin >> backToMenu; //we type our answer
    while(backToMenu != 'F' && backToMenu!= 'B')
    {
        cout << "Please enter a valid letter." << endl; //when the answer is not "F" or "B" we have to type it again
        cin >> backToMenu;
    }
    if(backToMenu == 'B')
    {
        return 'B';//returns B
    }
    if(backToMenu == 'F')
    {
        return 'F';//returns F
    }
}


int loadFile(char fileName[])//function that loads file
{
    ifstream file(fileName);
    if (!file.is_open())//if the file is not open
    {
        return -1;
    }
    const int MAX_SIZE = 150;//max size of each row in the file
    char str[MAX_SIZE];//creates a string for each row

    while (!file.eof())//if the file it's not finished
    {
        file.getline(str, MAX_SIZE);// that string's value is the same as a row from the file

        cout << str << endl;//we print it
    }
    file.close();//we close the file
    return 0;

}


int main ()
{
    cout << "Enter file name:" <<endl;
    char myStr[200] = {}; //here we type the name of the file we want to load
    cin.getline(myStr, 200);
    cout << endl;
    loadFile(myStr);//and then load it

    while(true)//we can do operations forever
    {
        cout << "Type the number of the operation you want to use: " << endl;
        char choice [1] = {}; //creating an char array that makes the user to choose the operation they want to use
        cin >> choice[0];
        while(choice[0] < '1' || choice[0] > '6')//if the choice is not between 1 and 6, the user have to initialize it again
        {
            cout << "The number of the operation is invalid" << endl;
            cin >> choice[0];
        }
        int m1, n1, m2, n2 = 0;//dimensions
        //choice "1" is for multiplying
        //choice "2" is for scalar multiply
        //choice "3" is for scalar divide
        //choice "4" is for transposing
        //choice "5" is for finding determinant
        //choice "6" is for finding the opposite matrix
        cout << "Set the two dimensions of the matrix" << endl;
        if(choice[0] == '1') cout << "(First matrix)" << endl;
        cin >> m1 >> n1;
        if(choice[0] == '5' || choice[0] == '6')// when the choice is for determinant or for opposite matrix
        {
            while(m1 != n1)//when the dimensions are not equal
            {
                cout << "The dimensions of the matrix should be equal" << endl;
                cout << "Set the two dimensions of the matrix" << endl;
                cin >> m1 >> n1;//initializing them again
            }
        }
        double** myMat1 = new double* [m1]; //creating a matrix that the user initialize
        for(int i = 0; i < m1; i++)
        {
            myMat1[i] = new double[n1];
        }
        cout << "Now initialize the matrix" << endl;
        initializeMat(m1, n1, myMat1);

        if(choice[0] == '1')
        {
            cout << "Set the two dimensions for the matrix" << endl;
            cout << "(Second one)" << endl;
            cin >> m2 >> n2;
            while(m2 != n1)
            {
                cout << "the second dimension of the first matrix and the first dimension of the second matrix should be equal" << endl;
                cout << "Set the two dimensions for the matrix" << endl;
                cout << "(Second matrix)" << endl;
                cin >> m2 >> n2;
            }
            cout << "Now initialize the matrix" << endl;
            double** myMat2 = new double* [m2];//a second matrix with which the first one is multiplyed
            for(int i = 0; i < m2; i++)
            {
                myMat2[i] = new double[n2];
            }
            initializeMat(m2, n2, myMat2);
            cout << "The answer is: " << endl;
            multiplyMats(myMat1, myMat2, m1, n1, m2, n2);
            if(endMesseges() == 'F')//if end messeges returns F we exit that while cycle
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
        if(choice[0] == '4')
        {
            cout << "The transposed matrix is: " << endl;
            transp(m1, n1, myMat1);
            if(endMesseges() == 'F')
            {
                break;
            }
        }
        if(choice[0] == '5')
        {
            cout << "The determinant of the matrix is: " << endl;
            cout << determinant(m1, n1, myMat1) << endl;
            if(endMesseges() == 'F')
            {
                break;
            }
        }
        if(choice[0] == '6')
        {
            opositeMat(m1, n1, myMat1);
            if(endMesseges() == 'F')
            {
                break;
            }
        }
        //if the cycle it's not broken, that means end messeges had returned B
        // so the program loads the file again
        cout << endl << endl;
        loadFile(myStr);
    }
    //when end messeges had returned F, the program prints one last message and the program ends
    cout << endl <<"Thank you for using the matrix calculator! Goodbye!" << endl;

    return 0;
}
