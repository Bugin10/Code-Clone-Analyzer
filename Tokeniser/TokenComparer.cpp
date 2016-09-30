using namespace std;

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm> // for std::copy
#include <iomanip>  

int main(int argc,char *argv[])
{
    //cout<<argv[1]<<endl;
    std::ifstream is1(argv[1]);
    std::istream_iterator<string> start1(is1), end1;
    std::vector<string> file1(start1, end1);

    
    std::ifstream is2(argv[2]);
    std::istream_iterator<string> start2(is2), end2;
    std::vector<string> file2(start2, end2);

    // print the numbers to stdout

    int fileSize = file1.size();
    int score = 0;
    int scoreMulti = 1;

    for(int i=0; i<fileSize; i++) {
        for(int j=0; j<file2.size(); j++) {
            if(file1[i] == file2[j])
            {
                j++;
                int k = i;
                k++;
                if(j>=file2.size())
                {
                    break;
                }
                if(k>=file1.size())
                {
                    break;
                }
                while(file1[k] == file2[j])
                {

                    score+= scoreMulti;
                    scoreMulti = scoreMulti += 2;
                    j++;
                    k++;
                    if(j>=file2.size())
                    {
                        break;
                    }
                    if(k>=file1.size())
                    {
                        break;
                    }
                }
                scoreMulti =1;
            }
        }
    }
    score /= fileSize;
    cout<<setw(50) <<left <<argv[2]<< "  |  "<<score<<endl;

    // std::copy(numbers.begin(), numbers.end(), 
    // std::ostream_iterator<string>(std::cout, " "));
    // std::cout << std::endl;

   // return 0;
}





