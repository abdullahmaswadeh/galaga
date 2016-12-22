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

    SDL_Surface *surface; // this surface will tell us the details of the image
    if ((surface = IMG_Load((Resources::getImage(path)).c_str())))
    {
        // Check that the image's width is a power of 2

        mWidth = surface->w;
        mHeight = surface->h;
        cellWidth = (float)mWidth;
        cellHeight = (float)mHeight;

        if ((surface->w & (surface->w - 1)) != 0)
        {
            //printf("warning: image width is not a power of 2\n");
        }
        // Also check if the height is a power of 2
        if ((surface->h & (surface->h - 1)) != 0)
        {
            //printf("warning: image height is not a power of 2\n");
        }
        //get number of channels in the SDL surface
        nofcolors = surface->format->BytesPerPixel;

        //contains an alpha channel
        if (nofcolors == 4)
        {
            if (surface->format->Rmask == 0x000000ff)
                texture_format = GL_RGBA;
            else
                texture_format = GL_BGRA;
        }
        else if (nofcolors == 3) //no alpha channel
        {
            if (surface->format->Rmask == 0x000000ff)
                texture_format = GL_RGB;
            else
                texture_format = GL_BGR;
        }
        else
        {
            printf("warning: the image is not truecolor...this will break ");
        }



        // Have OpenGL generate a texture object handle for us
        glGenTextures(1, &texture);
        // Bind the texture object
        glBindTexture(GL_TEXTURE_2D, texture);
        // Set the texture's stretching properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, nofcolors, surface->w, surface->h, 0,
                     texture_format, GL_UNSIGNED_BYTE, surface->pixels);
    }
    else
    {
        printf("SDL could not load image.bmp: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    // Free the SDL_Surface only if it was successfully created
    if (surface)
    {
        SDL_FreeSurface(surface);
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

    glBindTexture(texture, 0);
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

    glBindTexture(texture, 0);
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

    glBindTexture(texture, 0);

}


