#include <glm/ext.hpp>
#include "Cube.h"

const GLfloat Cube::VERTICES[] = {
        -1.0f, -1.0f, 1.0f, 0, 0,
        1.0f, -1.0f, 1.0f, 1, 0,
        1.0f, 1.0f, 1.0f, 1, 1,
        -1.0f, 1.0f, 1.0f, 0, 1,
        // back
        -1.0f, -1.0f, -1.0f, 0, 0,
        1.0f, -1.0f, -1.0f, 1, 0,
        1.0f, 1.0f, -1.0f, 1, 1,
        -1.0f, 1.0f, -1.0f, 0, 1
};
const GLuint Cube::INDEXES[] = {
        0, 1, 2,
        2, 3, 0,
        // top
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // bottom
        4, 0, 3,
        3, 7, 4,
        // left
        4, 5, 1,
        1, 0, 4,
        // right
        3, 2, 6,
        6, 7, 3
};

Cube::Cube() : Actor("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl") {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    program->use();

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), &VERTICES, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, reinterpret_cast<const GLvoid*>(sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDEXES), &INDEXES, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cube::render() {
    Actor::render();

    program->use();

    GLint location = program->getUniformLocation("modelMatrix");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    GLint textureLocation = program->getUniformLocation("sampler");
    glUniform1i(textureLocation, 0);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
