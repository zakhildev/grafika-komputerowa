#include "../include/Mesh.hpp"
#include "../include/Shader.hpp"
#include <string>

Mesh::Mesh(vector<Vertex> vertices, vector<uint> indices,
           vector<Texture> textures, Material material)
    : vertices(vertices), indices(indices), textures(textures),
      material(material) {
  setupMesh();
}

void Mesh::setupMesh() {
  // Generate data buffers
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Bind mesh data for OpenGL to use
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint),
               &indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(3 * sizeof(float)));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(6 * sizeof(float)));

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(8 * sizeof(float)));

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(11 * sizeof(float)));

  glBindVertexArray(0);
}

void Mesh::Draw(Shader &shader) {
  uint diffuseN = 1;
  uint specularN = 1;
  uint normalN = 1;
  uint heightN = 1;

  for (uint i = 0; i < textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    string num;
    string name = textures[i].type;

    if (name == "texture_diffuse") {
      num = to_string(diffuseN++);
    } else if (name == "texture_specular") {
      num = to_string(specularN++);
    } else if (name == "texture_normal") {
      num = to_string(normalN++);
    } else if (name == "texture_height") {
      num = to_string(heightN++);
    }

    string uniformName = name + num;
    shader.setInt(uniformName.c_str(), i);
    glBindTexture(GL_TEXTURE_2D, textures[i].id);
  }
  glActiveTexture(GL_TEXTURE0);

  // Pass material properties to shader
  shader.setVec3("material.diffuse", material.diffuse);
  shader.setVec3("material.specular", material.specular);
  shader.setFloat("material.shininess", material.shininess);
  shader.setFloat("material.metallic", material.metallic);
  shader.setFloat("material.alpha", material.alpha);

  // Inform shader whether textures are available
  shader.setInt("hasTextures", textures.size() > 0);

  // Bind vertex data and draw the mesh
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}