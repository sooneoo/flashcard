#ifndef _VERSION_H_
#define _VERSION_H_

typedef struct {
    unsigned short major;
    unsigned short minor;
    unsigned short patch;
} FlashCard_Version;


#define flashcard_version() (FlashCard_Version) {   \
    .major = 0                                      \
    , .minor = 2                                    \
    , .patch = 0                                    \
}


#endif


