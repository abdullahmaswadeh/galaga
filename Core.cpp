#include "header.h"
#include "Resources.h"
#include "Core.h"
#include "CFG.h"
#include <SDL2/SDL_mixer.h>


/* ******************************************** */

bool CCore::quitGame = false;
bool CCore::keyLeft = false;
bool CCore::keyRight = false;
bool CCore::spaceKey = false;
Game* CCore::game = new Game();

CCore::CCore(void)
{

    this->quitGame = false;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        glEnable(GL_MULTISAMPLE);

        //Attributes
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, GL_TRUE);

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);



        //Create window
        window = SDL_CreateWindow("GALAGA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CCFG::SCREEN_WIDTH, CCFG::SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else
        {

            if (CCFG::fullScreen)
            {
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
            }

            //Create context
            gContext = SDL_GL_CreateContext(window);



            if (gContext == NULL)
            {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
            }
            else
            {
                //Initialize GLEW
                glewExperimental = GL_TRUE;
                GLenum glewError = glewInit();
                if (glewError != GLEW_OK)
                {
                    printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
                }

                //Use

                if(!CCFG::fullScreen)
                {
                    if (SDL_GL_SetSwapInterval(1) < 0)
                    {
                        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                    }
                }


                glViewport(0, 0, CCFG::SCREEN_WIDTH, CCFG::SCREEN_HEIGHT);
                gluOrtho2D(0, CCFG::SCREEN_WIDTH, CCFG::SCREEN_HEIGHT, 0);


            }
        }
    }


    //Events Variable
    mainEvent = new SDL_Event();

    //Game Object
    game = new Game();
}

CCore::~CCore(void)
{
    delete mainEvent;
    SDL_DestroyWindow(window);
}

/* ******************************************** */

void CCore::mainLoop()
{

    const int TICKS_PER_SECOND = 50;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 5;

    unsigned long next_game_tick = SDL_GetTicks();
    int loops;


    while (!quitGame && mainEvent->type != SDL_QUIT)
    {




        SDL_PollEvent(mainEvent);

        //Render quad
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




        loops = 0;
        while (SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP)
        {


            Update();

            next_game_tick += SKIP_TICKS;
            loops++;
        }

        CCFG::interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_game_tick)
                              / float(SKIP_TICKS);

        Input();

        Draw();

        SDL_GL_SwapWindow(window);

    }
}


void CCore::Draw()
{
    game->Draw();
}

void CCore::Update()
{
    game->update();
}

void CCore::Input()
{
    if (!CCFG::controlsEnabled)
    {
        keyLeft = false;
        keyRight = false;
        spaceKey = false;
        return;

    }

    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        keyRight = false;
        keyLeft = true;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        keyRight = true;
        keyLeft = false;
    }
    else
    {
        keyRight = false;
        keyLeft = false;
    }

    if (currentKeyStates[SDL_SCANCODE_SPACE])
    {
        spaceKey = true;
    }
    else
    {
        spaceKey = false;
    }

    if (mainEvent->type == SDL_KEYDOWN && mainEvent->key.repeat == 0)
    {

        if (mainEvent->key.keysym.sym == SDLK_SPACE && mainEvent->key.repeat == 0)
        {
			if (Game::mainElements.rocketInitiated) {
                Game::mainElements.shoot();
            }
        }

        if (mainEvent->key.keysym.sym == SDLK_SPACE && game->gameState == 0)
        {
            game->Start();
        }


        if (mainEvent->key.keysym.sym == SDLK_ESCAPE)
        {
            quitGame = true;
        }

    }

}


/* ******************************************** */

