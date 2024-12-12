#include <cstdio>
#include <dlfcn.h>

int main() {
    getchar();
    void *plug = dlopen("build/libplugin.so", RTLD_LAZY | RTLD_LOCAL);
    getchar();
    dlclose(plug);
    getchar();
}