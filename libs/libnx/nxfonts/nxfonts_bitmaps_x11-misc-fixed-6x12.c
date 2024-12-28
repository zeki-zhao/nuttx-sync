typedef signed char _int8_t;
typedef unsigned char _uint8_t;
typedef signed short _int16_t;
typedef unsigned short _uint16_t;
typedef long int _int32_t;
typedef long unsigned int _uint32_t;
typedef signed long long _int64_t;
typedef unsigned long long _uint64_t;
typedef _int64_t _intmax_t;
typedef _uint64_t _uintmax_t;
typedef unsigned int _wchar_t;
typedef signed int _ssize_t;
typedef unsigned int _size_t;
typedef unsigned int irqstate_t;
typedef _int8_t int8_t;
typedef _uint8_t uint8_t;
typedef _int16_t int16_t;
typedef _uint16_t uint16_t;
typedef _int32_t int32_t;
typedef _uint32_t uint32_t;
typedef _int64_t int64_t;
typedef _uint64_t uint64_t;
typedef _int8_t int_least8_t;
typedef _uint8_t uint_least8_t;
typedef _int16_t int_least16_t;
typedef _uint16_t uint_least16_t;
typedef _int32_t int_least24_t;
typedef _uint32_t uint_least24_t;
typedef _int32_t int_least32_t;
typedef _uint32_t uint_least32_t;
typedef _int64_t int_least64_t;
typedef _uint64_t uint_least64_t;
typedef _int8_t int_fast8_t;
typedef _uint8_t uint_fast8_t;
typedef int int_fast16_t;
typedef unsigned int uint_fast16_t;
typedef _int32_t int_fast24_t;
typedef _uint32_t uint_fast24_t;
typedef _int32_t int_fast32_t;
typedef _uint32_t uint_fast32_t;
typedef _int64_t int_fast64_t;
typedef _uint64_t uint_fast64_t;
typedef _ssize_t intptr_t;
typedef _size_t uintptr_t;
typedef _intmax_t intmax_t;
typedef _uintmax_t uintmax_t;
typedef int16_t b8_t;
typedef uint16_t ub8_t;
typedef int32_t b16_t;
typedef uint32_t ub16_t;
typedef int64_t b32_t;
typedef uint64_t ub32_t;
b16_t b16sin(b16_t rad);
b16_t b16cos(b16_t rad);
b16_t b16atan2(b16_t y, b16_t x);
ub16_t ub32sqrtub16(ub32_t a);
ub8_t ub16sqrtub8(ub16_t a);
typedef unsigned int mode_t;
typedef _size_t size_t;
typedef _ssize_t ssize_t;
typedef _size_t rsize_t;
typedef int16_t uid_t;
typedef int16_t gid_t;
typedef uint32_t dev_t;
typedef uint16_t ino_t;
typedef uint16_t nlink_t;
typedef int pid_t;
typedef int id_t;
typedef int32_t key_t;
typedef intptr_t ptrdiff_t;
typedef _wchar_t wchar_t;
typedef int wint_t;
typedef int wctype_t;
typedef uint32_t fsblkcnt_t;
typedef uint32_t fsfilcnt_t;
typedef uint32_t blkcnt_t;
typedef int32_t off_t;
typedef int32_t fpos_t;
typedef int16_t blksize_t;
typedef unsigned int socklen_t;
typedef uint16_t sa_family_t;
typedef uint32_t clock_t;
typedef uint32_t useconds_t;
typedef int32_t suseconds_t;
typedef volatile uint8_t cpu_set_t;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef unsigned char unchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef signed char s_char;
typedef char *caddr_t;
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef uint64_t u_int64_t;
struct fsid_s
{
  int val[2];
};
typedef int (*main_t)(int argc, char *argv[]);
enum
{
  ERROR = -1,
  OK = 0,
};
int nsh_main(int argc, char *argv[]);
struct winsize
{
  uint16_t ws_row;
  uint16_t ws_col;
  uint16_t ws_xpixel;
  uint16_t ws_ypixel;
};
struct serial_rs485
{
  uint32_t flags;
  uint32_t delay_rts_before_send;
  uint32_t delay_rts_after_send;
};
typedef uint16_t fb_coord_t;
struct fb_videoinfo_s
{
  uint8_t fmt;
  fb_coord_t xres;
  fb_coord_t yres;
  uint8_t nplanes;
  uint8_t noverlays;
};
struct fb_planeinfo_s
{
  void *fbmem;
  size_t fblen;
  fb_coord_t stride;
  uint8_t display;
  uint8_t bpp;
  uint32_t xres_virtual;
  uint32_t yres_virtual;
  uint32_t xoffset;
  uint32_t yoffset;
};
struct fb_area_s
{
  fb_coord_t x;
  fb_coord_t y;
  fb_coord_t w;
  fb_coord_t h;
};
struct fb_transp_s
{
  uint8_t transp;
  uint8_t transp_mode;
};
struct fb_overlayinfo_s
{
  void *fbmem;
  size_t fblen;
  fb_coord_t stride;
  uint8_t overlay;
  uint8_t bpp;
  uint8_t blank;
  uint32_t chromakey;
  uint32_t color;
  struct fb_transp_s transp;
  struct fb_area_s sarea;
  uint32_t accl;
};
struct fb_vtable_s
{
  int (*getvideoinfo)( struct fb_vtable_s *vtable,
                      struct fb_videoinfo_s *vinfo);
  int (*getplaneinfo)( struct fb_vtable_s *vtable, int planeno,
                      struct fb_planeinfo_s *pinfo);
  int (*open)( struct fb_vtable_s *vtable);
  int (*close)( struct fb_vtable_s *vtable);
  int (*getoverlayinfo)( struct fb_vtable_s *vtable, int overlayno,
                        struct fb_overlayinfo_s *oinfo);
  int (*settransp)( struct fb_vtable_s *vtable,
                   const struct fb_overlayinfo_s *oinfo);
  int (*setchromakey)( struct fb_vtable_s *vtable,
                      const struct fb_overlayinfo_s *oinfo);
  int (*setcolor)( struct fb_vtable_s *vtable,
                  const struct fb_overlayinfo_s *oinfo);
  int (*setblank)( struct fb_vtable_s *vtable,
                  const struct fb_overlayinfo_s *oinfo);
  int (*setarea)( struct fb_vtable_s *vtable,
                 const struct fb_overlayinfo_s *oinfo);
  int (*pandisplay)( struct fb_vtable_s *vtable,
                    struct fb_planeinfo_s *pinfo);
  int (*setframerate)( struct fb_vtable_s *vtable, int rate);
  int (*getframerate)( struct fb_vtable_s *vtable);
  int (*getpower)( struct fb_vtable_s *vtable);
  int (*setpower)( struct fb_vtable_s *vtable, int power);
  int (*ioctl)( struct fb_vtable_s *vtable, int cmd, unsigned long arg);
  void *priv;
};
struct fb_fix_screeninfo
{
  char id[16];
  unsigned long smem_start;
  uint32_t smem_len;
  uint32_t type;
  uint32_t type_aux;
  uint32_t visual;
  uint16_t xpanstep;
  uint16_t ypanstep;
  uint16_t ywrapstep;
  uint32_t line_length;
  unsigned long mmio_start;
  uint32_t mmio_len;
  uint32_t accel;
  uint16_t capabilities;
  uint16_t reserved[2];
};
struct fb_bitfield
{
  uint32_t offset;
  uint32_t length;
  uint32_t msb_right;
};
struct fb_var_screeninfo
{
  uint32_t xres;
  uint32_t yres;
  uint32_t xres_virtual;
  uint32_t yres_virtual;
  uint32_t xoffset;
  uint32_t yoffset;
  uint32_t bits_per_pixel;
  uint32_t grayscale;
  struct fb_bitfield red;
  struct fb_bitfield green;
  struct fb_bitfield blue;
  struct fb_bitfield transp;
  uint32_t nonstd;
  uint32_t activate;
  uint32_t height;
  uint32_t width;
  uint32_t accel_flags;
  uint32_t pixclock;
  uint32_t left_margin;
  uint32_t right_margin;
  uint32_t upper_margin;
  uint32_t lower_margin;
  uint32_t hsync_len;
  uint32_t vsync_len;
  uint32_t sync;
  uint32_t vmode;
  uint32_t rotate;
  uint32_t colorspace;
  uint32_t reserved[4];
};
int up_fbinitialize(int display);
 struct fb_vtable_s *up_fbgetvplane(int display, int vplane);
