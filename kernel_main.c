#include "common.h"
#include "fs.h"
#include "kernel.h"
#include "virtio.h"

void kernel_main(void) {
    memset(__bss, 0, (size_t)__bss_end - (size_t)__bss);
    printf("\n\n");
    WRITE_CSR(stvec, (uint32_t)kernel_entry);

    virtio_blk_init();
    fs_init();

    idle_proc = create_process(NULL, 0);
    idle_proc->pid = 0;
    current_proc = idle_proc;

    create_process(_binary_shell_bin_start, (size_t)_binary_shell_bin_size);

    yield();
    PANIC("switched to idle process");

    for (;;) {
        __asm__ __volatile__("wfi");
    }
}
