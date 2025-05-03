// minigear.c - minimal Master System/Game Gear emulator scaffold

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// ----------------------
// CPU State (Z80-like)
// ----------------------
typedef struct {
    uint16_t pc, sp;
    uint8_t a, f;
    uint8_t b, c, d, e, h, l;
    bool halted;
} CPU;

// 64KB addressable memory (no paging yet)
uint8_t memory[0x10000];
CPU cpu;

// Load ROM into memory (naive, for now)
bool load_rom(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) return false;
    fread(&memory[0x0000], 1, 0x8000, f); // Load into $0000-$7FFF
    fclose(f);
    return true;
}

// Debug function: print CPU state
void print_cpu_state() {
    printf("PC:%04X SP:%04X A:%02X F:%02X\n", cpu.pc, cpu.sp, cpu.a, cpu.f);
    printf("B:%02X C:%02X D:%02X E:%02X H:%02X L:%02X\n", cpu.b, cpu.c, cpu.d, cpu.e, cpu.h, cpu.l);
}

// Simplified Z80 instruction execution
void cpu_step() {
    uint8_t opcode = memory[cpu.pc++];
    switch (opcode) {
        case 0x00: /* NOP */
            break;
        case 0x3E: /* LD A, nn */
            cpu.a = memory[cpu.pc++];
            break;
        case 0x32: /* LD (nn), A */ {
            uint8_t lo = memory[cpu.pc++];
            uint8_t hi = memory[cpu.pc++];
            uint16_t addr = lo | (hi << 8);
            memory[addr] = cpu.a;
            break;
        case 0xF3: /* DI */{
            break;
        }
        }
        default:
            printf("Unknown opcode: %02X at %04X\n", opcode, cpu.pc - 1);
            cpu.halted = true;
            break;
    }
}

// Emulator main loop
void run_emulator() {
    cpu.pc = 0x0000;
    cpu.sp = 0xDFF0;
    cpu.a = cpu.f = cpu.b = cpu.c = cpu.d = cpu.e = cpu.h = cpu.l = 0;
    cpu.halted = false;

    while (!cpu.halted) {
        print_cpu_state();
        cpu_step();
        getchar(); // Pause per step for debugging
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s romfile.sms\n", argv[0]);
        return 1;
    }

    if (!load_rom(argv[1])) {
        printf("Failed to load ROM: %s\n", argv[1]);
        return 1;
    }

    printf("ROM loaded. Starting emulation...\n\n");
    run_emulator();

    return 0;
}
