#include "sl.h"
#include "invaders.h"
#include "player.h"
#include <iostream>

#define W_WIDTH 640
#define W_HEIGHT 480

enum GameStates {TITLE, GAME, WIN, LOSE};
enum GameStates state;

int main(int args, char *argv[]){
    // Create and prepare the window
	slWindow(W_WIDTH, W_HEIGHT, "Space Invaders", false);
	slSetBackColor(0.0, 0.0, 0.0);
	slSetTextAlign(SL_ALIGN_CENTER);
	slSetFont(slLoadFont("BULKYPIX.ttf"), 24);

	// Set the game's state and prepare it's elements
	state = TITLE;
	InvController invaders(0.0, W_HEIGHT, W_WIDTH, 0.0);
	Player player(48, 48, 0, W_WIDTH);

	// Main game loop:
	while(!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
	    if(state == TITLE){
            slSetForeColor(1.0, 1.0, 1.0, 1.0);

            slSetFontSize(32);
            slText(W_WIDTH / 2, W_HEIGHT / 2, "SPACE INVADERS");

            slSetFontSize(16);
            slText(W_WIDTH / 2, 4, "Press [ENTER] to begin.");

            if(slGetKey(SL_KEY_ENTER)) state = GAME;
	    }else if(state == GAME){
	        // Update and draw game elements
            player.update();
            player.draw();

            invaders.update();
            invaders.draw();

            // Check for collisions between the invaders' bullets and the player.
            for(int i = 0; i < invaders.bullets.size(); i++){
                if(player.checkBullet(invaders.bullets[i].x, invaders.bullets[i].y) || invaders.bullets[i].y <= 0)
                    invaders.bullets.erase(invaders.bullets.begin() + i);
            }

            // Check for collisions between the player's bullet and the invaders.
            if(player.pbullet.active){
                if(invaders.checkBullet(player.pbullet.x, player.pbullet.y) || player.pbullet.y > invaders.y)
                    player.pbullet.active = false;
            }

            // If either the player, or all of the invaders are dead, set the state appropriately.
            if(player.dead || invaders.y <= player.y) state = LOSE;
            if(!invaders.alive) state = WIN;
	    }else if(state == WIN){
            slSetForeColor(1.0, 1.0, 1.0, 1.0);

            slSetFontSize(32);
            slText(W_WIDTH / 2, W_HEIGHT / 2, "CONGRATULATIONS!\nYou Won!");

            slSetFontSize(16);
            slText(W_WIDTH / 2, 4, "Press [ESC] to close the game.");
	    }else if(state == LOSE){
            slSetForeColor(1.0, 1.0, 1.0, 1.0);

            slSetFontSize(32);
            slText(W_WIDTH / 2, W_HEIGHT / 2, "GAME OVER!\nYou lost!");

            slSetFontSize(16);
            slText(W_WIDTH / 2, 4, "Press [ESC] to close the game.");
	    }

		//DEBUG: FOR TESTING HITBOXES
		/*
		if(slGetMouseButton(SL_MOUSE_BUTTON_1) != 0){
            //std::cout << slGetMouseX() << " " << slGetMouseY() << std::endl;
            invaders.checkBullet(slGetMouseX(), slGetMouseY());
		}
		*/

		// Render everything
		slRender();
	}
    // End of the main game loop

	// Close the window and exit.
	slClose();
	return 0;
}
