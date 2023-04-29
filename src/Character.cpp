#include "Character.h"

Character::Character(float x, float y)
    : Poly(x, y)
{
    //ctor
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
