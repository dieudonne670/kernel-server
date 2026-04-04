#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * This program:
 * 1. Checks the patch server
 * 2. Downloads the latest patch
 * 3. Applies it by calling the livepatch agent
 */

#define SERVER "http://127.0.0.1:8000"

int main() {
    printf("[UPDATER] Checking for updates...\n");

    // STEP 1: Get latest patch name
    system("curl -s http://127.0.0.1:8000/latest_patch/ -o latest.json");

    FILE *f = fopen("latest.json", "r");
    if (!f) {
        printf("[UPDATER] Error: Cannot open latest.json\n");
        return -1;
    }

    char buffer[256];
    fread(buffer, 1, 256, f);
    fclose(f);

    // Extract filename
    char *pos = strstr(buffer, "latest_patch");
    if (!pos) {
        printf("[UPDATER] No patches available.\n");
        return 0;
    }

    char filename[128];
    sscanf(pos, "latest_patch\":\"%127[^\"]", filename);

    printf("[UPDATER] Latest patch: %s\n", filename);

    // STEP 2: Download patch
    char download_cmd[300];
    sprintf(download_cmd, "curl -s http://127.0.0.1:8000/download_patch/%s -o ../patches/%s", filename, filename);

    system(download_cmd);

    printf("[UPDATER] Patch downloaded.\n");

    // STEP 3: Apply patch
    printf("[UPDATER] Applying patch...\n");
    system("./livepatch_agent");

    return 0;
}
