#pragma once
#include <array>

#include "Vector.hpp"

struct Material {
    alignas(16) vector::vec3 ambient;
    alignas(16) vector::vec3 diffuse;
    alignas(16) vector::vec3 specular;
    alignas(4) GLfloat shininess;
};