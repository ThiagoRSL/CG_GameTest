#include "Character.h"

static int death_frames = 20;

Character::Character(float x, float y, float RGB[3])
    : Poly(x, y)
{
    this->orientationVector.y = -1;
    this->orientationVector.x = 0;

    this->movement_speed = 500;
    this->rotation_speed = 200;

    //Autonomous Module
    this->autonomous = false;
    this->view_range = 600;
    this->Target = nullptr;
    this->target_last_known_location = new Pnt2();

    this->hit_points = 25;
    this->base_damage = 10;
    this->shot_cooldown = 0;

    this->dying = false;
    this->dead = false;
    //Controls
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
    if(shot_cooldown == 0)
    {
        Projectile* shotPoly = new Projectile(this->anchor->x, this->anchor->y, this->base_damage, this);
        shotPoly->AddVertex(this->anchor->x - 5, this->anchor->y - 5);
        shotPoly->AddVertex(this->anchor->x + 5, this->anchor->y - 5);
        shotPoly->AddVertex(this->anchor->x + 5, this->anchor->y + 5);
        shotPoly->AddVertex(this->anchor->x - 5, this->anchor->y + 5);
        shotPoly->SetOrientation(this->orientationVector.x, this->orientationVector.y);
        RenderManager::shared_instance().AddRenderableToList(shotPoly);
        shot_cooldown = 20;
    }
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
    //CollisionManager::shared_instance().RemoveNPC(this);
}

void Character::RefreshShotCooldown()
{
    if(shot_cooldown == 0)
        return;

    float frames = FPSManager::shared_instance().GetFrames();
    if(last_shot_frame != frames)
    {
        shot_cooldown--;
        last_shot_frame = frames;
    }
}
void Character::Render()
{
    RefreshShotCooldown();
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
    this->orientationVector.Render();

    Poly::Render();
}
void Character::ResetControls()
{
    this->moving = 0;
    this->rotating = 0;
}

void Character::AutonomousThinking()
{
    if(Target == nullptr || Target->IsDying() || Target->IsDead())
    {
        Character* player = CollisionManager::shared_instance().GetPlayerCharacter();
        //FindNewTarget
        if(!player->IsDead() && !player->IsDying())
            this->Target = player;
        else
        {
            Target = nullptr;
            this->ResetControls();
            this->SetAutonomous(false);
            return;
        }
    }
    if(GeometryAux::DistanceBetween(this->anchor, Target->GetAnchor()) > view_range)
    {
        rotating = 0;
        if(GeometryAux::DistanceBetween(this->anchor, this->target_last_known_location) > 100)
        {
            moving = 0.5;
        }
        else
            moving = 0;
        return;
    }
    moving = 0;
    this->target_last_known_location->x = Target->GetAnchor()->x;
    this->target_last_known_location->y = Target->GetAnchor()->y;

    float x1 = this->anchor->x;
    float y1 = this->anchor->y;
    float x2 = Target->GetAnchor()->x - x1; // Considerando o ponto âncora como a origem
    float y2 = Target->GetAnchor()->y - y1; // Considerando o ponto âncora como a origem
    float x3 = this->orientationVector.x;
    float y3 = this->orientationVector.y;

    float angleTarget = GeometryAux::AngleBetween(0, 0, x2, y2);
    float angleOrientation = GeometryAux::AngleBetween(0, 0, x3, y3);

    float angleDifference = angleTarget - angleOrientation;
    float angleDifferenceInverse = (360.0 - abs(angleDifference));

    if(abs(angleDifference) > 0 && abs(angleDifference) < 3)
    {
        rotating = 0;
        Shoot();
    }
    else
    {
        //Verifica se é melhor virar em sentido horário ou anti-horário.
        if(abs(angleDifferenceInverse) < abs(angleDifference))
        {
            if(angleDifference > 0)
                rotating = -0.25;
            else
                rotating = 0.25;
        }
        else
        {
            if(angleDifference > 0)
                rotating = 0.25;
            else
                rotating = -0.25;
        }
        //Atualizar o valor de rotação para o minimo necessário no último frame.
    }
}
