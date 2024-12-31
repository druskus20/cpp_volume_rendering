#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL
typedef int errno_t;
#define sscanf_s sscanf
#endif


