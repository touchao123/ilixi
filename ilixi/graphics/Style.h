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

#ifndef ILIXI_STYLE_H_
#define ILIXI_STYLE_H_

#include <types/Image.h>
#include <types/Font.h>
#include <types/Rectangle.h>
#include <libxml/tree.h>
#include <map>

namespace ilixi
{

class Style
{
public:
    /*!
     * Initialise to default.
     */
    Style();

    /*!
     * Destructor.
     */
    ~Style();

    /*!
     * If name is found returns icon as a sub-image, else returns NOIMAGE image.
     */
    Image*
    getIcon(std::string name);

    /*!
     * Initialise style from an XML file.
     *
     * Returns false on error.
     */
    bool
    parseStyle(const char* filename);



    //--------------------------------------------------------------
    // Fonts
    //--------------------------------------------------------------
    //! Font for rendering button text.
    Font* _buttonFont;
    //! Default font to render text.
    Font* _defaultFont;
    //! Font for rendering input text.
    Font* _inputFont;
    //! Font for rendering title text.
    Font* _titleFont;

    //--------------------------------------------------------------
    // Icons
    //--------------------------------------------------------------
    //! This image stores the icon pack.
    Image* _iconPack;
    //! Default size for icons in the icon pack, e.g. Size(48, 48).
    int _defaultIconSize;

    typedef std::map<std::string, Point> IconMap;
    //! This is for mapping icons to sub_images.
    IconMap _iconMap;

    //--------------------------------------------------------------
    // Pack
    //--------------------------------------------------------------
    //! This image stores the widget pack.
    Image* _pack;

    struct r3
    {
        Rectangle l;
        Rectangle m;
        Rectangle r;
    };

    struct r9
    {
        Rectangle tl;
        Rectangle tm;
        Rectangle tr;
        Rectangle l;
        Rectangle m;
        Rectangle r;
        Rectangle bl;
        Rectangle bm;
        Rectangle br;
    };

    struct threesInput
    {
        r3 def;
        r3 pre;
        r3 exp;
        r3 dis;
        r3 foc;
    } pb;

    struct onesInput
    {
        Rectangle def;
        Rectangle pre;
        Rectangle exp;
        Rectangle dis;
        Rectangle foc;
    } cb, rb, slI;

    struct ninesInput
    {
        r9 def;
        r9 pre;
        r9 exp;
        r9 dis;
        r9 foc;
    } tb, li;

    struct threesView
    {
        r3 def;
        r3 dis;
    } pr, prI;

    struct threesViewV
    {
        r3 def;
        r3 dis;
        r3 defV;
        r3 disV;
    } sl;

    struct ninesView
    {
        r9 def;
        r9 dis;
    } fr, tab;

    Rectangle check;
    Rectangle tri_check;
    Rectangle radioOff;
    Rectangle radioOn;

protected:
    void
    parseFonts(xmlNodePtr node);

    void
    parseIcons(xmlNodePtr node);

    void
    parseTheme(xmlNodePtr node);

    void
    getRectangle(xmlNodePtr node, Rectangle& r);

    void
    get3Rectangle(xmlNodePtr node, r3& r);

    void
    get9Rectangle(xmlNodePtr node, r9& r);

private:
    void
    release();
};

}

#endif /* ILIXI_STYLE_H_ */
