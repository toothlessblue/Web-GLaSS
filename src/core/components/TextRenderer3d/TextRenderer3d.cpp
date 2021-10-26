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
    
    // TODO generate vertices
    // TODO generate UVs
}

void TextRenderer3d::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->material->use();
    this->material->setVec3("textColour", this->colour);

    glDisable(GL_BLEND);
}