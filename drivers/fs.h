#ifndef FS_H
#define FS_H

void fs_init();
void fs_list();
void fs_write(char *filename, char *content);
void fs_read(char *filename);
char* fs_get_content(char *filename);

#endif
