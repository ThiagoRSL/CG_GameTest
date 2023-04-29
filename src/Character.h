#ifndef CHARACTER_H
#define CHARACTER_H

#include <math.h>
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
        void AutonomousThinking();
    private:
        Character* Target;
        bool autonomous;
        float movement_speed;
        float rotation_speed;
        float base_damage;
        float rotating;
        float moving;
        float hit_points;
        float speed;
        bool dying;
        bool dead;
        int death_frame;
        float death_rgb_save[3];
        float last_death_frame;

    //Getters e Setters
    public:
        bool IsDying() {return this->dying;}
        bool IsDead() {return this->dead;}
        Pnt2* GetAnchor() {return this->anchor;}

        void SetAutonomous(bool autonomous){this->autonomous = autonomous;}
        bool SetTarget(Character* target) {this->Target = target;}
};

#endif // CHARACTER_H
