#ifndef CHARACTER_H
#define CHARACTER_H

#include "Poly.h"
#include "Projectile.h"



class Character : public Poly
{
    public:
        Character(float x, float y);

        void Shoot();

    protected:

    private:
};

#endif // CHARACTER_H
