#include "ResourceTheme.h"

#include "Color.h"
#include "DisplayBuffer.h"

ResourceTheme::ResourceTheme()
{
    // focusColor = std::make_unique<Color>(0, 0, 0);
    // unfocusColor = std::make_unique<Color>(255, 255, 255);
    // borderColor = std::make_unique<Color>(0, 0, 0);
    // backgroundMenuColor = std::make_unique<Color>(255, 255, 255);
    // backgroundGameColor = std::make_unique<Color>(255, 255, 255);
    // netColor = std::make_unique<Color>(0, 0, 0);
    // figureIColor = std::make_unique<Color>(255, 255, 255);
    // figureLColor = std::make_unique<Color>(0, 0, 0);
    // figureJColor = std::make_unique<Color>(255, 255, 255);
    // figureZColor = std::make_unique<Color>(0, 0, 0);
    // figureSColor = std::make_unique<Color>(255, 255, 255);
    // figureTColor = std::make_unique<Color>(0, 0, 0);
    // figureOColor = std::make_unique<Color>(255, 255, 255);
}

ResourceTheme::ResourceTheme(const ResourceTheme& _fromResourceTheme)
{
    focusColor = std::make_unique<Color>( _fromResourceTheme.getFocusColor() );
    unfocusColor = std::make_unique<Color>( _fromResourceTheme.getUnfocusColor() );
    borderColor = std::make_unique<Color>( _fromResourceTheme.getBorderColor() );
    backgroundMenuColor = std::make_unique<Color>( _fromResourceTheme.getBackgroundMenuColor() );
    backgroundGameColor = std::make_unique<Color>( _fromResourceTheme.getBackgroundGameColor() );
    netColor = std::make_unique<Color>( _fromResourceTheme.getNetColor() );
    figureIColor = std::make_unique<Color>( _fromResourceTheme.getFigureIColor() );
    figureLColor = std::make_unique<Color>( _fromResourceTheme.getFigureLColor() );
    figureJColor = std::make_unique<Color>( _fromResourceTheme.getFigureJColor() );
    figureZColor = std::make_unique<Color>( _fromResourceTheme.getFigureZColor() );
    figureSColor = std::make_unique<Color>( _fromResourceTheme.getFigureSColor() );
    figureTColor = std::make_unique<Color>( _fromResourceTheme.getFigureTColor() );
    figureOColor = std::make_unique<Color>( _fromResourceTheme.getFigureOColor() );
}

ResourceTheme::~ResourceTheme()
{
}

Color ResourceTheme::getFocusColor() const { return *focusColor; }
void ResourceTheme::setFocusColor(Color _focusColor) 
{ 
    focusColor = std::make_unique<Color>(_focusColor.toUint16());
    // DisplayBuffer::bindColor(_focusColor.toUint16(), DisplayBuffer::colorCodes[1]);
}

Color ResourceTheme::getUnfocusColor() const { return *unfocusColor; }
void ResourceTheme::setUnfocusColor(Color _unfocusColor) 
{ 
    unfocusColor = std::make_unique<Color>(_unfocusColor.toUint16());
    // DisplayBuffer::bindColor(_unfocusColor.toUint16(), DisplayBuffer::colorCodes[2]);
};

Color ResourceTheme::getBorderColor() const { return *borderColor; }
void ResourceTheme::setBorderColor(Color _borderColor) 
{ 
    borderColor = std::make_unique<Color>(_borderColor.toUint16());
    // DisplayBuffer::bindColor(_borderColor.toUint16(), DisplayBuffer::colorCodes[3]);
}

Color ResourceTheme::getBackgroundMenuColor() const { return *backgroundMenuColor; }
void ResourceTheme::setBackgroundMenuColor(Color _backgroundMenuColor) 
{ 
    backgroundMenuColor = std::make_unique<Color>(_backgroundMenuColor);
    // DisplayBuffer::bindColor(_backgroundMenuColor.toUint16(), DisplayBuffer::colorCodes[4]); 
}

Color ResourceTheme::getBackgroundGameColor() const { return *backgroundGameColor; }
void ResourceTheme::setBackgroundGameColor(Color _backgroundGameColor) 
{ 
    backgroundGameColor = std::make_unique<Color>(_backgroundGameColor);
    // DisplayBuffer::bindColor(_backgroundGameColor.toUint16(), DisplayBuffer::colorCodes[5]); 
}

Color ResourceTheme::getNetColor() const { return *netColor; }
void ResourceTheme::setNetColor(Color _netColor) 
{ 
    netColor = std::make_unique<Color>(_netColor);
    // DisplayBuffer::bindColor(_netColor.toUint16(), DisplayBuffer::colorCodes[6]); 
}

Color ResourceTheme::getFigureIColor() const { return *figureIColor; }
void ResourceTheme::setFigureIColor(Color _figureIColor) 
{ 
    figureIColor = std::make_unique<Color>(_figureIColor); 
    // DisplayBuffer::bindColor(_figureIColor.toUint16(), DisplayBuffer::colorCodes[7]); 
}

Color ResourceTheme::getFigureLColor() const { return *figureLColor; }
void ResourceTheme::setFigureLColor(Color _figureLColor) 
{ 
    figureLColor = std::make_unique<Color>(_figureLColor); 
    // DisplayBuffer::bindColor(_figureLColor.toUint16(), DisplayBuffer::colorCodes[8]); 
}

Color ResourceTheme::getFigureJColor() const { return *figureJColor; }
void ResourceTheme::setFigureJColor(Color _figureJColor) 
{ 
    figureJColor = std::make_unique<Color>(_figureJColor); 
    // DisplayBuffer::bindColor(_figureJColor.toUint16(), DisplayBuffer::colorCodes[9]); 
}

Color ResourceTheme::getFigureZColor() const { return *figureZColor; }
void ResourceTheme::setFigureZColor(Color _figureZColor) 
{ 
    figureZColor = std::make_unique<Color>(_figureZColor); 
    // DisplayBuffer::bindColor(_figureZColor.toUint16(), DisplayBuffer::colorCodes[10]); 
}

Color ResourceTheme::getFigureSColor() const { return *figureSColor; }
void ResourceTheme::setFigureSColor(Color _figureSColor) 
{ 
    figureSColor = std::make_unique<Color>(_figureSColor); 
    // DisplayBuffer::bindColor(_figureSColor.toUint16(), DisplayBuffer::colorCodes[11]); 
}

Color ResourceTheme::getFigureTColor() const { return *figureTColor; }
void ResourceTheme::setFigureTColor(Color _figureTColor) 
{ 
    figureTColor = std::make_unique<Color>(_figureTColor); 
    // DisplayBuffer::bindColor(_figureTColor.toUint16(), DisplayBuffer::colorCodes[12]); 
}

Color ResourceTheme::getFigureOColor() const { return *figureOColor; }
void ResourceTheme::setFigureOColor(Color _figureOColor) 
{ 
    figureOColor = std::make_unique<Color>(_figureOColor); 
    // DisplayBuffer::bindColor(_figureOColor.toUint16(), DisplayBuffer::colorCodes[13]); 
}
