import processing.core.PApplet;
import processing.core.PImage;

public class Ryu extends PApplet {
    private int x;
    private int y;
    private PImage ryuImage;
    static int ryuWidth = 64;
    static int ryuHeight = 78;

    Ryu(PApplet pApplet) {
        x = SpringGame.WIDTH / 2;
        y = SpringGame.HEIGHT-77;
        ryuImage = pApplet.loadImage("/home/kimdo/Ryu.jpg");
    }

    int getX() { return x; }

    int getY() { return y; }

    void plusX(int x) { this.x += x; }

    public void setX(int x) { this.x = x; }

    void display(PApplet pApplet){
        pApplet.image(ryuImage,x,y,ryuWidth,ryuHeight);
    }
}

