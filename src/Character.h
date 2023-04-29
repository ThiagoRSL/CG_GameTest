#ifndef CHARACTER_H
#define CHARACTER_H

#include "Poly.h"
#include "Projectile.h"

class Character : public Poly
{
    public:
        Character(float x, float y, float RGB[3]);

        void SetRotating(float degree);
        void SetMoving(float movement);
        void Shoot();
        void ReceiveDamage(float damage);
        void AnimateDeath();
        void Die();

        void Render();

    protected:

    private:
        float rotating;
        float moving;
        float hit_points;
        float speed;
        bool dying;
        int death_frame;
        float death_rgb_save[3];
        float last_death_frame;
};

#endif // CHARACTER_H
