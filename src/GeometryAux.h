#ifndef GEOMETRYAUX_H
#define GEOMETRYAUX_H
#define _USE_MATH_DEFINES
#include <math.h>

class Point
{
    public:
        Point()
        {
            this->x = 0;
            this->y = 0;
        };
        Point(float x, float y)
        {
            this->x = x;
            this->y = y;
        };
        void PointBetween(float x0, float y0, float x1, float y1)
        {
            this->x = x0 + ((x1 - x0)/2);
            this->y = y0 + ((y1 - y0)/2);
        };
        float x;
        float y;
};
class GeometryAux
{
    public:
        static int GetOrientation(float x0, float y0, float x1, float y1, float x2, float y2);
        static bool Intercept(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
        static float DistanceBetween(float x0, float y0, float x1, float y1);
        static float GetDiff(float c0, float c1);
        static float AngleBetween(float x1, float y1, float x2, float y2);

    protected:

    private:
};

#endif // GEOMETRYAUX_H
