#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.h"

class Player{
public:
    double x, y;
    bool dead;
    void update();
    void draw();
    bool checkBullet(double bx, double by);
    bullet pbullet;
    Player(double xx, double yy, double new_min_x, double new_max_x) : x(xx), y(yy), min_x(new_min_x), max_x(new_max_x), pbullet(bullet(0, 0)), dead(false) {pbullet.active = false;};

private:
    double min_x, max_x;
};

#endif // PLAYER_H
