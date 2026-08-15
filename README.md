# pycryptodome

[pycryptodome](https://www.pycryptodome.org/) for z/OS: a self-contained
cryptographic library — AES, ChaCha20, RSA, ECC, SHA-2/3, HMAC, PBKDF2 — in C,
with no external library to link against and no runtime dependencies.

It is not interchangeable with the other two crypto ports. `cryptography` wraps
OpenSSL and `pynacl` wraps libsodium; code written against pycryptodome's
`Crypto.*` API will not accept either.

## Install

```sh
zopen install pycryptodome
```

or, into a virtual environment:

```sh
export PIP_EXTRA_INDEX_URL="https://repo.zopen.community/pypi/wheels/simple/"
export PIP_CONSTRAINT="https://repo.zopen.community/pulp/content/constraints/zopen-constraints.txt"
pip install pycryptodome
```

See [Using Python packages on z/OS](https://zopen.community/#/Guides/PythonPackages)
for why both settings are needed.

## Notes for this platform

Upstream builds one `cp37-abi3` wheel intended to serve every interpreter, by
setting `py_limited_api` on all forty extensions. This port turns that off and
builds ordinary per-interpreter wheels instead.

Two reasons, either sufficient. The stable ABI does not hold across versions
here: an abi3 extension built by 3.12 dies inside CPython's allocator under 3.13
and 3.14 with `CEE3204S`, taking the interpreter down rather than raising
`ImportError`. And building once per interpreter would emit the same
`cp37-abi3` filename three times, so the wheels would overwrite one another and
two interpreters would end up with none.

The limited API is requested in two independent places — the `Extension` flags,
which decide how the modules compile, and a `bdist_wheel` option, which decides
what the filename claims. Clearing only the first still produced a single
`cp37-none-any` wheel.

Separately, `posix_memalign` needs an explicit declaration here. `src/common.h`
includes `<stdlib.h>` and calls it, but through that include chain it ends up
implicitly declared whatever feature-test macros are set, and the clang on this
system rejects an implicit declaration rather than warning. The port supplies a
prototype via `zos/zos-posix-memalign.h` rather than disabling the diagnostic,
which would silence it for every function across forty extension modules.
