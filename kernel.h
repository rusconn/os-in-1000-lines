#pragma once

#include "common.h"

#define PANIC(fmt, ...)                                                                            \
    do {                                                                                           \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);                      \
        while (1)                                                                                  \
            ;                                                                                      \
    } while (0)

struct sbiret {
    long error;
    long value;
};

struct trap_frame {
    uint32_t ra;
    uint32_t gp;
    uint32_t tp;
    uint32_t t0;
    uint32_t t1;
    uint32_t t2;
    uint32_t t3;
    uint32_t t4;
    uint32_t t5;
    uint32_t t6;
    uint32_t a0;
    uint32_t a1;
    uint32_t a2;
    uint32_t a3;
    uint32_t a4;
    uint32_t a5;
    uint32_t a6;
    uint32_t a7;
    uint32_t s0;
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;
    uint32_t s8;
    uint32_t s9;
    uint32_t s10;
    uint32_t s11;
    uint32_t sp;
} __attribute__((packed));

#define READ_CSR(reg)                                                                              \
    ({                                                                                             \
        unsigned long __tmp;                                                                       \
        __asm__ __volatile__("csrr %0, " #reg : "=r"(__tmp));                                      \
        __tmp;                                                                                     \
    })

#define WRITE_CSR(reg, value)                                                                      \
    do {                                                                                           \
        uint32_t __tmp = (value);                                                                  \
        __asm__ __volatile__("csrw " #reg ", %0" ::"r"(__tmp));                                    \
    } while (0)

#define PROCS_MAX 8
#define PROC_UNUSED 0
#define PROC_RUNNABLE 1

struct process {
    int pid;
    int state;  // PROC_UNUSED | PROC_RUNNABLE
    vaddr_t sp; // コンテキストスイッチ時のスタックポインタ
    uint32_t *page_table;
    uint8_t stack[8192]; // カーネルスタック
};

#define SATP_SV32 (1u << 31)
#define PAGE_V (1 << 0) // 有効化ビット
#define PAGE_R (1 << 1) // 読み込み可能
#define PAGE_W (1 << 2) // 書き込み可能
#define PAGE_X (1 << 3) // 実行可能
#define PAGE_U (1 << 4) // ユーザーモードでアクセス可能

#define USER_BASE 0x1000000

#define SSTATUS_SPIE (1 << 5)
#define SSTATUS_SUM (1 << 18)

#define SCAUSE_ECALL 8

#define PROC_EXITED 2

// リンクスクリプト (kernel.ld) が定義するシンボル
extern char __kernel_base[];
extern char __bss[], __bss_end[];
extern char __stack_top[];
extern char __free_ram[], __free_ram_end[];
extern char _binary_shell_bin_start[], _binary_shell_bin_size[];

// 他ファイルから使われるグローバル変数
extern struct process procs[PROCS_MAX];
extern struct process *current_proc;
extern struct process *idle_proc;

// エントリポイント
void kernel_entry(void);
void kernel_main(void);

// sbi.c
void putchar(char ch);
long getchar(void);

// vm.c
paddr_t alloc_pages(uint32_t n);
void map_page(uint32_t *table1, uint32_t vaddr, paddr_t paddr, uint32_t flags);

// proc.c
struct process *create_process(const void *image, size_t image_size);
void yield(void);
