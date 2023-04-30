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

        void RefreshShotCooldown();
        void Render();

    protected:
        void AutonomousThinking();
    private:
        //Control Variables
        float rotating;
        float moving;

        //Base stats
        float movement_speed;
        float rotation_speed;
        float base_damage;
        float speed;

        // Life
        float hit_points;
        bool dying;
        bool dead;

        //Autonomy
        Character* Target;
        bool autonomous;
        float view_range;

        // Shot control
        float last_shot_frame;
        float shot_cooldown;

        // Death Animation
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
