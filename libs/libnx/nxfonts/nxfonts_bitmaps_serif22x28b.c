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
struct lcd_dev_s;
struct lcd_planeinfo_s
{
  int (*putrun)( struct lcd_dev_s *dev, fb_coord_t row, fb_coord_t col,
                const uint8_t *buffer, size_t npixels);
  int (*putarea)( struct lcd_dev_s *dev, fb_coord_t row_start,
                 fb_coord_t row_end, fb_coord_t col_start,
                 fb_coord_t col_end, const uint8_t *buffer,
                 fb_coord_t stride);
  int (*getrun)( struct lcd_dev_s *dev, fb_coord_t row,
                fb_coord_t col, uint8_t *buffer, size_t npixels);
  int (*getarea)( struct lcd_dev_s *dev, fb_coord_t row_start,
                 fb_coord_t row_end, fb_coord_t col_start,
                 fb_coord_t col_end, uint8_t *buffer,
                 fb_coord_t stride);
  int (*redraw)( struct lcd_dev_s *dev);
  uint8_t *buffer;
  uint8_t bpp;
  struct lcd_dev_s *dev;
};
struct lcd_dev_s
{
  int (*getvideoinfo)( struct lcd_dev_s *dev,
         struct fb_videoinfo_s *vinfo);
  int (*getplaneinfo)( struct lcd_dev_s *dev, unsigned int planeno,
         struct lcd_planeinfo_s *pinfo);
  int (*getpower)(struct lcd_dev_s *dev);
  int (*setpower)(struct lcd_dev_s *dev, int power);
  int (*getcontrast)(struct lcd_dev_s *dev);
  int (*setcontrast)(struct lcd_dev_s *dev, unsigned int contrast);
  int (*setframerate)(struct lcd_dev_s *dev, int rate);
  int (*getframerate)(struct lcd_dev_s *dev);
};
typedef uint8_t nxgl_mxpixel_t;
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
int nx_runinstance( const char *mqname, struct lcd_dev_s *dev);
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
  , FONTID_SERIF22X28B = 11
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
  static const uint8_t g_bitmap_33[] = {0x40, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x40, 0x40, 0x0, 0xe0, 0xe0, 0xe0};
  static const uint8_t g_bitmap_34[] = {0xcc, 0xcc, 0xcc, 0xcc, 0x88, 0x88};
  static const uint8_t g_bitmap_35[] = {0x19, 0x80, 0x19, 0x80, 0x19, 0x80, 0x7f, 0xc0, 0x7f, 0xc0, 0x33, 0x0, 0x33, 0x0, 0xff, 0x80, 0xff, 0x80, 0x66, 0x0, 0x66, 0x0, 0x66, 0x0};
  static const uint8_t g_bitmap_36[] = {0x18, 0x7e, 0xdb, 0xdb, 0xd8, 0xf8, 0x7c, 0x3e, 0x1f, 0x1f, 0x1b, 0xdb, 0xdb, 0x7e, 0x18, 0x18};
  static const uint8_t g_bitmap_37[] = {0x3c, 0x18, 0x77, 0xf0, 0xe2, 0x60, 0xe2, 0x40, 0xe4, 0xc0, 0xfd, 0x80, 0x73, 0x78, 0x6, 0xec, 0x6, 0xc4, 0xd, 0xc4, 0x19, 0xc8, 0x31, 0xf8, 0x30, 0xe0};
  static const uint8_t g_bitmap_38[] = {0x1e, 0x0, 0x33, 0x0, 0x33, 0x0, 0x33, 0x0, 0x3a, 0x0, 0x1c, 0xf0, 0x3c, 0x60, 0x5e, 0x40, 0xcf, 0x80, 0xc7, 0x80, 0xe3, 0xc0, 0xff, 0xf8, 0x78, 0xf0};
  static const uint8_t g_bitmap_39[] = {0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80};
  static const uint8_t g_bitmap_40[] = {0x8, 0x10, 0x30, 0x60, 0x60, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0x60, 0x60, 0x30, 0x10, 0x8};
  static const uint8_t g_bitmap_41[] = {0x80, 0x40, 0x60, 0x30, 0x30, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x38, 0x30, 0x20, 0x60, 0x40, 0x80};
  static const uint8_t g_bitmap_42[] = {0x18, 0x18, 0xdb, 0xff, 0x3c, 0xff, 0xdb, 0x18, 0x18};
  static const uint8_t g_bitmap_43[] = {0xc, 0x0, 0xc, 0x0, 0xc, 0x0, 0xc, 0x0, 0xff, 0xc0, 0xff, 0xc0, 0xc, 0x0, 0xc, 0x0, 0xc, 0x0, 0xc, 0x0};
  static const uint8_t g_bitmap_44[] = {0x70, 0x70, 0x70, 0x30, 0x60, 0xc0};
  static const uint8_t g_bitmap_45[] = {0xf8, 0xf8, 0xf8};
  static const uint8_t g_bitmap_46[] = {0xe0, 0xe0, 0xe0};
  static const uint8_t g_bitmap_47[] = {0x18, 0x18, 0x18, 0x30, 0x30, 0x30, 0x20, 0x60, 0x60, 0x60, 0xc0, 0xc0, 0xc0};
  static const uint8_t g_bitmap_48[] = {0x3c, 0x66, 0x67, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0x66, 0x66, 0x3c};
  static const uint8_t g_bitmap_49[] = {0x1c, 0x3c, 0xfc, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x7f};
  static const uint8_t g_bitmap_50[] = {0x3c, 0x7e, 0xcf, 0x87, 0x7, 0x7, 0x6, 0xc, 0x18, 0x31, 0x63, 0xff, 0xff};
  static const uint8_t g_bitmap_51[] = {0x3c, 0x0, 0x7e, 0x0, 0x8f, 0x0, 0x7, 0x0, 0xe, 0x0, 0x1c, 0x0, 0x3e, 0x0, 0xf, 0x0, 0x7, 0x80, 0x3, 0x80, 0xc3, 0x0, 0xe6, 0x0, 0x7c, 0x0};
  static const uint8_t g_bitmap_52[] = {0xe, 0x1e, 0x1e, 0x2e, 0x2e, 0x4e, 0xce, 0x8e, 0xff, 0xff, 0xe, 0xe, 0xe};
  static const uint8_t g_bitmap_53[] = {0x3f, 0x0, 0x3f, 0x0, 0x3e, 0x0, 0x40, 0x0, 0x78, 0x0, 0x7e, 0x0, 0x3f, 0x0, 0x7, 0x80, 0x3, 0x80, 0x3, 0x80, 0xc3, 0x0, 0xe6, 0x0, 0xfc, 0x0};
  static const uint8_t g_bitmap_54[] = {0x7, 0x1c, 0x38, 0x70, 0x60, 0xfc, 0xe6, 0xe7, 0xe7, 0xe7, 0xe7, 0x66, 0x3c};
  static const uint8_t g_bitmap_55[] = {0xff, 0xff, 0xfe, 0x86, 0xc, 0xc, 0xc, 0x18, 0x18, 0x38, 0x30, 0x30, 0x70};
  static const uint8_t g_bitmap_56[] = {0x3c, 0x66, 0xe3, 0xe3, 0xf6, 0x7c, 0x3c, 0x7e, 0xcf, 0xc7, 0xc3, 0xe7, 0x7e};
  static const uint8_t g_bitmap_57[] = {0x3c, 0x66, 0xe7, 0xe7, 0xe7, 0xe7, 0x67, 0x3f, 0x7, 0x6, 0xe, 0x3c, 0xf0};
  static const uint8_t g_bitmap_58[] = {0xe0, 0xe0, 0xe0, 0x0, 0x0, 0x0, 0xe0, 0xe0, 0xe0};
  static const uint8_t g_bitmap_59[] = {0x70, 0x70, 0x70, 0x0, 0x0, 0x0, 0x70, 0x70, 0x70, 0x30, 0x60, 0xc0};
  static const uint8_t g_bitmap_60[] = {0x3, 0x80, 0xf, 0x0, 0x3c, 0x0, 0xf0, 0x0, 0xc0, 0x0, 0xf0, 0x0, 0x3c, 0x0, 0xf, 0x0, 0x3, 0x80};
  static const uint8_t g_bitmap_61[] = {0xff, 0x80, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0, 0xff, 0x80, 0xff, 0x80};
  static const uint8_t g_bitmap_62[] = {0xe0, 0x0, 0x78, 0x0, 0x1e, 0x0, 0x7, 0x80, 0x1, 0x80, 0x7, 0x80, 0x1e, 0x0, 0x78, 0x0, 0xe0, 0x0};
  static const uint8_t g_bitmap_63[] = {0x7c, 0xce, 0xee, 0xee, 0x4e, 0xc, 0x18, 0x10, 0x10, 0x0, 0x38, 0x38, 0x38};
  static const uint8_t g_bitmap_64[] = {0x3, 0xe0, 0xf, 0x38, 0x38, 0xc, 0x30, 0x4, 0x73, 0xb6, 0x67, 0x76, 0xe7, 0x76, 0xee, 0x66, 0xee, 0x66, 0xee, 0xec, 0xef, 0xfc, 0x67, 0xb8, 0x70, 0x0, 0x38, 0x0, 0x1e, 0x0, 0x7, 0xf0};
  static const uint8_t g_bitmap_65[] = {0x3, 0x0, 0x3, 0x80, 0x7, 0x80, 0x5, 0xc0, 0xd, 0xc0, 0x8, 0xc0, 0x18, 0xe0, 0x10, 0x60, 0x1f, 0xf0, 0x30, 0x70, 0x20, 0x38, 0x60, 0x38, 0xf8, 0xfc};
  static const uint8_t g_bitmap_66[] = {0xfe, 0x0, 0x73, 0x80, 0x71, 0xc0, 0x71, 0xc0, 0x71, 0xc0, 0x73, 0x80, 0x7e, 0x0, 0x73, 0x80, 0x71, 0xc0, 0x71, 0xc0, 0x71, 0xc0, 0x73, 0x80, 0xff, 0x0};
  static const uint8_t g_bitmap_67[] = {0xf, 0x90, 0x38, 0xf0, 0x70, 0x70, 0x70, 0x30, 0xe0, 0x0, 0xe0, 0x0, 0xe0, 0x0, 0xe0, 0x0, 0xe0, 0x0, 0x70, 0x0, 0x70, 0x30, 0x3c, 0xe0, 0xf, 0x80};
  static const uint8_t g_bitmap_68[] = {0xff, 0x0, 0x71, 0xc0, 0x70, 0xe0, 0x70, 0x60, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x60, 0x70, 0xe0, 0x71, 0xc0, 0xff, 0x0};
  static const uint8_t g_bitmap_69[] = {0xff, 0xc0, 0x70, 0xc0, 0x70, 0x40, 0x70, 0x0, 0x70, 0x0, 0x71, 0x0, 0x7f, 0x0, 0x71, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x40, 0x70, 0xc0, 0xff, 0xc0};
  static const uint8_t g_bitmap_70[] = {0xff, 0xc0, 0x70, 0xc0, 0x70, 0x40, 0x70, 0x0, 0x70, 0x0, 0x71, 0x0, 0x7f, 0x0, 0x71, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0xf8, 0x0};
  static const uint8_t g_bitmap_71[] = {0xf, 0x90, 0x38, 0xf0, 0x70, 0x70, 0x70, 0x30, 0xe0, 0x0, 0xe0, 0x0, 0xe0, 0xf8, 0xe0, 0x70, 0xe0, 0x70, 0x70, 0x70, 0x70, 0x70, 0x38, 0xf0, 0xf, 0xc0};
  static const uint8_t g_bitmap_72[] = {0xf8, 0xf8, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x7f, 0xf0, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0xf9, 0xf8};
  static const uint8_t g_bitmap_73[] = {0xf8, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0xf8};
  static const uint8_t g_bitmap_74[] = {0x1f, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xee, 0xec, 0x78};
  static const uint8_t g_bitmap_75[] = {0xf9, 0xf0, 0x70, 0xc0, 0x71, 0x80, 0x73, 0x0, 0x76, 0x0, 0x7c, 0x0, 0x7c, 0x0, 0x7e, 0x0, 0x77, 0x0, 0x77, 0x80, 0x73, 0xc0, 0x71, 0xe0, 0xf8, 0xf0};
  static const uint8_t g_bitmap_76[] = {0xf8, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x40, 0x70, 0xc0, 0xff, 0xc0};
  static const uint8_t g_bitmap_77[] = {0xf0, 0x1e, 0x70, 0x1c, 0x78, 0x3c, 0x78, 0x3c, 0x7c, 0x5c, 0x5c, 0x5c, 0x5e, 0xdc, 0x4e, 0x9c, 0x4f, 0x9c, 0x47, 0x1c, 0x47, 0x1c, 0x43, 0x1c, 0xe2, 0x3e};
  static const uint8_t g_bitmap_78[] = {0xf0, 0x70, 0x78, 0x20, 0x78, 0x20, 0x7c, 0x20, 0x5e, 0x20, 0x4e, 0x20, 0x4f, 0x20, 0x47, 0xa0, 0x43, 0xa0, 0x43, 0xe0, 0x41, 0xe0, 0x40, 0xe0, 0xe0, 0xe0};
  static const uint8_t g_bitmap_79[] = {0xf, 0x80, 0x38, 0xe0, 0x70, 0x70, 0x70, 0x70, 0xe0, 0x38, 0xe0, 0x38, 0xe0, 0x38, 0xe0, 0x38, 0xe0, 0x38, 0x70, 0x70, 0x70, 0x70, 0x38, 0xe0, 0xf, 0x80};
  static const uint8_t g_bitmap_80[] = {0xff, 0x0, 0x73, 0x80, 0x71, 0xc0, 0x71, 0xc0, 0x71, 0xc0, 0x73, 0x80, 0x7f, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0xf8, 0x0};
  static const uint8_t g_bitmap_81[] = {0xf, 0x80, 0x38, 0xe0, 0x70, 0x70, 0x70, 0x70, 0xe0, 0x38, 0xe0, 0x38, 0xe0, 0x38, 0xe0, 0x38, 0xe0, 0x38, 0x70, 0x70, 0x70, 0x70, 0x38, 0xe0, 0xf, 0x80, 0xf, 0x0, 0x7, 0x80, 0x3, 0xe0, 0x0, 0xf8};
  static const uint8_t g_bitmap_82[] = {0xff, 0x0, 0x73, 0x80, 0x71, 0xc0, 0x71, 0xc0, 0x71, 0xc0, 0x73, 0x80, 0x7f, 0x0, 0x77, 0x0, 0x73, 0x80, 0x71, 0xc0, 0x71, 0xc0, 0x70, 0xe0, 0xf8, 0xf0};
  static const uint8_t g_bitmap_83[] = {0x1e, 0x80, 0x63, 0x80, 0xe1, 0x80, 0xe0, 0x0, 0xf8, 0x0, 0x7c, 0x0, 0x3f, 0x0, 0xf, 0x80, 0x7, 0x80, 0x3, 0x80, 0xc3, 0x80, 0xe7, 0x0, 0xbc, 0x0};
  static const uint8_t g_bitmap_84[] = {0xff, 0xe0, 0xce, 0x60, 0x8e, 0x20, 0xe, 0x0, 0xe, 0x0, 0xe, 0x0, 0xe, 0x0, 0xe, 0x0, 0xe, 0x0, 0xe, 0x0, 0xe, 0x0, 0xe, 0x0, 0x1f, 0x0};
  static const uint8_t g_bitmap_85[] = {0xf8, 0xf0, 0x70, 0x20, 0x70, 0x20, 0x70, 0x20, 0x70, 0x20, 0x70, 0x20, 0x70, 0x20, 0x70, 0x20, 0x70, 0x20, 0x70, 0x20, 0x70, 0x60, 0x38, 0xc0, 0x1f, 0x80};
  static const uint8_t g_bitmap_86[] = {0xfc, 0x7c, 0x78, 0x18, 0x38, 0x10, 0x3c, 0x30, 0x1c, 0x20, 0x1e, 0x60, 0x1e, 0x40, 0xe, 0xc0, 0xf, 0x80, 0x7, 0x80, 0x7, 0x0, 0x3, 0x0, 0x2, 0x0};
  static const uint8_t g_bitmap_87[] = {0xfd, 0xf7, 0xc0, 0x79, 0xe1, 0x80, 0x38, 0xe1, 0x0, 0x3c, 0xe3, 0x0, 0x3c, 0xe2, 0x0, 0x1c, 0x72, 0x0, 0x1e, 0x76, 0x0, 0xe, 0x74, 0x0, 0xe, 0xbc, 0x0, 0xf, 0x3c, 0x0, 0x7, 0x3c, 0x0, 0x6, 0x18, 0x0, 0x6, 0x18, 0x0};
  static const uint8_t g_bitmap_88[] = {0xf8, 0x78, 0x78, 0x30, 0x3c, 0x60, 0x1c, 0xc0, 0xf, 0x80, 0x7, 0x0, 0x7, 0x80, 0x7, 0xc0, 0xd, 0xc0, 0x18, 0xe0, 0x30, 0x70, 0x60, 0x78, 0xf0, 0xfc};
  static const uint8_t g_bitmap_89[] = {0xfc, 0x78, 0x78, 0x30, 0x38, 0x60, 0x3c, 0x40, 0x1e, 0xc0, 0xe, 0x80, 0xf, 0x80, 0x7, 0x0, 0x7, 0x0, 0x7, 0x0, 0x7, 0x0, 0x7, 0x0, 0x1f, 0xc0};
  static const uint8_t g_bitmap_90[] = {0xff, 0xc0, 0xc3, 0xc0, 0x83, 0x80, 0x7, 0x80, 0xf, 0x0, 0xe, 0x0, 0x1e, 0x0, 0x3c, 0x0, 0x38, 0x0, 0x78, 0x0, 0xf0, 0x40, 0xe0, 0xc0, 0xff, 0xc0};
  static const uint8_t g_bitmap_91[] = {0xf0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf0};
  static const uint8_t g_bitmap_92[] = {0xc0, 0xc0, 0xc0, 0x60, 0x60, 0x60, 0x20, 0x30, 0x30, 0x30, 0x18, 0x18, 0x18};
  static const uint8_t g_bitmap_93[] = {0xf0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xf0};
  static const uint8_t g_bitmap_94[] = {0x18, 0x18, 0x3c, 0x24, 0x66, 0xc3, 0xc3};
  static const uint8_t g_bitmap_95[] = {0xff, 0x80, 0xff, 0x80};
  static const uint8_t g_bitmap_96[] = {0xe0, 0x70, 0x18};
  static const uint8_t g_bitmap_97[] = {0x7c, 0xce, 0xce, 0x1e, 0x6e, 0xce, 0xce, 0xfe, 0x77};
  static const uint8_t g_bitmap_98[] = {0xf0, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x76, 0x0, 0x7f, 0x0, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x0, 0x6e, 0x0};
  static const uint8_t g_bitmap_99[] = {0x3e, 0x76, 0xe6, 0xe0, 0xe0, 0xe0, 0xe0, 0x76, 0x3c};
  static const uint8_t g_bitmap_100[] = {0xf, 0x0, 0x7, 0x0, 0x7, 0x0, 0x7, 0x0, 0x37, 0x0, 0x7f, 0x0, 0xe7, 0x0, 0xe7, 0x0, 0xe7, 0x0, 0xe7, 0x0, 0xe7, 0x0, 0x77, 0x0, 0x3b, 0x80};
  static const uint8_t g_bitmap_101[] = {0x3c, 0x76, 0xe6, 0xfe, 0xe0, 0xe0, 0xe0, 0x76, 0x3c};
  static const uint8_t g_bitmap_102[] = {0x3e, 0x76, 0x76, 0x70, 0xfc, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0xf8};
  static const uint8_t g_bitmap_103[] = {0x3f, 0x80, 0xe7, 0x0, 0xe7, 0x0, 0xe7, 0x0, 0xe6, 0x0, 0x78, 0x0, 0x60, 0x0, 0xfe, 0x0, 0xff, 0x80, 0xe3, 0x80, 0xc1, 0x80, 0xe3, 0x0, 0x7e, 0x0};
  static const uint8_t g_bitmap_104[] = {0xf0, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x77, 0x0, 0x7f, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0xfb, 0xc0};
  static const uint8_t g_bitmap_105[] = {0x60, 0x60, 0x60, 0x0, 0xf0, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0xf8};
  static const uint8_t g_bitmap_106[] = {0x18, 0x18, 0x18, 0x0, 0x3c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xdc, 0xd8, 0x70};
  static const uint8_t g_bitmap_107[] = {0xf0, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x73, 0x80, 0x73, 0x0, 0x76, 0x0, 0x7c, 0x0, 0x7c, 0x0, 0x7e, 0x0, 0x77, 0x0, 0x73, 0x80, 0xf7, 0xc0};
  static const uint8_t g_bitmap_108[] = {0xf0, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0xf8};
  static const uint8_t g_bitmap_109[] = {0xf7, 0x38, 0x7b, 0xdc, 0x73, 0x9c, 0x73, 0x9c, 0x73, 0x9c, 0x73, 0x9c, 0x73, 0x9c, 0x73, 0x9c, 0xfb, 0xde};
  static const uint8_t g_bitmap_110[] = {0xe7, 0x0, 0x7f, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0xfb, 0xc0};
  static const uint8_t g_bitmap_111[] = {0x3c, 0x66, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0x66, 0x3c};
  static const uint8_t g_bitmap_112[] = {0xe6, 0x0, 0x7f, 0x0, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x7b, 0x0, 0x76, 0x0, 0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0xf8, 0x0};
  static const uint8_t g_bitmap_113[] = {0x39, 0x0, 0x77, 0x0, 0xe7, 0x0, 0xe7, 0x0, 0xe7, 0x0, 0xe7, 0x0, 0xe7, 0x0, 0x7f, 0x0, 0x37, 0x0, 0x7, 0x0, 0x7, 0x0, 0x7, 0x0, 0xf, 0x80};
  static const uint8_t g_bitmap_114[] = {0xee, 0x76, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0xf8};
  static const uint8_t g_bitmap_115[] = {0x7c, 0xcc, 0xe4, 0xf0, 0x78, 0x3c, 0x9c, 0xcc, 0xf8};
  static const uint8_t g_bitmap_116[] = {0x10, 0x30, 0xfc, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x74, 0x38};
  static const uint8_t g_bitmap_117[] = {0xf7, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x73, 0x80, 0x7f, 0x80, 0x3d, 0xc0};
  static const uint8_t g_bitmap_118[] = {0xfb, 0xc0, 0x71, 0x80, 0x79, 0x0, 0x3b, 0x0, 0x3b, 0x0, 0x1e, 0x0, 0x1e, 0x0, 0xc, 0x0, 0xc, 0x0};
  static const uint8_t g_bitmap_119[] = {0xf7, 0x9c, 0x77, 0x18, 0x73, 0x90, 0x3b, 0xb0, 0x39, 0xa0, 0x1d, 0xe0, 0x1f, 0xe0, 0xc, 0xc0, 0xc, 0xc0};
  static const uint8_t g_bitmap_120[] = {0xf3, 0x80, 0x73, 0x0, 0x7a, 0x0, 0x3c, 0x0, 0x1c, 0x0, 0x1e, 0x0, 0x37, 0x0, 0x67, 0x80, 0xe3, 0x80};
  static const uint8_t g_bitmap_121[] = {0xfb, 0xc0, 0x71, 0x80, 0x79, 0x0, 0x3b, 0x0, 0x3a, 0x0, 0x1e, 0x0, 0x1e, 0x0, 0xc, 0x0, 0xc, 0x0, 0xc, 0x0, 0xc8, 0x0, 0xd8, 0x0, 0xf0, 0x0};
  static const uint8_t g_bitmap_122[] = {0xfe, 0xce, 0x8e, 0x1c, 0x38, 0x70, 0x72, 0xe6, 0xfe};
  static const uint8_t g_bitmap_123[] = {0x1e, 0x38, 0x30, 0x30, 0x30, 0x30, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x30, 0x30, 0x30, 0x30, 0x38, 0x1e};
  static const uint8_t g_bitmap_124[] = {0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0};
  static const uint8_t g_bitmap_125[] = {0xf0, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0xc, 0x6, 0xc, 0x18, 0x18, 0x18, 0x18, 0x18, 0x38, 0xf0};
  static const uint8_t g_bitmap_126[] = {0x70, 0xf9, 0x9f, 0xe};
