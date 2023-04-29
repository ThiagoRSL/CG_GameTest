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
    this->Move(1000/FPSManager::shared_instance().GetFrames());
    if(this->Owner->HasCollision(this->anchor->x, this->anchor->y))
    {
        return;
    }
    CV::color(1,1,1);
    CV::circleFill(this->anchor->x, this->anchor->y, 5, 30);

    Character* target = CollisionManager::shared_instance().VerifyCollisionNPCs(this->anchor->x, this->anchor->y);

    if(target == this->Owner)
    {
        printf("Vasco");
    }
    else
    {
        if(target != nullptr)
        {
            target->ReceiveDamage(this->damage);
            DestroyProjectile();
        }
    }
}

void Projectile::DestroyProjectile()
{
    RenderManager::shared_instance().RemoveRenderableFromList(this);
}
