#pragma once

class Texture2D {
private:
    unsigned int rendererID;
    int width;
    int height;
    int channel;
public:
    Texture2D(const char* filepath, unsigned int format);
    Texture2D(const Texture2D&) = delete;
    ~Texture2D();

    void bind(unsigned int slot = 0) const;
    void unBind() const;
    unsigned int getRendererID();
};