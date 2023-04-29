#include "Character.h"

Character::Character(float x, float y)
    : Poly(x, y)
{
    this->hit_points = 25;
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
        this->Die();
}
void Character::Die()
{
    RenderManager::shared_instance().RemoveRenderableFromList(this);
    CollisionManager::shared_instance().RemoveNPC(this);
}
