/*
 Copyright 2010-2012 Tarik Sekmen.

 All Rights Reserved.

 Written by Tarik Sekmen <tarik@ilixi.org>.

 This file is part of ilixi.

 ilixi is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 ilixi is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with ilixi.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <ui/Icon.h>
#include <graphics/Painter.h>
#include <core/Logger.h>

namespace ilixi
{

D_DEBUG_DOMAIN( ILX_ICON, "ilixi/ui/Icon", "Icon");

Icon::Icon(Widget* parent)
        : Widget(parent),
          _image(new Image())
{
    ILOG_TRACE_W(ILX_ICON);
    setConstraints(FixedConstraint, FixedConstraint);
}

Icon::Icon(const std::string& path, Widget* parent)
        : Widget(parent),
          _image(new Image(path))
{
    ILOG_TRACE_W(ILX_ICON);
    setConstraints(FixedConstraint, FixedConstraint);
}

Icon::Icon(const Image& image, Widget* parent)
        : Widget(parent),
          _image(new Image(image))
{
    ILOG_TRACE_W(ILX_ICON);
    setConstraints(FixedConstraint, FixedConstraint);
}

Icon::Icon(StyleHint::PackedIcon packedIcon, Widget* parent)
        : Widget(parent)
{
    ILOG_TRACE_W(ILX_ICON);
    _image = stylist()->defaultIcon(packedIcon);
}

Icon::~Icon()
{
    ILOG_TRACE_W(ILX_ICON);
    delete _image;
}

Size
Icon::preferredSize() const
{
    if (_image)
        return _image->size();
    return Size();
}

Image* const
Icon::image()
{
    return _image;
}

void
Icon::setImage(const std::string& path)
{
    if (_image)
        _image->setImagePath(path);
    else
        _image = new Image(path);
}

void
Icon::setState(WidgetState state)
{
    _state = state;
}

void
Icon::compose(const PaintEvent& event)
{
    Painter painter(this);
    painter.begin(event);
    stylist()->drawIcon(&painter, this);
    painter.end();
}

} /* namespace ilixi */
