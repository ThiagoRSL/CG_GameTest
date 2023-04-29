#ifndef CHARACTER_H
#define CHARACTER_H

#include "Poly.h"
#include "Projectile.h"

class Character : public Poly
{
    public:
        Character(float x, float y);

        void Shoot();
        void ReceiveDamage(float damage);
        void Die();

    protected:

    private:
        float hit_points;
        float speed;
};

#endif // CHARACTER_H
