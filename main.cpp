#include <iostream>
#include <dlfcn.h>

int main(){
    void* plug = dlopen("build/libplugin.so", RTLD_LAZY | RTLD_LOCAL);
    dlclose(plug);
}