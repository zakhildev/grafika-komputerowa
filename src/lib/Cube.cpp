/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../include/Cube.h"

namespace SimpleModels {

Cube cube;

Cube::Cube() {
  vertices = CubeInternal::vertices;
  normals = CubeInternal::normals;
  vertexNormals = CubeInternal::vertexNormals;
  texCoords = CubeInternal::texCoords;
  colors = CubeInternal::colors;
  vertexCount = CubeInternal::vertexCount;
  texCoordComponents = 2;
}

Cube::~Cube() {}

void Cube::drawSolid(bool smooth) { renderSolid(smooth, true); }

namespace CubeInternal {
unsigned int vertexCount = 36;

float vertices[] = {
    1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,
    -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, 1.0f,

    1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
    -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,

    -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,

    -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,
    1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,

    1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
    -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

    1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,

    -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,
    1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,

    -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,
    -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,

    -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f,
    1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

    -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,

    -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
    -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,

    -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,
    -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,

};

float colors[] = {
    1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
};

float normals[] = {
    0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,
    -1.0f, 0.0f,  0.0f,  0.0f,  -1.0f, 0.0f,

    0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,
    -1.0f, 0.0f,  0.0f,  0.0f,  -1.0f, 0.0f,

    0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

    1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

    -1.0f, 0.0f,  0.0f,  0.0f,  -1.0f, 0.0f,
    0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,

    -1.0f, 0.0f,  0.0f,  0.0f,  -1.0f, 0.0f,
    0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,

    0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,  -1.0f,
    0.0f,  0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,

    0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,  -1.0f,
    0.0f,  0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,

    0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
};

float vertexNormals[] = {
    1.0f,  -1.0f, -1.0f, 0.0f,  -1.0f, 1.0f,
    -1.0f, 0.0f,  -1.0f, -1.0f, -1.0f, 0.0f,

    1.0f,  -1.0f, -1.0f, 0.0f,  1.0f,  1.0f,
    -1.0f, 0.0f,  -1.0f, 1.0f,  -1.0f, 0.0f,

    -1.0f, -1.0f, 1.0f,  0.0f,  1.0f,  1.0f,
    1.0f,  0.0f,  1.0f,  -1.0f, 1.0f,  0.0f,

    -1.0f, -1.0f, 1.0f,  0.0f,  -1.0f, 1.0f,
    1.0f,  0.0f,  1.0f,  1.0f,  1.0f,  0.0f,

    1.0f,  -1.0f, 1.0f,  0.0f,  1.0f,  1.0f,
    -1.0f, 0.0f,  1.0f,  -1.0f, -1.0f, 0.0f,

    1.0f,  -1.0f, 1.0f,  0.0f,  1.0f,  1.0f,
    1.0f,  0.0f,  1.0f,  1.0f,  -1.0f, 0.0f,

    -1.0f, -1.0f, -1.0f, 0.0f,  -1.0f, 1.0f,
    1.0f,  0.0f,  -1.0f, -1.0f, 1.0f,  0.0f,

    -1.0f, -1.0f, -1.0f, 0.0f,  -1.0f, 1.0f,
    -1.0f, 0.0f,  -1.0f, 1.0f,  1.0f,  0.0f,

    -1.0f, -1.0f, -1.0f, 0.0f,  1.0f,  -1.0f,
    1.0f,  0.0f,  1.0f,  -1.0f, -1.0f, 0.0f,

    -1.0f, -1.0f, -1.0f, 0.0f,  -1.0f, -1.0f,
    1.0f,  0.0f,  1.0f,  -1.0f, 1.0f,  0.0f,

    -1.0f, 1.0f,  1.0f,  0.0f,  1.0f,  1.0f,
    -1.0f, 0.0f,  1.0f,  1.0f,  1.0f,  0.0f,

    -1.0f, 1.0f,  1.0f,  0.0f,  -1.0f, 1.0f,
    -1.0f, 0.0f,  1.0f,  1.0f,  -1.0f, 0.0f,
};

float texCoords[] = {
    1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

    1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

    1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

    1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

    1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

    1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
};
} // namespace CubeInternal
} // namespace SimpleModels
