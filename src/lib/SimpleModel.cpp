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

#include "../include/SimpleModel.h"
#include <cstring>

namespace SimpleModels {

SimpleModel::SimpleModel()
    : vertexCount(0), vertices(nullptr), normals(nullptr),
      vertexNormals(nullptr), texCoords(nullptr), colors(nullptr),
      vertexComponents(4), normalComponents(4), vertexNormalComponents(4),
      texCoordComponents(4), colorComponents(4), vao(0),
      buffersInitialized(false) {
  std::memset(vbo, 0, sizeof(vbo));
}

SimpleModel::~SimpleModel() {
  if (buffersInitialized) {
    glDeleteBuffers(5, vbo);
    glDeleteVertexArrays(1, &vao);
  }
}

void SimpleModel::ensureBuffers() {
  if (buffersInitialized)
    return;

  glGenVertexArrays(1, &vao);
  glGenBuffers(5, vbo);

  glBindVertexArray(vao);

  if (vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexCount * vertexComponents * sizeof(float), vertices,
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, vertexComponents, GL_FLOAT, GL_FALSE, 0, 0);
  }

  if (normals) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexCount * normalComponents * sizeof(float), normals,
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, normalComponents, GL_FLOAT, GL_FALSE, 0, 0);
  }

  if (vertexNormals) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexCount * vertexNormalComponents * sizeof(float),
                 vertexNormals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, vertexNormalComponents, GL_FLOAT, GL_FALSE, 0, 0);
  }

  if (texCoords) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexCount * texCoordComponents * sizeof(float), texCoords,
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, texCoordComponents, GL_FLOAT, GL_FALSE, 0, 0);
  }

  if (colors) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * colorComponents * sizeof(float),
                 colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, colorComponents, GL_FLOAT, GL_FALSE, 0, 0);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  buffersInitialized = true;
}

void SimpleModel::renderSolid(bool smooth, bool hasColor) {
  ensureBuffers();

  glBindVertexArray(vao);

  if (!smooth && normals) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, normalComponents, GL_FLOAT, GL_FALSE, 0, 0);
  } else if (smooth && vertexNormals) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glVertexAttribPointer(1, vertexNormalComponents, GL_FLOAT, GL_FALSE, 0, 0);
  }

  if (hasColor && colors) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
    glVertexAttribPointer(3, colorComponents, GL_FLOAT, GL_FALSE, 0, 0);
  }

  glDrawArrays(GL_TRIANGLES, 0, vertexCount);

  glBindVertexArray(0);
}

void SimpleModel::drawWire(bool smooth) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  drawSolid(smooth);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
} // namespace SimpleModels