#ifndef GLSPHERE_H
#define GLSPHERE_H

#include "glabstractpainting.h"
class GLSphere : public GLAbstractPainting
{
    float radius, precision,a, b, c;
public:
    GLSphere(float r, float ,float A, float B,float Cp);
    float getRadius() const;
    void setRadius(float r);
    float getPrecision() const;
    void setPrecision(float p);
    void paint() override;
    void animate(int t) override;
};

#endif // GLSPHERE_H
