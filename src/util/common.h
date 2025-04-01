#ifndef COMMON_H
#define COMMON_H

#define ASSERT(_e, ...) if (!(_e)) {fprintf(stderr, __VA_ARGS__); exit(1);}

#endif