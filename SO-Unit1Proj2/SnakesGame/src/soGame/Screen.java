package soGame;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.BufferedImage;
import java.io.File;

/**
 * Class Canvas - a class to allow for simple graphical drawing on a canvas.
 * 
 * @author 	Shirley Ohara Telemaco de Freitas (shirleyohara@ufrn.edu.com)
 * @author 	Joaliton Luan Pereira de Ferreira (luanpereira00@outlook.com)
 * 
 * @version 01.09.2018
 */
public class Screen implements KeyListener{
	private final int height = 650; 	/**< The height of the screen */
    private final int width = 650;		/**< The width of the screen */
	public Color backgroundColor;		/**< The screen background color */
	private CanvasPane canvas;			/**< The screen canvas */
    public Graphics2D graphic;			/**< The graphic part of canvas */
    private Image canvasImage;			/**< The screen image */
    public int movimentSide; 			/**< The field to know the movement side */
    private int pxScale;				/**< The pxScale of the board */
    public JFrame frame;				/**< The frame of the screen*/
    
    /**
     * Create a Screen
     */
    public Screen(int pxScale) {
    	this.pxScale = pxScale;
    	frame = new JFrame();
    	
    	frame.addKeyListener(this);
        canvas = new CanvasPane();
        frame.setContentPane(canvas);
        canvas.setPreferredSize(new Dimension(width, height));
        backgroundColor = Color.black;
        frame.pack();
        setVisible(true); 
        firstScreen();
        movimentSide = 0;
    }
    
    /**
     * Return the width size of the screen 
     * @return width
     */
    public int getWidth() {
    	return width;
    }
    
    /**
     * Return the width size of the screen 
     * @return height
     */
    public int getHeight() {
    	return height;
    }
        
    /**
     * Set the canvas visibility and brings canvas to the front of screen
     * when made visible. This method can also be used to bring an already
     * visible canvas to the front of other windows.
     * @param visible  boolean value representing the desired visibility of
     * the canvas (true or false) 
     */
    private void setVisible(boolean visible) {
        if(graphic == null) {
            // first time: instantiate the offscreen image and fill it with
            // the background color
            Dimension size = canvas.getSize();
            canvasImage = canvas.createImage(size.width, size.height);
            graphic = (Graphics2D)canvasImage.getGraphics();
            graphic.setColor(backgroundColor);
            graphic.fillRect(0, 0, size.width, size.height);
            graphic.setColor(Color.yellow);
        }
        frame.setVisible(true);
    }

    /**
     * Draw the outline of a given shape onto the canvas.
     * @param  shape  the shape object to be drawn on the canvas
     */
    public void draw(Shape shape) {
        graphic.draw(shape);
        canvas.repaint();
    }
 
    /**
     * Fill the internal dimensions of a given shape with the current 
     * foreground color of the canvas.
     * @param  shape  the shape object to be filled 
     */
    public void fill(Shape shape) {
        graphic.fill(shape);
        canvas.repaint();
    }

    /**
     * Erase the whole canvas.
     */
    public void erase() {
        Color original = graphic.getColor();
        graphic.setColor(backgroundColor);
        Dimension size = canvas.getSize();
        graphic.fill(new Rectangle(0, 0, size.width, size.height));
        graphic.setColor(original);
        canvas.repaint();
        border();
    }

    /**
     * Erase a given shape's interior on the screen.
     * @param  shape  the shape object to be erased 
     */
    public void erase(Shape shape) {
        Color original = graphic.getColor();
        graphic.setColor(backgroundColor);
        graphic.fill(shape);              // erase by filling background color
        graphic.setColor(original);
        canvas.repaint();
        setForegroundColor(Color.red);
        border();
    }
    
    /**
     * Draw the first screen with the game name and the game image
     */
    private void firstScreen () {
    	setFont(new Font("Times New Roman", Font.BOLD, 24));
    	setForegroundColor(Color.red);
    	drawString("Welcome to Snake's Game", width/2 - 150, height/2);
    	
    	try {
    		File file = new File("../image/snake.png");
	    	BufferedImage image = ImageIO.read(file);
	    	drawImage(image, width/2 - 60, height/2 - 140);
    	} catch (Exception e) {
    		System.out.println(e);
    	}
    	
    	wait(3000);
    	erase();    	
    }
    
    /**
     * Draw the game over screen with the score
     */
    public void gameOverScreen () {
    	setFont(new Font("Times New Roman", Font.BOLD, 24));
    	setForegroundColor(Color.red);
    	drawString("Game Over :(", width/2 - 50, height/2);
    	wait(1000);
    	erase();    	
    }
    
    /**
     * Draw the game over screen with the ponctuation
     */
    public void gameOverScreen (Integer ponctuation) {
    	setFont(new Font("Times New Roman", Font.BOLD, 30));
    	String score = ponctuation.toString();
    	drawString("Score: " + score, width/2 - 40, height/2 - 20);
    	setFont(new Font("Times New Roman", Font.BOLD, 24));
    	setForegroundColor(Color.red);
    	drawString("Game Over :(", width/2 - 50, height/2 + 20);
    	wait(2000);
    	erase();   
    }
    
