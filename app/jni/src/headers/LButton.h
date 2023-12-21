#ifndef LBUTTON_H
#define LBUTTON_H

#include "Constants.h"


class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y, int pos);

		//Handles mouse event
		void handleEvent( SDL_Event* e);
	
		//Shows button sprite
		// void render();

		private:
		//Top left position
		SDL_Point mPosition;

};

#endif