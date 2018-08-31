package soGame;
import java.util.ArrayList;
import java.awt.Dimension;
import java.awt.Rectangle;
import java.util.Scanner;
import java.awt.Color;

/**
 * @brief 	This class to do the union of the classes of the Snake Game. The fields of
 *  		this class are: snake list, screen, px scale, apple and if there is apple 
 *  		(thereIsApple) 
 * 
 * @author 	Shirley Ohara Telemaco de Freitas (shirleyohara@ufrn.edu.com)
 * @author 	Joaliton Luan Pereira de Ferreira (luanpereira00@outlook.com)
 * 
 * @version 01.09.2018
 */

public class SnakeGame {
	private ArrayList<DemoSnake> snakeList; 	/**< An ArrayList with all Snakes playable **/
	public Screen screen; 						/**< The screen of the game **/
	public int pxScale;  						/**< Pixel scale of rectangles of snake's body **/
	Rectangle apple; 							/**< The apple, if the game choice be human player **/ 
	boolean thereIsApple;						/**< Verify if there is apple in the screen **/ 						
	
	/**
	 * Constructor for SnakeGame class
	 */
	public SnakeGame() {
		pxScale = 10;
		thereIsApple = false;
		apple = new Rectangle();
		screen = new Screen(pxScale);
		snakeList = new ArrayList<DemoSnake>();			
	}
	
	/**
	 * @brief 	Add a snake to snakeList's array
	 * @param 	color		Color 	- The snake color
	 * @param 	userOrIA 	boolean - A flag that says who control the snake
	 */
	public void addDSnake(Color color, boolean userOrIA) {	
		DemoSnake d = new DemoSnake(screen, pxScale);
		snakeList.add(d);
		d.buildSnake(color, userOrIA);
	}
	
	/**
	 * @brief 	Check if the snake present in DrawingSnake collided 
	 * 			in something and send to erase if collision is true
	 * 
	 * @param 	d The DrawingSnake that has a snake
	 * @return 	true/false - True if collided, false in others cases
	 */
	public boolean checkColision(DemoSnake d) {
		if(hadColided(d)) return true;
		else return false;
	}
	
	/**
	 * @brief 	Check if a rectangle passed had collided with some wall
	 * @param 	rect The rectangle to test
	 * @return 	true/false - True if collided in the Wall, false in otherwise
	 */
	public boolean checkWallColision(Rectangle rect) {
		if(checkTopColision(rect)) return true;
		if(checkBottomColision(rect)) return true;
		if(checkLeftColision(rect)) return true;
		if(checkRightColision(rect)) return true;
		return false;
	}
	
	/**
	 * @brief 	Check if a rectangle passed had collided in top of screen
	 * @param 	rect  Rectangle	- The rectangle to test
	 * @return 	true/false - True if collided, false in otherwise
	 */
	private boolean checkTopColision(Rectangle rect) {
		if((int)rect.getY() <= pxScale) return true;
		return false;
	}
	
	/**
	 * @brief 	Check if a rectangle passed had collided in bottom of screen
	 * @param 	rect Rectangle - The rectangle to test
	 * @return 	true/false - True if collided, false in otherwise
	 */
	private boolean checkBottomColision(Rectangle rect) {
		if((int)rect.getY() >= screen.getHeight() - pxScale) return true;
		return false;
	}
	
	/**
	 * @brief 	Check if a rectangle passed had collided in left of screen
	 * @param 	rect The rectangle to test
	 * @return 	true/false - True if collided, false in otherwise
	 */
	private boolean checkLeftColision(Rectangle rect) {
		if((int)rect.getX() <= pxScale) return true;
		return false;
	}
	
	/**
	 * @brief 	Check if a rectangle passed had collided in right of screen
	 * @param 	rect The rectangle to test
	 * @return 	true/false - True if collided, false in otherwise
	 */
	private boolean checkRightColision(Rectangle rect) {
		if((int)rect.getX() >= screen.getWidth() - pxScale) return true;
		return false;
	}
	
	/**
	 * @brief 	Check if a drawing snake passed had collided with his snake's body
	 * @param 	toCheck The drawing snake that contains the snake that is going to be checked
	 * @return 	true/false - True if collided in itself, false in otherwise
	 */
	public boolean checkSelfColision(DemoSnake toCheck) {
		Rectangle rect = toCheck.getSnake().getHead();
		for(int i = 1; i < toCheck.getSnake().body.size(); i++) {
			Rectangle r = toCheck.getSnake().body.get(i);
			if(rect.equals(r)) return true;
		}
		return false;
	}
	
	/**
	 * @brief 	Check if a drawing snake passed had collided with something
	 * @param 	toCheck
	 * @return	true/false - True if the snake collided on something, false otherwise
	 */
	public boolean hadColided(DemoSnake toCheck) {
		Rectangle rect = toCheck.getSnake().getHead();
		if(checkWallColision(rect)) return true;
		if(checkSelfColision(toCheck)) return true;
		
		for(DemoSnake d : snakeList) {
			if(!toCheck.equals(d)) {
				for(Rectangle r : d.getSnake().body) {
					if(rect.equals(r)) return true;
				}
			}
		}
		if(toCheck.ateApple(apple)) thereIsApple = false;
		return false;
	}
	
