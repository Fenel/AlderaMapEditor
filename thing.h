#ifndef __THING_H__
#define __THING_H__

class Thing 
{
 public:
	Thing()
    {
    };
	
   ~Thing()
   {
   };
   virtual void render(unsigned char startWidth,unsigned char startHeight) { };

   Thing* parent;
};


#endif
