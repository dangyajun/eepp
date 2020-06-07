#ifndef EE_UIHELPER_HPP
#define EE_UIHELPER_HPP

#include <eepp/graphics/font.hpp>
#include <eepp/ui/base.hpp>

using namespace EE::Graphics;

namespace EE { namespace UI {

#define UI_HALIGN_LEFT TEXT_ALIGN_LEFT
#define UI_HALIGN_MASK TEXT_HALIGN_MASK
#define UI_VALIGN_TOP TEXT_ALIGN_TOP
#define UI_VALIGN_MASK TEXT_VALIGN_MASK

enum UIFlag {
	UI_HALIGN_RIGHT = TEXT_ALIGN_RIGHT,
	UI_HALIGN_CENTER = TEXT_ALIGN_CENTER,
	UI_VALIGN_BOTTOM = TEXT_ALIGN_BOTTOM,
	UI_VALIGN_CENTER = TEXT_ALIGN_MIDDLE,
	UI_AUTO_SIZE = ( 1 << 4 ),
	UI_SKIN_KEEP_SIZE_ON_DRAW = ( 1 << 5 ),
	UI_FILL_BACKGROUND = ( 1 << 6 ),
	UI_FILL_FOREGROUND = ( 1 << 7 ),
	UI_BORDER = ( 1 << 8 ),
	UI_TAB_STOP = ( 1 << 9 ),
	UI_WORD_WRAP = ( 1 << 10 ),
	UI_MULTI_SELECT = ( 1 << 11 ),
	UI_AUTO_PADDING = ( 1 << 12 ),
	UI_DRAG_ENABLE = ( 1 << 13 ),
	UI_ANCHOR_TOP = ( 1 << 14 ),
	UI_ANCHOR_BOTTOM = ( 1 << 15 ),
	UI_ANCHOR_LEFT = ( 1 << 16 ),
	UI_ANCHOR_RIGHT = ( 1 << 17 ),
	UI_TOUCH_DRAG_ENABLED = ( 1 << 18 ),
	UI_TEXT_SELECTION_ENABLED = ( 1 << 19 ),
	UI_ATTRIBUTE_CHANGED = ( 1 << 20 ),
	UI_CHECKED = ( 1 << 21 ),
	UI_OWNS_CHILDS_POSITION = ( 1 << 22 ),
	UI_DRAG_VERTICAL = ( 1 << 23 ),
	UI_DRAG_HORIZONTAL = ( 1 << 24 ),
	UI_TAB_FOCUSABLE = ( 1 << 25 )
};

enum UINodeType {
	UI_TYPE_NODE = 0,
	UI_TYPE_UINODE,
	UI_TYPE_WIDGET,
	UI_TYPE_IMAGE,
	UI_TYPE_TEXTUREREGION,
	UI_TYPE_SPRITE,
	UI_TYPE_TEXTVIEW,
	UI_TYPE_TEXTINPUT,
	UI_TYPE_PUSHBUTTON,
	UI_TYPE_CHECKBOX,
	UI_TYPE_RADIOBUTTON,
	UI_TYPE_SLIDER,
	UI_TYPE_SPINBOX,
	UI_TYPE_SCROLLBAR,
	UI_TYPE_SCROLLVIEW,
	UI_TYPE_PROGRESSBAR,
	UI_TYPE_LISTBOX,
	UI_TYPE_LISTBOXITEM,
	UI_TYPE_DROPDOWNLIST,
	UI_TYPE_MENU_SEPARATOR,
	UI_TYPE_COMBOBOX,
	UI_TYPE_MENU,
	UI_TYPE_MENUITEM,
	UI_TYPE_MENUCHECKBOX,
	UI_TYPE_MENUSUBMENU,
	UI_TYPE_TEXTEDIT,
	UI_TYPE_TOOLTIP,
	UI_TYPE_TABLE,
	UI_TYPE_WINDOW,
	UI_TYPE_MENUBAR,
	UI_TYPE_SELECTBUTTON,
	UI_TYPE_POPUPMENU,
	UI_TYPE_COMMONDIALOG,
	UI_TYPE_TAB,
	UI_TYPE_TABWIDGET,
	UI_TYPE_LOADER,
	UI_TYPE_LINEAR_LAYOUT,
	UI_TYPE_RELATIVE_LAYOUT,
	UI_TYPE_TOUCH_DRAGGABLE_WIDGET,
	UI_TYPE_GRID_LAYOUT,
	UI_TYPE_LAYOUT,
	UI_TYPE_VIEWPAGER,
	UI_TYPE_ITEMCONTAINER,
	UI_TYPE_CODEEDITOR,
	UI_TYPE_SPLITTER,
	UI_TYPE_USER = 10000
};

enum class ScrollBarMode : Uint32 { Auto, AlwaysOn, AlwaysOff };

enum class UIOrientation : Uint32 { Vertical, Horizontal };

enum class SizePolicy : Uint32 { Fixed, MatchParent, WrapContent };

enum class PositionPolicy : Uint32 { None, LeftOf, RightOf, TopOf, BottomOf };

enum class UIScaleType : Uint32 { None, Expand, FitInside };

static const Uint32 UI_NODE_DEFAULT_ALIGN = UI_HALIGN_LEFT | UI_VALIGN_CENTER;

static const Uint32 UI_NODE_ALIGN_CENTER = UI_HALIGN_CENTER | UI_VALIGN_CENTER;

static const Uint32 UI_NODE_DEFAULT_ANCHOR = UI_ANCHOR_LEFT | UI_ANCHOR_TOP;

static const Uint32 UI_NODE_DEFAULT_DRAG = UI_DRAG_VERTICAL | UI_DRAG_HORIZONTAL;

static const Uint32 UI_NODE_DEFAULT_FLAGS =
	UI_NODE_DEFAULT_ANCHOR | UI_NODE_DEFAULT_ALIGN | UI_NODE_DEFAULT_DRAG;

static const Uint32 UI_NODE_DEFAULT_FLAGS_CENTERED =
	UI_ANCHOR_LEFT | UI_ANCHOR_TOP | UI_HALIGN_CENTER | UI_VALIGN_CENTER;

}} // namespace EE::UI

#endif
