# Tic-Tac-Toe-W-AI (Implemented using MiniMax Algorithm)
### Description
- The player is first prompted to select who goes first.
  Option 1 = AI first, Option 2 = Player first, Option 3 = Random
- Beware! The AI uses the MiniMax Algorithm to pick the best possible spots
on the Tic-Tac-Toe board. The best you can draw out of the AI is a tie!
- When its their turn, the player is prompted to enter a row number
 and a column number.
- For example: 1,2 is row 1, column 2
- The game will continue until someone has 3 in a row or until all 
 available spaces are taken (A tie).

### Complications
-My biggest issue was the fact that I used global variables
 at the wrong times. There were a few global variables that 
 needed to be local, and I wasted time realizing that.

-The algorithm itself is easy to comprehend. If we had not done
 a 3x3 Tic-Tac-Toe, there would need to be more adjustments to scores.
