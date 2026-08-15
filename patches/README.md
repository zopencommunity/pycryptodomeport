Patches for the pycryptodome port.

None. The one z/OS-specific change -- turning off the CPython limited API -- is
made by `zopen_pre_build` in the buildenv rather than by a patch, because it
applies to a flag repeated on every extension and a diff would need reapplying
each time upstream adds a module. See the comment there for why it is needed.
