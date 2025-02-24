#pragma once

class Texture {
private:
    unsigned int rendererID;
    int width;
    int height;
    int channel;
public:
    Texture(unsigned int width, unsigned int height);
    Texture(const char* filepath, unsigned int format);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unBind() const;
    unsigned int getRendererID();
};