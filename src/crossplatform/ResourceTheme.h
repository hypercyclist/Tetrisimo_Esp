#ifndef RESOURCETHEME_H
#define RESOURCETHEME_H

class Color;

#include <memory>

// This is game resource theme object. From there we should take a colors for
// painting widgets. One of the theme selected to game necessarily.
class ResourceTheme
{
    public:
        std::unique_ptr<Color> undefinedColor;
        std::unique_ptr<Color> focusColor;
        std::unique_ptr<Color> unfocusColor;
        std::unique_ptr<Color> borderColor;
        std::unique_ptr<Color> backgroundMenuColor;
        std::unique_ptr<Color> backgroundGameColor;
        std::unique_ptr<Color> netColor;
        std::unique_ptr<Color> figureIColor;
        std::unique_ptr<Color> figureLColor;
        std::unique_ptr<Color> figureJColor;
        std::unique_ptr<Color> figureZColor;
        std::unique_ptr<Color> figureSColor;
        std::unique_ptr<Color> figureTColor;
        std::unique_ptr<Color> figureOColor;

        ResourceTheme();
        ResourceTheme(const ResourceTheme& _fromResourceTheme);
        ~ResourceTheme();

        Color getUndefinedColor() const;
        void setUndefinedColor(Color _undefinedColor);

        Color getFocusColor() const;
        void setFocusColor(Color _focusColor);

        Color getUnfocusColor() const;
        void setUnfocusColor(Color _focusColor);

        Color getBorderColor() const;
        void setBorderColor(Color _borderColor);
        
        Color getBackgroundMenuColor() const;
        void setBackgroundMenuColor(Color _backgroundMenuColor);
        
        Color getBackgroundGameColor() const;
        void setBackgroundGameColor(Color _backgroundGameColor);

        Color getNetColor() const;
        void setNetColor(Color _netColor);

        Color getFigureIColor() const;
        void setFigureIColor(Color _figureIColor);
        
        Color getFigureLColor() const;
        void setFigureLColor(Color _figureLColor);

        Color getFigureJColor() const;
        void setFigureJColor(Color _figureJColor);

        Color getFigureZColor() const;
        void setFigureZColor(Color _figureZColor);

        Color getFigureSColor() const;
        void setFigureSColor(Color _figureSColor);

        Color getFigureTColor() const;
        void setFigureTColor(Color _figureTColor);

        Color getFigureOColor() const;
        void setFigureOColor(Color _figureOColor);
};

#endif
