#include <cmath>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>

#include "Common/FileUtil.h"
#include "Core/PixelDumper.h"

#define PIXELDUMPER_SIZE (1 << 20) * 100

struct dump {
    int width;
    int height;
    int stride;
};


namespace PixelDumper
{
static int s_shm_open_fd;
static void *s_shm;
bool g_initialized = false;

void Initialize()
{
    if (!File::CreateDir(File::GetUserPath(D_PIXELDUMPER_IDX))) {
        std::cout << "oops" << std::endl;
        return;
    }
    if (shm_unlink("/pixeldumper") == -1) {
        perror("unlink");
    }
    if ((s_shm_open_fd = shm_open("/pixeldumper", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1) {
        std::cout << "can't open shared stuff" << std::endl;
        perror("lol");
    }
    if (ftruncate(s_shm_open_fd, PIXELDUMPER_SIZE)) {
        perror("ftruncate");
    }
    if ((s_shm = mmap(0, PIXELDUMPER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, s_shm_open_fd, 0)) 
            == MAP_FAILED) {
        perror("mmap");
    }
    memset(s_shm, 0, PIXELDUMPER_SIZE);
    std::cout << "initialized" << std::endl;
    g_initialized = true;
}
void CopyFrame(const u8* data, int width, int height, int stride)
{
    struct dump dumper;
    dumper.width = width;
    dumper.height = height;
    dumper.stride = stride;
    std::memcpy(s_shm, &dumper, sizeof(struct dump));
    for (int i = 0; i < height; i++)
    {
        std::memcpy(((u8*) s_shm) + sizeof(struct dump) + i * std::abs(stride), data + i * stride, std::abs(stride));
    }
}

}
