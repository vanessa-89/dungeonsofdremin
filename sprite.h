#ifndef SPRITE_H
#define SPRITE_H

#include <string>

class Sprite
{
    public:
        Sprite();
        virtual ~Sprite();
        int Load(std::string fname);
    protected:
    private:
};

#endif // SPRITE_H
