#ifndef _BULLET_H_
#define _BULLET_H_
#include "header.h"
#include "texture.h"
#include "Objects.h"


class Bullet: public GameObject {
public:
	bool fromRocket = false;
	Bullet();
	~Bullet();
	void Update();
	void Render();
};



#endif // _BULLET_H_
