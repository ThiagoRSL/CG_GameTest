#include "Character.h"

static int death_frames = 20;

Character::Character(float x, float y, float RGB[3])
    : Poly(x, y)
{
    this->autonomous = false;
    this->Target = nullptr;
    this->dying = false;
    this->dead = false;
    this->hit_points = 25;
    this->base_damage = 10;
    this->rotating = 0;
    this->moving = 0;
    this->movement_speed = 500;
    this->rotation_speed = 200;


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
    Projectile* shotPoly = new Projectile(this->anchor->x, this->anchor->y, this->base_damage, this);
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
    dead = true;
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
    if(autonomous)  AutonomousThinking();
    if(moving)      Move(moving*movement_speed/FPSManager::shared_instance().GetFrames());
    if(rotating)    Rotate(rotating*rotation_speed/FPSManager::shared_instance().GetFrames());

    Poly::Render();
}

void Character::AutonomousThinking()
{
    if(Target == nullptr || Target->IsDead())
    {
        Character* player = CollisionManager::shared_instance().GetPlayerCharacter();
        //FindNewTarget
        if(!player->IsDead())
            this->Target = player;
        else
        {
            Target = nullptr;
            this->SetAutonomous(false);
        }

    }
    float x1 = this->anchor->x; //this->orientationVector.x;
    float y1 = this->anchor->y; //this->orientationVector.y;
    float x2 = Target->GetAnchor()->x;
    float y2 = Target->GetAnchor()->y;

    float angleTarget = GeometryAux::AngleBetween(x1, y1, x2, y2);

    float x3 = this->anchor->x + this->orientationVector.x;
    float y3 = this->anchor->y + this->orientationVector.y;
    float angleOrientation = GeometryAux::AngleBetween(x1, y1, x3, y3);

    float angleDifference = abs(angleTarget - angleOrientation);
    if(angleDifference > 0 && angleDifference < 0.5)
    {
        rotating = 0;
        Shoot();
    }
    else
    {
        rotating = 1;
    }




    printf("\nAngle %f", angleDifference);
    //if(angleDifference > 0) rotating = 1;
    //else if(angleDifference < 0) rotating = -1;
    //else rotating = 0;
}
