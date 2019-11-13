#include "invaders.h"
#include "bullet.h"
#include "sl.h"
#include <tgmath.h>
#include <cstdlib>
#include <time.h>

InvController::InvController(double min_x, double min_y, double max_x, double max_y){
    // Set everything's values
    this->min_x = min_x;
    this->min_y = min_y;
    this->max_x = max_x;
    this->max_y = max_y;
    x = min_x;
    y = min_y;
    dir = 1;
    width = height = 24.0;
    spacing = 8.0;
    timer = 0.0;
    alive = true;
    srand(time(NULL));

    // Fill the 'invaders' array
    for(int i = 0; i < INV_Y_COUNT; i++){
        for(int j = 0; j < INV_X_COUNT; j++){
            invaders[i][j] = true;
        }
    }
}

void InvController::update(){
    if(!alive) return;

    timer += slGetDeltaTime();

    if(timer >= 0.5){ // If half-a-second has passed since the last move...
        timer = 0; // ...reset the timer...
        x += ((width + spacing) / 2) * dir; // ...and move the invaders.

        // If the invaders leave the previously set movement boundaries, change the direction they move in.
        if(x <= min_x || (width + spacing) * INV_X_COUNT + x >= max_x){
            dir = -dir;
            y -= height + spacing;
        }

        // 50/50 chance the enemies shoot (a bullet spawns at a random spot within the block of invaders)
        if(rand() % 2 == 0){
            int block_w = (width + spacing) * INV_X_COUNT;
            int block_h = (height + spacing) * INV_Y_COUNT;
            bullets.push_back(bullet(x + rand() % block_w, y - rand() % block_h));
        }
    }

    // Move every bullet
    for(int i = 0; i < bullets.size(); i++){
        if(bullets[i].active) bullets[i].y -= 4;
    }
}

void InvController::draw(){
    if(!alive) return;

    double xOff = width / 2 + x;
    double yOff = y - height;

    slSetForeColor(1.0, 1.0, 1.0, 1.0);

    alive = false; // Assume all enemies are dead.
    // Check if any enemies are still alive. If yes, draw them and set the 'alive' flag to true.
    for(int i = 0; i < INV_Y_COUNT; i++){
        for(int j = 0; j < INV_X_COUNT; j++){
            alive = invaders[i][j] || alive;

            if(invaders[i][j]) // If the entry == true, that means the enemy's still alive
                slRectangleFill((width + spacing) * j + xOff, -(height + spacing) * i + yOff, width, height); // Draw the enemy
        }
    }

    // Draw the enemy bullets
    for(int i = 0; i < bullets.size(); i++){
        slRectangleFill(bullets[i].x, bullets[i].y, 4, 8);
    }
}

// This function searches for enemies at the given coordinates. If any are found, they are killed and 'true' is returned.
bool InvController::checkBullet(double bx, double by){
    bx -= x;
    by = y - by;

    // Sprawdź czy podany pocisk w ogóle jest w miejscu, które zajmuje przeciwnicy
    if(bx > 0 && by > 0
       && bx < (width + spacing) * INV_X_COUNT && by < (height + spacing) * INV_Y_COUNT){
        int ix = floor(bx / (width + spacing));
        int iy = floor(by / (height + spacing));

        if(invaders[iy][ix]){ // Jeżli przeciwnik nie jest martwy...
            invaders[iy][ix] = false; // ...zabij go.
            return true;
        }
    }

    return false;
}
