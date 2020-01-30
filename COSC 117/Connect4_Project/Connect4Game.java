import java.util.Scanner;

/*
 * A note on Methods before we begin
 * 
 * There are four methods used:
 * 
 * gameLoop - run all game logic on a loop until a winner is found
 * gameWinner - look to see if any player has fulfilled requirements to win a game
 * initBoard - reset game board back to all blank spaces
 * gameState - output current state of the game
 * 
 */

public class Connect4Game {
	
	/*
	 * data members (globals)
	 * 
	 * so we don't have to keep passing these variables
	 * as parameters through out the methods
	 * (primarily the gameLoop)
	 * 
	 */
	
	//declare constants for rows and columns (six rows, seven columns)
	
	final static int COLUMNS = 7;
	final static int ROWS = 6;
			
	//game board, will hold current state of game	
	//2d character array
					
	static char[][] board = new char[ROWS][COLUMNS];
			
	//player color assignment
	//player will decide assignment later in program
			
	static char p1Color, p2Color;
	
	//user input as it will be used by game loop method
	
	static Scanner stdin = new Scanner(System.in);
	
	/*
	 * winner integer,
	 * 
	 * will be 0 for no current winner
	 * 1 for player 1 win
	 * 2 for player 2 win
	 * 3 for draw
	 * 
	 * game loop will run as long as it's 0
	 * 
	 */

	static int winner = 0;
	
	public static void main(String[] args) {
		
		//boolean to indicate if player wishes to continue playing
		//this is used when running game loop according to user-preference (user decides when to stop playing)
		//default to true to play at least once
		
		boolean isPlaying = true;
		
		//variables to keep track of players scores as there will be multiple games
		
		int p1Total = 0;
		int p2Total = 0;
		
		//int to decide which player's turn
		
		int currentPlyr;
		
		//first, get colors from respective players
		
		System.out.println("Welcome to Connect 4! We will begin with color assignments");
		
		System.out.println("Player one, please enter 'R' to player as red, or 'Y' to play as yellow");
		
		//loop until valid input is recieved
		
		do {
			
			//look for first character of input
			
			p1Color = stdin.next().charAt(0);
			
			//Upper case character (in case they enter 'r' or 'y')
			
			p1Color = Character.toUpperCase(p1Color);
			
			if(p1Color == 'R') {
				
				//assign player 2 to opposite color
				
				p2Color = 'Y';
				
				//output player 2 color
				
				System.out.println("Player two will be yellow");
				
				//break out of loop if valid input
				
				break;
				
			} else if(p1Color == 'Y') {
				
				p2Color = 'R';
				
				System.out.println("Player two will be red");
				
				break;
				
			} else {
				
				System.out.println("invalid color, please enter only 'R' or 'Y'");
			}
			
		} while(p1Color != 'R' || p1Color != 'Y');
		
		//spacer
		
		System.out.println("");
		
		while(isPlaying == true) {
			
			//reset board method
			
			initBoard();
			
			//set current player to player one before entering game loop
			
			currentPlyr = 1;
			
			//run the game loop
			
			gameLoop(currentPlyr);
			
			//once game loop is over, add to scores for winner
			//don't use 'else{' as it is possible to achieve a draw
			
			if(winner == 1) {
				
				p1Total++;
			
			} else if(winner == 2) {
				
				p2Total++;
				
			}
			
			//put spacer, then alert of game over
			
			System.out.println("");
			
			System.out.println("Would you like to play again? Enter Y to continue or N to quit");
			
			//user input after alert
			
			char continueInput;
			
			//ensure input is valid
			
			do {
				
				//look for first character of input
				
				continueInput = stdin.next().charAt(0);
				
				//Upper case character
				
				continueInput = Character.toUpperCase(continueInput);
				
				if(continueInput == 'Y') {
					
					System.out.println("Starting a new game");
					
					break;
					
				} else if(continueInput == 'N') {
					
					//output player totals
					
					System.out.println("Player One score: " + p1Total);
					System.out.println("Player Two score: " + p2Total);
					
					System.out.println("");
					
					System.out.println("Thank you for playing Connect 4!");
					
					//set isPlaying to false
					
					isPlaying = false;
					
					break;
					
				} else {
					
					System.out.println("invalid, please try again");
				}
				
			} while(continueInput != 'Y' || continueInput != 'N');
			
		}
		
	}
	
