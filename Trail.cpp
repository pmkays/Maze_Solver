
#include "Trail.h"

Trail::Trail() 
{
   length = 0; 
   for(int i = 0; i <TRAIL_ARRAY_MAX_SIZE; i++)
   {
      breadcrumbs[i] = nullptr;
   }
}
Trail::~Trail() 
{
   for(int i = 0; i < TRAIL_ARRAY_MAX_SIZE ; i++)
   {
      if(breadcrumbs[i] != nullptr)
      {
         delete breadcrumbs[i];
         breadcrumbs[i] = nullptr;
      }
   }
}

int Trail::size() 
{
   return length;
}

Breadcrumb* Trail::getPtr(int i) 
{
   return breadcrumbs[i];
}

void Trail::addCopy(Breadcrumb* t) 
{
   breadcrumbs[length] = t;
   length++;
}

bool Trail::contains(int x, int y) 
{
   bool success = false;
   for(int i = 0; i < length; i++)
   {
      if(breadcrumbs[i]->getX() == x && breadcrumbs[i]->getY() == y)
      {
         success = true;
      }
   }
   return success;
}

bool Trail::containsStale(int x, int y) 
{
   bool success = false;
   for(int i = 0; i < length; i++)
   {
      if(breadcrumbs[i]->getX() == x && breadcrumbs[i]->getY() == y && breadcrumbs[i]->isStale())
      {
         success = true;
      }
   }
   return success;
}