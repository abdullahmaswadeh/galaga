#include "texture.h"
#include "Resources.h"

LTexture::LTexture()
{
    //Initialize
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    texture = 0;
}


bool LTexture::loadFromFile(std::string path)
{
    bool success = true;
    //Get rid of preexisting texture

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SDL_Surface *loaded; // this surface will tell us the details of the image
    if ((loaded = IMG_Load((Resources::getImage(path)).c_str())))
    {
        // Convert surface to RGBA to handle all formats (indexed, RGB, BGRA, etc.)
        SDL_Surface *surface = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_RGBA32, 0);
        SDL_FreeSurface(loaded);

        if (!surface) {
            printf("SDL could not convert surface: %s\n", SDL_GetError());
            return false;
        }

        mWidth = surface->w;
        mHeight = surface->h;
        cellWidth = (float)mWidth;
        cellHeight = (float)mHeight;

        nofcolors = 4;
        texture_format = GL_RGBA;

        // Have OpenGL generate a texture object handle for us
        glGenTextures(1, &texture);
        // Bind the texture object
        glBindTexture(GL_TEXTURE_2D, texture);
        // Set the texture's stretching properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, surface->pitch / surface->format->BytesPerPixel);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

        SDL_FreeSurface(surface);
    }
    else
    {
        printf("SDL could not load image: %s\n", SDL_GetError());
        return false;
    }

    return success;
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

void LTexture::setWidth(int w)
{
    this->mWidth = w;
}
void LTexture::setHeight(int h)
{
    this->mHeight = h;
}

void LTexture::render(GLfloat x, GLfloat y, float color[3])
{

    this->x = x;
    this->y = y;

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, texture);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    glPushMatrix();
    //glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);

    glBegin(GL_QUADS);
    if(color!=NULL)
    {
        glColor3f(color[0], color[1], color[2]);
    }
    else
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    glTexCoord2i(0, 0);
    glVertex2f(x, y);
    glTexCoord2i(1, 0);
    glVertex2f(x +mWidth, y);
    glTexCoord2i(1, 1);
    glVertex2f(x +mWidth, y +mHeight);
    glTexCoord2i(0, 1);
    glVertex2f(x, y +mHeight);
    glEnd();

    glPopMatrix();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, 0);
}



void LTexture::renderCenter(GLfloat x, GLfloat y, float color[3], GLfloat angle)
{

    this->x = x;
    this->y = y;

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, texture);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);

    glBegin(GL_QUADS);
    if (color != NULL)
    {
        glColor3f(color[0], color[1], color[2]);
    }
    else
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    glTexCoord2i(0, 0);
    glVertex2f(0.0f - mWidth/2.0f, 0.0f - mHeight/2.0f);
    glTexCoord2i(1, 0);
    glVertex2f(0.0f + mWidth / 2.0f, 0.0f - mHeight / 2.0f);
    glTexCoord2i(1, 1);
    glVertex2f(0.0f + mWidth / 2.0f, 0.0f + mHeight / 2.0f);
    glTexCoord2i(0, 1);
    glVertex2f(0.0f - mWidth / 2.0f, 0.0f + mHeight/ 2.0f);
    glEnd();

    glPopMatrix();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, 0);
}

//Render Frame / Center origin
void LTexture::renderFrame(int frame, float x, float y, GLfloat angle)
{

    this->x = x;
    this->y = y;

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, texture);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);

    float tx = frame * (cellWidth / (float)mWidth);
    float wx = tx + cellWidth / (float)mWidth;



    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(tx, 0);
    glVertex2f(0.0f - cellWidth / 2.0f, 0.0f - cellHeight / 2.0f);
    glTexCoord2f(wx, 0);
    glVertex2f(0.0f + cellWidth / 2.0f, 0.0f - cellHeight / 2.0f);
    glTexCoord2f(wx, 1);
    glVertex2f(0.0f + cellWidth / 2.0f, 0.0f + cellHeight / 2.0f);
    glTexCoord2f(tx, 1);
    glVertex2f(0.0f - cellWidth / 2.0f, 0.0f + cellHeight / 2.0f);
    glEnd();

    glPopMatrix();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, 0);

}