void up_fbuninitialize(int display);
void fb_pollnotify( struct fb_vtable_s *vtable);
int fb_register(int display, int plane);
typedef uint16_t nxgl_mxpixel_t;
typedef int16_t nxgl_coord_t;
struct nxgl_point_s
{
  nxgl_coord_t x;
  nxgl_coord_t y;
};
struct nxgl_size_s
{
  nxgl_coord_t w;
  nxgl_coord_t h;
};
struct nxgl_rect_s
{
  struct nxgl_point_s pt1;
  struct nxgl_point_s pt2;
};
struct nxgl_vector_s
{
  struct nxgl_point_s pt1;
  struct nxgl_point_s pt2;
};
struct nxgl_run_s
{
  b16_t x1;
  b16_t x2;
  nxgl_coord_t y;
};
struct nxgl_trapezoid_s
{
  struct nxgl_run_s top;
  struct nxgl_run_s bot;
};
void nxgl_rgb2yuv(uint8_t r, uint8_t g, uint8_t b,
                  uint8_t *y, uint8_t *u, uint8_t *v);
void nxgl_yuv2rgb(uint8_t y, uint8_t u, uint8_t v,
                  uint8_t *r, uint8_t *g, uint8_t *b);
void nxgl_area2rect( struct nxgl_rect_s *dest,
                    const struct fb_area_s *src);
