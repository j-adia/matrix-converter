// Converts a matrix into echelon form using Gaussian Elimination

#include <iostream>
#include <vector>
#include <iomanip>
#include <limits.h>
#include <fstream>
#include <string>
#include <numbers>

#define FLOAT_MIN -80000000.0

void printMatrix(std::vector<std::vector<float>> &matrix){
    int rows = matrix.size();
    int cols = matrix[0].size(); 

    std::cout << std::setw((6*cols) + 1) << std::left << " _";
    std::cout << std::setw((5*cols) - 2) << std::right << "_";
    std::cout << "\n";

    int i, j;

    for (i = 0; i < rows; i++){
        if (i == rows-1){
            std::cout << std::setw(6) << std::left << "|_";

            for (j = 0; j < cols; j++){
                if (j == cols-1){
                    std::cout << std::fixed << std::setprecision(2) << std::setw(7) << std::left << matrix[i][j]; 
                }
                else {
                    std::cout << std::fixed << std::setprecision(2) << std::setw(9) << std::left << matrix[i][j];
                }
            }

            std::cout << "_|";
        }

        else {
            std::cout << "|";

            for (j = 0; j < cols; j++)
                std::cout << std::fixed << std::setprecision(2) << std::setw(9)  << std::right << matrix[i][j];

            std::cout << std::setw(5) << "|"; 
            std::cout << "\n";
        }
    }

    std::cout << "\n";
}

void echelonForm(std::vector<std::vector<float>> &matrix){
    std::cout << "\n Matrix in Echelon Form:\n";
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
        if (pivot == FLOAT_MIN){
            matrix.push_back(matrix[i]);
            matrix.erase(matrix.begin() + i);
        }

        // Make all columns under the pivot = 0
        else {
            // Keep track of the current row and the row of the pivot
            int loc = i;
            int cur = i+1;

            while (cur < row){
                // x is the value to use in the row replacement operation
                float x = (matrix[cur][pivot] / matrix[loc][pivot]);

                for(int i = 0; i < col; i++)
                    matrix[cur][i] = matrix[cur][i] - (x * matrix[loc][i]);

                cur++;
            }
        }
    }

    printMatrix(matrix);
}

void reducedForm(std::vector<std::vector<float>> &matrix){
    std::cout << "\n Matrix in Reduced Echelon Form:\n";
    int row, col;
    row = matrix.size();
    col = matrix[0].size();

    int i, j;
    for (int i = row-1; i >= 0; i--){
        float pivot = FLOAT_MIN;

        for (int j = 0; j < col-2; j++){
            // Find pivot
            if (matrix[i][j] != 0){
                pivot = j;
                break;
            }
        }

        // If no pivot is found in this row, move on 
        if (pivot == FLOAT_MIN){
            continue;
        }

        else if (i != 0) {
            // Keep track of the current row and the row of the pivot
            int loc = i;
            int cur = i-1;
            
            // d is the scalar used to make the pivot 1 (which is 1/pivot)
            float d = matrix[loc][pivot];
            float x = matrix[cur][pivot];

            // Divide every value in the same row by the scalar
            // Then, make the values above the pivot = 0
            while (cur >= 0){
                for(int i = 0; i < col; i++){
                    matrix[loc][i] /= d;
                    matrix[cur][i] = matrix[cur][i] - (x * matrix[loc][i]); 
                }
                cur--;
            }
        }
    }

    printMatrix(matrix);
}

int main(){
    std::cout << "Welcome to the Matrix Equation Solver!\n";
        
    std::ifstream input("m34.txt", std::ios_base::in);
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

    std::cout << "\nOriginal Matrix:\n";
    printMatrix(equationSet);
    echelonForm(equationSet);
    reducedForm(equationSet);


    return 0;
}
