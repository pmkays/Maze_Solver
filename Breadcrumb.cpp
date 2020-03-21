
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
   return x;
}

int Breadcrumb::getY() 
{
   return y;
}

bool Breadcrumb::isStale() 
{
   return stale;
}

void Breadcrumb::setStale(bool stale) 
{
   this->stale = stale;
}
