#include <iostream>
#include <vector>
#include <string>
#include <sstream>


void computeInput();
void solveProblem1(std::vector<int> &values);
void solveProblem2(std::vector<std::vector<int>> &values);
void printValues(std::vector<int> &values);


int main()
{
    computeInput();
    return 0;
}



/**
 * @brief 
 *      reads the input given and executes the program
 *      accordingly. If the first int read is a 1 we want
 *      to solve problem1, if its a 2 we want to solve
 *      problem2.
 */
void computeInput()
{
    int problem, val;

    std::cin >> problem;

    if(!std::cin) {
        std::cout << "input error" << std::endl;
        exit(1);
    }
    
    if(problem == 1) {

        std::vector<int> values1;

        while(std::cin >> val) {
            values1.push_back(val);
        }

        solveProblem1(values1);
    }
    else if(problem == 2) {

        std::vector<std::vector<int>> values2;
        std::string line;

        while(getline(std::cin, line)) {
            
            if(!line.empty()) {

                std::stringstream stream(line);
                std::vector<int> aux;

                while(stream >> val) {
                    aux.push_back(val);
                }

                values2.push_back(aux);
            }
        }

        solveProblem2(values2);
    }
    else {
        std::cout << "invalid input...ending" << std::endl;
    }
}



void solveProblem1(std::vector<int> &values)
{
    std::cout << "joao1\n _____________" << std::endl;

    printValues(values);
}



void solveProblem2(std::vector<std::vector<int>> &values)
{
    std::cout << "joao2\n _____________" << std::endl;

    for(std::vector<int> vec: values)
        printValues(vec);
}



void printValues(std::vector<int> &values)
{
    std::cout << "[ ";

    for(int v: values) {
        std::cout << v << " ";
    }

    std::cout << "]" << std::endl;
}
