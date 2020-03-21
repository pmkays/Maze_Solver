
#include "Trail.h"

Trail::Trail() 
{
   this->length = 0; 
   breadcrumbs[TRAIL_ARRAY_MAX_SIZE] = {}; 
}
Trail::~Trail() 
{
   // TODO
}

int Trail::size() 
{
   // TODO
   return this->length;
}

Breadcrumb* Trail::getPtr(int i) 
{
   return this->breadcrumbs[i];
}

void Trail::addCopy(Breadcrumb* t) {
   // TODO
}

bool Trail::contains(int x, int y) 
{
   bool success = false;
   for(int i = 0; i < this->length; i++)
   {
      if(breadcrumbs[i]->getX() == x && breadcrumbs[i]->getY() == y)
      {
         success = true;
      }
   }
   return success;
}
