#include "TextRenderer3d.hpp"

TextRenderer3d::TextRenderer3d() {
    this->material = new Material("/shaders/BasicFont.vert", "/shaders/BasicFont.frag");

    glGenBuffers(1, &this->vbo);
}

void TextRenderer3d::setFont(char* filepath) {
    RuntimeFont::FontFace face = RuntimeFont::loadFont(filepath);
    this->setFont(face);
}

void TextRenderer3d::setFont(RuntimeFont::FontFace face) {
    this->face = face;
}

void TextRenderer3d::setText(char* text) {
    delete this->text;
    this->text = text;
    
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    this->textMesh = this->face.generateMesh(this->text, 10, 10);
}

void TextRenderer3d::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->material->use();
    this->material->setVec3("textColour", this->colour);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->textMesh.vertexBuffer);
    glVertexAttribPointer(
        0,                    // attribute 0
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        8 * sizeof(float),    // stride
        (void*)0              // array buffer offset
    );

    glVertexAttribPointer(
        1,                    // attribute 1
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        8 * sizeof(float),    // stride
        (void*)(3 * sizeof(float)) // array buffer offset
    );

    glVertexAttribPointer(
        2,                    // attribute 2
        2,                    // size - vec2
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        8 * sizeof(float),    // stride
        (void*)(6 * sizeof(float)) // array buffer offset
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->textMesh.indexBuffer);

    glDrawElements(GL_TRIANGLES, this->textMesh.indexes.size(), GL_UNSIGNED_INT, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisable(GL_BLEND);
}