#include "fs.h"
#include "../kernel/string.h"
#include "screen.h"
#include "../kernel/mem.h"

struct File {
    char name[32];
    char *content; 
    int exists;
};

struct File root_files[10];

void fs_init() {
    for (int i = 0; i < 10; i++) {
        root_files[i].exists = 0;
    }
    
    // --- THE FIX: Mount the app at the new physical address ---
    // Sector 40 is offset 39 sectors from the kernel start (0x8000).
    // 39 * 512 = 19,968 bytes. 0x8000 + 19968 = 0xCE00.
    root_files[0].exists = 1;
    strcpy("APP.ELF", root_files[0].name);
    root_files[0].content = (char *)0xCE00; 
}

void fs_list() {
    kprint("--- FILES ---\n");
    for (int i = 0; i < 10; i++) {
        if (root_files[i].exists) {
            kprint(root_files[i].name); kprint("\n");
        }
    }
    kprint("-------------\n");
}

void fs_write(char *filename, char *content) {
    for (int i = 0; i < 10; i++) {
        if (root_files[i].exists && strcmp(root_files[i].name, filename) == 0) {
            root_files[i].content = (char*)malloc(strlen(content) + 1);
            strcpy(content, root_files[i].content);
            kprint("File overwritten.\n"); return;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (root_files[i].exists == 0) {
            strcpy(filename, root_files[i].name);
            root_files[i].content = (char*)malloc(strlen(content) + 1);
            strcpy(content, root_files[i].content);
            root_files[i].exists = 1;
            kprint("File saved.\n"); return;
        }
    }
    kprint("Error: Disk full.\n");
}

void fs_read(char *filename) {
    for (int i = 0; i < 10; i++) {
        if (root_files[i].exists == 1 && strcmp(filename, root_files[i].name) == 0) {
            kprint("Content: "); kprint(root_files[i].content); kprint("\n"); return;
        }
    }
    kprint("Error: File not found.\n");
}

char* fs_get_content(char *filename) {
    for (int i = 0; i < 10; i++) {
        if (root_files[i].exists == 1 && strcmp(filename, root_files[i].name) == 0) {
            return root_files[i].content;
        }
    }
    return 0;
}