void nxgl_rect2area( struct fb_area_s *dest,
                    const struct nxgl_rect_s *src);
void nxgl_rectcopy( struct nxgl_rect_s *dest,
                   const struct nxgl_rect_s *src);
void nxgl_rectoffset( struct nxgl_rect_s *dest,
                     const struct nxgl_rect_s *src,
                     nxgl_coord_t dx, nxgl_coord_t dy);
void nxgl_vectoradd( struct nxgl_point_s *dest,
                    const struct nxgl_point_s *v1,
                    const struct nxgl_point_s *v2);
void nxgl_vectsubtract( struct nxgl_point_s *dest,
                       const struct nxgl_point_s *v1,
                       const struct nxgl_point_s *v2);
void nxgl_rectintersect( struct nxgl_rect_s *dest,
                        const struct nxgl_rect_s *src1,
                        const struct nxgl_rect_s *src2);
_Bool nxgl_intersecting( const struct nxgl_rect_s *rect1,
                       const struct nxgl_rect_s *rect2);
void nxgl_rectadd( struct nxgl_rect_s *dest,
                  const struct nxgl_rect_s *src1,
                  const struct nxgl_rect_s *src2);
void nxgl_rectunion( struct nxgl_rect_s *dest,
                    const struct nxgl_rect_s *src1,
                    const struct nxgl_rect_s *src2);
void nxgl_nonintersecting( struct nxgl_rect_s result[4],
                          const struct nxgl_rect_s *rect1,
                          const struct nxgl_rect_s *rect2);
_Bool nxgl_rectoverlap( struct nxgl_rect_s *rect1,
                      struct nxgl_rect_s *rect2);
_Bool nxgl_rectinside( const struct nxgl_rect_s *rect,
                     const struct nxgl_point_s *pt);
void nxgl_rectsize( struct nxgl_size_s *size,
                   const struct nxgl_rect_s *rect);
_Bool nxgl_nullrect( const struct nxgl_rect_s *rect);
void nxgl_runoffset( struct nxgl_run_s *dest,
                    const struct nxgl_run_s *src,
                    nxgl_coord_t dx, nxgl_coord_t dy);
void nxgl_runcopy( struct nxgl_run_s *dest,
                  const struct nxgl_run_s *src);
void nxgl_trapoffset( struct nxgl_trapezoid_s *dest,
                     const struct nxgl_trapezoid_s *src,
                     nxgl_coord_t dx, nxgl_coord_t dy);
void nxgl_trapcopy( struct nxgl_trapezoid_s *dest,
                   const struct nxgl_trapezoid_s *src);
int nxgl_splitline( struct nxgl_vector_s *vector,
                   struct nxgl_trapezoid_s *traps,
                   struct nxgl_rect_s *rect,
                   nxgl_coord_t linewidth);
void nxgl_circlepts( const struct nxgl_point_s *center,
                    nxgl_coord_t radius,
                    struct nxgl_point_s *circle);
void nxgl_circletraps( const struct nxgl_point_s *center,
                      nxgl_coord_t radius,
                      struct nxgl_trapezoid_s *circle);
uint32_t nxglib_rgb24_blend(uint32_t color1, uint32_t color2, ub16_t frac1);
uint16_t nxglib_rgb565_blend(uint16_t color1, uint16_t color2, ub16_t frac1);
typedef int (*vnc_mouseout_t)( void *arg, int16_t x,
                                   int16_t y, uint8_t buttons);
typedef int (*vnc_kbdout_t)( void *arg, uint8_t nch,
                                 const uint8_t *ch);
int vnc_fbinitialize(int display, vnc_kbdout_t kbdout,
                     vnc_mouseout_t mouseout, void *arg);
