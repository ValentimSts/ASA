/**
 * @file
 *   p1.cpp
 * 
 * @author
 *   Grupo: al012
 *      - Valentim Santos ist199343
 *      - Tiago Santos ist199333
 */


#include <iostream>
#include <vector>
#include <string>
#include <sstream>


int main()
{
    computeInput();
    return 0;
}



/**
 * @brief 
 *   reads the input given and executes the program
 *   accordingly. If the first int read is a 1 we want
 *   to solve problem1, if its a 2 we want to solve
 *   problem2.
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



/**
 * @brief 
 *   returns the index of the next value of the vector higher than the key given.
 * 
 * @param values
 *   vector of values
 * @param left
 *   left boudary of the vector
 * @param right
 *   right boundary of the vector
 * @param key
 *   key used reference
 * @return
 *   index of highest value smaller than key
 */
int LISBinarySearch(std::vector<int> &values, int left, int right, int key)
{
    int middle;

    while (right - left > 1) {

        middle = left + (right - left) / 2;

        if (values[middle] >= key)
            right = middle;

        else
            left = middle;
    }
 
    return right;
}
 

/**
 * @brief 
 *   finds the length of the longest increasing subsequence of a sequence, aswell as the number
 *   of subsequences of the same length.
 * 
 * std::vector<int> aux:
 *   - vector containing the highest values of the longest subsequence of length j (from
 *     the origianl vector). j being an index of aux.
 * 
 *     example:
 *         - if the longest subsequence of length 3 from the "values" vector is < 1, 3, 4 >
 *           then aux[3] - 4
 * 
 * int len:
 *   - stores the index of the first empty slot in the aux array (starting at 1)
 * int max_counter:
 *   - counter to keep track of  the number of subsequences of max size
 * 
 * @param values
 *   the sequence in question
 * @return 
 *   length of the longest increasing subsequence
 */
void LongestIncreasingSubsequence(std::vector<int> &values)
{
    int size = values.size();

    if (size <= 1)  {
        std::cout << size << " 1" << std::endl;
        return;
    }

    std::vector<int> aux(size, 0);

    aux[0] = values[0];

    int len = 1;
    int max_counter = 1;
 
    for (int i = 1; i < size; i++) {
 
        // values[i] is the new smallest value. We replace the current one in the aux vector
        // for this new one.
        if (values[i] < aux[0])
            aux[0] = values[i];
 
        // values[i] is the new highest value. We add it to the aux vector, as it is now
        // the new end value for the new longest subsequence.
        else if (values[i] > aux[len - 1])
            aux[len++] = values[i];
 
        // values[i] is neither smaller than the first value of aux, nor is it greater than the last one.
        // We replace the next higher value than values[i], from aux, with values[i] and increment
        // max_counter, as there is now one more subsequence of the max current size.
        else {
            int index = LISBinarySearch(aux, 0, len - 1, values[i]);
            aux[index] = values[i];

            if(index == len-1)
                max_counter++;
        }
    }

    std::cout << len << " " << max_counter << std::endl;
}



void solveProblem1(std::vector<int> &values)
{
    std::cout << "Sequence:" << std::endl;
    printValues(values);

    LongestIncreasingSubsequence(values);
}


/**
 * @brief 
 *   finds the length of the longest common subsequence between two
 *   integer sequences given.
 * 
 * @param values1
 *   the first sequence
 * @param values2
 *   the second sequence
 * @param i
 *   sequence one's iterator
 * @param j
 *   sequence two's iterator
 * @return 
 *   length of the longest common subsequence
 */
int LongestCommonSubsequence(std::vector<int> &values1, std::vector<int> &values2, int i, int j)
{
    // if either i or j are 0 it means we have gone through every element of values1
    // or values2, respectively, and so we can stop.
    if(i == 0 || j == 0)
        return 0;

    else if(values1[i] == values2[j])
        return 1 + LongestCommonSubsequence(values1, values2, i-1, j-1);

    else
        return std::max(LongestCommonSubsequence(values1, values2, i, j-1), LongestCommonSubsequence(values1, values2, i-1, j));

}



void solveProblem2(std::vector<std::vector<int>> &values)
{
    int res;

    std::cout << "Sequences:" << std::endl;
    for(std::vector<int> vec: values)
        printValues(vec);

    int i = values[0].size();
    int j = values[1].size();

    res = LongestCommonSubsequence(values[0], values[1], i, j);

    std::cout << res << std::endl;   
}



void printValues(std::vector<int> &values)
{
    std::cout << "[ ";

    for(int v: values) {
        std::cout << v << " ";
    }

    std::cout << "]" << std::endl;
}
