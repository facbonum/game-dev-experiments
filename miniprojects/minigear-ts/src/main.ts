import { Memory } from "./memory/memory";
import { Z80 } from "./cpu/z80";
import { VDP } from "./video/vdp";

// Setup canvas
const canvas = document.getElementById("screen") as HTMLCanvasElement;
const ctx = canvas.getContext("2d")!;

// Setup framebuffer and imageData for 256x192 screen
const framebuffer = new Uint32Array(256 * 192);
const imageData = ctx.createImageData(256, 192);

// Create Memory with empty ROM initially
const memory = new Memory(new Uint8Array([0x00]));
const cpu = new Z80(memory);
cpu.reset();

const vdp = new VDP(ctx); // Optional, depending on your VDP implementation

// ROM loader input element
const romLoader = document.getElementById("romLoader") as HTMLInputElement;

romLoader.addEventListener("change", async () => {
  const file = romLoader.files?.[0];
  if (!file) {
    alert("No file selected");
    return;
  }
  const arrayBuffer = await file.arrayBuffer();
  const romData = new Uint8Array(arrayBuffer);

  memory.loadROM(romData); // <-- Load ROM dynamically here
  cpu.reset();
  console.log(`Loaded ROM ${file.name}, size ${romData.length} bytes`);
});

function mainLoop() {
  // Run some CPU steps per frame
  for (let i = 0; i < 100; i++) {
    cpu.step();
  }

  // Example: Draw an 8x8 tile from RAM at 0xC000 for debug
  for (let y = 0; y < 8; y++) {
    const row = memory.readByte(0xC000 + y);
    for (let x = 0; x < 8; x++) {
      const bit = (row >> (7 - x)) & 1;
      framebuffer[y * 256 + x] = bit ? 0xffffffff : 0xff000000; // white or black pixel
    }
  }

  // Copy framebuffer pixels into ImageData for canvas
  for (let i = 0; i < framebuffer.length; i++) {
    const color = framebuffer[i];
    const j = i * 4;
    imageData.data[j + 0] = (color >> 16) & 0xff;
    imageData.data[j + 1] = (color >> 8) & 0xff;
    imageData.data[j + 2] = color & 0xff;
    imageData.data[j + 3] = (color >> 24) & 0xff;
  }

  ctx.putImageData(imageData, 0, 0);

  requestAnimationFrame(mainLoop);
}

mainLoop();
