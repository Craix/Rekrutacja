#include <iostream>
#include <type_traits>

struct vec3 {
    float x, y, z;

    float magnitude() {
        return sqrt(x * x + y * y + z * z);
    }

    vec3(const vec3& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }
    vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    vec3 operator / (float num) {
        return vec3(x / num, y / num, z / num);
    }

    vec3 operator * (float num) {
        return vec3(x * num, y * num, z * num);
    }

    vec3 operator * (const vec3& vec) {
        return vec3(x * vec.x, y * vec.y, z * vec.z);
    }


    vec3 operator + (const vec3& vec) {
        return vec3(x + vec.x, y + vec.y, z + vec.z);
    }

    vec3 operator - (const vec3& vec) {
        return vec3(x - vec.x, y - vec.y, z - vec.z);
    }

    friend std::ostream& operator<<(std::ostream& os, const vec3& vec);

};

std::ostream& operator<<(std::ostream& os, const vec3& vec) {
    os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
    return os;
}

vec3 abs(vec3 vec)
{
    return vec3(abs(vec.x), abs(vec.y), abs(vec.z));
}

// Implement this function for the following shapes:
struct Sphere {
    vec3 center;
    float radius;
};

struct Aabb {
    vec3 min;
    vec3 max;
};

// Triangular pyramid.
struct Tetrahedron
{
    vec3 points[4];
};

// Cylinder with hemispherical ends.
struct Capsule
{
    vec3 points[2];
    float radius;
};

template <typename Shape> vec3 support(vec3 v, Shape  s) {

    vec3 dir(v / v.magnitude());

    if constexpr (std::is_same<Shape, Sphere>::value) {

        return (s.center + (dir * s.radius));
    }

    if constexpr (std::is_same<Shape, Aabb>::value) {
        vec3 center(((s.min + s.max) / 2));
        vec3 size2(abs(s.min - s.max) / 2);

        return (center + (dir * size2));
    }

    if constexpr (std::is_same<Shape, Tetrahedron>::value) {
        vec3 center((s.points[0] + s.points[1] + s.points[2] + s.points[3]) / 4);

        float R = (center - s.points[0]).magnitude();

        vec3 one(1, 1, 1);
        float sum = (v.x * one.x + v.y * one.y + v.z * one.z);
        float cosA = (sum / (v.magnitude() * one.magnitude()));

        //unfinished
        float size = R * cosA;

        return (center + (dir * size));
    }

    if constexpr (std::is_same<Shape, Capsule>::value) {

        //TO;DO
        return vec3(1, 1, 1);
    }

    std::cout << "Not suported yet, return Null vector" << std::endl;
    return vec3(NULL, NULL, NULL);
}

int main() {

    vec3 vector{ -2, 5, 3 };

    Sphere sphere{ vec3{0,0,0}, 50 };
    std::cout << support<Sphere>(vector, sphere) << std::endl;

    Aabb aabb{ vec3{0,0,0}, vec3{100, 100, 100} };
    std::cout << support<Aabb>(vector, aabb) << std::endl;

    Tetrahedron tetrahedron{ vec3{1,1,1}, vec3{-1,-1,1}, vec3{-1,1,-1}, vec3{1,-1,-1} };
    std::cout << support<Tetrahedron>(vector, tetrahedron) << std::endl;

    Capsule capsule{ vec3{1,1,1}, vec3{100,100,100}, 50 };
    std::cout << support<Capsule>(vector, capsule) << std::endl;

    return 0;
}