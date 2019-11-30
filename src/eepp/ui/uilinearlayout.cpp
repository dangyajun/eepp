#include <eepp/ui/uilinearlayout.hpp>
#include <eepp/ui/css/propertydefinition.hpp>

namespace  EE { namespace UI {

UILinearLayout * UILinearLayout::New() {
	return eeNew( UILinearLayout, () );
}

UILinearLayout * UILinearLayout::NewVertical() {
	return eeNew( UILinearLayout, () );
}

UILinearLayout * UILinearLayout::NewHorizontal() {
	return ( eeNew( UILinearLayout, () ) )->setOrientation( UI_HORIZONTAL );
}

UILinearLayout::UILinearLayout() :
	UILayout( "linearlayout" ),
	mOrientation( UI_VERTICAL )
{
	clipEnable();
}

Uint32 UILinearLayout::getType() const {
	return UI_TYPE_LINEAR_LAYOUT;
}

bool UILinearLayout::isType( const Uint32& type ) const {
	return UILinearLayout::getType() == type ? true : UILayout::isType( type );
}

UI_ORIENTATION UILinearLayout::getOrientation() const {
	return mOrientation;
}

UILinearLayout * UILinearLayout::setOrientation(const UI_ORIENTATION & orientation) {
	mOrientation = orientation;
	return this;
}

UILinearLayout * UILinearLayout::add( UIWidget * widget ) {
	widget->setParent( this );
	return this;
}

void UILinearLayout::onSizeChange() {
	UILayout::onSizeChange();
	pack();
}

void UILinearLayout::onParentSizeChange( const Vector2f& ) {
	UILayout::onParentChange();
	pack();
}

void UILinearLayout::onChildCountChange() {
	UILayout::onChildCountChange();
	pack();
}

void UILinearLayout::pack() {
	if ( mOrientation == UI_VERTICAL )
		packVertical();
	else
		packHorizontal();
}

void UILinearLayout::packVertical() {
	bool sizeChanged = false;
	Sizef size( getSize() );

	if ( getLayoutWidthRules() == MATCH_PARENT && 0 == getLayoutWeight() ) {
		Float w = getParent()->getSize().getWidth() - mLayoutMargin.Left - mLayoutMargin.Right;

		if ( getParent()->isType( UI_TYPE_LAYOUT ) ) {
			UILayout * pLay = static_cast<UILayout*>(getParent());
			w = w - pLay->getPadding().Left - pLay->getPadding().Right;
		}

		if ( (int)w != (int)getSize().getWidth() ) {
			sizeChanged = true;

			size.setWidth( w );
		}
	}

	if ( getLayoutHeightRules() == MATCH_PARENT ) {
		Float h = getParent()->getSize().getHeight() - mLayoutMargin.Top - mLayoutMargin.Bottom;

		if ( getParent()->isType( UI_TYPE_LAYOUT ) ) {
			UILayout * pLay = static_cast<UILayout*>(getParent());
			h = h - pLay->getPadding().Top - pLay->getPadding().Bottom;
		}

		if ( (int)h != (int)getSize().getHeight() ) {
			sizeChanged = true;

			size.setHeight( h );
		}
	}

	if ( sizeChanged ) {
		setInternalSize( size );
	}

	Node * ChildLoop = mChild;

	while ( NULL != ChildLoop ) {
		if ( ChildLoop->isWidget() && ChildLoop->isVisible() ) {
			UIWidget * widget = static_cast<UIWidget*>( ChildLoop );

			if ( widget->getLayoutHeightRules() == WRAP_CONTENT ) {
				widget->setFlags( UI_AUTO_SIZE );
			}

			switch ( widget->getLayoutWidthRules() ) {
				case WRAP_CONTENT:
				{
					widget->setFlags( UI_AUTO_SIZE );
					break;
				}
				case MATCH_PARENT:
				{
					int w = getSize().getWidth() - widget->getLayoutMargin().Left - widget->getLayoutMargin().Right - mPadding.Left - mPadding.Right;

					if ( (int)widget->getSize().getWidth() != w && w > 0 )
						widget->setSize( w, widget->getSize().getHeight() );

					break;
				}
				case FIXED:
				default:
				{
				}
			}

			if ( widget->getLayoutHeightRules() == MATCH_PARENT && widget->getLayoutWeight() == 0 &&
				 widget->getSize().getHeight() != getSize().getHeight() - widget->getLayoutMargin().Top - widget->getLayoutMargin().Bottom - mPadding.Top - mPadding.Bottom ) {
				widget->setSize( widget->getSize().getWidth(), getSize().getHeight() - widget->getLayoutMargin().Top - widget->getLayoutMargin().Bottom - mPadding.Top - mPadding.Bottom );
			}
		}

		ChildLoop = ChildLoop->getNextNode();
	}

	Int32 curY = mPadding.Top;
	Int32 maxX = 0;
	Sizei freeSize = getTotalUsedSize();

	ChildLoop = mChild;

	while ( NULL != ChildLoop ) {
		if ( ChildLoop->isWidget() ) {
			UIWidget * widget = static_cast<UIWidget*>( ChildLoop );
			Rect margin = widget->getLayoutMargin();

			curY += margin.Top;

			Vector2f pos( mPadding.Left, curY );

			if ( widget->getLayoutWeight() != 0 ) {
				Int32 totSize = ( getLayoutHeightRules() == MATCH_PARENT ) ? getSize().getHeight() - mPadding.Top - mPadding.Bottom :
																			 getParent()->getSize().getHeight() - mLayoutMargin.Bottom - mLayoutMargin.Top - mPadding.Top - mPadding.Bottom;
				Float size = (Float)( totSize - freeSize.getHeight() ) * widget->getLayoutWeight();

				widget->setSize( widget->getSize().getWidth(), (Int32)size );
			}

			switch ( fontHAlignGet( widget->getLayoutGravity() ) ) {
				case UI_HALIGN_CENTER:
					pos.x = ( getSize().getWidth() - mPadding.Left - mPadding.Right - widget->getSize().getWidth() ) / 2;
					break;
				case UI_HALIGN_RIGHT:
					pos.x = getSize().getWidth() - mPadding.Left - mPadding.Right - widget->getSize().getWidth() - widget->getLayoutMargin().Right;
					break;
				case UI_HALIGN_LEFT:
				default:
					pos.x = widget->getLayoutMargin().Left + mPadding.Left;
					break;
			}

			widget->setPosition( pos );

			curY += widget->getSize().getHeight() + margin.Bottom;

			maxX = eemax( maxX, (Int32)( widget->getSize().getWidth() + widget->getLayoutMargin().Left + widget->getLayoutMargin().Right ) );
		}

		ChildLoop = ChildLoop->getNextNode();
	}

	if ( getLayoutHeightRules() == WRAP_CONTENT ) {
		curY += mPadding.Bottom;

		if ( curY != (int)getSize().getHeight() ) {
			setInternalHeight( curY );
			notifyLayoutAttrChangeParent();
		}
	} else if ( getLayoutHeightRules() == MATCH_PARENT ) {
		int h = getParent()->getSize().getHeight() - mLayoutMargin.Top - mLayoutMargin.Bottom;

		if ( getParent()->isType( UI_TYPE_LAYOUT ) ) {
			UILayout * pLay = static_cast<UILayout*>(getParent());
			h = h - pLay->getPadding().Top - pLay->getPadding().Bottom;
		}

		if ( h != (int)getSize().getHeight() )
			setInternalHeight( h );
	}

	if ( getLayoutWidthRules() == WRAP_CONTENT && getSize().getWidth() != maxX ) {
		if ( !(0 != getLayoutWeight() && getParent()->isType( UI_TYPE_LINEAR_LAYOUT ) &&
			 getParent()->asType<UILinearLayout>()->getOrientation() == UI_HORIZONTAL) ) {
			setInternalWidth( maxX );
			packVertical();
			notifyLayoutAttrChangeParent();
		}
	}

	alignAgainstLayout();
}

void UILinearLayout::packHorizontal() {
	bool sizeChanged = false;
	Sizef size( getSize() );

	if ( getLayoutWidthRules() == MATCH_PARENT ) {
		Float w = getParent()->getSize().getWidth() - mLayoutMargin.Left - mLayoutMargin.Right;

		if ( getParent()->isType( UI_TYPE_LAYOUT ) ) {
			UILayout * pLay = static_cast<UILayout*>(getParent());
			w = w - pLay->getPadding().Left - pLay->getPadding().Right;
		}

		if ( (int)w != (int)getSize().getWidth() ) {
			sizeChanged = true;

			size.setWidth( w );
		}
	}

	if ( getLayoutHeightRules() == MATCH_PARENT && 0 == getLayoutWeight() ) {
		Float h = getParent()->getSize().getHeight() - mLayoutMargin.Top - mLayoutMargin.Bottom;

		if ( getParent()->isType( UI_TYPE_LAYOUT ) ) {
			UILayout * pLay = static_cast<UILayout*>(getParent());
			h = h - pLay->getPadding().Top - pLay->getPadding().Bottom;
		}

		if ( (int)h != (int)getSize().getHeight() ) {
			sizeChanged = true;

			size.setHeight( h );
		}
	}

	if ( sizeChanged ) {
		setInternalSize( size );;
	}

	Node * ChildLoop = mChild;

	while ( NULL != ChildLoop ) {
		if ( ChildLoop->isWidget() ) {
			UIWidget * widget = static_cast<UIWidget*>( ChildLoop );

			if ( widget->getLayoutWidthRules() == WRAP_CONTENT ) {
				widget->setFlags( UI_AUTO_SIZE );
			}

			switch ( widget->getLayoutHeightRules() ) {
				case WRAP_CONTENT:
				{
					widget->setFlags( UI_AUTO_SIZE );
					break;
				}
				case MATCH_PARENT:
				{
					int h = getSize().getHeight() - widget->getLayoutMargin().Top - widget->getLayoutMargin().Bottom - mPadding.Top - mPadding.Bottom;

					if ( h != (int)widget->getSize().getHeight() && h > 0 )
						widget->setSize( widget->getSize().getWidth(), h );

					break;
				}
				case FIXED:
				default:
				{
				}
			}

			if ( widget->getLayoutWidthRules() == MATCH_PARENT && widget->getLayoutWeight() == 0 &&
				 widget->getSize().getWidth() != getSize().getWidth() - widget->getLayoutMargin().Left  - widget->getLayoutMargin().Top - mPadding.Left - mPadding.Right ) {
				widget->setSize( getSize().getWidth(), widget->getSize().getWidth() - widget->getLayoutMargin().Left  - widget->getLayoutMargin().Top - mPadding.Left - mPadding.Right );
			}
		}

		ChildLoop = ChildLoop->getNextNode();
	}

	Int32 curX = mPadding.Left;
	Int32 maxY = 0;
	Sizei freeSize = getTotalUsedSize();

	ChildLoop = mChild;

	while ( NULL != ChildLoop ) {
		if ( ChildLoop->isWidget() && ChildLoop->isVisible() ) {
			UIWidget * widget = static_cast<UIWidget*>( ChildLoop );
			Rect margin = widget->getLayoutMargin();

			curX += margin.Left;

			Vector2f pos( curX, mPadding.Top );

			if ( widget->getLayoutWeight() != 0 ) {
				Int32 totSize = ( getLayoutWidthRules() == MATCH_PARENT ) ? getSize().getWidth() - mPadding.Left - mPadding.Right :
																			getParent()->getSize().getWidth() - mLayoutMargin.Right - mLayoutMargin.Left - mPadding.Left - mPadding.Right;
				Float size = (Float)( totSize - freeSize.getWidth() ) * widget->getLayoutWeight();

				widget->setSize( (Int32)size, widget->getSize().getHeight() );
			}

			switch ( fontVAlignGet( widget->getLayoutGravity() ) ) {
				case UI_VALIGN_CENTER:
					pos.y = ( getSize().getHeight() - mPadding.Top - mPadding.Bottom - widget->getSize().getHeight() ) / 2;
					break;
				case UI_VALIGN_BOTTOM:
					pos.y = getSize().getHeight() - mPadding.Top - mPadding.Bottom - widget->getSize().getHeight() - widget->getLayoutMargin().Bottom;
					break;
				case UI_VALIGN_TOP:
				default:
					pos.y = widget->getLayoutMargin().Top + mPadding.Top;
					break;
			}

			widget->setPosition( pos );

			curX += widget->getSize().getWidth() + margin.Right;

			maxY = eemax( maxY, (Int32)( widget->getSize().getHeight() + widget->getLayoutMargin().Top + widget->getLayoutMargin().Bottom ) );
		}

		ChildLoop = ChildLoop->getNextNode();
	}

	if ( getLayoutWidthRules() == WRAP_CONTENT ) {
		curX += mPadding.Right;

		if ( curX != (int)getSize().getWidth() ) {
			setInternalWidth( curX );
			notifyLayoutAttrChangeParent();
		}
	} else if ( getLayoutWidthRules() == MATCH_PARENT ) {
		int w = getParent()->getSize().getWidth() - mLayoutMargin.Left - mLayoutMargin.Right;

		if ( getParent()->isType( UI_TYPE_LAYOUT ) ) {
			UILayout * pLay = static_cast<UILayout*>(getParent());
			w = w - pLay->getPadding().Left - pLay->getPadding().Right;
		}

		if ( w != (int)getSize().getWidth() )
			setInternalWidth( w );
	}

	if ( getLayoutHeightRules() == WRAP_CONTENT && getSize().getHeight() != maxY ) {
		if ( !(0 != getLayoutWeight() && getParent()->isType( UI_TYPE_LINEAR_LAYOUT ) &&
			 getParent()->asType<UILinearLayout>()->getOrientation() == UI_VERTICAL) ) {
			setInternalHeight( maxY );
			packHorizontal();
			notifyLayoutAttrChangeParent();
		}
	}

	alignAgainstLayout();
}

Sizei UILinearLayout::getTotalUsedSize() {
	Node * ChildLoop = mChild;
	Sizei size( 0, 0 );

	while ( NULL != ChildLoop ) {
		if ( ChildLoop->isWidget() ) {
			UIWidget * widget = static_cast<UIWidget*>( ChildLoop );
			Rect margin = widget->getLayoutMargin();

			size.x += margin.Left + margin.Right;

			size.y += margin.Top + margin.Bottom;

			if ( widget->getLayoutWidthRules() == FIXED || widget->getLayoutWidthRules() == WRAP_CONTENT ) {
				if ( 0 == widget->getLayoutWeight() && mOrientation == UI_HORIZONTAL ) {
					size.x += widget->getSize().getWidth();
				}
			}

			if ( widget->getLayoutHeightRules() == FIXED || widget->getLayoutHeightRules() == WRAP_CONTENT ) {
				if ( 0 == widget->getLayoutWeight() && mOrientation == UI_VERTICAL ) {
					size.y += widget->getSize().getHeight();
				}
			}
		}

		ChildLoop = ChildLoop->getNextNode();
	}

	return size;
}

std::string UILinearLayout::getPropertyString( const PropertyDefinition* propertyDef ) {
	if ( NULL == propertyDef ) return "";

	switch ( propertyDef->getPropertyId() ) {
		case PropertyId::Orientation:
			return getOrientation() == UI_HORIZONTAL ? "horizontal" : "vertical";
		default:
			return UILayout::getPropertyString( propertyDef );
	}
}

bool UILinearLayout::applyProperty( const StyleSheetProperty& attribute ) {
	if ( !checkPropertyDefinition( attribute ) ) return false;

	switch ( attribute.getPropertyDefinition()->getPropertyId() ) {
		case PropertyId::Orientation:
		{
			std::string val = attribute.asString();
			String::toLowerInPlace( val );

			if ( "horizontal" == val )
				setOrientation( UI_HORIZONTAL );
			else if ( "vertical" == val )
				setOrientation( UI_VERTICAL );
			break;
		}
		default:
			return UILayout::applyProperty( attribute );
	}

	return true;
}

Uint32 UILinearLayout::onMessage(const NodeMessage * Msg) {
	switch( Msg->getMsg() ) {
		case NodeMessage::LayoutAttributeChange:
		{
			pack();
			break;
		}
	}

	return 0;
}

}}
