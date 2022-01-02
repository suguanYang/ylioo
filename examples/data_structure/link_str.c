// linked string is good for concatenating strings
// it usually takes more memory than a normal string
// and it's implementation is not very efficient
#define CHUNK_SIZE 100
typedef struct Chunk {
    char chunk[CHUNK_SIZE];
    struct Chunk *next;
} Chunk;

typedef struct {
    Chunk *head;
    Chunk *tail;
    int len;
} LinkStr;