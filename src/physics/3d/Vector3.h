//
// Created by Amy on 2/4/2021.
//

#ifndef DUST_VECTOR3_H
#define DUST_VECTOR3_H


template<typename T>
struct Vector3 {
    T x, y, z;

    Vector3<T> cross(Vector3<T> _other) {
        return Vector3({
                y * _other.z - z * _other.y,
                z * _other.x - x * _other.z,
                x * _other.y - y * _other.x
        });
    }
};

#endif //DUST_VECTOR3_H