typedef void *NXHANDLE;
typedef void *NXWINDOW;
enum nx_event_e
{
  NXEVENT_BLOCKED = 0,
  NXEVENT_SYNCHED,
};
struct nx_callback_s
{
  void (*redraw)(NXWINDOW hwnd, const struct nxgl_rect_s *rect,
                 _Bool more, void *arg);
  void (*position)(NXWINDOW hwnd, const struct nxgl_size_s *size,
                   const struct nxgl_point_s *pos,
                   const struct nxgl_rect_s *bounds,
                   void *arg);
  void (*event)(NXWINDOW hwnd, enum nx_event_e event, void *arg1,
                void *arg2);
};
int nx_runinstance( const char *mqname, struct fb_vtable_s *dev);
NXHANDLE nx_connectinstance( const char *svrmqname);
void nx_disconnect(NXHANDLE handle);
int nx_eventhandler(NXHANDLE handle);
int nx_eventnotify(NXHANDLE handle, int signo);
NXWINDOW nx_openwindow(NXHANDLE handle, uint8_t flags,
                       const struct nx_callback_s *cb, void *arg);
int nx_closewindow(NXWINDOW hwnd);
int nx_block(NXWINDOW hwnd, void *arg);
int nx_synch(NXWINDOW hwnd, void *arg);
int nx_requestbkgd(NXHANDLE handle, const struct nx_callback_s *cb,
                   void *arg);
int nx_releasebkgd(NXWINDOW hwnd);
int nx_getposition(NXWINDOW hwnd);
int nx_setposition(NXWINDOW hwnd, const struct nxgl_point_s *pos);
int nx_setsize(NXWINDOW hwnd, const struct nxgl_size_s *size);
int nx_raise(NXWINDOW hwnd);
int nx_lower(NXWINDOW hwnd);
int nx_modal(NXWINDOW hwnd, _Bool modal);
int nx_setvisibility(NXWINDOW hwnd, _Bool hide);
_Bool nx_ishidden(NXWINDOW hwnd);
int nx_setpixel(NXWINDOW hwnd, const struct nxgl_point_s *pos,
                nxgl_mxpixel_t color[1]);
int nx_fill(NXWINDOW hwnd, const struct nxgl_rect_s *rect,
            nxgl_mxpixel_t color[1]);
int nx_getrectangle(NXWINDOW hwnd, const struct nxgl_rect_s *rect,
                    unsigned int plane, uint8_t *dest,
                    unsigned int deststride);
int nx_filltrapezoid(NXWINDOW hwnd, const struct nxgl_rect_s *clip,
                     const struct nxgl_trapezoid_s *trap,
                     nxgl_mxpixel_t color[1]);
int nx_drawline(NXWINDOW hwnd, struct nxgl_vector_s *vector,
                nxgl_coord_t width, nxgl_mxpixel_t color[1],
                uint8_t caps);
int nx_drawcircle(NXWINDOW hwnd, const struct nxgl_point_s *center,
                  nxgl_coord_t radius, nxgl_coord_t width,
                  nxgl_mxpixel_t color[1]);
int nx_fillcircle(NXWINDOW hwnd, const struct nxgl_point_s *center,
                  nxgl_coord_t radius,
                  nxgl_mxpixel_t color[1]);
int nx_setbgcolor(NXHANDLE handle, nxgl_mxpixel_t color[1]);
int nx_move(NXWINDOW hwnd, const struct nxgl_rect_s *rect,
            const struct nxgl_point_s *offset);
int nx_bitmap(NXWINDOW hwnd, const struct nxgl_rect_s *dest,
              const void *src[1],
              const struct nxgl_point_s *origin, unsigned int stride);
void nx_redrawreq(NXWINDOW hwnd, const struct nxgl_rect_s *rect);
int nx_constructwindow(NXHANDLE handle, NXWINDOW hwnd, uint8_t flags,
                       const struct nx_callback_s *cb, void *arg);
