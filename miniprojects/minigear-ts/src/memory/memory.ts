export class Memory {
  private ram: Uint8Array;
  private rom: Uint8Array;

  constructor(romData: Uint8Array) {
    this.ram = new Uint8Array(0x2000); // 8KB Work RAM
    this.rom = romData;
  }

    loadROM(romData: Uint8Array) {
    this.rom = romData;               // new ROM loaded here anytime
  }

  readByte(addr: number): number {
    if (addr < 0xC000) {
      // Cartridge ROM (up to 0xBFFF)
      return this.rom[addr] ?? 0xFF;
    } else if (addr >= 0xC000 && addr < 0xE000) {
      // 8KB Work RAM
      return this.ram[addr - 0xC000];
    }
    return 0xFF; // open bus or unmapped
  }

  writeByte(addr: number, value: number) {
    if (addr >= 0xC000 && addr < 0xE000) {
      this.ram[addr - 0xC000] = value & 0xFF;
    } else {
      console.warn(`Attempted write to ROM or invalid address 0x${addr.toString(16)}`);
    }
  }
}
