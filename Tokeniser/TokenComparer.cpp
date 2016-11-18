using namespace std;

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>

//accept two arguments
int main(int argc, char *argv[])
{
    //check number of arguments
    int first, second;
    //self compare
    if (argc == 2)
    {
        first = 1;
        second = 1;
    }
    //two file compare
    else
    {
        first = 1;
        second = 2;
    }

    //read files into vectors
    std::ifstream is1(argv[first]);
    std::istream_iterator<string> start1(is1), end1;
    std::vector<string> file1(start1, end1);

    std::ifstream is2(argv[second]);
    std::istream_iterator<string> start2(is2), end2;
    std::vector<string> file2(start2, end2);

    //initialise number of tokens and score
    int fileSize = file1.size();
    int score = 0;
    int scoreMulti = 2;

    //loop over every token
    for (int i = 0; i < fileSize; i++)
    {
        for (int j = 0; j < file2.size(); j++)
        {
            //begin comparison loop
            if (file1[i] == file2[j])
            {
                j++;
                int k = i;
                k++;
                //break if end of tokens
                if (j >= file2.size())
                {
                    break;
                }
                if (k >= file1.size())
                {
                    break;
                }
                //increase score while the next token is a copy
                while (file1[k] == file2[j])
                {
                    //increase score and multiplier
                    score += scoreMulti;
                    scoreMulti += 3;
                    j++;
                    k++;
                    if (j >= file2.size())
                    {
                        break;
                    }
                    if (k >= file1.size())
                    {
                        break;
                    }
                }
                //reset multiplier
                scoreMulti = 2;
            }
        }
    }

    //print score for self comparison
    if (argc == 2)
    {
        int res = score;

        cout << res;
    }
    //print structured score for multi file comparison
    else
    {
        score = score / fileSize;
        cout << setw(50) << left << argv[2] << "  |  " << score << endl;
    }
}
