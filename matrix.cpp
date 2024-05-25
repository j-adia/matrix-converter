#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cmath>
// flag for empty row
#define EMPTY -8000000

// -~- prototypes -~-
void printMatrix(std::vector<std::vector<float>> &matrix);
void echelonForm(std::vector<std::vector<float>> &matrix);
void reducedForm(std::vector<std::vector<float>> &matrix);

int main(int argc, char * argv[]){
    if (argc < 1){
        std::cout << "No filename entered";
        return -1;
    }

    std::ifstream input(argv[1], std::ios_base::in);
    if (!input.is_open()){
        std::cout << "Error opening file.";
        return -1;
    }

    std::cout << "Welcome to the Matrix Equation Solver!\n";
    int rows, cols;
    input >> rows;
    input >> cols;
    std::vector<std::vector<float>> equationSet;

    // create the matrix
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

    std::cout << "\noriginal matrix:\n";
    printMatrix(equationSet);
    echelonForm(equationSet);
    reducedForm(equationSet);

    return 0;
}

void printMatrix(std::vector<std::vector<float>> &matrix){
    int rows = matrix.size();
    int cols = matrix[0].size(); 
    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++)
            std::cout << std::fixed << std::setprecision(2) << std::setw(9)  << std::right << matrix[i][j];

        std::cout << "\n";
    }
}

void echelonForm(std::vector<std::vector<float>> &matrix){
    std::cout << "\n echelon form:\n";
    int row, col;
    row = matrix.size();
    col = matrix[0].size();

    int i, j;
    for (int i = 0; i < row; i++){
        bool firstZero = false; 
        int pivot = EMPTY;

        for (int j = 0; j < col; j++){
            if (i == 0 && j == 0 && matrix[i][j] == 0){
                firstZero = true; // flag if the first entry in the matrix is 0
                break;
            }
            // find pivot
            else if (matrix[i][j] != 0){
                pivot = j;
                break;
            }
        }

        // if no pivot is found in this row or the first entry is zero, 
        // move row to the end of the matrix
        if (pivot == EMPTY || firstZero){
            matrix.push_back(matrix[i]);
            matrix.erase(matrix.begin() + i);
            i--; // backtrack to the previous row 

            continue;
        }
        // make all columns under the pivot = 0
        // keep track of the current row and the row of the pivot
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
    }
    printMatrix(matrix);
}

void reducedForm(std::vector<std::vector<float>> &matrix){
    std::cout << "\n reduced form:\n";

    int row, col;
    row = matrix.size();
    col = matrix[0].size();

    int i, j;
    for (int i = row-1; i >= 0; i--){  
        int pivot = EMPTY;
        
        for (int j = 0; j < col-1; j++){
            if (matrix[i][j] != 0){
                pivot = j;
                break;
            }
        }

        if (pivot == EMPTY){
            continue;
        }

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

        // divide every value in the same row by the scalar
        for(int i = 0; i < col; i++){
            matrix[loc][i] /= d;
        }

        // make the values above the pivot = 0
        while (cur >= 0){
            float x = matrix[cur][pivot];

            for(int i = 0; i < col; i++){
                matrix[cur][i] = matrix[cur][i] - (x * matrix[loc][i]); 
            }

            cur--;
        }
    }
    printMatrix(matrix);
}
