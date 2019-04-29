
import processing.core.PApplet;
import processing.core.PImage;

import java.util.Scanner;


public class SpringGame extends PApplet {
    private static final int SPEED = 20;
    private int cigacheck = 0;
    static final int WIDTH = 960;
    static final int HEIGHT = 521;
    private static final int NUM = 12;
    private PImage img;
    private Blossom[] blossom = new Blossom[NUM];
    private Ryu ryu;
    private static Cigaratte[] cigaratte = new Cigaratte[3];
    private boolean flag = true;

    @Override
    public void settings() {
        size(WIDTH, HEIGHT);
        img = loadImage("/home/kimdo/spring.jpg");
        ryu = new Ryu(this);
        for (int i = 0; i < NUM; i++) {
            blossom[i] = new Blossom(this);
        }
        for (int i = 0; i < 3; i++) {
            cigaratte[i] = new Cigaratte(i, this);
        }
    }

    @Override
    public void draw() {
        image(img, 0, 0, width, height);
        for (int i = 0; i < 3; i++) {
            cigaratte[i].display(this);
        }

        ryu.display(this);
        for (int i = 0; i < NUM; i++) {
            blossom[i].move();
        }

        for (int i = 0; i < NUM; i++) {
            blossom[i].display(this);
        }

        //check
        for (int i = 0; i < NUM; i++) {
            if (blossom[i].reachedBottom()) {
                blossom[i] = new Blossom(this);
            }
        }

        if (checkTouch()) {
            cigaratte[cigacheck].lifeminus();
            cigacheck++;
            if (cigacheck == 3) {
                for (int i = 0; i < NUM; i++) {
                    blossom[i].setSpeedZero();
                    blossom[i].setYInit();
                }
                flag = false;
            }
        }
        if (!flag) {
            textSize(80);
            fill(255, 0, 0);
            textAlign(CENTER);
            text("GameOver", WIDTH / 2, HEIGHT / 2);

            textSize(50);
            fill(255, 0, 0);
            textAlign(CENTER);
            text("Enterkey is restart \n q key is Quit", WIDTH / 2, HEIGHT / 2 + 80);
            if (key == ENTER) {
                flag = true;
                cigacheck = 0;
                settings();
            } else if (key == 'q') {
                exit();
            }
        }
    }

    private boolean checkTouch() {
        for (int i = 0; i < NUM; i++) {
            // Best idea
            if (blossom[i].getX() < ryu.getX() + Ryu.ryuWidth &&
                    blossom[i].getX() + 2 * blossom[i].getRadius() > ryu.getX() &&
                    blossom[i].getY() < ryu.getY() + Ryu.ryuHeight &&
                    blossom[i].getY() + 2 * blossom[i].getRadius() > ryu.getY()) {
                blossom[i].setX(random(WIDTH - 2 * blossom[i].getRadius()));
                blossom[i].setYInit();
                return true;
            }
              //Bad idea
//            if ((blossom[i].getX() < ryu.getX() && blossom[i].getX() + 2 * blossom[i].getRadius() >= ryu.getX())
//                    || (blossom[i].getX() >= ryu.getX() && blossom[i].getX() + 2 * blossom[i].getRadius() <= ryu.getX() + Ryu.ryuWidth)
//                    || (blossom[i].getX() <= ryu.getX() + Ryu.ryuWidth && blossom[i].getX() + 2 * blossom[i].getRadius() > ryu.getX() + Ryu.ryuWidth)) {
//                if ((blossom[i].getY() < ryu.getY() && blossom[i].getY() + 2 * blossom[i].getRadius() >= ryu.getY())
//                        || (blossom[i].getY() >= ryu.getY() && blossom[i].getY() + 2 * blossom[i].getRadius() <= ryu.getY() + Ryu.ryuWidth)
//                        || (blossom[i].getY() <= ryu.getY() + Ryu.ryuWidth && blossom[i].getY() + 2 * blossom[i].getRadius() > ryu.getY() + Ryu.ryuWidth)) {
//                    blossom[i].setX(random(WIDTH - 2 * blossom[i].getRadius()));
//                    blossom[i].setYInit();
//                    return true;
//                }
//            }
        }
        return false;
    }

    @Override
    public void keyPressed() {
        if (key == CODED) {
            if (keyCode == LEFT) {
                ryu.plusX(-SPEED);
                if (ryu.getX() < 0) {
                    ryu.setX(0);
                }
            } else if (keyCode == RIGHT) {
                ryu.plusX(SPEED);
                if (ryu.getX() > WIDTH - Ryu.ryuWidth) {
                    ryu.setX(WIDTH - Ryu.ryuWidth);
                }
            }
        }
    }

    public static void main(String[] args) {
        PApplet.main("processing.avoidpoop.SpringGame");
    }
}


