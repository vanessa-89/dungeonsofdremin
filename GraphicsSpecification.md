
```
Graphics.hpp Specifications - Luke Connor 11/8/12

void put_pixel16(SDL_Surface *surface, int x, int y, int r, int g, int b)
	Write a RGB coloured pixel to a SDL surface
	Returns nothing.
		*surface
			The SDL surface you wish to draw to.
		x
			The x position on the surface to write to.
		y
			The y position on the surface to write to.
		r
			The red RGB component of the pixel.
		g
			The green RGB component of the pixel.
		b
			The blue RGB component of the pixel.
Uint16 get_pixel16(SDL_Surface *surface, int x, int y)
	Read a uint16 pixel from a SDL surface
	Returns a uint16 pixel value.
		*surface
			The surface to read from.
		x
			The x position on the surface to read from.
		y
			The y position on the surface to read from.
window::screen
	A SDL_Surface* that points to the screen, window::open must be called before access.
window::xres
	A int containing the windows x resolution, window::open must be called before access.
window::yres
	A int containing the windows y resolution, window::open must be called before access.
window::depth
	A int containing the windows color depth, window::open must be called before access.
window::open(int x, int y, int dep, bool fullsreen)
	Open the window for viewing.
	returns a bool, 1 for fail and 0 for sucess.
		x
			The x resolution(size) of the window to open.
		y
			The y resolution(size) of the window to open.
		dep
			The color depth in bits of the window to open.
		fullscreen
			The flag for setting the window to fullscreen mode.
window::clear()
	Clears the screen.
	Returns nothing.
window::update()
	Updates the screen(flips the buffers).
```