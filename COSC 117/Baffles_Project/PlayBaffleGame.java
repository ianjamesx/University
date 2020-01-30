
/*
 * Baffle Game
 * 
 * Game in which user attempts
 * to guess the location of 'baffles'
 * hidden along a 10x10 grid
 * 
 * user shoots a laser and is only
 * told where laser exits as clue
 * to baffle location
 * 
 * Programmed by Ian Thomas
 * 
 * 11/15/17
 * 
 */

import java.util.Scanner;

public class PlayBaffleGame {
	
	//we will declare the objects globally so we dont need to pass them
	
	static Scanner stdin = new Scanner(System.in);
	
	static BaffleGame game = new BaffleGame();
	
	//a bool for if player is playing
	
	static boolean playing = true;
	
	//keep track of baffles found and total baffles
	
	static int bafflesFound = 0;
	static int totalBaffles;
	
	//main

	public static void main(String[] args) {
		
		//define character used for current user input (in the game loop)
		
		char input;
		
		//player difficulty, will be used in game object
		
		int difficulty;
			
		//set a boolean input verification, if false (in case of invalid input), will not let user proceed further
				
		boolean pass = false;
		
		//alert user
		
		System.out.println("Welcome to The Baffle Game!");
		System.out.println("");
		System.out.println("Please select your difficulty. Enter '1' for Easy, '2' for Medium, or '3' for Hard");
		
		do {
			
			difficulty = stdin.nextInt();
			
			//if difficulty is not a valid option
					
			if(!(difficulty == 1 || difficulty == 2 || difficulty == 3)) {
				
				System.out.println("That is not a valid difficulty, please try again");
				
			} else {
				
				//if it is, let them through
				
				pass = true;
			}
			
			//user has not passed if pass is still false
			
		} while (pass == false);
		
		//set the game difficulty once input is received
		
		game.setDifficulty(difficulty);
		
		System.out.println("Starting a new Baffle Game... Get Ready!");
		System.out.println("");
		
		//create game board and baffles
		
		game.initBoard();
		game.generateBaffles();
		
		//get the total number of baffles
		
		totalBaffles = game.getBaffleNumber();
		
		//start game loop
		
		do {
			
			//print out user options
			
			printMenu();
			
			//take user input 
			
			input = stdin.next().charAt(0);
			
			//upper case their input character (so we don't need to check lower case cases
			
			input = Character.toUpperCase(input);
			
			//call handleInput, pass input and current game object
			
			handleInput(input);
			
			//loop while playing

		} while(playing);
		
	}
	
	public static void printMenu() {
		
		//print the game menu
		
		System.out.println("Your Options:");
		System.out.println("Enter L to take a shot with a laser from a specific column or row");
		System.out.println("Enter G to take a guess as to the location of a baffle");
		System.out.println("Enter S to view your current score, guesses made, and number of shots");
		System.out.println("Enter P to view the current game board with the locations of all baffles you have found so far");
		System.out.println("Enter Q to quit the game");
		System.out.println("Enter C to view the board with all baffle locations");
		
		//put spacer
		
		System.out.println("");
		
	}
	
