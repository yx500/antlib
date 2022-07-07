#include <QString>
#include <QPainter>
#include <QString>

#include "antlib_string_vx.h"

#ifdef _VX_



QString  __bgi_adopt_String(const AntString& text){
  return text.asQString();
}

int __bgi_adopt_WidthTxt(const QFont& font, const AntString& text){
  if(text.cache.width==0){
    QFontMetrics fm(font);
    text.cache.width = fm.horizontalAdvance( text.asQString() );
  }
  return text.cache.width;
  //return text.asQStaticText().textWidth();
}


void __bgi_adopt_DrawTxt(QPainter *painter, const QRectF &rectangle, int flags, const AntString &text){
  painter->drawText(rectangle, flags, text.asQString() );
  //painter->drawStaticText( rectangle.x(), rectangle.y(), text.asQStaticText() );
}





#endif
