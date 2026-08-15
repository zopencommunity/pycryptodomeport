/*
 * Declare posix_memalign for the pycryptodome build on z/OS.
 *
 * src/common.h includes <stdlib.h> and then calls posix_memalign under
 * HAVE_POSIX_MEMALIGN. Through that include chain the function ends up
 * implicitly declared regardless of the feature-test macros on the command
 * line -- _UNIX03_SOURCE and _XOPEN_SOURCE=600 are both set and it still is.
 * The clang on PATH here is 21.1.1, which rejects an implicit declaration
 * rather than warning about it:
 *
 *   src/common.h:164: error: call to undeclared function 'posix_memalign';
 *   ISO C99 and later do not support implicit function declarations
 *
 * The symbol itself is present -- /usr/include/stdlib.h declares it at line
 * 1342 as __new4205(int, posix_memalign, (void**, size_t, size_t)) and it
 * links -- so the gap is the declaration, not the function.
 *
 * Declaring it here is preferable to passing -Wno-error on the implicit
 * declaration diagnostic, which would silence the same error for every other
 * function in forty extension modules and hide a real mistake.
 */

#ifndef ZOPEN_ZOS_POSIX_MEMALIGN_H
#define ZOPEN_ZOS_POSIX_MEMALIGN_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int posix_memalign(void **memptr, size_t alignment, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* ZOPEN_ZOS_POSIX_MEMALIGN_H */
