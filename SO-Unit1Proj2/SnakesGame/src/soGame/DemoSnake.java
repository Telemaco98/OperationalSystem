package soGame;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Rectangle;
import java.util.ArrayList;
import java.util.Random;

/**
 * @brief 	This class to do the union of the classes of the Snake Game. The fields of
 *  		this class are: screen, snake, px scale and stop.
 * 
 * @author 	Shirley Ohara Telemaco de Freitas (shirleyohara@ufrn.edu.com)
 * @author 	Joaliton Luan Pereira de Ferreira (luanpereira00@outlook.com)
 * 
 * @version 01.09.2018
 */
public class DemoSnake implements Runnable {
	private Screen screen; 	/**< The screen where is the snake */
	private Snake snake;    /**< The Snake */
    private int pxScale;	/**< The px Scale of the snake */
    public boolean stop;	/**< Determines the snake should stop */
	
    /**
     * Build a object DemoSnake
     * @param screen
     * @param pxScale
     */
	public DemoSnake (Screen screen, int pxScale) {
		this.screen = screen;
		this.pxScale = pxScale;
		stop = false; 
	}
	
	/**
	 * Implementation of the method run() if the interface Runnable. It build 
	 * draw the snake and movements its.
	 */
	public void run () {
		printSnake();
		
		if(!stop) movementSnake();
	}
	
	/**
	 * Build the snake in the screen
	 * @param color
	 * @param userOrIA
	 */
	public void buildSnake (Color color, boolean userOrIA) {
		Dimension start = randDimension();
		Dimension end = randDimensionInLine(start, 10);
		snake = new Snake(color, createBody(start, end), userOrIA);
	}

	/**
	 * Creates a random dimension for start of snake's body
	 * @return Return a dimension
	 */
	public Dimension randDimension() {	
		Random rnd = new Random();
		int xPos = rnd.nextInt();
		int yPos = rnd.nextInt();
		
		if(xPos<0) xPos*=-1;
		if(yPos<0) yPos*=-1;
		
		xPos = xPos % (int) screen.getSize().getWidth()/pxScale;
		yPos = yPos % (int) screen.getSize().getHeight()/pxScale;	
		
		return new Dimension(xPos*pxScale, yPos*pxScale);
	}
	
	/**
	 * Creates a random dimension for end of snake's body based on start
	 * @param start The start of snake's body
	 * @param howManyBodyPart A variable that sets how long will be the snake body
	 * @return Return a dimension
	 */
	public Dimension randDimensionInLine(Dimension start, int howManyBodyPart) {	
		Random rnd = new Random();
		
		int xPos = (int) start.getWidth();
		int yPos = (int) start.getHeight();
 		
		if(rnd.nextBoolean()) {//creates a horizontal snake
			if(start.getWidth()<(screen.getSize().getWidth()/2)) {
				xPos=xPos + howManyBodyPart*pxScale;
			} else {
				xPos=xPos - howManyBodyPart*pxScale;
			}
		}
		else { // creates a vertical snake
			if(start.getHeight()<(screen.getSize().getHeight()/2)) {
				yPos=yPos + howManyBodyPart*pxScale;
			} else {
				yPos=yPos - howManyBodyPart*pxScale;
			}
		}		
		return new Dimension(xPos, yPos);
	}
	
	/**
	 * Creates snake's body for the one that is being created 
	 * @param start The start Dimension of the snake
	 * @param end The end Dimension of the snake
	 * @return Return a ArrayList with snake's body
	 */
	private ArrayList<Rectangle> createBody(Dimension start, Dimension end) {
		ArrayList<Rectangle> body = new ArrayList<Rectangle>();
		int xPos = (int) start.getWidth();
		int yPos = (int) start.getHeight();
		if(yPos == (int) end.getHeight()) { //horizontal snakes
			if(xPos-end.getWidth()<0) { //horizontal snakes headed for left
				while(xPos <= (int) end.getWidth()) {
					body.add(0, new Rectangle(xPos, yPos, pxScale, pxScale));
					xPos += pxScale;
				}
			} else { //horizontal snakes headed for right
				while(xPos >= (int) end.getWidth()) {
					body.add(0, new Rectangle(xPos, yPos, pxScale, pxScale));
					xPos -= pxScale;
				}
			}
		} 
		else { //vertical snakes, by consequence
			if(yPos-end.getHeight()<0) { //vertical snakes headed for up
				while(yPos <= (int) end.getHeight()) {
					body.add(0, new Rectangle(xPos, yPos, pxScale, pxScale));
					yPos += pxScale;
				}
			}
			else { //vertical snakes headed for down
				while(yPos >= (int) end.getHeight()) {
					body.add(0, new Rectangle(xPos, yPos, pxScale, pxScale));
					yPos -= pxScale;
				}
			}
		}
		
		return body;
	}
	