	public static void handleInput(char input) {
		
		int i;
		
		//boolean for input
		
		boolean valid;
		
		//handle input with a switch case for all scenarios

		switch(input) {
		
			case 'L':
				
				System.out.println("Please enter the number of the column or row you want to shoot a laser from (integer from 0 - 39)");
				
				//ensure input is valid with a boolean
				
				valid = false;
				
				//we will need the index the enter to be declared outside verification loop so it can be passed to game object
				
				int fireIndex;
				
				do {
					
					//take user input
					
					fireIndex = stdin.nextInt();
					
					//loop through all possible values for a valid column or row (0-39)
					
					for(i = 0; i < 40; i++) {
						
						if(fireIndex == i) {
							
							//if input is any number from 0 - 39
							
							valid = true;
							
						}
						
					}
					
					//if its not valid
					
					if(valid == false) {
						
						System.out.println("That is not a valid column or row number, please only enter an integer from 0 to 39");
						
					}
					
					//run until valid input is received
					
				} while (valid == false);
				
				int exitIndex = game.laserShot(fireIndex);
				
				System.out.println("Your laser exited from spot #" + exitIndex);
				
				//increment amount of shots, and score
				
				game.shots++;
				
				game.score++;
				
			break;
			
			case 'G':
				
				//tell user how many guesses this is
				
				System.out.println("This is guess " + game.guesses);
				
				//validity checks for rows, columns, and direction
				
				boolean row = false, col = false, dir = false;
				
				//variables for row guess, column guess, and direction guess
				
				int rowGuess, colGuess;
				
				char dirGuess;
				
				System.out.println("Where do you think the baffle is? First enter the row number (from the left, so guess an integer from 0 - 9)");
				
				//loop for row input validity
				
				do {
					
					rowGuess = stdin.nextInt();
					
					//ensure input is valid
					
					for(i = 0; i < 10; i++) {
						
						if(rowGuess == i) {
							
							row = true;
							
							break;
							
						}
						
					}
					
					if(row == false) {
						
						System.out.println("That is not a valid row number, please try again");
					}
					
				} while (row == false);
				
				//loop for column input validity
				
				System.out.println("Now, which column do you think it's in? (from the top, so guess an integer from 10 - 19");
				
				do {
					
					colGuess = stdin.nextInt();
					
					//ensure input is valid
					
					for(i = 10; i < 20; i++) {
						
						if(colGuess == i) {
							
							col = true;
							
							break;
							
						}
						
					}
					
					if(col == false) {
						
						System.out.println("That is not a valid column number, please try again");
					}
					
				} while (col == false);
				
				//direction guess
				
				//escape the forward slash again
				
				System.out.println("Now, which direction do you think it's facing? Enter 'R' for right ( / ) or 'L' for left ( \\ )");
				
				do {
					
					dirGuess = stdin.next().charAt(0);
					
					//convert to upper case
					
					dirGuess = Character.toUpperCase(dirGuess);
					
					//ensure input is valid
					
					if(dirGuess == 'R' || dirGuess == 'L') {
						
						dir = true;
						
					} else {
						
						System.out.println("That is not a valid character input, please try again");
					}
					
				} while (dir == false);
				
				//add to guess counter
				
				game.guesses++;
				
				//two more points for a guess
				
				game.score += 2;
				
				//call guess method to see if it works
				
				int guess = game.guess(rowGuess, colGuess, dirGuess);
				
				if(guess == 1) {
					
					System.out.println("Correct! There was a baffle at that location!");
					
					bafflesFound++;
					
					System.out.println("You have found " + bafflesFound + " baffle(s)");
					
					if(bafflesFound == totalBaffles) {
						
						//alert user that all baffles have been found, ending the game
						
						//spacer
						
						System.out.println("");
						
						System.out.println("You have found all the baffles!");
						
						System.out.println("");
						
						game.printStats();
						
						System.out.println("");
						
						game.printBoard(false);
						
						System.out.println("");
						
						System.out.println("Thanks for playing The Baffle Game!");
						
						//set playing to false (to break out of game loop)
						
						playing = false;
						
					}
					
				} else if(guess == 0){
					
					System.out.println("Wrong! There was no baffle at that location! Better luck next time.");
					
				} else if(guess == 2) {
					
					System.out.println("That Baffle has already been found!");
				}
				
			break;
			
			case 'S':
				
				game.printStats();
				
			break;
			
			case 'P':
				
				//print the board (cheating turned off)
				
				game.printBoard(false);
				
			break;
			
			case 'Q':
				
				//output final score, guesses, and shots
				
				game.printStats();
				
				System.out.println("");
				System.out.println("Thanks for playing The Baffle Game!");
				
				//set playing to false (to break out of game loop)
				
				playing = false;
				
			break;
			
			case 'C':
				
				//print the board (cheating turned on)
				
				game.printBoard(true);
				
			break;
			
			default:
				
				System.out.println("That's not a valid input character, let's try that again");
		
		}
		
		//spacer for separating game menu from output
		
		System.out.println("");
		
	}

}