	public static int gameWinner(int player) {
		
		//can win by rows, columns, or diagonals (diagonals are complex, will be declared later)
		
		int row = 0;
		int col = 0;
		

		//please note that for simplicity, i and j are used throughout for-loop structures
		//'i' will refer to rows and 'j' will refer to columns in all for-loops
		//in this case we need a third, 'l', for diagonals
		
		int i, j, l;
		
		//color character
		
		char color;
		
		//int for win found, follows same properties as global int winner, default to 0
		
		int win = 0;
		
		//handle color assignment
		
		if(player == 1) {
			
			color = p1Color;
			
		} else {
			
			color = p2Color;
		}
		
		//row-win, check to see if player has four discs continuously in a single row
		
		for(i = 0; i < ROWS; i++) {
			
			for(j = 0; j < COLUMNS; j++) {
				
				if(board[i][j] == color) {
					
					row++;
					
				} else {
					
					//streak broken, set back to zero
					
					row = 0;
				}
				
				if(row == 4) {
					
					//four in a row, current player is a winner
					
					win = player;
					
					//break loop
					
					break;
					
				}
				
			}
			
		}
		
		//winner not found from rows
		
		//check columns (use reverse of previous loop)
				
		if(win == 0) {
			
			for(j = 0; j < COLUMNS; j++) {
				
				for(i = 0; i < ROWS; i++) {
					
					if(board[i][j] == color) {
						
						col++;
						
					} else {
						
						//streak broken, set back to zero
						
						col = 0;
					}
					
					if(col == 4) {
						
						//four in a row, current player is a winner
						
						win = player;
						
						//break loop
						
						break;
						
					}
					
				}
				
			}
			
		}
		
		//winner not found from rows or columns
		
		//check the diagonals (most complex win)
		
		if(win == 0) {
			
			for(i = 0; i < ROWS; i++) {
				
				for(j = 0; j < COLUMNS; j++) {
					
					//look for a color match
					
					if(board[i][j] == color) {
						
						/*
						 * 
						 * with diagonals, we will check two directions
						 * to find a row of diagonal color matches
						 * 
						 * we will begin three indexes to the top right
						 * and top left of a color match, then work our way
						 * down to see if there is a streak of colors
						 * 
						 * because of this method, we need two integers to
						 * keep track of the current streak of colors (diag1 and diag2)
						 * 
						 * the looping structure will count from the three indexes to the top
						 * left or right, then count all the way down to the bottom left and
						 * right three indexes
						 * 
						 */
							
						int diag1 = 0, diag2 = 0;
							
						for(l = 3; l > -3; l--) {
							
							//we declare the new row and column we will use
							
							//in this case it is the top right (decrease the rows to go up, increase the columns to go right)
								
							int rightRow = i - l, rightColumn = j + l;
							
							//we have to ensure that the columns and rows exist, and are in the array's bounds
								
							if(rightRow > -1 && rightRow < 6 && rightColumn > -1 && rightColumn < 7) {
									
								if(board[rightRow][rightColumn] == color) {
										
									//add to streak
											
									diag1++;
								
								} else {
										
									//color not found in row, reset to 1
										
									diag1 = 0;
								}
								
								//we do the same for the top left, except the columns now are left instead of right
								
								int leftRow = i - l, leftColumn = j - l;
								
								if(leftRow > -1 && leftRow < 6 && leftColumn > -1 && leftColumn < 7) {
									
									if(board[leftRow][leftColumn] == color) {
										
										//add to streak
												
										diag2++;
									
									} else {
											
										//color not found in row, reset to 1
											
										diag2 = 0;
									}
									
								}
								
								//if the diagonal of each is 4 (four has been connected)
									
								if(diag1 == 4 || diag2 == 4) {
									
									//declare winner and break loop
									
									win = player;
									
									break;
								}
									
							}
							
						}
						
					}
					
				}
				
			}
			
		}
		
		//if there still is not a winner, make sure that not all spaces are filled (indicating a draw)
		
		if(win == 0) {
			
			//use a bool to keep note of a draw
			
			//default to true, but change it if an empty space is found
			
			boolean draw = true;
			
			//loop through all spaces
			
			for(i = 0; i < ROWS; i++) {
				
				for(j = 0; j < COLUMNS; j++) {
					
					//is a single array index is an empty space, then game must continue
					
					if(board[i][j] == ' ') {
						
						draw = false;
						
						break;
					}
					
				}	
					
			}
			
			//if no spaces found, draw boolean should still be true, indicating no spaces were found
			
			//and thus, the game is a draw
			
			if(draw == true) {
				
				win = 3;
			}
			
		}
		
		if(win == 1 || win == 2) {
			
			//show final game state
			
			gameState();
			
			//put spacer between state and winner alert
			
			System.out.println("");
			
			//alert of winner
			
			System.out.println("Player " + player + " has won the game!");
		
		} else if(win == 3) {
			
			//draw 
			
			System.out.println("");
			
			//alert of draw
			
			System.out.println("The game is a draw! No spaces left!");
		}
		
		//return winner, if it is not undetermined it will break the game loop, ending the game
		
		return win;

	}
	
