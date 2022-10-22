#pragma once

#include "../../vendor/stb/stb_image.h"
#include "../../Application.h"
#include <GL/glew.h>
#include <iostream>
#include <exception>

class TextureLoader {
private:

	unsigned int _texture;
	int _width, _height, _nbrChannels;

	void generateTexture();
	void setTextureWrapping(GLint sParam, GLint tParam) const;
	void setTextureFiltering(GLint sParam, GLint tParam) const;
	void flipTextureVertically(bool value) const;
	void loadTexture(std::string textureFilePath);

public:
	TextureLoader(std::string textureFilePath);

	void activeTexture(ShaderProgram& program, const int GL_TEXTURE_NB);
	unsigned int getTexture() const;
	int getWidth();
	int getHeight();
};
