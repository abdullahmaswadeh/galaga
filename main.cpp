#include "header.h"
#include "Core.h"

int main(int argc, char *argv[])
{


    /*
    	const SDL_MessageBoxButtonData buttons[] = {
    		{     0, 0, "Yes" },
    		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "No" }
    	};

    	const SDL_MessageBoxData messageboxdata = {
    		SDL_MESSAGEBOX_INFORMATION,
    		NULL,
    		"Full Screen",
    		"Do you want to run in full screen mode ? ",
    		SDL_arraysize(buttons),
    		buttons,
    		NULL
    	};
    	int buttonid = -2;
    	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
    		SDL_Log("error displaying message box");
    	}
    	if (buttonid == 0) {
    		CCFG::fullScreen = true;
    	}




    	if(buttonid > -2){
    	*/
    CCore oCore;
    oCore.mainLoop();
    //}

    return 0;
}
