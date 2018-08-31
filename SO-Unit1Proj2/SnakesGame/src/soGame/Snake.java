package soGame;
import java.util.ArrayList;
import java.awt.Color;
import java.awt.Rectangle;

/**
 * @brief 	This class represents a snake . The fields of a snake are: body, 
 * 			userOrIA and color. 
 * 
 * @author 	Shirley Ohara Telemaco de Freitas (shirleyohara@ufrn.edu.com)
 * @author 	Joaliton Luan Pereira de Ferreira (luanpereira00@outlook.com)
 * 
 * @version 01.09.2018
 */

public class Snake{
	public ArrayList<Rectangle> body; 	/**< The body of the snake */
	public boolean userOrIA;			/**< True, if is user and false in otherwise */
	public Color color;					/**< Color of the snake */

	/**
	 * Constructor for Snake class.
	 */
	public Snake(Color color, ArrayList<Rectangle> body, boolean userOrIA){
		this.userOrIA = userOrIA;
		this.color = color;		
		this.body = body;
	}

	/**
	 * @return 'True' if snake is controlled by user and 'False' if snake is controlled by IA.
	 */
	public boolean isUser(){
		return userOrIA;
	}

	/**
	 * @return color - snake's color
	 */
	public Color getColor(){
		return color;
	}
	
	/**
	 * Return the head of the snake
	 * @return body.get(0)
	 */
	public Rectangle getHead() {
		return body.get(0);
	}
	
	/**
	 * Return the neck of the snake
	 * @return body.get(1)
	 */
	public Rectangle getNeck() {
		return body.get(1);
	}
	
	/**
	 * Remove snake's tail
	 * @return r - The tail
	 */
	private Rectangle removeTail(){
		Rectangle r = body.get(body.size()-1);
		body.remove(body.size()-1);
		return r;
	}
	
	/**
	 * Add snake's head
	 * @param head Snake's head
	 */
	public void addHead(Rectangle head){
		body.add(0, head);
	}

	
	/**
	 * Movement the snake to some direction
	 * @param 	head Rectangle with the next position of the head
	 * @return	removeTail() - The tail 
	 */
	public Rectangle moviment(Rectangle head){	
		addHead(head);
		return removeTail();
	}
}
