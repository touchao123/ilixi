/*
 * RemoteContentArea.cpp
 *
 *  Created on: 9 Aug 2012
 *      Author: tarik
 */

#include "RemoteContentArea.h"
#include <core/Logger.h>
#include <graphics/Painter.h>
#include <ui/SurfaceView.h>
#include <ui/HBoxLayout.h>

namespace ilixi
{

D_DEBUG_DOMAIN( ILX_STATUSRCA, "ilixi/StatusBar/RCA", "RemoteContentArea");

Image* RemoteContentArea::_bgDef = NULL;

RemoteContentArea::RemoteContentArea(Widget* parent)
        : ContainerBase(parent)
{
    if (!_bgDef)
        _bgDef = new Image(ILIXI_DATADIR"statusbar/statusbar-buttons.png");

    setConstraints(MinimumExpandingConstraint, MinimumExpandingConstraint);
    setLayout(new HBoxLayout());
}

RemoteContentArea::~RemoteContentArea()
{
}

Size
RemoteContentArea::preferredSize() const
{
    Size s = _layout->preferredSize();
    return Size(s.width(), std::min(s.height(), 54));
}

bool
RemoteContentArea::addRemoteContent(DFBSurfaceID id)
{
    SurfaceView* s = new SurfaceView();
    s->setSourceFromSurfaceID(id);

    if (addWidget(s))
    {
        _remoteContent.push_back(s);
        ILOG_DEBUG(ILX_STATUSRCA, "addRemoteContent..\n");
        return true;
    }
    return false;
}

bool
RemoteContentArea::removeRemoteContent(DFBSurfaceID id)
{
    for (std::vector<SurfaceView*>::iterator it = _remoteContent.begin();
            it != _remoteContent.end(); ++it)
    {
        if ((*it)->sourceID() == id)
        {
            _remoteContent.erase(it);
            ILOG_DEBUG(ILX_STATUSRCA, "removeRemoteContent..\n");
            return true;
        }
    }
    return false;
}

void
RemoteContentArea::compose(const PaintEvent& event)
{
    Painter p(this);
    p.begin(event);

    p.blitImage(_bgDef, Rectangle(0, 0, 15, 15), 0, 0);
    p.blitImage(_bgDef, Rectangle(106, 0, 20, 15), width() - 20, 0);

    // mid
    p.setClip(15, 0, width() - 35, height());
    p.tileImage(_bgDef, 15, 0, Rectangle(15, 0, 91, 54));
    p.resetClip();

    // left
    p.setClip(0, 15, 15, height());
    p.tileImage(_bgDef, 0, 0, Rectangle(0, 15, 15, 39));
    p.resetClip();

    // right
    p.setClip(width() - 20, 15, 20, height());
    p.tileImage(_bgDef, width() - 20, 0, Rectangle(106, 15, 20, 39));
    p.resetClip();

    p.end();
}

} /* namespace ilixi */