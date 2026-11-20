#!/bin/sh

set -xue

# QEMUのコマンド(パスが通っていること)
QEMU=qemu-system-riscv32

# QEMUを起動
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot
