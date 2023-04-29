#include "Character.h"

static int death_frames = 50;

Character::Character(float x, float y, float RGB[3])
    : Poly(x, y)
{
    this->dying = false;
    this->hit_points = 25;
    this->rotating = 0;
    this->moving = 0;



    this->background_color[0] = RGB[0];
    this->background_color[1] = RGB[1];
    this->background_color[2] = RGB[2];

    //Ir pro laranja quando morre
    this->death_rgb_save[0] = 1 - this->background_color[0];
    this->death_rgb_save[1] = (1 - this->background_color[1])/4;
    this->death_rgb_save[2] = - this->background_color[2];
}
void Character::SetRotating(float degree)
{
    this->rotating = degree;
}
void Character::SetMoving(float movement)
{
    this->moving = movement;
}

void Character::Shoot()
{
    Projectile* shotPoly = new Projectile(this->anchor->x, this->anchor->y, this);
    shotPoly->AddVertex(this->anchor->x - 5, this->anchor->y - 5);
    shotPoly->AddVertex(this->anchor->x + 5, this->anchor->y - 5);
    shotPoly->AddVertex(this->anchor->x + 5, this->anchor->y + 5);
    shotPoly->AddVertex(this->anchor->x - 5, this->anchor->y + 5);
    shotPoly->SetOrientation(this->orientationVector.x, this->orientationVector.y);
    RenderManager::shared_instance().AddRenderableToList(shotPoly);
}
void Character::ReceiveDamage(float damage)
{
    this->hit_points = hit_points - damage;
    if(this->hit_points <= 0)
    {
        dying = true;
        death_frame = 0;
    }
}
void Character::AnimateDeath()
{
    float frames = FPSManager::shared_instance().GetFrames();
    if(last_death_frame != frames)
    {
        death_frame++;
        last_death_frame = frames;
        this->background_color[0] += death_rgb_save[0]/death_frames;
        this->background_color[1] += death_rgb_save[1]/death_frames;
        this->background_color[2] += death_rgb_save[2]/death_frames;
    }
}
void Character::Die()
{
    dying = false;
    RenderManager::shared_instance().RemoveRenderableFromList(this);
    CollisionManager::shared_instance().RemoveNPC(this);
}

void Character::Render()
{
    if(dying)
    {
        this->AnimateDeath();
        if(death_frame == death_frames) this->Die();
        Poly::Render();
        return;
    }
    if(moving)
    {
        Move(moving*500/FPSManager::shared_instance().GetFrames());
    }
    if(rotating)
    {
        Rotate(rotating*200/FPSManager::shared_instance().GetFrames());
    }

    Poly::Render();
}
