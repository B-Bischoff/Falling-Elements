#include "TextureLoader.hpp"

TextureLoader::TextureLoader(std::string textureFilePath)
{
    generateTexture();
    setTextureWrapping(GL_REPEAT, GL_LINEAR);
    setTextureFiltering(GL_LINEAR, GL_LINEAR);
    flipTextureVertically(true);
    loadTexture(textureFilePath);
}

void TextureLoader::generateTexture()
{
	glGenTextures(1, &this->_texture);
	glBindTexture(GL_TEXTURE_2D, this->_texture);
}

void TextureLoader::setTextureWrapping(GLint sParam, GLint tParam) const
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sParam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tParam);
}

void TextureLoader::setTextureFiltering(GLint sParam, GLint tParam) const
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tParam);
}

void TextureLoader::flipTextureVertically(bool value) const
{
    stbi_set_flip_vertically_on_load(value);
}

void TextureLoader::loadTexture(std::string textureFilePath)
{
    unsigned char *data = stbi_load(textureFilePath.c_str(), &this->_width, &this->_height, &this->_nbrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
		throw std::invalid_argument("[TextureLoader] Can't open file");
    }
    stbi_image_free(data);
}

void TextureLoader::activeTexture(ShaderProgram& program, const int GL_TEXTURE_NB)
{
    program.useProgram();
    glActiveTexture(GL_TEXTURE_NB);
    glBindTexture(GL_TEXTURE_2D, this->_texture);
}

unsigned int TextureLoader::getTexture() const
{
    return this->_texture;
}

int TextureLoader::getWidth()
{
    return this->_width;
}

int TextureLoader::getHeight()
{
    return this->_height;
}

