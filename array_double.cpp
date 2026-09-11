#include "array_double.hpp"

void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[])
{
    ifstream ignoreFile(ignoreWordFileName);

    if (!ignoreFile.is_open())
    {
        cout << "Failed to open " << ignoreWordFileName << endl;
        return;
    }

    string word;
    int index = 0;

    while (ignoreFile >> word && index < 50)
    {
        ignoreWords[index] = word;
        index++;
    }

    ignoreFile.close();
}


bool isIgnoreWord(string word, string ignoreWords[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (word == ignoreWords[i])
        {
            return true;
        }
    }

    return false;
}


int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length)
{
    int total = 0;

    for (int i = 0; i < length; i++)
    {
        total += distinctWords[i].count;
    }

    return total;
}


void sortArray(wordRecord distinctWords[], int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        {
            bool swapNeeded = false;

            // Sort by count descending
            if (distinctWords[j].count < distinctWords[j + 1].count)
            {
                swapNeeded = true;
            }
            // If counts are equal, sort alphabetically
            else if (distinctWords[j].count == distinctWords[j + 1].count)
            {
                if (distinctWords[j].word > distinctWords[j + 1].word)
                {
                    swapNeeded = true;
                }
            }

            if (swapNeeded)
            {
                wordRecord temp = distinctWords[j];
                distinctWords[j] = distinctWords[j + 1];
                distinctWords[j + 1] = temp;
            }
        }
    }
}


void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords)
{
    cout << "Probability of next 10 words from rank " << N << endl;
    cout << "---------------------------------------" << endl;

    for (int i = N; i < N + 10; i++)
    {
        float probability = (float)distinctWords[i].count / totalNumWords;

        cout << fixed << setprecision(5)
             << probability
             << " - "
             << distinctWords[i].word
             << endl;
    }
}