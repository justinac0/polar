#include "resources.hpp"
#include <raylib.h>

Font global_font; 

void load_resources() {
    global_font = LoadFontEx("resources/JetBrainsMono-Regular.ttf", 64, 0, 250);
    SetTextureFilter(global_font.texture, TEXTURE_FILTER_TRILINEAR);
    // did it load?
}

Font get_font() {
    return global_font;
}

