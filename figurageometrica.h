#ifndef FIGURAGEOMETRICA_H_INCLUDED
#define FIGURAGEOMETRICA_H_INCLUDED
#include "sculptor.h"

//class abstrata
class FiguraGeometrica{
protected:
    float r, g, b, a;

public:
    virtual ~FiguraGeometrica(){};
    virtual void draw(Sculptor &s)=0;
};

#endif // FIGURAGEOMETRICA_H_INCLUDED
