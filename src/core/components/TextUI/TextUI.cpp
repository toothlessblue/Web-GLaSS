#include "TextUI.hpp"

TextUI::TextUI() {
    this->material = new Material("/shaders/2dFont.vert", "/shaders/2dFont.frag");
    this->setFont("/fonts/Roboto-Black.ttf");
    this->setColour(glm::vec3(1, 1, 1));

    glGenBuffers(1, &this->vbo);
}

void TextUI::setFont(const char* filepath) {
    RuntimeFont::FontFace* face = RuntimeFont::loadFont(filepath);
    this->setFont(face);
}

void TextUI::setFont(RuntimeFont::FontFace* face) {
    this->face = face;
    this->material->setTexture("fontAtlas", this->face->atlasTexture);
}

void TextUI::setText(const char* text) {
    if (!this->face) {
        std::cerr << "No font is applied while trying to set text" << std::endl;
        return;
    }

    this->text = text;
    
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    this->textMesh = this->face->generateMesh(this->text);
}

void TextUI::setColour(glm::vec3 colour) {
    this->colour = colour;
    this->material->setVec3("textColour", this->colour);
}

void TextUI::render() {
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->material->use();

    this->textMesh.bindMesh();
    glDrawElements(GL_TRIANGLES, this->textMesh.indexes.size(), GL_UNSIGNED_INT, (void*)0);
    this->textMesh.unbindMesh();

    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}

RuntimeFont::FontFace* TextUI::getFont() {
    return this->face;
}