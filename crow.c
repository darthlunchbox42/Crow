/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <spoor42@gmx.us> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Stephen Poorman
 * ----------------------------------------------------------------------------
*/

#include <xcb/xcb.h>
#include <xcb/xproto.h>

int main() {
	int scrnNum;
	xcb_connection_t * conn;
	const xcb_setup_t * setup;
	xcb_screen_t * scrn;
	xcb_drawable_t win;
	xcb_gcontext_t black;
	
	//initialize the connection to X
	conn = xcb_connect(NULL, &scrnNum);
	
	//setup brings in the info on available screens, image formats, etc...
	setup = xcb_get_setup(conn);
	
	//get the first screen data
	scrn = xcb_setup_roots_iterator = setup.data;
	
	//create a black graphic context for drawing
	win = scrn -> root;
	black = xcb_generate_id(conn);
	
	//get the visual
	
