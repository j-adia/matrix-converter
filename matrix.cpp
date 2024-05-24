#include <iostream>
#include <vector>
#include <iomanip>
#include <limits.h>
#include <fstream>
#include <string>
#include <numbers>

#define FLOAT_MIN -80000000.0

// using namespace std; (best practice to ommit this)

// needs fixing :(
void printMatrix(std::vector<std::vector<float>> matrix){
    int rows = matrix.size();
    int cols = matrix[0].size(); 

    std::cout << std::setw((6*cols) - (cols)) << std::left << " _";
    std::cout << std::setw(5) << std::right << "_";
    std::cout << "\n";

    int i, j;

    for (i = 0; i < rows; i++){
        if (i == rows-1){
            std::cout << std::setw(5) << std::left << "|_";

            for (j = 0; j < cols; j++)
                std::cout << matrix[i][j] << std::setprecision(2) << std::setw(4) << std::right << " ";

            std::cout << "_|";
        }

        else {
            std::cout << std::setw(5) << std::left << "|";

            for (j = 0; j < cols; j++)
                std::cout << std::setw(5) << std::setprecision(2) << std::left << matrix[i][j];

            std::cout << "|"; 
            std::cout << "\n";
        }
    }

    std::cout << "\n";
}

void echelonForm(std::vector<std::vector<float>> matrix){
    int row, col;
    row = matrix.size();
    col = matrix[0].size();

    int i, j;
    for (int i = 0; i < row; i++){
        float pivot = FLOAT_MIN;

        for (int j = 0; j < col; j++){
            // Find pivot
            if (matrix[i][j] != 0){
                pivot = j;
                break;
            }
        }

        // If no pivot is found in this row, move to the end of the matrix
        if (pivot == INT_MIN){
            matrix.push_back(matrix[i]);
            matrix.erase(matrix.begin() + i);
        }

        // Make all columns under the pivot = 0
        else {
            // Keep track of the current row
            int cur = i+1;

            if (cur == row-1)
                break;
            // x is the value to use in the row replacement operation
            float x = (matrix[cur][pivot] / matrix[cur-1][pivot]);

            while (cur < row){
                for(int i = 0; i < col; i++)
                    matrix[cur][i] = matrix[cur][i] - (x * matrix[cur-1][i]);

                cur++;
            }
        }
    }

    printMatrix(matrix);
}

int main(){
    std::cout << "Welcome to the Matrix Equation Solver!\n";
        
    std::ifstream input("m1.txt", std::ios_base::in);
    if (!input.is_open()){
        std::cout << "Error opening file.";
        return 1;
    }

    int rows, cols;

    input >> rows;
    input >> cols;

    std::vector<std::vector<float>> equationSet;

    for (int i = 0; i < rows; i++){
        std::vector<float> equation;
        float val;

        while(input >> val){
            equation.push_back(val);

            if (input.peek() == '\n')
                break;
        }

        equationSet.push_back(equation);
    }

    printMatrix(equationSet);
    echelonForm(equationSet);


    return 0;
}
