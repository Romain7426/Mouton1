#include "global.h"
#include "biglib.h"
#include "biglib_rm_recursive.h"
#include <sys/types.h>
#include <sys/dir.h>
#include <dirent.h>

static bool_t biglib_rm_recursive_delete_all_files_in_dir(const char * path, const int verbose_level);


enum file_or_dir_t {
  FILE_OR_DIR__IS_DIR,
  FILE_OR_DIR__IS_FILE,
  FILE_OR_DIR__IS_SYMLINK,
  FILE_OR_DIR__IS_OTHER,
  FILE_OR_DIR__ERROR
};

static bool_t path_exists_huh(const char * path) {
  struct stat sb;
  int retval;
  // retval = stat(path, &sb); // follow symbolic link
  retval = lstat(path, &sb); // don't follow symbolic link
  
  if (retval == 0) return true;

  return false;
}


static enum file_or_dir_t path_is_file_or_dir(const char * path) {
  //man 2 stat
  //#include <sys/stat.h>
  //int stat(const char *restrict path, struct stat *restrict buf);
  // The stat() function obtains information about the file pointed to by path. 
  // The buf argument is a pointer to a stat structure.
  // Upon successful completion a value of 0 is returned.
#if 0
  struct stat { /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
    dev_t    st_dev;    /* device inode resides on */
    ino_t    st_ino;    /* inode's number */
    mode_t   st_mode;   /* inode protection mode */
    nlink_t  st_nlink;  /* number of hard links to the file */
    uid_t    st_uid;    /* user-id of owner */
    gid_t    st_gid;    /* group-id of owner */
    dev_t    st_rdev;   /* device type, for special file inode */
    struct timespec st_atimespec;  /* time of last access */
    struct timespec st_mtimespec;  /* time of last data modification */
    struct timespec st_ctimespec;  /* time of last file status change */
    off_t    st_size;   /* file size, in bytes */
    quad_t   st_blocks; /* blocks allocated for file */
    u_long   st_blksize;/* optimal file sys I/O ops blocksize */
    u_long   st_flags;  /* user defined flags for file */
    u_long   st_gen;    /* file generation number */
  };
#endif

#if 0
  // The status information word st_mode has the following bits:
#define S_IFMT 0170000           /* type of file */
#define        S_IFIFO  0010000  /* named pipe (fifo) */
#define        S_IFCHR  0020000  /* character special */
#define        S_IFDIR  0040000  /* directory */
#define        S_IFBLK  0060000  /* block special */
#define        S_IFREG  0100000  /* regular */
#define        S_IFLNK  0120000  /* symbolic link */
#define        S_IFSOCK 0140000  /* socket */
#define        S_IFWHT  0160000  /* whiteout */
#define S_ISUID 0004000  /* set user id on execution */
#define S_ISGID 0002000  /* set group id on execution */
#define S_ISVTX 0001000  /* save swapped text even after use */
#define S_IRUSR 0000400  /* read permission, owner */
#define S_IWUSR 0000200  /* write permission, owner */
#define S_IXUSR 0000100  /* execute/search permission, owner */
#endif
  

  struct stat sb;
  // pour rendre un fichier exécutable:
  //   mode_t mode;
  //   mode = st.st_mode | S_IXUSR;
  //   chmod(fichier_nom, mode);
  int retval;
  // retval = stat(path, &sb); // follow symbolic link
  retval = lstat(path, &sb); // don't follow symbolic link
  if (retval != 0) {
    return FILE_OR_DIR__ERROR;
  }

  const int file_type = sb.st_mode & S_IFMT;

#if 0
  fprintf(stderr, "path = %s\n", path);
  fprintf(stderr, "%d\n", file_type);
  fprintf(stderr, "%d", file_type & 1);
#endif


  switch (file_type) {
  case S_IFREG:  /* regular */
    return FILE_OR_DIR__IS_FILE;
    break;
  case S_IFDIR:  /* directory */
    return FILE_OR_DIR__IS_DIR;
    break;
  case S_IFLNK:  /* symbolic link */
    return FILE_OR_DIR__IS_SYMLINK;
    break;
  case S_IFIFO:  /* named pipe (fifo) */
  case S_IFCHR:  /* character special */
  case S_IFBLK:  /* block special */
  case S_IFSOCK: /* socket */
  //case S_IFWHT:  /* whiteout */
    return FILE_OR_DIR__IS_OTHER;
    break;
  default: assert(false); return FILE_OR_DIR__ERROR; break;
  }
  
  assert(false);
  return FILE_OR_DIR__ERROR;
}

const char * path_type(const char * path) {
  const enum file_or_dir_t file_type = path_is_file_or_dir(path);

  switch (file_type) {
  default: assert(false); return NULL; break;
  case FILE_OR_DIR__IS_DIR: return "FILE_OR_DIR__IS_DIR"; break;
  case FILE_OR_DIR__IS_FILE: return "FILE_OR_DIR__IS_FILE"; break;
  case FILE_OR_DIR__IS_SYMLINK: return "FILE_OR_DIR__IS_SYMLINK"; break;
  case FILE_OR_DIR__IS_OTHER: return "FILE_OR_DIR__IS_OTHER"; break;
  case FILE_OR_DIR__ERROR: return "FILE_OR_DIR__ERROR"; break;
  }

  assert(false);
  return NULL;
}

