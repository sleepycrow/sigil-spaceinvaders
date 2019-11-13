#include "player.h"
#include "bullet.h"
#include "sl.h"
#include <algorithm>

int player_size = 32;

void Player::update(){
    if(dead) return;

    // Move the player whenever the left or right arrow key is pressed.
    if(slGetKey(SL_KEY_LEFT)){
        x -= 4;
    }else if(slGetKey(SL_KEY_RIGHT)){
        x += 4;
    }

    // Limit the player's movement to a previously specified area.
    x = std::max(std::min(x, max_x), min_x);

    // Whenever the space key is pressed, spawn a bullet. (the player is only allowed to have one bullet on screen at a time)
    if(slGetKey(' ') && !pbullet.active) pbullet = bullet(x, y);

    // Move the player's bullet.
    if(pbullet.active) pbullet.y += 4;
}

void Player::draw(){
    if(dead) return;

    // Draw the player
    slTriangleFill(x, y, player_size, player_size);

    // Draw the player's bullet (if any)
    if(pbullet.active) slRectangleFill(pbullet.x, pbullet.y, 4, 8);
}

// This function checks if the given coordinates coincide with the player's position. If so, kills the player and returns 'true'.
bool Player::checkBullet(double bx, double by){
    if(bx < x + (player_size / 2) && bx > x - (player_size / 2) && by <= y){
        dead = true;
        return true;
    }
    return false;
}
