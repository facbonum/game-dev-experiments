import { Memory } from "./memory/memory";

export class Z80 {
  private memory: Memory;

  // Registers
  private A = 0;
  private F = 0;
  private B = 0;
  private C = 0;
  private D = 0;
  private E = 0;
  private H = 0;
  private L = 0;

  private PC = 0;
  private SP = 0;

  constructor(memory: Memory) {
    this.memory = memory;
    this.reset();
  }

  reset() {
    this.PC = 0x0000;
    this.SP = 0xFFFE;
    this.A = this.F = this.B = this.C = this.D = this.E = this.H = this.L = 0;
  }

  private fetchByte(): number {
    const byte = this.memory.readByte(this.PC);
    this.PC = (this.PC + 1) & 0xFFFF;
    return byte;
  }

step(): number {
  const opcode = this.fetchByte();

  switch (opcode) {
    case 0x00: // NOP
      return 4;

    case 0x3E: // LD A, n
      this.A = this.fetchByte();
      return 7;

    case 0x06: // LD B, n
      this.B = this.fetchByte();
      return 7;

    case 0x0E: // LD C, n
      this.C = this.fetchByte();
      return 7;

    case 0x16: // LD D, n
      this.D = this.fetchByte();
      return 7;

    case 0x1E: // LD E, n
      this.E = this.fetchByte();
      return 7;

    case 0x26: // LD H, n
      this.H = this.fetchByte();
      return 7;

    case 0x2E: // LD L, n
      this.L = this.fetchByte();
      return 7;

    case 0x32: // LD (nn), A
      {
        const low = this.fetchByte();
        const high = this.fetchByte();
        const addr = (high << 8) | low;
        this.memory.writeByte(addr, this.A);
        return 13;
      }

    case 0x3A: // LD A, (nn)
      {
        const low = this.fetchByte();
        const high = this.fetchByte();
        const addr = (high << 8) | low;
        this.A = this.memory.readByte(addr);
        return 13;
      }

    case 0xC3: // JP nn
      {
        const low = this.fetchByte();
        const high = this.fetchByte();
        this.PC = (high << 8) | low;
        return 10;
      }

    case 0xCD: // CALL nn
      {
        const low = this.fetchByte();
        const high = this.fetchByte();
        const addr = (high << 8) | low;
        // Push PC to stack
        this.SP = (this.SP - 1) & 0xFFFF;
        this.memory.writeByte(this.SP, (this.PC >> 8) & 0xFF);
        this.SP = (this.SP - 1) & 0xFFFF;
        this.memory.writeByte(this.SP, this.PC & 0xFF);
        this.PC = addr;
        return 17;
      }

    case 0xC9: // RET
      {
        const low = this.memory.readByte(this.SP);
        this.SP = (this.SP + 1) & 0xFFFF;
        const high = this.memory.readByte(this.SP);
        this.SP = (this.SP + 1) & 0xFFFF;
        this.PC = (high << 8) | low;
        return 10;
      }

    case 0x76: // HALT
      this.PC = (this.PC - 1) & 0xFFFF; // Stay on HALT
      return 4;

    default:
      console.warn(`Unimplemented opcode: 0x${opcode.toString(16)} at PC=${(this.PC - 1).toString(16)}`);
      return 4;
  }
}

}
