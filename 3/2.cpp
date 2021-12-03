// compile with at least C++17, i.e. -std=c++17
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <tuple>
#include <algorithm>

constexpr auto inputFile = "input.txt";
bool lineStatusInitialized = false;
std::vector<std::tuple<std::string, bool, bool>> lineStatus;

bool nextLine(std::string& line, int lineIndex)
{
    if(!lineStatusInitialized)
    {
        static std::ifstream inputFileStream(inputFile, std::ios_base::in);
        if(!inputFileStream.is_open())
        {
            return false;
        }

        if(!std::getline(inputFileStream, line))
        {
            lineStatusInitialized = true;
            return false;
        }

        lineStatus.emplace_back(std::tuple<std::string, bool, bool>{line, true, true});

        return true;
    }

    if(lineIndex >= lineStatus.size())
        return false;

    line = std::get<0>(lineStatus.at(lineIndex));
    return true;
}

int main(int argc, char* argv[])
{
    std::vector<std::array<int, 4>> bitCounts;
    size_t currentBitPosition = 0;

    int oxygenGeneratorCounter = 0;
    int co2ScrubberCounter = 0;

    int oxygenGeneratorRating = 0;
    int co2ScrubberRating = 0;

    do
    {
        for (auto [line, lineIndex] = std::tuple(std::string(), 0); nextLine(line, lineIndex); ++lineIndex)
        {
            auto& currentLineStatus = lineStatus.at(lineIndex);
            auto& keepByMostCommon = std::get<1>(currentLineStatus);
            auto& keepByLeastCommon = std::get<2>(currentLineStatus);

            bool lastBitIteration = !(currentBitPosition < line.length());

            if(!lastBitIteration)
            {
                if(bitCounts.size() <= currentBitPosition)
                {
                    bitCounts.emplace_back(std::array<int, 4>{0, 0, 0, 0});
                }

                auto& currentBitCounts = bitCounts.at(currentBitPosition);
                int currentLineCurrentBit = line.at(currentBitPosition) - '0';

                if(keepByMostCommon)
                {
                    ++currentBitCounts[0 + currentLineCurrentBit];
                }
                if(keepByLeastCommon)
                {
                    ++currentBitCounts[2 + currentLineCurrentBit];
                }
            }

            if(currentBitPosition > 0)
            {
                const auto& previousBitCounts = bitCounts.at(currentBitPosition - 1);
                auto mostCommonForPreviousBitPosition = previousBitCounts[1] >= previousBitCounts[0] ? 1 : 0;
                auto leastCommonForPreviousBitPosition = previousBitCounts[2 + 0] <= previousBitCounts[2 + 1] ? 0 : 1;

                int currentLinePreviousBit = line.at(currentBitPosition - 1) - '0';
                
                if(keepByMostCommon && mostCommonForPreviousBitPosition != currentLinePreviousBit)
                {
                    if(!lastBitIteration)
                    {
                        int currentLineCurrentBit = line.at(currentBitPosition) - '0';
                        auto& currentBitCounts = bitCounts.at(currentBitPosition);
                        --currentBitCounts[currentLineCurrentBit];
                    }

                    if(oxygenGeneratorCounter != lineStatus.size() - 1)
                    {
                        keepByMostCommon = false;
                        ++oxygenGeneratorCounter;
                    }
                }
                
                if(keepByLeastCommon && leastCommonForPreviousBitPosition != currentLinePreviousBit)
                {
                    if(!lastBitIteration)
                    {
                        int currentLineCurrentBit = line.at(currentBitPosition) - '0';
                        auto& currentBitCounts = bitCounts.at(currentBitPosition);
                        --currentBitCounts[2 + currentLineCurrentBit];
                    }
                    
                    if(co2ScrubberCounter != lineStatus.size() - 1)
                    {
                        keepByLeastCommon = false;
                        ++co2ScrubberCounter;
                    }
                }

                if(lastBitIteration)
                {
                    if(keepByMostCommon)
                    {
                        oxygenGeneratorRating = std::stoi(line, 0, 2);
                    }

                    if(keepByLeastCommon)
                    {
                        co2ScrubberRating = std::stoi(line, 0, 2);
                    }
                }
            }
        }
        ++currentBitPosition;
    } while(currentBitPosition <= bitCounts.size());

    std::cout << oxygenGeneratorRating * co2ScrubberRating << std::endl;

    return 0;
}