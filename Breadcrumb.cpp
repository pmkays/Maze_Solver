
#include "Breadcrumb.h"

Breadcrumb::Breadcrumb(int x, int y, bool stale) 
{
   this->x = x;
   this->y = y;
   this->stale = stale;
}

Breadcrumb::~Breadcrumb() 
{
   // TODO
}

int Breadcrumb::getX() 
{
   return this->x;
}

int Breadcrumb::getY() 
{
   return this->y;
}

bool Breadcrumb::isStale() 
{
   return this->stale;
}

void Breadcrumb::setStale(bool stale) 
{
   this->stale = stale;
}
