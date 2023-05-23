#include <iostream>
#include <cmath>

#define PI 3.14159265

using namespace std;

class Shape {
public:
    Shape() {
        cout << "Shape ctor" << endl;
    }

    virtual ~Shape() {
        cout << "Shape dtor" << endl;
    }

    virtual float Area() const = 0;
};

class Circle : public Shape {
protected:
    float radius;

public:
    Circle(float r) : radius(r) {
        cout << "Circle ctor" << endl;
    }

    ~Circle() {
        cout << "Circle dtor" << endl;
    }

    float Area() const override {
        return PI * radius * radius;
    }
};

class Cylinder : public Circle {
protected:
    float height;

public:
    Cylinder(float r, float h) : Circle(r), height(h) {
        cout << "Cylinder ctor" << endl;
    }

    ~Cylinder() {
        cout << "Cylinder dtor" << endl;
    }

    float Area() const override {
        return 2 * Circle::Area() + 2 * PI * radius * height;
    }
};

class Sphere : public Circle {
public:
    Sphere(float r) : Circle(r) {
        cout << "Sphere ctor" << endl;
    }

    ~Sphere() {
        cout << "Sphere dtor" << endl;
    }

    float Area() const override {
        return 4 * Circle::Area();
    }
};

float FindArea(Shape& shape) {
    return shape.Area();
}

int main() {
    Shape* pS1 = new Cylinder(2, 4);
    Shape* pS2 = new Sphere(3);

    cout << "Cylinder area: " << FindArea(*pS1) << endl;
    cout << "Sphere area: " << FindArea(*pS2) << endl;

    delete pS1;
    delete pS2;

    return 0;
}
