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

#include "Home.h"
#include <core/Logger.h>

namespace ilixi
{

D_DEBUG_DOMAIN( ILX_HOMEAPP, "ilixi/Home", "Home");

Image* Home::_circle = NULL;
Image* Home::_circle_sm = NULL;

void
appVisible(void* ctx, void* arg)
{
    ILOG_TRACE_F(ILX_HOMEAPP);
    Home* home = (Home*) ctx;
    VisibilityNotification notification = *((VisibilityNotification*) arg);
    home->_pages->setAppStatus(notification, 1);
}

void
appHidden(void* ctx, void* arg)
{
    ILOG_TRACE_F(ILX_HOMEAPP);
    Home* home = (Home*) ctx;
    VisibilityNotification notification = *((VisibilityNotification*) arg);
    home->_pages->setAppStatus(notification, 0);
}

void
appStarting(void* ctx, void* arg)
{
    ILOG_TRACE_F(ILX_HOMEAPP);
    Home* home = (Home*) ctx;
    VisibilityNotification notification = *((VisibilityNotification*) arg);
    home->_pages->setAppStarting(notification);
}

void
receiveAppList(void* ctx, void* arg)
{
    ILOG_TRACE_F(ILX_HOMEAPP);
    Home* home = (Home*) ctx;

    int* size = ((int*) arg);
    ILOG_DEBUG(ILX_HOMEAPP, " -> Size: %d\n", *size);
    Home::AppData *srcdata = (Home::AppData*) (size + 1);
    Home::AppDataVector vec;

    for (int i = 0; i < *size; ++i)
    {
        ILOG_DEBUG(ILX_HOMEAPP, "%s - %s\n", srcdata[i].name, srcdata[i].icon);

        Home::AppData data;
        snprintf(data.name, 64, "%s", srcdata[i].name);
        snprintf(data.icon, 128, "%s", srcdata[i].icon);
        vec.push_back(data);
    }
    home->initButtons(vec);
}

Home::Home(int argc, char* argv[])
        : Application(&argc, &argv, OptDale),
          _compositor(NULL)
{
    ILOG_TRACE_W(ILX_HOMEAPP);
    setTitle("Home");
    setBackgroundImage(ILIXI_DATADIR"compositor/bg.png");
    setPaletteFromFile(ILIXI_DATADIR"statusbar/def_palette.xml");

    if (!_circle)
    {
        _circle = new Image(ILIXI_DATADIR"home/circle.png", Size(48, 48));
        _circle_sm = new Image(ILIXI_DATADIR"home/circle_small.png",
                               Size(38, 38));
    }

    _pages = new NumPages();
    _pages->sigAppStart.connect(sigc::mem_fun(this, &Home::runApp));
    addWidget(_pages);

    DaleDFB::comaGetComponent("CompositorComponent", &_compositor);

    sigGeometryUpdated.connect(sigc::mem_fun(this, &Home::updateHomeGeometry));
    sigVisible.connect(sigc::mem_fun(this, &Home::requestAppList));
}

Home::~Home()
{
    delete _circle;
    delete _circle_sm;
    if (_compositor)
        _compositor->Release(_compositor);
}

void
Home::runApp(const char* name)
{
    if (_compositor)
    {
        void *ptr;
        DaleDFB::comaGetLocal(128, &ptr);
        char* n = (char*) ptr;
        snprintf(n, 128, "%s", name);
        DaleDFB::comaCallComponent(_compositor, 7, (void*) n);
    }
}

void
Home::initButtons(const AppDataVector& dataVector)
{
    ILOG_TRACE_W(ILX_HOMEAPP);
    for (AppDataVector::const_iterator it = dataVector.begin();
            it != dataVector.end(); ++it)
        _pages->addItem(((AppData) *it).name, ((AppData) *it).icon);
    _pages->initPages();
}

void
Home::requestAppList()
{
    if (_compositor)
    {
        _compositor->Listen(_compositor, 0, appVisible, this);
        _compositor->Listen(_compositor, 1, appHidden, this);
        _compositor->Listen(_compositor, 2, appStarting, this);
        _compositor->Listen(_compositor, 7, receiveAppList, this);
        DaleDFB::comaCallComponent(_compositor, 8, NULL);
    }
}

void
Home::updateHomeGeometry()
{
    ILOG_TRACE_W(ILX_HOMEAPP);
    _pages->setGeometry(0, 100, width(), height() - 200);
}

}

int
main(int argc, char* argv[])
{
    ilixi::Home app(argc, argv);
    app.exec();
    return 0;
}
