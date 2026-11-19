# Third-Party Libraries

- https://github.com/nothings/stb
- https://github.com/memononen/nanosvg
- https://github.com/kikuchan/pngle
- ~~https://github.com/richgel999/miniz~~ - shipped with pngle
- https://github.com/karlstav/cava 
- https://github.com/doctest/doctest

Update Date: 2026-11-16

## Custom Changes

Little tweaks in libraries.

**cavacore.c**

In `cava_init`:
```c
// @NOTE(furudbat): measure not needed, let just do estimate
//int fftw_flag = FFTW_MEASURE;
int fftw_flag = FFTW_ESTIMATE;
```

**nanosvgrast.h**

- Adds new function `nsvgRasterizeA` for [`src/image_loader/load_svgs.cpp`](src/image_loader/load_svgs.cpp).
```c
// @NOTE(furudbat): same as nsvgRasterize, but with alpha_mask_color
void nsvgRasterizeA(NSVGrasterizer* r,
				   NSVGimage* image, float tx, float ty, float scale,
				   unsigned char* dst, int w, int h, int stride, uint32_t alpha_mask_color);
```
_After the `nsvgRasterize` function_

- Add Header:
```c
#include <stdint.h>
```


- In the implementation, before `nsvgRasterize`:
```c
// @NOTE(furudbat): make pixels matching mask_color (0xRRGGBBAA) fully transparent
static void nsvg__applyAlphaMask(unsigned char* image, int w, int h, int stride, uint32_t mask_color)
{
  // Extract mask RGBA
  unsigned char mr = (mask_color >> 24) & 0xFF;
  unsigned char mg = (mask_color >> 16) & 0xFF;
  unsigned char mb = (mask_color >> 8)  & 0xFF;
  unsigned char ma = (mask_color)       & 0xFF;

  for (int y = 0; y < h; y++) {
    unsigned char* row = &image[y * stride];
    for (int x = 0; x < w; x++) {
      if (row[0] == mr && row[1] == mg &&
          row[2] == mb && row[3] == ma)
      {
        row[3] = 0;
      }

      row += 4;
    }
  }
}
```

Rename the `nsvgRasterize` implementation to `nsvgRasterizeA` and add the `alpha_mask_color` parameter:
```c
// @NOTE(furudbat): old nsvgRasterize becomes nsvgRasterizeA with alpha_mask_color added
void nsvgRasterizeA(NSVGrasterizer* r,
				   NSVGimage* image, float tx, float ty, float scale,
				   unsigned char* dst, int w, int h, int stride, uint32_t alpha_mask_color)
{
	// ...
	nsvg__unpremultiplyAlpha(dst, w, h, stride);

	// @NOTE(furudbat): apply alpha mask
	nsvg__applyAlphaMask(dst, w, h, stride, alpha_mask_color);

	r->bitmap = NULL;
	// ...
}
```

Re-add `nsvgRasterize` as a wrapper after it:
```c
// @NOTE(furudbat): original nsvgRasterize now calls nsvgRasterizeA (no alpha mask)
void nsvgRasterize(NSVGrasterizer* r,
				   NSVGimage* image, float tx, float ty, float scale,
				   unsigned char* dst, int w, int h, int stride)
{
	nsvgRasterizeA(r, image, tx, ty, scale, dst, w, h, stride, 0);
}
```

---

Special thanks to [waybar](https://github.com/alexays/waybar) and [hyprland](https://github.com/hyprwm/Hyprland).