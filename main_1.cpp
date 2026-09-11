#include <iostream>
#include <fstream>
#include "array_double.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
        return 0;
    }

    int N = stoi(argv[1]);
    const char* inputFileName = argv[2];
    const char* ignoreWordFileName = argv[3];

    string ignoreWords[50];
    getIgnoreWords(ignoreWordFileName, ignoreWords);

    ifstream inputFile(inputFileName);

    if (!inputFile.is_open())
    {
        cout << "Failed to open " << inputFileName << endl;
        return 0;
    }

    int arraySize = 100;
    wordRecord* distinctWords = new wordRecord[arraySize];

    int numDistinctWords = 0;
    int timesDoubled = 0;

    string word;

    while (inputFile >> word)
    {
        if (isIgnoreWord(word, ignoreWords, 50))
        {
            continue;
        }

        bool found = false;

        for (int i = 0; i < numDistinctWords; i++)
        {
            if (distinctWords[i].word == word)
            {
                distinctWords[i].count++;
                found = true;
                break;
            }
        }

        if (!found)
        {
            if (numDistinctWords == arraySize)
            {
                int newSize = arraySize * 2;
                wordRecord* newArray = new wordRecord[newSize];

                for (int i = 0; i < numDistinctWords; i++)
                {
                    newArray[i] = distinctWords[i];
                }

                delete[] distinctWords;
                distinctWords = newArray;
                arraySize = newSize;
                timesDoubled++;
            }

            distinctWords[numDistinctWords].word = word;
            distinctWords[numDistinctWords].count = 1;
            numDistinctWords++;
        }
    }

    inputFile.close();

    int totalNonCommonWords = getTotalNumberNonIgnoreWords(distinctWords, numDistinctWords);

    sortArray(distinctWords, numDistinctWords);

    cout << "Array doubled: " << timesDoubled << endl;
    cout << "Distinct non-common words: " << numDistinctWords << endl;
    cout << "Total non-common words: " << totalNonCommonWords << endl;

    printTenFromN(distinctWords, N, totalNonCommonWords);

    delete[] distinctWords;

    return 0;
}