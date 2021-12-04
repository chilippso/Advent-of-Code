public class BingoBoard
{
    public BingoBoardCell[,] BoardMatrix { get; } = new BingoBoardCell[5,5];

    public bool Finished {get; protected set;} = false;

    public BingoBoard()
    {
        for(int row = 0; row < 5; row++)
        {
            for(int column = 0; column < 5; column++)
            {
                BoardMatrix[row,column] = new BingoBoardCell();
            }
        }
    }

    public bool DrawNumber(int number)
    {
        if(Finished)
        {
            return true;
        }

        bool[] columnCompleted = new[] {true,true,true,true,true};
        bool rowCompleted = true;

        for(int row = 0; row < 5; row++)
        {
            rowCompleted = true;
            for(int column = 0; column < 5; column++)
            {
                BingoBoardCell boardCell = BoardMatrix[row, column];

                if (boardCell.Number == number)
                {
                    boardCell.IsMarked = true;
                }
                if(!boardCell.IsMarked)
                {
                    rowCompleted = false;
                    columnCompleted[column] = false;
                }
            }
            if(rowCompleted)
            {
                break;
            }
        }

        bool isWinningBoard = rowCompleted;
        if(!isWinningBoard)
        {
            foreach(var isColumnCompleted in columnCompleted)
            {
                if(isColumnCompleted)
                {
                    isWinningBoard = true;
                    break;
                }
            }
        }

        
        if(isWinningBoard)
        {
            int unmarkedSum = 0;

            for(int row = 0; row < 5; row++)
            {
                for(int column = 0; column < 5; column++)
                {
                    BingoBoardCell boardCell = BoardMatrix[row, column];

                    if(!boardCell.IsMarked)
                    {
                        unmarkedSum += boardCell.Number;
                    }
                }
            }

            int score = unmarkedSum * number;
            Console.WriteLine("Score: " + score);
            Finished = true;
        }

        return Finished;
    }
}