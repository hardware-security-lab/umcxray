#!/bin/sh

KVER=$(uname -r)
KDIR="/lib/modules/$KVER/build"

cat > compile_commands.json <<EOF
[
  {
    "directory": "$(pwd)",
    "file": "src/kmod/main.c",
    "arguments": [
      "gcc",
      "-nostdinc",
      "-I$KDIR/arch/x86/include",
      "-I$KDIR/arch/x86/include/generated",
      "-I$KDIR/include",
      "-I$KDIR/include/uapi",
      "-I$KDIR/include/generated",
      "-I$KDIR/include/generated/uapi",
      "-I$KDIR/arch/x86/include/uapi",
      "-I$KDIR/arch/x86/include/generated/uapi",
      "-D__KERNEL__",
      "-DMODULE",
      "-std=gnu11"
    ]
  }
]
EOF