    /**
     * Show the choices of the Snake Game on the screen
     */
    public void gameChoices () {
    	setFont(new Font("Times New Roman", Font.BOLD, 24));
    	setForegroundColor(Color.red);
    	drawString(" Choices Menu ", width/2 - 40, height/2 - 40);
    	
    	setForegroundColor(Color.white);
    	setFont(new Font("Times New Roman", Font.PLAIN, 20));
    	drawString(" ( 1 ) - Artificial Intelligence ", width/2 - 100, height/2);
    	drawString(" ( 2 ) - Human Player ", width/2 - 100, height/2 + 20);
    	drawString(" ( 3 ) - Human Player vs. AI", width/2 - 100, height/2 + 40);
    	drawString(" ( 0 ) - QUIT ", width/2 - 100, height/2 + 60);
    	
    	setForegroundColor(Color.red);
    }
    
    /**
     * Print the border on the screen
     */
    public void border () {    	
    	Stroke oldStroke = graphic.getStroke();
    	graphic.setStroke(new BasicStroke((float) pxScale*2));
    	setForegroundColor(Color.red);
    	graphic.drawRect(0, 0, width, height);
    	graphic.setStroke(oldStroke);
    }
    
    /**
     * Draws a String on the Canvas.
     * @param  text   the String to be displayed 
     * @param  x      x co-ordinate for text placement 
     * @param  y      y co-ordinate for text placement
     */
    public void drawString(String text, int x, int y) {
        graphic.drawString(text, x, y);   
        canvas.repaint();
    }

    /**
     * Erases a String on the Canvas.
     * @param  text     the String to be displayed 
     * @param  x        x co-ordinate for text placement 
     * @param  y        y co-ordinate for text placement
     */
    public void eraseString(String text, int x, int y) {
        Color original = graphic.getColor();
        graphic.setColor(backgroundColor);
        graphic.drawString(text, x, y);   
        graphic.setColor(original);
        //canvas.repaint();
    }
    
    /**
     * Draws an image onto the canvas.
     * @param  img   	the Image object to be displayed 
     * @param  x      	x co-ordinate for Image placement 
     * @param  y       	y co-ordinate for Image placement 
     * @return  returns boolean value representing whether the image was 
     *          completely loaded 
     */
    public boolean drawImage(Image img, int x, int y) {
        boolean result = graphic.drawImage(img, x, y, null);
        canvas.repaint();
        return result;
    }

    /**
     * Sets the foreground color of the Canvas.
     * @param  newColor   the new color for the foreground of the Canvas 
     */
    public void setForegroundColor(Color newColor) {
        graphic.setColor(newColor);
    }

    /**
     * Returns the current color of the foreground.
     * @return   the color of the foreground of the Canvas 
     */
    public Color getForegroundColor() {
        return graphic.getColor();
    }

    /**
     * Sets the background color of the Canvas.
     * @param  newColor   the new color for the background of the Canvas 
     */
    public void setBackgroundColor(Color newColor) {
        backgroundColor = newColor;   
        graphic.setBackground(newColor);
    }

    /**
     * Returns the current color of the background
     * @return   the color of the background of the Canvas 
     */
    public Color getBackgroundColor() {
        return backgroundColor;
    }

    /**
     * changes the current Font used on the Canvas
     * @param  newFont   new font to be used for String output
     */
    public void setFont(Font newFont) {
        graphic.setFont(newFont);
    }

    /**
     * Returns the size of the canvas.
     * @return     The current dimension of the canvas
     */
    public Dimension getSize() {
        return canvas.getSize();
    }

    /**
     * Waits for a specified number of milliseconds before finishing.
     * This provides an easy way to specify a small delay which can be
     * used when producing animations.
     * @param  milliseconds  the number 
     */
    public void wait(int milliseconds) {
        try {
            Thread.sleep(milliseconds);
        } catch (InterruptedException e) {
            // ignoring exception at the moment
        }
    }

    /**
     * Check the arrow that is pressed
     */
	public void keyPressed(KeyEvent e) {
        int keyCode = e.getKeyCode();
        movimentSide = 0;
        
        if (keyCode == KeyEvent.VK_UP) {
        		movimentSide = 1;
        }
        if (keyCode == KeyEvent.VK_DOWN) {
        	movimentSide = 4;
        }
        if (keyCode == KeyEvent.VK_LEFT) {
        	movimentSide = 2;
        }
        if (keyCode == KeyEvent.VK_RIGHT) {
        	movimentSide = 3;
        }
	}

	public void keyReleased(KeyEvent e) {
		// 
	}

	/**
     * Check the arrow that was pressed
     */
	public void keyTyped(KeyEvent e) {
		int keyCode = e.getKeyCode();
        movimentSide = 0;
        
        if (keyCode == KeyEvent.VK_UP) {
        		movimentSide = 1;
        }
        if (keyCode == KeyEvent.VK_DOWN) {
        	movimentSide = 4;
        }
        if (keyCode == KeyEvent.VK_LEFT) {
        	movimentSide = 2;
        }
        if (keyCode == KeyEvent.VK_RIGHT) {
        	movimentSide = 3;
        }
	}


    /************************************************************************
     * Inner class CanvasPane - the actual canvas component contained in the
     * Canvas frame. This is essentially a JPanel with added capability to
     * refresh the image drawn on it.
     */
    private class CanvasPane extends JPanel {
		private static final long serialVersionUID = 1L;

		public void paint(Graphics g) {
            g.drawImage(canvasImage, 0, 0, null);
        }
    }
}
