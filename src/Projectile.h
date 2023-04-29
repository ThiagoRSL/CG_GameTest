#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "FPSManager.h"
#include "Poly.h"

class Character;

class Projectile : public Poly
{
    public:
        Projectile(float x, float y, Character* Owner);
        void Render();

    protected:
        Character* Owner;

    private:
};

#endif // PROJECTILE_H