	/**
	 * @brief 	Erase the snake of the screen
	 * @param 	d DemoSnake - Snake to be erase of the screen
	 */
	public void sendToErase(DemoSnake d) {		
		for(Rectangle r: d.getSnake().body) {
			screen.erase(r);
		}
	}
	
	/**
	 * @brief Simulate the game mode artificial intelligence
	 */
	public void gameAI () {
		screen.erase();
		addDSnake(Color.blue, false);
		addDSnake(Color.green, false);
		addDSnake(Color.yellow, false);
		addDSnake(Color.gray, false);
		addDSnake(Color.cyan, false);
		addDSnake(Color.white, false);
		addDSnake(Color.pink, false);
		addDSnake(Color.magenta, false);
		addDSnake(Color.orange, false);
		addDSnake(Color.LIGHT_GRAY, false);
		
		while (!snakeList.isEmpty()) {
			boolean tRemove = false;
			DemoSnake r = new DemoSnake(screen, 15);
			
			for(DemoSnake d : snakeList) {			
				Thread t = new Thread(d); 
				t.start();

				screen.wait(10);
								
				if(checkColision(d)) {
					d.stop = true;
					tRemove = true;
					r = d;
					break;								
				}				
			}
			
			if(tRemove) {
				sendToErase(r);
				snakeList.remove(r);
				
			}
		}
		
		screen.erase();
		screen.gameOverScreen();
	}
	
	/**
	 * @brief Simulate the game mode human player
	 */
	public void gameHP () {
		screen.erase();
		addDSnake(Color.pink, true);
		int score = 0;
		
		while (!snakeList.isEmpty()) {
			boolean tRemove = false;
			DemoSnake r = new DemoSnake(screen, 10);
			
			if(!thereIsApple) {
				do {
					Dimension d = r.randDimension();
					apple = new Rectangle((int)d.getWidth(), (int)d.getHeight(), pxScale, pxScale);
				} while(checkWallColision(apple));
				screen.fill(apple);
				thereIsApple = true;
			}
		
			for(DemoSnake d : snakeList) {
				Thread t = new Thread(d);
				t.start();
				screen.wait(150);

				if(checkColision(d)) {
					d.stop = true;
					tRemove = true;
					r = d;
					break;
				}else {
					if(d.ateApple(apple)) score += 10;
				}
			}
			
			if(tRemove) {
				sendToErase(r);
				snakeList.remove(r);
			}
		}
		
		thereIsApple = false;
		screen.erase();
		screen.gameOverScreen(score);
	}
	
	/**
	 * @brief Simulate the game mode human player vs. artificial intelligence
	 */
	public void gameHPvsAI () {
		screen.erase();
		
		addDSnake(Color.white, false);
		addDSnake(Color.white, false);
		addDSnake(Color.white, false);
		addDSnake(Color.white, false);
		addDSnake(Color.white, false);
		addDSnake(Color.white, false);
		addDSnake(Color.white, false);
		addDSnake(Color.blue, true); // The snake controlled by a human
		
		while (!snakeList.isEmpty()) {
			boolean tRemove = false;
			DemoSnake r = new DemoSnake(screen, 15);
					
			for(DemoSnake d : snakeList) {
				Thread t = new Thread(d);
				t.start();		
				
				screen.wait(20);
								
				if(checkColision(d)) {
					d.stop = true;
					tRemove = true;
					r = d;
					break;								
				}
			}
			
			if(tRemove) {
				sendToErase(r);
				snakeList.remove(r);
				
			}
		}
		
		screen.erase();
		screen.gameOverScreen();
	}
	
	/**
	 * @brief Show the menu of the game's choices
	 */
	public void telaChoices () {
		System.out.println("+-------------------------------+");
		System.out.println("|         GAME's CHOICES        |");
		System.out.println("+-------------------------------+");
		System.out.println("| ( 1 ) Artificial Intelligence |");
		System.out.println("|-------------------------------|");
		System.out.println("| ( 2 ) Humam Player            |");
		System.out.println("|-------------------------------|");
		System.out.println("| ( 3 ) Humam vs. AI            |");
		System.out.println("|-------------------------------|");
		System.out.println("| ( 0 ) QUIT                    |");
		System.out.println("+-------------------------------+");
	}

	/**
	 * @brief 	Principal method that is responsible to do the game to function
	 * @param 	args
	 */
	public static void main(String args[]) {
		SnakeGame game = new SnakeGame();
		boolean exit = false;
		
		while(!exit) {
			game.screen.gameChoices();
			
			int choice;
			Scanner s = new Scanner(System.in);
			game.telaChoices();
			
			System.out.println(" - Choose an option - ");
			choice = s.nextInt();
			
			switch(choice) {
				case 0:
					exit = true;
					break;
				case 1: //ai
					game.gameAI();
					break;
				case 2: //Human player
					game.gameHP();
					break;
				case 3: //Human player vs. AI
					game.gameHPvsAI();
					break;
				default:
					System.out.println(" There isn't this choise! ");
			}
		}
		game.screen.erase();
		System.exit(0);
   }
}