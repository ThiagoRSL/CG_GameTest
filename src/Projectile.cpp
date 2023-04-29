#include "Projectile.h"
#include "Character.h"

Projectile::Projectile(float x, float y, Character* Owner)
    :Poly(x, y)
{
    this->Owner = Owner;
}

void Projectile::Render()
{
    if(!this->Owner->HasCollision(this->anchor->x, this->anchor->y))
    {
        CV::color(0,0,255);
        CV::circleFill(this->anchor->x, this->anchor->y, 5, 30);
    }
    //RenderManager::shared_instance().HasCollidedWith();
    this->Move(1000/FPSManager::shared_instance().GetFrames());
}
