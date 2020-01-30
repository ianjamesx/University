public class BaffleGame {
	
	//constants
	
	static final int ROWS = 10;
	static final int COLUMNS = 10;
	
	//keeping track of how many baffles per difficulty
	
	static final int EASY = 4;
	static final int MEDIUM = 7;
	static final int HARD = 10;
	
	//each baffle has three elements (row, column, and direction)
	
	static final int BAFFLEDATA = 4;
	
	//keeping track of baffles for each direction
	
	static final char RIGHTBAFFLE = '/';
	
	//escape the forward slash
	
	static final char LEFTBAFFLE = '\\';
	
	//counters for score, guesses, and number of shots
	
	int score = 0, guesses = 0, shots = 0;
	
	//game boards, main board and cheat board
	
	char[][] board;
	char[][] cheatBoard;
	
	//2d array for all baffle locations (each index holds row, column, and direction)
	
	int[][] baffleLoc;
	
	//the player's difficulty
	
	int difficulty;
	
	//the number of baffles (based on difficulty)
	
	int baffleNumber;
	
	//an enum to keep track of direction (for laser shooting)
	
	static public enum Dir {
		
		UP,
		DOWN,
		RIGHT,
		LEFT
		
	}
	
	public BaffleGame() {
		
		//default constructor (in this case, the only constructor)
		
		board = new char[ROWS][COLUMNS];
		cheatBoard = new char[ROWS][COLUMNS];
		
	}
	
	public void setDifficulty(int level) {
		
		//for setting game difficulty
		
		difficulty = level;
		
	}
	
	public void printStats() {
		
		System.out.println("Your score: " + score);
		System.out.println("The number of guesses you've made: " + guesses);
		System.out.println("The number of shots you've taken: " +  shots);
	}
	
	public void initBoard() {
		
		//initialize board
		
		int i, j;
		
		for(i = 0; i < ROWS; i++) {
			
			for(j = 0; j < COLUMNS; j++) {
				
				board[i][j] = ' ';
				
				cheatBoard[i][j] = ' ';
			}
			
		}
		
	}
	
	public void printBoard(boolean cheat) {
		
		//print out board
		
		int i, j;
			
		//first, print top row labels
			
		//print out two spaces to push top labels over 
			
		System.out.print("  ");
			
		for(i = 10; i < 20; i++) {
				
			System.out.print(i + "  ");
			
		}
			
		//break line
			
		System.out.println("");
			
		for(i = 0; i < ROWS; i++) {
				
			//print out inverse of i (when i is 0, print 9, i is 1, print 8 and so on)
			
			//we subtract i by 9, then turn it back into a positive by multiplying by -1
				
			System.out.print((i - 9) * -1 + " ");
				
			for(j = 0; j < COLUMNS; j++) {
				
				//check if player is cheating or not (wants to see baffles)
				
				if(cheat) {
					
					System.out.print(cheatBoard[i][j]);
				
				} else {
					
					System.out.print(board[i][j]);
					
				}
					
				System.out.print(" | ");
				
				if(j == 9) {
					
					//last index of column, print out labels on right side as well
					
					//we can get the number by adding 20 to the row index
					
					System.out.print(i + 20);
				}
					
			}
				
			//break after each row
			
			System.out.println("");
			
		}
		
		//after done displaying the entire board, we need to display the bottom labels
		
		//first, push two spaces over
		
		System.out.print("  ");
		
		//note that this label will count down from 40 (going 39 to 30) from left to right
		
		for(i = 39; i > 29; i--) {
			
			System.out.print(i + "  ");
			
		}
		
		//put two spacers after entire board
		
		System.out.println("");
		System.out.println("");
		
	}
	
	public void generateBaffles() {
		
		int i;
		
		//see how many baffles we need based off of difficulty
		
		switch(difficulty) {
		
			case 1:
				
				baffleNumber = EASY;
				
			break;
			
			case 2:
				
				baffleNumber = MEDIUM;
				
			break;
			
			case 3:
				
				baffleNumber = HARD;
			
		}
		
		//define the baffle array
		
		baffleLoc = new int[baffleNumber][BAFFLEDATA];
		
		//assign each array index (every baffle) a row, column, and direction number at random
		
		for(i = 0; i < baffleNumber; i++) {
			
			//row (x)
		
			baffleLoc[i][0] = (int)(Math.random() * 9) + 1;
			
			//column (y)
			
			baffleLoc[i][1] = (int)(Math.random() * 9) + 1;
			
			//direction (1 represents right, 2 represents left)
			
			baffleLoc[i][2] = (int)(Math.random() * 2) + 1;
			
			//if its found or not (0 for not, 1 for found)
			
			baffleLoc[i][3] = 0;
			
		}
		
		//once we have all the baffles, we can make a cheat board
		
		assignCheatBoard();
		
	}
	
	public int getBaffleNumber() {
		
		//just a getter method for the number of baffles
		
		return baffleNumber;
		
	}
	
	public void assignCheatBoard() {
		
		int i;
		
		for(i = 0; i < baffleNumber; i++) {
			
			//find index and x and y of baffle location
			
			int baffleX = baffleLoc[i][0];
			int baffleY = baffleLoc[i][1];
			
			//assign to correct direction
			
			//a '1' denotes that it is right
			
			if(baffleLoc[i][2] == 1) {

				cheatBoard[baffleX][baffleY] = RIGHTBAFFLE;
				
			//a '2' denotes left
						
			} else {

				cheatBoard[baffleX][baffleY] = LEFTBAFFLE;
				
			}
			
		}
		
	}
	
	public int guess(int row, int col, char dir) {
		
		//value we will return, will be 0 for not found, 1 for found, 2 for found but location has already
		//been discovered
		
		int result = 0;
		
		//since baffle direction is randomly generated, we need to convert to integer
		
		int baffleDir = 1;
		
		//first switch direction to either the right or left slash
		
		if(dir == 'R') {
			
			baffleDir = 1;
		
		} else if(dir == 'L') {
			
			baffleDir = 2;
			
		}
		
		//next switch the row to address the character index
		
		row = (row - 9) * -1;
		
		//same with columns, subtract by 10 to address array indexes
		
		col -= 10;
		
		int i;
		
		//loop through all baffles to see if we find a match
		
		for(i = 0; i < baffleNumber; i++) {
			
			if(baffleLoc[i][0] == row &&
				baffleLoc[i][1] == col &&
				baffleLoc[i][2] == baffleDir) {
				
				//see if its a baffle they found
				
				if(baffleLoc[i][3] == 0) {
					
					//turn baffle to found
					
					baffleLoc[i][3] = 1;
					
					//there was a match, player has found the baffle
					
					result = 1;
					
					//turn baffle on for players non cheat map
					
					addBaffle(row, col, baffleDir);
					
					break;
					
				} else {
					
					//user's search returned a baffle that has already been found
					
					result = 2;
					
				}
				
			}
			
		}
		
		return result;
	}
	
	public void addBaffle(int row, int col, int dir) {
		
		//adds baffle to board after player has found it
		
		//assign to correct direction
		
		if(dir == 1) {

			board[row][col] = RIGHTBAFFLE;
			
		//a '2' denotes left
					
		} else {

			board[row][col] = LEFTBAFFLE;
			
		}
		
	}
	
	public int laserShot(int loc) {
		
		//iterators
		
		int i;
		
		//set direction from enum, defaulting to right
		
		Dir direction = Dir.RIGHT;
		
		//keep track of x and y coordinates (rows and columns number) that laser is currently at
		
		int xLoc = 0, yLoc = 0;
		
		//we need to determine if input (int loc parameter) is a row or column
		//to do this, we put it through two loops, one of row numbers, and one of column numbers
		//inputType will be 'R' if its a row, or 'C' if its a column number
		//it is initialized to 'N', if it stays an 'N' by time all loops are done, it is not valid input
		
		char inputType = 'N';
		
		//start by checking rows (if loc is either 0 - 9, or 20 - 29)
		//we can use this to determine its direction as well
		
		for(i = 0; i < 10; i++) {
			
			if(loc == i) {
				
				inputType = 'R';
				
				//direction will be going right
				
				direction = Dir.RIGHT;
				
			}
		
		}
		
		for(i = 20; i < 30; i++) {
			
			if(loc == i) {
				
				inputType = 'R';
				
				//direction will be going left
				
				direction = Dir.LEFT;
				
			}
			
		}
		
		//next check columns (if loc is from 10 - 19, or 30 - 39)
		
		for(i = 10; i < 20; i++) {
			
			if(loc == i) {
				
				inputType = 'C';
				
				//direction will be going down
				
				direction = Dir.DOWN;
				
			}
			
		}
		
		for(i = 30; i < 40; i++) {
			
			if(loc == i) {
				
				inputType = 'C';
				
				//direction will be going up
				
				direction = Dir.UP;
				
			}
			
		}
		
		
		if(inputType == 'N') {
			
			//input type was not matched to any row or column number
			//return an invalid response
			
			return -1;
		
		} else if(inputType == 'R'){
			
			//determine index of x-coordinate and y-coordinate from direction and input
			//if its going right, then start from first index (left most of array)
			//if going left, start from end (index 9)
			
			//however,
			//indexes for opposite coordinate will be one less or more than real index
			//(for example, index 10 instead of index 9, or index -1 instead of index 0)
			//this will check first index in row or column, as loop will skip them
			
			if(direction == Dir.RIGHT) {
				
				xLoc = (loc - 9) * -1;
				yLoc = -1;
			}
			
			else if(direction == Dir.LEFT) {
				
				xLoc = loc - 20;
				yLoc = 10;
				
			}
			
			//if its a column number
			
		} else if(inputType == 'C') {
			
			if(direction == Dir.UP) {
				
				xLoc = 10;
				yLoc = (loc - 39) * -1;
	
			}
			
			else if(direction == Dir.DOWN) {
				
				xLoc = -1;
				yLoc = loc - 10;
				
			}
			
		}
		
		//run loop until laser exits the game board
		
		boolean exit = false;
		
		//we need a value to return once finished so the user can read which index the laser exited from
		//this can be determined from the direction, so we need it in each case in case the laser exits
		//initialize to -1 so we don't get any return errors, if the loop fails to find it, it will return
		//an invalid response (-1)
		
		int exitIndex = -1;	
		
		do {
			
			/*
			
			for debugging, this will output the current row index and column index for each iteration
			
			System.out.println("CURRENT ROW: " + xLoc + " - CURRENT COL: " + yLoc);
			
			*/
			
			//compare to cheat board to see if we run into any baffles
			
			switch(direction) {
			
				case RIGHT:
					
					if(yLoc + 1 > 9) {
						
						//index doesn't exist, laser must have exited the board
						//break out of the loop
						
						exit = true;
						
						//we need to convert the row number to a user-readable number
						//addressing a specific box number
						
						exitIndex = xLoc + 20;
						
						break;
						
					} else {
						
						//increment y location (column index)
						
						yLoc++;
						
						//if its blank, then continue with the loop
						
						if(cheatBoard[xLoc][yLoc] == ' ') {
							
							//no baffle found, lets keep going
							
							continue;
							
							//or if its facing right, then redirect direction upward
							
						} else if(cheatBoard[xLoc][yLoc] == '/') {
							
							direction = Dir.UP;
							
							//or if its left, then redirect down
						
						} else if(cheatBoard[xLoc][yLoc] == '\\') {
							
							direction = Dir.DOWN;
						
						}
						
					}
					
				break;
					
				case LEFT:
					
					if(yLoc - 1 < 0) {
						
						exit = true;
						exitIndex = (xLoc - 9) * -1;
						
						break;
						
					} else {
						
						//decrement y location (column index)
						
						yLoc--;
						
						//reverse logic from right-direction
						
						if(cheatBoard[xLoc][yLoc] == ' ') {
							
							continue;
							
						} else if(cheatBoard[xLoc][yLoc] == '/') {
							
							direction = Dir.DOWN;
						
						} else if(cheatBoard[xLoc][yLoc] == '\\') {
							
							direction = Dir.UP;
						
						}
						
					}
					
				break;
				
				case UP:
					
					if(xLoc - 1 < 0) {
						
						exit = true;
						exitIndex = yLoc + 10;
						
						break;
						
					} else {
						
						//decrement x location (row index)
						
						xLoc--;
						
						if(cheatBoard[xLoc][yLoc] == ' ') {
							
							continue;
							
						} else if(cheatBoard[xLoc][yLoc] == '/') {
							
							direction = Dir.RIGHT;
						
						} else if(cheatBoard[xLoc][yLoc] == '\\') {
							
							direction = Dir.LEFT;
						
						}
						
					}
					
				break;
					
				case DOWN:
					
					if(xLoc + 1 > 9) {
						
						exit = true;
						exitIndex = (yLoc - 39) * -1;
						
						break;
						
					} else {
						
						//increment x location (row index)
						
						xLoc++;
						
						if(cheatBoard[xLoc][yLoc] == ' ') {
							
							continue;
							
						} else if(cheatBoard[xLoc][yLoc] == '/') {
							
							direction = Dir.LEFT;
						
						} else if(cheatBoard[xLoc][yLoc] == '\\') {
							
							direction = Dir.RIGHT;
						
						}
						
					}
					
				break;
				
				default:
					
					//?
					
					System.out.println("What did you do??");
			
			}
			
		} while(exit == false);
		
		//return index which the laser exited from
		
		return exitIndex;

	}
	
}
 