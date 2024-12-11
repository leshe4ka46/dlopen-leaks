extern "C" __attribute__((visibility("default"))) const int *loadPlugin() {
    static int a;
    return &a;
}