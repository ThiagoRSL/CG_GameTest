#include "Projectile.h"
#include "Character.h"

Projectile::Projectile(float x, float y, float damage, Character* Owner)
    :Poly(x, y)
{
    this->Owner = Owner;
    this->damage = damage;
}

void Projectile::Render()
{
    if(!this->Owner->HasCollision(this->anchor->x, this->anchor->y))
    {
        CV::color(1,1,1);
        CV::circleFill(this->anchor->x, this->anchor->y, 5, 30);

        if(Character* enemy = CollisionManager::shared_instance().VerifyCollision(this->anchor->x, this->anchor->y))
        {
            DestroyProjectile();
            enemy->ReceiveDamage(this->damage);
        }
    }
    this->Move(1000/FPSManager::shared_instance().GetFrames());
}

void Projectile::DestroyProjectile()
{
    RenderManager::shared_instance().RemoveRenderableFromList(this);
}
