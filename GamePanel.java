import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.security.Key;
import java.util.Random;

public class GamePanel extends JPanel implements ActionListener {

    final static int HEIGHT = 800;
    final static int WIDTH = 800;
    final static int SIZE = 40;
    final static int COMPONENTS = HEIGHT*WIDTH/SIZE;
    final static int DELAY = 100;
    int appleX, appleY;
    int apples = 0;
    int body = 5;
    int x[] = new int[COMPONENTS];
    int y[] = new int[COMPONENTS];
    char dir ='R';
    boolean running = false;
    Timer timer;
    Random rand;

    GamePanel(){
        rand = new Random();
        this.setPreferredSize(new Dimension(WIDTH, HEIGHT));
        this.setFocusable(true);
        this.setBackground(Color.cyan);
        this.addKeyListener(new MyKeyAdapter());
        startGame();
    }

    public void startGame(){
        generateApple();
        running = true;
        timer = new Timer(DELAY, this);
        timer.start();
    }
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        draw(g);
    }

    public void draw(Graphics g){
        if(running) {
            g.setColor(Color.yellow);
            g.fillOval(appleX, appleY, SIZE, SIZE);
            for (int i = 0; i < body; i++) {
                if (i == 0) {
                    g.setColor(Color.black);
                    g.fillOval(x[i], y[i], SIZE, SIZE);
                } else {
                    g.setColor(Color.ORANGE);
                    g.fillRect(x[i], y[i], SIZE, SIZE);
                }
            }
        }
        else gameOver(g);
    }

    public void generateApple(){
        appleX = rand.nextInt((WIDTH/SIZE)) * SIZE;
        appleY = rand.nextInt((HEIGHT/SIZE)) * SIZE;
    }

    public void appleCheck(){
        if(x[0] == appleX && y[0] == appleY){
            apples++;
            body++;
            generateApple();
        }
    }

    public void deathCheck(){
        for(int i = body; i > 0; i--)
            if(x[i] == x[0] && y[i] == y[0])
                running = false;

        if(x[0] < 0 || x[0] > WIDTH || y[0] < 0 || y[0] > HEIGHT)
            running = false;
    }

    public void move(){
        for(int i = body; i > 0; i--) {
            x[i] = x[i-1];
            y[i] = y[i-1];
        }
        if(dir == 'R')
            x[0] = x[0] + SIZE;
        else if (dir == 'L') {
            x[0] = x[0] - SIZE;
        } else if (dir == 'U') {
            y[0] = y[0] - SIZE;
        }else y[0] = y[0] + SIZE;
    }

    class MyKeyAdapter extends KeyAdapter {
        public void keyPressed(KeyEvent e) {
            switch (e.getKeyCode()) {
                case KeyEvent.VK_RIGHT:
                    if (dir != 'L')
                        dir = 'R';
                    break;

                case KeyEvent.VK_LEFT:
                    if (dir != 'R')
                        dir = 'L';
                    break;

                case KeyEvent.VK_UP:
                    if(dir != 'D')
                        dir = 'U';
                    break;

                case KeyEvent.VK_DOWN:
                    if(dir != 'U')
                        dir = 'D';
                    break;
            }
        }
    }
    public void gameOver(Graphics g) {
        g.setColor(Color.red);
        g.setFont(new Font("Calibri", Font.BOLD+Font.ITALIC, 100));
        FontMetrics size = getFontMetrics(g.getFont());
        g.drawString("GAME OVER", (WIDTH-size.stringWidth("GAME OVER"))/2, HEIGHT/2);
        g.drawString("Score:" + apples, (WIDTH-size.stringWidth("Score:" + apples))/2, HEIGHT/3);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if(running){
            move();
            appleCheck();
            deathCheck();
        }
        repaint();
    }
}
