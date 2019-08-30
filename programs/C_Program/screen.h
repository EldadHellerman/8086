
#define color565(r,g,b) (0x0000 | (((r&0x00f8) << 8) | ((g&0x00fc) << 3) | ((b&0x00f8) >> 3)))
#define WHITE   color565(255,255,255)
#define RED     color565(255,0,0)
#define GREEN   color565(0,255,0)
#define BLUE    color565(0,0,255)
#define BLACK   color565(0,0,0)

//__attribute((cdecl));
extern void screen_init(void);
extern void screen_fill(int color);
extern void screen_fill_black(void);

extern void screen_rect(int sx, int sy, int ex, int ey, int color);
extern void screen_image(int sx, int sy, int ex, int ey, const char *image);
//extern void screen_letter(int x, int y, char letter);
extern void screen_bitmap(int sx, int sy, int ex, int ey, const char *bitmap);
extern void screen_bitmap_far(int sx, int sy, int ex, int ey, const char *bitmap, int segment);
