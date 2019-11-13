#ifndef INVADERS_H
#define INVADERS_H

#include <vector>
#include "bullet.h"

#define INV_Y_COUNT 4
#define INV_X_COUNT 12

class InvController{
public:
    void update();
    void draw();
    bool alive;
    bool checkBullet(double bx, double by);
    InvController(double min_x, double min_y, double max_x, double max_y);
    double x, y;
    int amount;
    std::vector<bullet> bullets;

private:
    double width, height, spacing, min_x, max_x, min_y, max_y, timer, speed;
    int dir;
    bool invaders[INV_Y_COUNT][INV_X_COUNT];
};

#endif // INVADERS_H
