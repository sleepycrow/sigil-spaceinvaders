#ifndef BULLET_H
#define BULLET_H

struct bullet{
    double x, y;
    bool active;
    bullet(double xx, double yy) : x(xx), y(yy), active(true) {}
};

#endif // BULLET_H
