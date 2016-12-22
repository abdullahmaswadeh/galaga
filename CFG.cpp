#include "CFG.h"

/* ******************************************** */
CCFG::CCFG(void) {}

CCFG::~CCFG(void) {}

int CCFG::SCREEN_WIDTH = 800;
int CCFG::SCREEN_HEIGHT = 600;

float CCFG::HALF_SCREEN_W = CCFG::SCREEN_WIDTH / 2.0f;
float CCFG::HALF_SCREEN_H = CCFG::SCREEN_HEIGHT / 2.0f;

Music* CCFG::Sounds = new Music();
bool CCFG::muteMusic = false;
bool CCFG::muteSounds = false;

bool CCFG::fullScreen = true;

float CCFG::interpolation = 0.0;
bool CCFG::controlsEnabled = true;

unsigned int CCFG::shots = 0;
unsigned int CCFG::hits = 0;


