/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <spoor42@gmx.us> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Stephen Poorman
 * ----------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <xcb/xcb.h>

int main() {
	xcb_connection_t 	* conn;
	xcb_screen_t 		* scrn;
	xcb_drawable_t 		win;
	xcb_gcontext_t 		foreground;
	xcb_generic_event_t	* e;
	uint32_t			mask = 0;
	uint32_t			values[2];
	
	xcb_point_t points[] = { { 10, 10 },
							 { 10, 20 },
							 { 20, 10 },
							 { 20, 20 } };
	xcb_point_t polyline[] = { { 50, 10 },
							   {  5, 20 },
							   { 25,-20 },
							   { 10, 10 } };
	xcb_segment_t segments[] = { { 100, 10, 140, 30 },
								 { 110, 25, 130, 60 } };
	xcb_rectangle_t rectangles[] = { { 10, 50, 40, 30 },
								     { 80, 50, 10, 40 } };
	xcb_arc_t arcs[] = { { 10, 100, 60, 40, 0,  90 << 6 },
						 { 90, 100, 55, 40, 0, 270 << 6 } };
	
	//initialize the connection to X
	conn = xcb_connect(NULL, &scrnNum);
	
	//get the first screen data
	scrn = get_setup_roots_iterator(xcb_get_setup(conn)).data;
	
	foreground = xcb_generate_id(conn);
	mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
	values[0] = scrn->black_pixel;
	values[1] = 0;
	xcb_create_gc(conn, foreground, win, mask, values);
	
	//ask for the window's id
	win = xcb_generate_id(conn);
	
	//create the window
	mask = XCB_CW_BLACK_PIXEL | XCB_GC_GRAPHICS_EXPOSURES
	values[0] = scrn->white_pixel;
	values[1] = XCB_EVENT_MASK_EXPOSURE;
	xcb_create_window(conn,
					  XCB_COPY_FROM_PARENT,
					  win,
					  scrn->root,
					  0, 0,
					  150, 150,
					  10,
					  XCB_WINDOW_CLASS_INPUT_OUTPUT,
					  scrn->root_visual,
					  mask, values);
	
	//map the window
	xcb_map_window(conn, win);
	xcb_flush(conn);
	
	while (( e = xcb_wait_for_event(conn)) {
		switch (e->response_type & ~0x80) {
		case XCB_EXPOSE: {
			//draw things
			xcb_poly_point(conn, XCB_COORD_MODE_ORIGIN, win, foreground, 4, points);
			
			xcb_poly_line(conn, XCB_COORD_MODE_PREVIOUS, win, foreground, 4, polyline);
			
			xcb_poly_segment(conn, win, foreground, 2, segments);
			
			xcb_poly_rectangle(conn, win, foreground, 2 , rectangles);
			
			xcb_poly_arc(conn, win, foreground, 2, arcs);
			
			xcb_flush(conn);
			
			break;
		}
		default: {
			break;
		}
		}
		free(e);
	}
	return 0;
}