enum nx_fontid_e
{
  FONTID_DEFAULT = 0
  , FONTID_X11_MISC_FIXED_6X12 = 26
};
struct nx_fontmetric_s
{
  uint32_t stride : 3;
  uint32_t width : 6;
  uint32_t height : 6;
  uint32_t xoffset : 6;
  uint32_t yoffset : 6;
  uint32_t unused : 5;
};
struct nx_fontbitmap_s
{
  struct nx_fontmetric_s metric;
  const uint8_t *bitmap;
};
struct nx_fontset_s
{
  uint8_t first;
  uint8_t nchars;
  const struct nx_fontbitmap_s *bitmap;
};
struct nx_font_s
{
  uint8_t mxheight;
  uint8_t mxwidth;
  uint8_t mxbits;
  uint8_t spwidth;
};
struct nx_fontpackage_s
{
  uint8_t id;
  const struct nx_font_s metrics;
  const struct nx_fontset_s font7;
};
typedef void *FCACHE;
struct nxfonts_glyph_s
{
  struct nxfonts_glyph_s *flink;
  uint8_t code;
  uint8_t height;
  uint8_t width;
  uint8_t stride;
  uint8_t bitmap[1];
};
NXHANDLE nxf_getfonthandle(enum nx_fontid_e fontid);
 const struct nx_font_s *nxf_getfontset(NXHANDLE handle);
 const struct nx_fontbitmap_s *nxf_getbitmap(NXHANDLE handle,
                                                uint16_t ch);
int nxf_convert_1bpp( uint8_t *dest, uint16_t height,
                     uint16_t width, uint16_t stride,
                     const struct nx_fontbitmap_s *bm,
                     nxgl_mxpixel_t color);
int nxf_convert_2bpp( uint8_t *dest, uint16_t height,
                     uint16_t width, uint16_t stride,
                     const struct nx_fontbitmap_s *bm,
                     nxgl_mxpixel_t color);
int nxf_convert_4bpp( uint8_t *dest, uint16_t height,
                     uint16_t width, uint16_t stride,
                     const struct nx_fontbitmap_s *bm,
                     nxgl_mxpixel_t color);
int nxf_convert_8bpp( uint8_t *dest, uint16_t height,
                     uint16_t width, uint16_t stride,
                     const struct nx_fontbitmap_s *bm,
                     nxgl_mxpixel_t color);
int nxf_convert_16bpp( uint16_t *dest, uint16_t height,
                      uint16_t width, uint16_t stride,
                      const struct nx_fontbitmap_s *bm,
                      nxgl_mxpixel_t color);
int nxf_convert_24bpp( uint32_t *dest, uint16_t height,
                      uint16_t width, uint16_t stride,
                      const struct nx_fontbitmap_s *bm,
                      nxgl_mxpixel_t color);
int nxf_convert_32bpp( uint32_t *dest, uint16_t height,
                      uint16_t width, uint16_t stride,
                      const struct nx_fontbitmap_s *bm,
                      nxgl_mxpixel_t color);
FCACHE nxf_cache_connect(enum nx_fontid_e fontid,
                         nxgl_mxpixel_t fgcolor, nxgl_mxpixel_t bgcolor,
                         int bpp, int maxglyph);
void nxf_cache_disconnect(FCACHE fhandle);
NXHANDLE nxf_cache_getfonthandle(FCACHE fhandle);
 const struct nxfonts_glyph_s *nxf_cache_getglyph(FCACHE fhandle,
                                                     uint8_t ch);
