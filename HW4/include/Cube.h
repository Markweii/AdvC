#ifndef Cube_h_
#define Cube_h_

#include <algorithm>
#include <cmath>
#include "Object.h"

class Cube : public Object {
public:
    Vector3 center; // Center of the cube
    Vector3 halfSize; // Half of the size (dimensions) of the cube

    Cube(const Vector3& center, const Vector3& size)
        : center(center), halfSize(size * 0.5f) {
            setColor(Vector3(0.f, 1.f, 0.f));  // Green color
        }

    bool getIntersection(const Ray& ray, IntersectionInfo* I) const {
        Vector3 min = center - halfSize;
        Vector3 max = center + halfSize;

        float tmin = (min.x - ray.o.x) / ray.d.x;
        float tmax = (max.x - ray.o.x) / ray.d.x;

        if (tmin > tmax) std::swap(tmin, tmax);

        float tymin = (min.y - ray.o.y) / ray.d.y;
        float tymax = (max.y - ray.o.y) / ray.d.y;

        if (tymin > tymax) std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax))
            return false;

        if (tymin > tmin)
            tmin = tymin;
        if (tymax < tmax)
            tmax = tymax;

        float tzmin = (min.z - ray.o.z) / ray.d.z;
        float tzmax = (max.z - ray.o.z) / ray.d.z;

        if (tzmin > tzmax) std::swap(tzmin, tzmax);

        if ((tmin > tzmax) || (tzmin > tmax))
            return false;

        if (tzmin > tmin)
            tmin = tzmin;
        if (tzmax < tmax)
            tmax = tzmax;

        I->object = this;
        I->t = tmin;

        return true;
    }

    Vector3 getNormal(const IntersectionInfo& I) const {
        Vector3 p = I.hit - center;
        Vector3 sign = Vector3((float)(p.x > 0) - (p.x < 0), (float)(p.y > 0) - (p.y < 0), (float)(p.z > 0) - (p.z < 0));
        return normalize(sign);
    }

    BBox getBBox() const {
        return BBox(center - halfSize, center + halfSize);
    }

    Vector3 getCentroid() const {
        return center;
    }
};

#endif

