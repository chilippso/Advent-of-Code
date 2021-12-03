// compile with at least C++14, i.e. -std=c++14
#include <iostream>
#include <fstream>
#include <vector>
#include <array>

constexpr auto inputFile = "input.txt";

int main(int argc, char* argv[])
{
    int ret = 0;
    std::string line;
    std::ifstream inputFileStream;
    
    std::vector<std::array<int, 2>> bitStatus;
    std::vector<int> gammaRateBits;
    std::vector<int> epsilonRateBits;

    inputFileStream.open(inputFile);

    if(inputFileStream.is_open())
    {
        while(getline(inputFileStream, line))
        {
            for(int bitIndex = 0; bitIndex < line.length(); bitIndex++)
            {
                if(bitStatus.size() <= bitIndex)
                {
                    std::array<int, 2> empty {0, 0};
                    bitStatus.emplace_back(empty);
                }

                auto& currentBitStatus = bitStatus.at(bitIndex);
                auto& currentBit = line.at(bitIndex);

                switch(currentBit)
                {
                case '0':
                    currentBitStatus[0]++;
                    break;
                case '1':
                    currentBitStatus[1]++;
                    break;
                default:
                    break;
                }

                int currentColumnDominantBitState = currentBitStatus[1] > currentBitStatus[0] ? 1 : 0;
                int currentColumnRecessiveBitState = currentBitStatus[1] < currentBitStatus[0] ? 1 : 0;

                if(gammaRateBits.size() <= bitIndex)
                {
                    gammaRateBits.emplace_back(currentColumnDominantBitState);
                }
                else
                {
                    gammaRateBits.at(bitIndex) = currentColumnDominantBitState;
                }

                if(epsilonRateBits.size() <= bitIndex)
                {
                    epsilonRateBits.emplace_back(currentColumnRecessiveBitState);
                }
                else
                {
                    epsilonRateBits.at(bitIndex) = currentColumnRecessiveBitState;
                }
            }
        }

        int gammaRate = gammaRateBits.front();
        std::for_each(std::begin(gammaRateBits)+1, std::end(gammaRateBits), [&gammaRate](auto const& currentColumnDominantBitState) {
            gammaRate <<= 1;
            gammaRate |= currentColumnDominantBitState;
        });

        int epsilonRate = epsilonRateBits.front();
        std::for_each(std::begin(epsilonRateBits)+1, std::end(epsilonRateBits), [&epsilonRate](auto const& currentColumnRecessiveBitState) {
            epsilonRate <<= 1;
            epsilonRate |= currentColumnRecessiveBitState;
        });

        std::cout << gammaRate * epsilonRate << std::endl;
    }
    else
    {
        ret = -1;
    }

    return ret;
}