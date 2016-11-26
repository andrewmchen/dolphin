#pragma once

namespace PixelDumper
{
    extern bool g_initialized;
    void Initialize();
    void CopyFrame(const u8* data, int width, int height, int stride);
}
