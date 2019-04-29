
import processing.core.PApplet;
import processing.core.PImage;

public class Blossom extends PApplet {
    private float x;
    private float y;
    private float speed;
    private float radius;
    private PImage bloImage;
    private static final int INIT = -50;
    Blossom(PApplet pApplet) {
        radius = random(15,20);
        x = random(SpringGame.WIDTH - radius*2);
        y = INIT;
        speed = random(1, 5);
        bloImage = pApplet.loadImage("/home/kimdo/blossom.png");
    }

    boolean reachedBottom(){ return y > SpringGame.HEIGHT + radius * 2; }

    void move() { y += speed; }

    float getRadius() { return radius; }

    void setSpeedZero() { this.speed=0; }

    public float getX() { return x; }

    float getY() { return y; }

    public void setX(float x) { this.x = x; }

    void setYInit() { this.y =(float) INIT; }

    void display(PApplet pApplet){
        pApplet.image(bloImage,x,y,radius*2,radius*2);
    }
}