	/**
	 * Check if the snake ate the appple.
	 * @param 	apple Rectangle - The apple
	 * @return 	true/false - True if the snake ate the apple, false in the otherwise
	 */
	public boolean ateApple(Rectangle apple) {
		if(snake.body.get(0).equals(apple)) {
			snake.body.add(apple);
			return true;
		}
		
		return false;
	}
	
	/**
	 * Print the snake in the screen
	 */
	public void printSnake() {
		for(Rectangle r : snake.body) {
			screen.setForegroundColor(snake.getColor());
			screen.fill(r);
		}
	}
	
	/**
	 * Movement the snake in this class
	 */
	private void movementSnake() {
		int chanceToDontDie = 0;
		Rectangle rect = chooseNextHeadPosition();
		while (checkSelfColision(rect) && chanceToDontDie<5 || checkWallColision(rect) && chanceToDontDie<5) {
			rect = chooseNextHeadPosition(); //new chance to snakes die less
			chanceToDontDie++;
		}
		
		Rectangle r = snake.moviment(rect);
		screen.erase(r);
		screen.movimentSide = 0;
	}
	
	/**
	 * Choose by random which one direction will be the next for snake
	 * @return The removed tail
	 */
	private Rectangle chooseNextHeadPosition() {
		Random rnd = new Random();
		int chooser = rnd.nextInt();
	
		if(!snake.userOrIA) { // false = IA
			if (chooser<0) chooser*=-1;
			chooser = chooser % 10; 
			if(chooser>1) { 			//80%
				return moveForward();
			} else if(chooser == 0) { 	//10%
				return moveToLeft();
				//Melhorando IA, elas não batem em si proprias, em teoria!
			} else { 					//10%
				return moveToRight();
			}
		} else { // true = user
			// 0 = default
			// 1 = up
			// 2 = left
			// 3 = right
			// 4 = down
			
			if(snake.getHead().getX()==snake.getNeck().getX()) {	
				//If a snake is on vertical
				if(snake.getHead().getY()-snake.getNeck().getY()>0) { 
					//If a snake is headed for down
					if (screen.movimentSide == 0) return moveForward();
					if (screen.movimentSide == 1) return moveForward();
					if (screen.movimentSide == 2) return moveToRight();
					if (screen.movimentSide == 3) return moveToLeft();
					if (screen.movimentSide == 4) return moveForward();
				}
				else {													
					//If a snake is headed for up, by consequence
					if (screen.movimentSide == 0) return moveForward();
					if (screen.movimentSide == 1) return moveForward();
					if (screen.movimentSide == 2) return moveToLeft();
					if (screen.movimentSide == 3) return moveToRight();
					if (screen.movimentSide == 4) return moveForward();
				}		
			}
			
			else { 													
				//If a snake is on horizontal, by consequence
				if(snake.getHead().getX()-snake.getNeck().getX()>0) { 
					//If a snake is headed for right
					if (screen.movimentSide == 0) return moveForward();
					if (screen.movimentSide == 1) return moveToLeft();
					if (screen.movimentSide == 2) return moveForward();
					if (screen.movimentSide == 3) return moveForward();
					if (screen.movimentSide == 4) return moveToRight();
				}
				else {													
					//If a snake is headed for left, by consequence
					if (screen.movimentSide == 0) return moveForward();
					if (screen.movimentSide == 1) return moveToRight();
					if (screen.movimentSide == 2) return moveForward();
					if (screen.movimentSide == 3) return moveForward();
					if (screen.movimentSide == 4) return moveToLeft();
				}
			}
			return moveForward();
		}
	}
	
	/**
	 * Check if a drawing snake passed had collided with his snake's body
	 * @param toCheck The drawing snake that contains the snake that is going to be checked
	 * @return True if collided, false in others cases
	 */
	public boolean checkSelfColision(Rectangle rect) {
		for(int i = 1; i < snake.body.size(); i++) {
			Rectangle r = snake.body.get(i);
			if(rect.equals(r)) return true;
		}
		return false;
	}
	
	/**
	 * Move a snake for front, based on for where it is headed
	 * @return The removed tail
	 */
	private Rectangle moveForward() {
		int xPos=0;
		int yPos=0;
		
		if(snake.getHead().getX()==snake.getNeck().getX()) {	
			//If a snake is on vertical
			if(snake.getHead().getY()-snake.getNeck().getY()>0) { 
				//If a snake is headed for down
				xPos = (int)snake.getHead().getX();
				yPos = (int)snake.getHead().getY()+pxScale;
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}
			else {													
				//If a snake is headed for up, by consequence
				xPos = (int)snake.getHead().getX();
				yPos = (int)snake.getHead().getY()-pxScale;
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}		
		}
		
		else { 													
			//If a snake is on horizontal, by consequence
			if(snake.getHead().getX()-snake.getNeck().getX()>0) { 
				//If a snake is headed for right
				xPos = (int)snake.getHead().getX()+pxScale;
				yPos = (int)snake.getHead().getY();
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}
			else {													
				//If a snake is headed for left, by consequence
				xPos = (int)snake.getHead().getX()-pxScale;
				yPos = (int)snake.getHead().getY();
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}
		}
	}
	