bool_t path_is_file_huh(const char * path) {
  return (path_is_file_or_dir(path) == FILE_OR_DIR__IS_FILE);
}

bool_t path_is_dir_huh(const char * path) {
  return (path_is_file_or_dir(path) == FILE_OR_DIR__IS_DIR);
}


bool_t biglib_rm_recursive(const char * path, const int verbose_level) {
  if (not(path_exists_huh(path))) {
    //printf("The path '%s' does not exist.\n", path);
    return true;
  }

  const enum file_or_dir_t file_type = path_is_file_or_dir(path);

  switch (file_type) {
  default: assert(false); return false; break;
  case FILE_OR_DIR__IS_DIR: {
    bool_t b;
    int retval;
    b = biglib_rm_recursive_delete_all_files_in_dir(path, verbose_level > 0 ? verbose_level - 1 : 0);
    assert(b);
    if (not(b)) return false;
    //printf("rm -Rf %s\n", path);
    //printf("rmdir %s\n", path);
    if (verbose_level >= 1) printf("rmdir %s\n", path);
    retval = rmdir(path);
    assert(retval == 0);
    return (retval == 0);
  }
    break;
  case FILE_OR_DIR__IS_FILE: {
    int retval;
    retval = unlink(path);
    assert(retval == 0);
    return (retval == 0);
  }
    break;
  case FILE_OR_DIR__IS_SYMLINK: {
    int retval;
    retval = unlink(path);
    assert(retval == 0);
    return (retval == 0);
  }
    break;
  case FILE_OR_DIR__IS_OTHER: 
    fprintf(stderr, "I don't know how to remove the file \"%s\"\n", path);
    return false; 
    break;
  case FILE_OR_DIR__ERROR: 
    fprintf(stderr, "Something wrong with the file \"%s\"\n", path);
    return false; 
    break;
  }

  assert(false);
  return false;
}



bool_t biglib_rm_recursive_delete_all_files_in_dir(const char * path, const int verbose_level) {
  assert(path_is_dir_huh(path));

  //man 3 directory
  //closedir, dirfd, opendir, readdir, readdir_r, rewinddir, seekdir, telldir -- directory operations
  //Standard C Library (libc, -lc)
  //#include <dirent.h>
  //int closedir(DIR *dirp);
  //int dirfd(DIR *dirp);
  //DIR * opendir(const char *dirname);
  //struct dirent * readdir(DIR *dirp);
  //int readdir_r(DIR *restrict dirp, struct dirent *restrict entry, struct dirent **restrict result);
  //void rewinddir(DIR *dirp);
  //void seekdir(DIR *dirp, long loc);
  //long telldir(DIR *dirp);
  
  DIR * dir_struct;
  dir_struct = opendir(path);
  assert(dir_struct != NULL);
  
  //int readdir_r(DIR *restrict dirp, struct dirent *restrict entry, struct dirent **restrict result);
  // readdir_r() provides the same functionality as readdir(), but the caller must 
  // provide a directory entry buffer to store the results in.  If the read succeeds, result is
  // pointed at the entry; upon reaching the end of the directory, result is set to NULL.  
  // readdir_r() returns 0 on success or an error number to indicate failure.

  struct dirent entry;
  struct dirent * result = NULL;
  for (;;) {
    int retval;
    retval = readdir_r(dir_struct, &entry, &result);
    assert(retval == 0);
    if (result == NULL) break;

    //man 5 dir
    //dir, dirent -- directory file format
    //#include <sys/types.h>
    //#include <sys/dir.h>
#if 0
    /*** Excerpt from <sys/dirent.h> ***/
    /*
     * The dirent structure defines the format of directory entries.
     *
     * A directory entry has a struct dirent at the front of it, containing its
     * inode number, the length of the entry, and the length of the name
     * contained in the entry.  These are followed by the name padded to a 4
     * byte boundary with null bytes.  All names are guaranteed null terminated.
     * The maximum length of a name in a directory is 255.
     */
    
    struct dirent { /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
      ino_t      d_ino;                /* file number of entry */
      __uint16_t d_reclen;             /* length of this record */
      __uint8_t  d_type;               /* file type, see below */
      __uint8_t  d_namlen;             /* length of string in d_name */
      char    d_name[255 + 1];   /* name must be no longer than this */ // RL: Name without path
    };
#endif
    if (strequal(result -> d_name, ".")) continue;
    if (strequal(result -> d_name, "..")) continue;
    if (verbose_level >= 1) printf("rm -f %s/%s\n", path, result -> d_name);

    // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
    //char file_with_path[strlen(path) + 1 + strlen(result -> d_name) + 1];
    const size_t file_with_path__strlen = strlen(path) + 1 + strlen(result -> d_name); 
    enum { file_with_path__unitsize = (1 << 10) }; 
    assert(file_with_path__unitsize > file_with_path__strlen);
    char file_with_path[file_with_path__unitsize];
    strcpy(file_with_path, path);
    strcat(file_with_path, "/");
    strcat(file_with_path, result -> d_name);
    
    bool_t b;
    b = biglib_rm_recursive(file_with_path, verbose_level > 0 ? verbose_level - 1 : 0);
    assert(b);
    if (not(b)) return false;
  } 
  
  closedir(dir_struct);

  return true;
}




