export class VDP {
  private width = 256;
  private height = 192;
  private framebuffer: Uint32Array;
  private ctx?: CanvasRenderingContext2D;

  constructor(ctx?: CanvasRenderingContext2D) {
    this.ctx = ctx;
    this.framebuffer = new Uint32Array(this.width * this.height);
  }

  clear(color: number = 0x000000) {
    this.framebuffer.fill(0xff000000 | color);
  }

  getFramebuffer(): Uint32Array {
    return this.framebuffer;
  }

  copyFramebufferToImageData(imageData: ImageData) {
    const data = imageData.data;
    for (let i = 0; i < this.framebuffer.length; i++) {
      const color = this.framebuffer[i];
      const offset = i * 4;
      data[offset + 0] = (color >> 16) & 0xff;
      data[offset + 1] = (color >> 8) & 0xff;
      data[offset + 2] = color & 0xff;
      data[offset + 3] = (color >> 24) & 0xff;
    }
  }

  draw(imageData: ImageData) {
    if (!this.ctx) return;
    this.copyFramebufferToImageData(imageData);
    this.ctx.putImageData(imageData, 0, 0);
  }

  stepVDP(_cycles: number) {
    // placeholder for syncing VDP cycles with CPU cycles
  }
}
