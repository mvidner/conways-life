#ifndef _MY_RANDOM_H
#define _MY_RANDOM_H

/// The maximum pseudo-random number
#define MY_RAND_MAX 32767
/// Return a pseudo-random number [0..MY_RAND_MAX]
int myrand(void);
/// Seed the pseudo-random generator
void mysrand(unsigned seed);

#endif
