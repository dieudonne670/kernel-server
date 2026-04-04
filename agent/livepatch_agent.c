#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

/* Original function that we will patch */
int iot_read_sensor() {
    printf("[AGENT] Original sensor value: 42\n");
    return 42;
}

/* Load a patch (.so) dynamically */
int load_patch(const char *so_file) {
    void *handle = dlopen(so_file, RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "Error loading patch: %s\n", dlerror());
        return -1;
    }

    void (*patch_func)() = dlsym(handle, "patch_iot_read_sensor");
    if (!patch_func) {
        fprintf(stderr, "Error finding patch function: %s\n", dlerror());
        dlclose(handle);
        return -1;
    }

    patch_func();
    printf("[AGENT] Patch applied from %s\n", so_file);
    return 0;
}

int main() {
    iot_read_sensor();  // BEFORE PATCH
    load_patch("../patches/example_patch.so");
    iot_read_sensor();  // AFTER PATCH
    return 0;
}