	/**
	 * Move a snake for left, based on for where it is headed
	 * @return The removed tail
	 */
	private Rectangle moveToLeft() {
		int xPos=0;
		int yPos=0;
		if(snake.getHead().getX()==snake.getNeck().getX()) {	
			//If a snake is on vertical
			if(snake.getHead().getY()-snake.getNeck().getY()>0) { 
				//If a snake is headed for down
				xPos = (int)snake.getHead().getX()+pxScale;
				yPos = (int)snake.getHead().getY();
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}
			else {															
				//If a snake is headed for up, by consequence
				xPos = (int)snake.getHead().getX()-pxScale;
				yPos = (int)snake.getHead().getY();
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}		
		}
		else { 
			//If a snake is on horizontal, by consequence
			if(snake.getHead().getX()-snake.getNeck().getX()>0) { 
				//If a snake is headed for right
				xPos = (int)snake.getHead().getX();
				yPos = (int)snake.getHead().getY()-pxScale;
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}
			else {														
				//If a snake is headed for left, by consequence
				xPos = (int)snake.getHead().getX();
				yPos = (int)snake.getHead().getY()+pxScale;
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}
		}
	}
	
	/**
	 * Move a snake for right, based on for where it is headed
	 * @return The removed tail
	 */
	private Rectangle moveToRight() {
		int xPos=0;
		int yPos=0;
		if(snake.getHead().getX()==snake.getNeck().getX()) {	
			//If a snake is on vertical
			if(snake.getHead().getY()-snake.getNeck().getY()>0) { 
				//If a snake is headed for down
				xPos = (int)snake.getHead().getX()-pxScale;
				yPos = (int)snake.getHead().getY();
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}
			else {															
				//If a snake is headed for up, by consequence
				xPos = (int)snake.getHead().getX()+pxScale;
				yPos = (int)snake.getHead().getY();
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}		
		}
		else {
			//If a snake is on horizontal, by consequence
			if(snake.getHead().getX()-snake.getNeck().getX()>0) { 
				//If a snake is headed for right
				xPos = (int)snake.getHead().getX();
				yPos = (int)snake.getHead().getY()+pxScale;
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}
			else {														
				//If a snake is headed for left, by consequence
				xPos = (int)snake.getHead().getX();
				yPos = (int)snake.getHead().getY()-pxScale;
				return new Rectangle(xPos, yPos,pxScale, pxScale);
			}
		}
	}
	
	/**
	 * Return the snake
	 * @return The snake
	 */
	public Snake getSnake () {
		return snake;
	}

	/**
	 * Check if a rectangle passed had collided with some wall
	 * @param rect The rectangle to test
	 * @return True if collided, false in others cases
	 */
	public boolean checkWallColision(Rectangle rect) {
		if(checkTopColision(rect)) return true;
		if(checkBottomColision(rect)) return true;
		if(checkLeftColision(rect)) return true;
		if(checkRightColision(rect)) return true;
		return false;
	}
	
	/**
	 * Check if a rectangle passed had collided in top of screen
	 * @param rect The rectangle to test
	 * @return True if collided, false in others cases
	 */
	private boolean checkTopColision(Rectangle rect) {
		if((int)rect.getY()==0) return true;
		return false;
	}
	
	/**
	 * Check if a rectangle passed had collided in bottom of screen
	 * @param rect The rectangle to test
	 * @return True if collided, false in others cases
	 */
	private boolean checkBottomColision(Rectangle rect) {
		if((int)rect.getY()==screen.getHeight()-pxScale) return true;
		return false;
	}
	
	/**
	 * Check if a rectangle passed had collided in left of screen
	 * @param rect The rectangle to test
	 * @return True if collided, false in others cases
	 */
	private boolean checkLeftColision(Rectangle rect) {
		if((int)rect.getX()==0) return true;
		return false;
	}
	
	/**
	 * Check if a rectangle passed had collided in right of screen
	 * @param rect The rectangle to test
	 * @return True if collided, false in others cases
	 */
	private boolean checkRightColision(Rectangle rect) {
		if((int)rect.getX()==screen.getWidth()-pxScale) return true;
		return false;
	}
	
}