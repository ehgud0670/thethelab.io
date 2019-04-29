
import processing.core.PApplet;
import processing.core.PImage;

public class Cigaratte extends PApplet {

    private int x;
    private int y;
    private PImage cigaImage;

    Cigaratte(int i, PApplet pApplet){
        x = SpringGame.WIDTH-200 + 65*i;
        y = 50;
        cigaImage = pApplet.loadImage("/home/kimdo/cigaratte.png");
    }

    void lifeminus(){
        y = -1000;
    }
    void display(PApplet pApplet){
        pApplet.image(cigaImage,x,y,60,60);
    }

}

