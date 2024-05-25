#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cmath>
// Flag for empty row
#define EMPTY -80000000

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
        int firstZero = 0;
        float pivot = EMPTY;

        for (int j = 0; j < col; j++){
            // Find pivot
            if (i == 0 && j == 0 && matrix[i][j] == 0){
                firstZero = 1;
                break;
            }

            else if (matrix[i][j] != 0){
                pivot = j;
                break;
            }
        }

        // If no pivot is found in this row or the first entry in the matrix is zero, 
        // move to the end of the matrix
        if (pivot == EMPTY || firstZero){
            matrix.push_back(matrix[i]);
            matrix.erase(matrix.begin() + i);
            // Decrement i to get back to the current row 
            i--; 

            continue;
        }

        // Make all columns under the pivot = 0
        // Keep track of the current row and the row of the pivot
        int loc = i;
        int cur = i+1;

        while (cur < row){
            // x is the value to use in the row replacement operation
            if (matrix[cur][pivot] != 0){
                float x = (matrix[cur][pivot] / matrix[loc][pivot]);

                for(int i = 0; i < col; i++){
                    matrix[cur][i] = matrix[cur][i] - (x * matrix[loc][i]);
                }
            }
            
            cur++;
        }

        printMatrix(matrix);
    }
}

void reducedForm(std::vector<std::vector<float>> &matrix){
    std::cout << "\n Matrix in Reduced Echelon Form:\n";
    int row, col;
    row = matrix.size();
    col = matrix[0].size();

    int i, j;
    for (int i = row-1; i >= 0; i--){
        float pivot = EMPTY;

        for (int j = 0; j < col-2; j++){
            // Find pivot
            if (matrix[i][j] != 0){
                pivot = j;
                break;
            }
        }

        // If no pivot is found in this row, move on 
        if (pivot == EMPTY){
            continue;
        }

        else if (i != 0) {
            std::cout << "pivot:" << pivot << "\n";
            // Keep track of the current row and the row of the pivot
            int loc = i;
            int cur = i-1;
            float d;
            
            // d is the scalar used to make the pivot 1 (which is 1/pivot)
            if (matrix[loc][pivot] < 0){
                d = matrix[loc][pivot];
            }
            else {
                d = abs(matrix[loc][pivot]);
            }

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
        
    std::ifstream input("test cases/7.txt", std::ios_base::in);
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