extern struct nx_fontset_s g_7bitfonts;
extern struct nx_font_s g_fonts;
  static const uint8_t g_bitmap_33[] = {0x0, 0x0, 0x0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0, 0x20, 0x0, 0x0};
  static const uint8_t g_bitmap_34[] = {0x0, 0x0, 0x50, 0x50, 0x50, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  static const uint8_t g_bitmap_35[] = {0x0, 0x0, 0x0, 0x0, 0x50, 0xf8, 0x50, 0x50, 0xf8, 0x50, 0x0, 0x0};
  static const uint8_t g_bitmap_36[] = {0x0, 0x0, 0x20, 0x70, 0xa8, 0xa0, 0x70, 0x28, 0xa8, 0x70, 0x20, 0x0};
  static const uint8_t g_bitmap_37[] = {0x0, 0x0, 0x0, 0xc8, 0xc8, 0x10, 0x20, 0x40, 0x98, 0x98, 0x0, 0x0};
  static const uint8_t g_bitmap_38[] = {0x0, 0x0, 0x0, 0x40, 0xa0, 0xa0, 0x40, 0xa8, 0x90, 0x68, 0x0, 0x0};
  static const uint8_t g_bitmap_39[] = {0x0, 0x0, 0x20, 0x20, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  static const uint8_t g_bitmap_40[] = {0x0, 0x0, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x20, 0x20, 0x10, 0x0};
  static const uint8_t g_bitmap_41[] = {0x0, 0x0, 0x40, 0x20, 0x20, 0x10, 0x10, 0x10, 0x20, 0x20, 0x40, 0x0};
  static const uint8_t g_bitmap_42[] = {0x0, 0x0, 0x0, 0x20, 0xa8, 0x70, 0x20, 0x70, 0xa8, 0x20, 0x0, 0x0};
  static const uint8_t g_bitmap_43[] = {0x0, 0x0, 0x0, 0x0, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x0, 0x0, 0x0};
  static const uint8_t g_bitmap_44[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x60, 0xc0, 0x0};
  static const uint8_t g_bitmap_45[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0};
  static const uint8_t g_bitmap_46[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x60, 0x0, 0x0};
  static const uint8_t g_bitmap_47[] = {0x0, 0x0, 0x0, 0x8, 0x10, 0x10, 0x20, 0x40, 0x40, 0x80, 0x0, 0x0};
  static const uint8_t g_bitmap_48[] = {0x0, 0x0, 0x0, 0x30, 0x48, 0x48, 0x48, 0x48, 0x48, 0x30, 0x0, 0x0};
  static const uint8_t g_bitmap_49[] = {0x0, 0x0, 0x0, 0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_50[] = {0x0, 0x0, 0x0, 0x70, 0x88, 0x8, 0x10, 0x20, 0x40, 0xf8, 0x0, 0x0};
  static const uint8_t g_bitmap_51[] = {0x0, 0x0, 0x0, 0xf8, 0x8, 0x10, 0x30, 0x8, 0x88, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_52[] = {0x0, 0x0, 0x0, 0x10, 0x30, 0x50, 0x90, 0xf8, 0x10, 0x10, 0x0, 0x0};
  static const uint8_t g_bitmap_53[] = {0x0, 0x0, 0x0, 0xf8, 0x80, 0xf0, 0x8, 0x8, 0x88, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_54[] = {0x0, 0x0, 0x0, 0x30, 0x40, 0x80, 0xf0, 0x88, 0x88, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_55[] = {0x0, 0x0, 0x0, 0xf8, 0x8, 0x10, 0x10, 0x20, 0x20, 0x20, 0x0, 0x0};
  static const uint8_t g_bitmap_56[] = {0x0, 0x0, 0x0, 0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_57[] = {0x0, 0x0, 0x0, 0x70, 0x88, 0x88, 0x78, 0x8, 0x10, 0x60, 0x0, 0x0};
  static const uint8_t g_bitmap_58[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x60, 0x0, 0x60, 0x60, 0x0, 0x0};
  static const uint8_t g_bitmap_59[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x60, 0x0, 0x60, 0x60, 0xc0, 0x0};
  static const uint8_t g_bitmap_60[] = {0x0, 0x0, 0x0, 0x0, 0x10, 0x20, 0x40, 0x20, 0x10, 0x0, 0x0, 0x0};
  static const uint8_t g_bitmap_61[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x0};
  static const uint8_t g_bitmap_62[] = {0x0, 0x0, 0x0, 0x0, 0x40, 0x20, 0x10, 0x20, 0x40, 0x0, 0x0, 0x0};
  static const uint8_t g_bitmap_63[] = {0x0, 0x0, 0x0, 0x70, 0x88, 0x10, 0x20, 0x20, 0x0, 0x20, 0x0, 0x0};
  static const uint8_t g_bitmap_64[] = {0x0, 0x0, 0x0, 0x70, 0x88, 0xb8, 0xa8, 0xb8, 0x80, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_65[] = {0x0, 0x0, 0x0, 0x70, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0x0, 0x0};
  static const uint8_t g_bitmap_66[] = {0x0, 0x0, 0x0, 0xf0, 0x48, 0x48, 0x70, 0x48, 0x48, 0xf0, 0x0, 0x0};
  static const uint8_t g_bitmap_67[] = {0x0, 0x0, 0x0, 0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_68[] = {0x0, 0x0, 0x0, 0xf0, 0x48, 0x48, 0x48, 0x48, 0x48, 0xf0, 0x0, 0x0};
  static const uint8_t g_bitmap_69[] = {0x0, 0x0, 0x0, 0xf8, 0x80, 0x80, 0xf0, 0x80, 0x80, 0xf8, 0x0, 0x0};
  static const uint8_t g_bitmap_70[] = {0x0, 0x0, 0x0, 0xf8, 0x80, 0x80, 0xf0, 0x80, 0x80, 0x80, 0x0, 0x0};
  static const uint8_t g_bitmap_71[] = {0x0, 0x0, 0x0, 0x70, 0x88, 0x80, 0x80, 0x98, 0x88, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_72[] = {0x0, 0x0, 0x0, 0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0x0, 0x0};
  static const uint8_t g_bitmap_73[] = {0x0, 0x0, 0x0, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_74[] = {0x0, 0x0, 0x0, 0x38, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60, 0x0, 0x0};
  static const uint8_t g_bitmap_75[] = {0x0, 0x0, 0x0, 0x88, 0x90, 0xa0, 0xc0, 0xa0, 0x90, 0x88, 0x0, 0x0};
  static const uint8_t g_bitmap_76[] = {0x0, 0x0, 0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xf8, 0x0, 0x0};
  static const uint8_t g_bitmap_77[] = {0x0, 0x0, 0x0, 0x88, 0xd8, 0xa8, 0x88, 0x88, 0x88, 0x88, 0x0, 0x0};
  static const uint8_t g_bitmap_78[] = {0x0, 0x0, 0x0, 0x88, 0x88, 0xc8, 0xa8, 0x98, 0x88, 0x88, 0x0, 0x0};
  static const uint8_t g_bitmap_79[] = {0x0, 0x0, 0x0, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_80[] = {0x0, 0x0, 0x0, 0xf0, 0x88, 0x88, 0xf0, 0x80, 0x80, 0x80, 0x0, 0x0};
  static const uint8_t g_bitmap_81[] = {0x0, 0x0, 0x0, 0x70, 0x88, 0x88, 0x88, 0xa8, 0x90, 0x68, 0x0, 0x0};
  static const uint8_t g_bitmap_82[] = {0x0, 0x0, 0x0, 0xf0, 0x88, 0x88, 0xf0, 0xa0, 0x90, 0x88, 0x0, 0x0};
  static const uint8_t g_bitmap_83[] = {0x0, 0x0, 0x0, 0x70, 0x88, 0x80, 0x70, 0x8, 0x88, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_84[] = {0x0, 0x0, 0x0, 0xf8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0, 0x0};
  static const uint8_t g_bitmap_85[] = {0x0, 0x0, 0x0, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_86[] = {0x0, 0x0, 0x0, 0x88, 0x88, 0x88, 0x88, 0x50, 0x50, 0x20, 0x0, 0x0};
  static const uint8_t g_bitmap_87[] = {0x0, 0x0, 0x0, 0x88, 0x88, 0x88, 0x88, 0xa8, 0xa8, 0x50, 0x0, 0x0};
  static const uint8_t g_bitmap_88[] = {0x0, 0x0, 0x0, 0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x0, 0x0};
  static const uint8_t g_bitmap_89[] = {0x0, 0x0, 0x0, 0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20, 0x0, 0x0};
  static const uint8_t g_bitmap_90[] = {0x0, 0x0, 0x0, 0xf8, 0x8, 0x10, 0x20, 0x40, 0x80, 0xf8, 0x0, 0x0};
  static const uint8_t g_bitmap_91[] = {0x0, 0x0, 0x70, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x70, 0x0};
  static const uint8_t g_bitmap_92[] = {0x0, 0x0, 0x0, 0x80, 0x40, 0x40, 0x20, 0x10, 0x10, 0x8, 0x0, 0x0};
  static const uint8_t g_bitmap_93[] = {0x0, 0x0, 0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x0};
  static const uint8_t g_bitmap_94[] = {0x0, 0x0, 0x20, 0x50, 0x88, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  static const uint8_t g_bitmap_95[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf8};
  static const uint8_t g_bitmap_96[] = {0x0, 0x0, 0x40, 0x20, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  static const uint8_t g_bitmap_97[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x8, 0x78, 0x88, 0x78, 0x0, 0x0};
  static const uint8_t g_bitmap_98[] = {0x0, 0x0, 0x0, 0x80, 0x80, 0xf0, 0x88, 0x88, 0x88, 0xf0, 0x0, 0x0};
  static const uint8_t g_bitmap_99[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x88, 0x80, 0x88, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_100[] = {0x0, 0x0, 0x0, 0x8, 0x8, 0x78, 0x88, 0x88, 0x88, 0x78, 0x0, 0x0};
  static const uint8_t g_bitmap_101[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x88, 0xf0, 0x80, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_102[] = {0x0, 0x0, 0x0, 0x30, 0x48, 0x40, 0xe0, 0x40, 0x40, 0x40, 0x0, 0x0};
  static const uint8_t g_bitmap_103[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x88, 0x88, 0x88, 0x78, 0x8, 0x70};
  static const uint8_t g_bitmap_104[] = {0x0, 0x0, 0x0, 0x80, 0x80, 0xf0, 0x88, 0x88, 0x88, 0x88, 0x0, 0x0};
  static const uint8_t g_bitmap_105[] = {0x0, 0x0, 0x0, 0x20, 0x0, 0x60, 0x20, 0x20, 0x20, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_106[] = {0x0, 0x0, 0x0, 0x8, 0x0, 0x18, 0x8, 0x8, 0x8, 0x8, 0x48, 0x30};
  static const uint8_t g_bitmap_107[] = {0x0, 0x0, 0x0, 0x80, 0x80, 0x88, 0x90, 0xe0, 0x90, 0x88, 0x0, 0x0};
  static const uint8_t g_bitmap_108[] = {0x0, 0x0, 0x0, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_109[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0xd0, 0xa8, 0xa8, 0xa8, 0xa8, 0x0, 0x0};
  static const uint8_t g_bitmap_110[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0xb0, 0xc8, 0x88, 0x88, 0x88, 0x0, 0x0};
  static const uint8_t g_bitmap_111[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x88, 0x88, 0x88, 0x70, 0x0, 0x0};
  static const uint8_t g_bitmap_112[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x88, 0x88, 0x88, 0xf0, 0x80, 0x80};
  static const uint8_t g_bitmap_113[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x78, 0x88, 0x88, 0x88, 0x78, 0x8, 0x8};
  static const uint8_t g_bitmap_114[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0xb0, 0xc8, 0x80, 0x80, 0x80, 0x0, 0x0};
  static const uint8_t g_bitmap_115[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x78, 0x80, 0x70, 0x8, 0xf0, 0x0, 0x0};
  static const uint8_t g_bitmap_116[] = {0x0, 0x0, 0x0, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x20, 0x18, 0x0, 0x0};
  static const uint8_t g_bitmap_117[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x88, 0x88, 0x88, 0x98, 0x68, 0x0, 0x0};
  static const uint8_t g_bitmap_118[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x88, 0x88, 0x88, 0x50, 0x20, 0x0, 0x0};
  static const uint8_t g_bitmap_119[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x88, 0x88, 0xa8, 0xa8, 0x50, 0x0, 0x0};
  static const uint8_t g_bitmap_120[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x88, 0x50, 0x20, 0x50, 0x88, 0x0, 0x0};
  static const uint8_t g_bitmap_121[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x88, 0x88, 0x88, 0x50, 0x20, 0x40, 0x80};
  static const uint8_t g_bitmap_122[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0x10, 0x20, 0x40, 0xf8, 0x0, 0x0};
  static const uint8_t g_bitmap_123[] = {0x0, 0x0, 0x10, 0x20, 0x20, 0x20, 0x40, 0x20, 0x20, 0x20, 0x10, 0x0};
  static const uint8_t g_bitmap_124[] = {0x0, 0x0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0};
  static const uint8_t g_bitmap_125[] = {0x0, 0x0, 0x40, 0x20, 0x20, 0x20, 0x10, 0x20, 0x20, 0x20, 0x40, 0x0};
  static const uint8_t g_bitmap_126[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x48, 0xa8, 0x90, 0x0, 0x0, 0x0, 0x0};
static const struct
nx_fontbitmap_s g_x11_misc_fixed_6x12_7bitmaps[(126 - 33 + 1)] =
{
  { {1, 6, 12, 0, 0, 0}, g_bitmap_33 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_34 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_35 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_36 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_37 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_38 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_39 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_40 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_41 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_42 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_43 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_44 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_45 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_46 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_47 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_48 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_49 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_50 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_51 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_52 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_53 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_54 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_55 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_56 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_57 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_58 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_59 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_60 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_61 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_62 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_63 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_64 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_65 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_66 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_67 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_68 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_69 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_70 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_71 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_72 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_73 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_74 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_75 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_76 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_77 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_78 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_79 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_80 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_81 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_82 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_83 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_84 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_85 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_86 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_87 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_88 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_89 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_90 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_91 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_92 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_93 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_94 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_95 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_96 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_97 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_98 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_99 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_100 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_101 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_102 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_103 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_104 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_105 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_106 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_107 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_108 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_109 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_110 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_111 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_112 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_113 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_114 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_115 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_116 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_117 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_118 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_119 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_120 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_121 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_122 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_123 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_124 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_125 },
  { {1, 6, 12, 0, 0, 0}, g_bitmap_126 },
};
const struct nx_fontpackage_s g_x11_misc_fixed_6x12_package =
{
  FONTID_X11_MISC_FIXED_6X12,
  {
    12,
    6,
    7,
    6,
  },
  {
    33,
    (126 - 33 + 1),
    g_x11_misc_fixed_6x12_7bitmaps
  },
};
