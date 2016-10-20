

using namespace std;

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm> // for std::copy
#include <iomanip>

int main(int argc, char *argv[])
{
    int first, second;
    if (argc == 2)
    {
        first = 1;
        second = 1;
    }
    else
    {
        first = 1;
        second = 2;
    }
    //cout<<argv[1]<<endl;
    std::ifstream is1(argv[first]);
    std::istream_iterator<string> start1(is1), end1;
    std::vector<string> file1(start1, end1);

    std::ifstream is2(argv[second]);
    std::istream_iterator<string> start2(is2), end2;
    std::vector<string> file2(start2, end2);

    // print the numbers to stdout

    int fileSize = file1.size();
    int score = 0;
    int scoreMulti = 2;

    for (int i = 0; i < fileSize; i++)
    {
        for (int j = 0; j < file2.size(); j++)
        {
            if (file1[i] == file2[j])
            {
                j++;
                int k = i;
                k++;
                if (j >= file2.size())
                {
                    break;
                }
                if (k >= file1.size())
                {
                    break;
                }
                while (file1[k] == file2[j])
                {

                    score += scoreMulti;
                    scoreMulti += 1;
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
                scoreMulti = 1;
            }
        }
    }


    if (argc == 2)
    {
        int res = score;
        
        cout << res;
    }
    else
    {
        std::ifstream total(argv[3]);
        std::istream_iterator<string> start3(total), end3;
        std::vector<string> file3(start3, end3);
        
        score = score/fileSize;
        
        cout << setw(50) << left << argv[2] << "  |  " << score << endl;
    }
    // std::copy(numbers.begin(), numbers.end(),
    // std::ostream_iterator<string>(std::cout, " "));
    // std::cout << std::endl;

    // return 0;
}
