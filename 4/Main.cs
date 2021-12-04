/**
 * compile / run via: dotnet run (.NET 6)
 * The scores are output according to their winning series,
 * i.e. first output is first won, last output is last won
 */
using StreamReader streamReader = new StreamReader("_input.txt");
var numbersString = streamReader.ReadLine() ?? throw new Exception("Unable to read file.");
var numbers = numbersString.Split(",", StringSplitOptions.RemoveEmptyEntries).Select(callNumber => int.Parse(callNumber));

List<BingoBoard> bingoBoards = new();
BingoBoard? currentBingoBoard = null;

string? line;
int row = 0;
while((line = streamReader.ReadLine()) != null)
{
    if(line.Length == 0)
    {
        currentBingoBoard = new BingoBoard();
        bingoBoards.Add(currentBingoBoard);
        row = 0;
        continue;
    }

    string[] rowCells = line.Split(new char[0], StringSplitOptions.RemoveEmptyEntries);
    for(int column = 0; column < rowCells.Length; column++)
    {
        if(currentBingoBoard != null)
        {
            currentBingoBoard.BoardMatrix[row, column].Number = int.Parse(rowCells[column]);
        }
    }

    row++;
}

foreach(var number in numbers)
{
    foreach(var bingoBoard in bingoBoards)
    {
        bingoBoard.DrawNumber(number);
    }
}