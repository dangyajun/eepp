#ifndef EE_UIHELPER_HPP 
#define EE_UIHELPER_HPP 

#include "base.hpp"

namespace EE { namespace UI {

#define UI_HALIGN_LEFT		FONT_DRAW_LEFT
#define UI_HALIGN_RIGHT		FONT_DRAW_RIGHT
#define UI_HALIGN_CENTER	FONT_DRAW_CENTER
#define UI_HALIGN_MASK		FONT_DRAW_HALIGN_MASK

Uint32 EE_API HAlignGet( Uint32 Flags );

#define UI_VALIGN_TOP		FONT_DRAW_TOP
#define UI_VALIGN_BOTTOM	FONT_DRAW_BOTTOM
#define UI_VALIGN_CENTER	FONT_DRAW_MIDDLE
#define UI_VALIGN_MASK		FONT_DRAW_VALIGN_MASK

Uint32 EE_API VAlignGet( Uint32 Flags );

#define UI_CTRL_FLAG_CLOSE		(1 << 0)
#define UI_CTRL_FLAG_CLOSE_FO	(1 << 1)
#define UI_CTRL_FLAG_ANIM		(1 << 2)

#define UI_TEXT_DRAW_SHADOW 	FONT_DRAW_SHADOW
#define UI_AUTO_SIZE			(1 << 6)
#define UI_INGORE_FOCUS			(1 << 7)
#define UI_FILL_BACKGROUND		(1 << 8)
#define UI_BORDER				(1 << 9)
#define UI_TAB_STOP				(1 << 10)
#define UI_FIT_TO_CONTROL 		(1 << 11)
#define UI_CLIP_ENABLE 			(1 << 12)
#define UI_AUTO_SHRINK_TEXT 	(1 << 13)

#define UI_TYPE_CONTROL		 	(0)
#define UI_TYPE_CONTROL_ANIM 	(1)
#define UI_TYPE_GFX 		 	(2)
#define UI_TYPE_TEXTBOX 	 	(3)

#define UI_TYPE_GET(X) 			( 1 << (X) )

}}

#endif
