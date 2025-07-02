import { Memory } from "../memory/memory";
import { Z80 } from "../cpu/z80";
import { VDP } from "../video/vdp";

export class Emulator {
  private memory: Memory;
  private cpu: Z80;
  private vdp: VDP;

  constructor(romData: Uint8Array) {
    this.memory = new Memory(romData);
    this.cpu = new Z80(this.memory);
    this.vdp = new VDP();
  }

  // Step one CPU instruction, return cycles used
  step(): number {
    const cycles = this.cpu.step();
    //this.cpu.step();
    // We will add VDP timing and rendering next
    // Advance VDP timing with cycles used
    this.vdp.stepVDP(cycles);
    return cycles;
  }

  getVDP(): VDP {
    return this.vdp;
  }
}