static const struct
nx_fontbitmap_s g_serif22x28b_7bitmaps[(126 - 33 + 1)] =
{
  { {1, 3, 13, 1, 8, 0}, g_bitmap_33 },
  { {1, 6, 6, 2, 8, 0}, g_bitmap_34 },
  { {2, 10, 12, 0, 9, 0}, g_bitmap_35 },
  { {1, 8, 16, 0, 7, 0}, g_bitmap_36 },
  { {2, 14, 13, 1, 8, 0}, g_bitmap_37 },
  { {2, 13, 13, 2, 8, 0}, g_bitmap_38 },
  { {1, 2, 6, 1, 8, 0}, g_bitmap_39 },
  { {1, 5, 17, 1, 8, 0}, g_bitmap_40 },
  { {1, 5, 17, 0, 8, 0}, g_bitmap_41 },
  { {1, 8, 9, 0, 8, 0}, g_bitmap_42 },
  { {2, 10, 10, 0, 11, 0}, g_bitmap_43 },
  { {1, 4, 6, 0, 18, 0}, g_bitmap_44 },
  { {1, 5, 3, 0, 14, 0}, g_bitmap_45 },
  { {1, 3, 3, 1, 18, 0}, g_bitmap_46 },
  { {1, 5, 13, 0, 8, 0}, g_bitmap_47 },
  { {1, 8, 13, 0, 8, 0}, g_bitmap_48 },
  { {1, 8, 13, 0, 8, 0}, g_bitmap_49 },
  { {1, 8, 13, 0, 8, 0}, g_bitmap_50 },
  { {2, 9, 13, 0, 8, 0}, g_bitmap_51 },
  { {1, 8, 13, 0, 8, 0}, g_bitmap_52 },
  { {2, 9, 13, 0, 8, 0}, g_bitmap_53 },
  { {1, 8, 13, 0, 8, 0}, g_bitmap_54 },
  { {1, 8, 13, 0, 8, 0}, g_bitmap_55 },
  { {1, 8, 13, 0, 8, 0}, g_bitmap_56 },
  { {1, 8, 13, 0, 8, 0}, g_bitmap_57 },
  { {1, 3, 9, 1, 12, 0}, g_bitmap_58 },
  { {1, 4, 12, 0, 12, 0}, g_bitmap_59 },
  { {2, 9, 9, 1, 12, 0}, g_bitmap_60 },
  { {2, 9, 6, 1, 13, 0}, g_bitmap_61 },
  { {2, 9, 9, 1, 12, 0}, g_bitmap_62 },
  { {1, 7, 13, 1, 8, 0}, g_bitmap_63 },
  { {2, 15, 16, 1, 8, 0}, g_bitmap_64 },
  { {2, 14, 13, 0, 8, 0}, g_bitmap_65 },
  { {2, 10, 13, 1, 8, 0}, g_bitmap_66 },
  { {2, 12, 13, 1, 8, 0}, g_bitmap_67 },
  { {2, 12, 13, 1, 8, 0}, g_bitmap_68 },
  { {2, 10, 13, 2, 8, 0}, g_bitmap_69 },
  { {2, 10, 13, 2, 8, 0}, g_bitmap_70 },
  { {2, 13, 13, 1, 8, 0}, g_bitmap_71 },
  { {2, 13, 13, 1, 8, 0}, g_bitmap_72 },
  { {1, 5, 13, 1, 8, 0}, g_bitmap_73 },
  { {1, 8, 15, 0, 8, 0}, g_bitmap_74 },
  { {2, 12, 13, 2, 8, 0}, g_bitmap_75 },
  { {2, 10, 13, 2, 8, 0}, g_bitmap_76 },
  { {2, 15, 13, 2, 8, 0}, g_bitmap_77 },
  { {2, 12, 13, 1, 8, 0}, g_bitmap_78 },
  { {2, 13, 13, 1, 8, 0}, g_bitmap_79 },
  { {2, 10, 13, 1, 8, 0}, g_bitmap_80 },
  { {2, 13, 17, 1, 8, 0}, g_bitmap_81 },
  { {2, 12, 13, 1, 8, 0}, g_bitmap_82 },
  { {2, 9, 13, 1, 8, 0}, g_bitmap_83 },
  { {2, 11, 13, 1, 8, 0}, g_bitmap_84 },
  { {2, 12, 13, 1, 8, 0}, g_bitmap_85 },
  { {2, 14, 13, 0, 8, 0}, g_bitmap_86 },
  { {3, 18, 13, 1, 8, 0}, g_bitmap_87 },
  { {2, 14, 13, 0, 8, 0}, g_bitmap_88 },
  { {2, 13, 13, 1, 8, 0}, g_bitmap_89 },
  { {2, 10, 13, 2, 8, 0}, g_bitmap_90 },
  { {1, 4, 16, 1, 8, 0}, g_bitmap_91 },
  { {1, 5, 13, 0, 8, 0}, g_bitmap_92 },
  { {1, 4, 16, 1, 8, 0}, g_bitmap_93 },
  { {1, 8, 7, 1, 8, 0}, g_bitmap_94 },
  { {2, 9, 2, 0, 23, 0}, g_bitmap_95 },
  { {1, 5, 3, 0, 8, 0}, g_bitmap_96 },
  { {1, 8, 9, 0, 12, 0}, g_bitmap_97 },
  { {2, 9, 13, 0, 8, 0}, g_bitmap_98 },
  { {1, 7, 9, 0, 12, 0}, g_bitmap_99 },
  { {2, 9, 13, 0, 8, 0}, g_bitmap_100 },
  { {1, 7, 9, 0, 12, 0}, g_bitmap_101 },
  { {1, 7, 13, 0, 8, 0}, g_bitmap_102 },
  { {2, 9, 13, 0, 12, 0}, g_bitmap_103 },
  { {2, 10, 13, 0, 8, 0}, g_bitmap_104 },
  { {1, 5, 13, 0, 8, 0}, g_bitmap_105 },
  { {1, 6, 17, 0, 8, 0}, g_bitmap_106 },
  { {2, 10, 13, 0, 8, 0}, g_bitmap_107 },
  { {1, 5, 13, 0, 8, 0}, g_bitmap_108 },
  { {2, 15, 9, 0, 12, 0}, g_bitmap_109 },
  { {2, 10, 9, 0, 12, 0}, g_bitmap_110 },
  { {1, 8, 9, 0, 12, 0}, g_bitmap_111 },
  { {2, 9, 13, 0, 12, 0}, g_bitmap_112 },
  { {2, 9, 13, 0, 12, 0}, g_bitmap_113 },
  { {1, 7, 9, 0, 12, 0}, g_bitmap_114 },
  { {1, 6, 9, 0, 12, 0}, g_bitmap_115 },
  { {1, 6, 11, 0, 10, 0}, g_bitmap_116 },
  { {2, 10, 9, 0, 12, 0}, g_bitmap_117 },
  { {2, 10, 9, 0, 12, 0}, g_bitmap_118 },
  { {2, 14, 9, 0, 12, 0}, g_bitmap_119 },
  { {2, 9, 9, 0, 12, 0}, g_bitmap_120 },
  { {2, 10, 13, 0, 12, 0}, g_bitmap_121 },
  { {1, 7, 9, 0, 12, 0}, g_bitmap_122 },
  { {1, 7, 17, 0, 8, 0}, g_bitmap_123 },
  { {1, 2, 16, 1, 8, 0}, g_bitmap_124 },
  { {1, 7, 17, 1, 8, 0}, g_bitmap_125 },
  { {1, 8, 4, 1, 14, 0}, g_bitmap_126 },
};
const struct nx_fontpackage_s g_serif22x28b_package =
{
  FONTID_SERIF22X28B,
  {
    28,
    22,
    7,
    5,
  },
  {
    33,
    (126 - 33 + 1),
    g_serif22x28b_7bitmaps
  },
};
