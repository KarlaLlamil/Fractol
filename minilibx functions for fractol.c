/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx functions for fractol.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielm3 <danielm3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:29:05 by danielm3          #+#    #+#             */
/*   Updated: 2025/07/07 19:42:47 by danielm3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void *mlx_init(void);
// Initializes the MLX library and opens a connection to the X11 display.
// Returns a pointer to the MLX instance, used in all other MLX functions.

void *mlx_new_window(void *mlx_ptr, int width, int height, char *title);
// Creates a new window.
// mlx_ptr: the MLX instance from mlx_init
// width, height: size of the window in pixels
// title: string displayed in the window title bar
// Returns a pointer to the new window.

void *mlx_new_image(void *mlx_ptr, int width, int height);
// Creates a new image in memory to draw on (not visible until shown).
// mlx_ptr: the MLX instance
// width, height: size of the image in pixels
// Returns a pointer to the image object.
// Returns an opaque handle (an internal MLX struct)
// that represents your image. It’s not the raw pixel buffer.

char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *line_length, int *endian);
// Gives access to the image's raw pixel memory buffer.
// img_ptr: the image from mlx_new_image
// bits_per_pixel: pointer to an int that will hold how many bits per pixel (usually 32)
// line_length: pointer to an int that will hold the number of bytes per row (may include padding)
// endian: pointer to an int that will be set to 0 (little-endian) or 1 (big-endian)
// Returns a pointer into that handle’s pixel memory. That pointer typically points 
// to the very first byte of the pixel data, but it’s a different pointer value than the 
// handle itself.

int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);
// Displays the image (created and drawn in memory) onto the window.
// mlx_ptr: the MLX instance
// win_ptr: the window where to display the image
// img_ptr: the image to display
// x, y: top-left coordinates in the window where to place the image

int mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
// (Slow) Draws a single pixel directly in the window.
// mlx_ptr: the MLX instance
// win_ptr: the window to draw in
// x, y: position of the pixel
// color: the color of the pixel in hexadecimal (e.g. 0xFFFFFF for white)

int mlx_loop(void *mlx_ptr);
// Starts the MLX event loop. This function blocks and keeps the window open.
// mlx_ptr: the MLX instance

int mlx_hook(void *win_ptr, int event, int mask, int (*f)(), void *param);
// Registers a callback function for a window event (like keypress or mouse).
// win_ptr: the window to listen to
// event: the event code (e.g. 2 for keypress)
// mask: the event mask (usually 1L << 0 for keypress)
// f: the function to call when the event happens
// param: a pointer passed to your callback function

int mlx_destroy_window(void *mlx_ptr, void *win_ptr);
// Destroys the given window and frees its resources.
// mlx_ptr: the MLX instance
// win_ptr: the window to destroy


/* Here are the most common event codes and their matching masks:

Event codes (second argument to mlx_hook):

KeyPress        = 2
KeyRelease      = 3
ButtonPress     = 4
ButtonRelease   = 5
MotionNotify    = 6
EnterNotify     = 7
LeaveNotify     = 8
Expose          = 12
DestroyNotify   = 17


Event masks (third argument to mlx_hook):

NoEventMask           = 0L
KeyPressMask          = (1L<<0)
KeyReleaseMask        = (1L<<1)
ButtonPressMask       = (1L<<2)
ButtonReleaseMask     = (1L<<3)
PointerMotionMask     = (1L<<6)
ExposureMask          = (1L<<15)
StructureNotifyMask   = (1L<<17)
17 with mask 0L means “listen for DestroyNotify (window-close) and
 no extra sub-events.”

You can combine masks (e.g. KeyPressMask | ExposureMask) if you
need multiple event types in one hook.


Tú dijiste:
explain to me what those masks are doing, i dont understand that 
syntax

Event masks in X11 (and thus in MiniLibX) are just bitfields where 
each bit enables delivery of a particular class of event. The syntax

KeyPressMask = (1L << 0)
ButtonPressMask = (1L << 2)
StructureNotifyMask = (1L << 17)
means:

1L << n

Take the number 1 (a long integer), then shift its single “1” bit 
left by n positions.

The result is a value where only bit n is set.

E.g. (1L<<0) is 0b…0001, (1L<<2) is 0b…0100, (1L<<17) is a 1 in 
the 18th bit position.

Why masks?

When you call mlx_hook, you give it a mask so the underlying X11
 connection only sends you the kinds of events you asked for 
 (key presses, mouse clicks, window structure changes, etc.).

If you OR together multiple masks, e.g.

KeyPressMask | ExposureMask
you’ll receive both key‐press events and expose (redraw) events 
in that one hook.

The special case 0L

Passing 0L means “no extra mask bits”—you rely only on the event 
code (like 17 for DestroyNotify) and don’t need to filter sub‐types.

So masks are just bit flags. By shifting a 1 into different bit 
positions, you turn on the exact bits corresponding to the event 
classes you want. 

Main mouse button codes in X11 (used by MiniLibX on Linux):

1 → Left click
2 → Middle click
3 → Right click
4 → Scroll up (wheel up)
5 → Scroll down (wheel down)

*/

/* 
✅ In Julia:
c is a constant, chosen once (e.g. from user input)

You vary z₀ (each pixel is a different z₀)

You ask: “For this fixed c, which starting points z₀ stay bounded?”

✅ In Mandelbrot:
z₀ is always 0

c varies (each pixel is a different c)

You ask: “Which complex numbers c keep the sequence starting at 0 bounded?”

So yes:

In Julia, c = constant

In Mandelbrot, c = pixel (i.e. variable)
*/

/*
main:

mlx_hook(mlx.win_ptr, 2, 1L << 0, on_key_press, &env);

- 2: the X11 event code for KeyPress.
- 1L << 0: the mask that enables listening 
for key press events (KeyPressMask).


mlx_hook(mlx.win_ptr, 17, 0L, on_close, &mlx);

- 17: the X11 event code for DestroyNotify (window close).
- 0L: no mask needed for this event.

mlx_mouse_hook(mlx.win_ptr, mouse_zoom, &env);
int	mouse_zoom(int button, int x, int y, void *param)
int mlx_int_param_ButtonPress(t_xvar *xvar, XEvent *ev, t_win_list *win)

win->hooks[ButtonPress].hook(
    ev->xbutton.button,  // passed as `button`
    ev->xbutton.x,       // passed as `x`
    ev->xbutton.y,       // passed as `y`
    win->hooks[ButtonPress].param // passed as `param`
);




------------------ ENDIANNESS -----------------------

In mlx_get_data_addr, the endian value means:

0 = Little-endian → least significant byte first

1 = Big-endian → most significant byte first

🖥 Common systems:
Platform / Architecture	Endian
x86 / x86_64 (Intel/AMD)	0 (Little-endian) ✅
ARM (most modern phones, Apple M1/M2)	0 (Little-endian) ✅
PowerPC (old Macs, some consoles)	1 (Big-endian) ❌
SPARC, MIPS (older servers/routers)	1 (Big-endian) ❌

TL;DR:
💻 Almost all modern systems (PCs, Macs, phones) use little-endian → endian == 0

Only legacy or specialized hardware uses big-endian. 
So your typical MLX program will almost always run with endian == 0.




*/