	//method for outputting current game state
	
	public static void gameState() {
		
		//loop increments
		
		int i, j;
		
		//output current game state
		
		for(i = 0; i < ROWS; i++) {
			
			for(j = 0; j < COLUMNS; j++) {
				
				System.out.print(board[i][j]);
					
				if(j != 6) {
						
					//if not on last column, put spacer and vertical line (column[6])
						
					System.out.print(" | ");
					
				}
				
			}
			
			//break line after each row
			
			System.out.println("");
			
		}

		//display labels for columns and labels after displaying game state
		
		System.out.println("-------------------------");
		System.out.println("1 | 2 | 3 | 4 | 5 | 6 | 7");
		
	}
	
	public static void initBoard() {
		
		//initialize game board array to empty spaces
		
		int i, j;
						
		for(i = 0; i < ROWS; i++) {
							
			for(j = 0; j < COLUMNS; j++) {
								
				//initialize each array index to space (blank)
						
				board[i][j] = ' ';
						
			}
					
		}
		
	}
	
	public static void gameLoop(int currentPlyr) {
		
		/*
		 * all game logic will be ran here
		 * 
		 * the reason so many data members were needed
		 * before the main method is so this method
		 * could access and modify game elements
		 * 
		 * (board, player colors, etc)
		 * 
		 */

		//declare array of valid input characters for game
		//we will use this to determine if user input is acceptable
				
		int[] validInput = {0, 1, 2, 3, 4, 5, 6};
		
		//declare i for loops
		
		int i;
		
		do {
			
			//column user will be entering
			
			int column;
			
			//user input verification
			
			boolean inputVerified, columnVerified;
			
			//alert of current player
			
			System.out.println("player " + currentPlyr + "'s turn");
			System.out.println("please select a column to place your disc");
			
			//spacer
			
			System.out.println("");
			
			//output current game state with a method, passing board as parameter
			
			gameState();
			
			//use a loop to validate user input
			
			do {
				
				//default both verification layers to false

				columnVerified = inputVerified = false;
				
				//player chooses which column to place disc
				
				column = stdin.nextInt();
				
				//subtract column by 1 to address array index
				
				column--;
				
				for(i = 0; i < COLUMNS; i++) {
					
					//verify input by comparing it to array of valid input options
					
					if(column == validInput[i]) {
						
						inputVerified = true;
						
						//break out of loop if match found
						
						break;
						
					}
					
				}
				
				if(inputVerified == false) {
					
					//if input did not pass verification test
					
					System.out.println("that is not a column number, please try again");
					
				} else {
					
					//input verified, now check to see if column full by checking columns top index (index 0)
					
					if(board[0][column] != ' ') {
							
						System.out.println("Column full, please try again");
					
					} else {
						
						//column is verified, input is valid
						
						columnVerified = true;
						
					}
					
				}
				
			} while(columnVerified == false);
			
			//decide which array index will be turned 'R' or 'Y'
			
			//go in descending order to find lowest open space on row (go to -1 since we will need to check index 0)
			
			for(i = 5; i > -1; i--) {
				
				//note that the row is in first dimension of array, column is in second
				
				if(board[i][column] == ' ') {
					
					if(currentPlyr == 1) {
						
						//turn to player one's color
						
						board[i][column] = p1Color;
						
					} else {
						
						//turn to player two's color
						
						board[i][column] = p2Color;
					}
					
					//break loop once spot found
					
					break;
					
				}
				
			}
			
			//look for winner before going to next player
			
			//call gameWinner method, passing current player, player color assignment, and board (game state) as parameters
			
			winner = gameWinner(currentPlyr);
			
			//go to next player
			
			if(currentPlyr == 1) {
				
				currentPlyr = 2;
				
			} else {
				
				currentPlyr = 1;
			}
			
			//run while winner is undetermined
			
		} while(winner == 0);
		
	}

}
