#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

#if !defined(ARENA_MALLOC) || !defined(ARENA_FREE)

#warning \
"Using <stdlib.h> malloc and free, because a replacement for one or both \
was not specified before including 'arena.h'."

#include <stdlib.h>
#define ARENA_MALLOC malloc
#define ARENA_FREE free

#endif /* !defined ARENA_MALLOC, ARENA_FREE */

typedef struct Arena_s
{
    char *region;
    size_t index;
    size_t size;
} Arena;

Arena* arena_create(size_t size)
{
    Arena *arena = ARENA_MALLOC(sizeof(Arena));
    if(arena == NULL)
    {
        return NULL;
    }
    
    arena->region = ARENA_MALLOC(size);
    if(arena->region == NULL)
    {
        return NULL;
    }

    arena->index = 0;
    arena->size = size;
    return arena;
}

void* arena_alloc(Arena *arena, size_t size)
{
    if(arena == NULL)
    {
        return NULL;
    }

    if(arena->size - arena->index >= size)
    {
        arena->index += size;
        return arena->region + (arena->index - size);
    }
    return NULL;
}

void arena_destroy(Arena *arena)
{
    if(arena == NULL)
    {
        return;
    }
    if(arena->region != NULL)
    {
        free(arena->region);            
    }
    free(arena);
}

#endif /* ARENA_H */