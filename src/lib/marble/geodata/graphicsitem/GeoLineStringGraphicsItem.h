//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Andrew Manson <g.real.ate@gmail.com>
//

#ifndef MARBLE_GEOLINESTRINGGRAPHICSITEM_H
#define MARBLE_GEOLINESTRINGGRAPHICSITEM_H

#include "GeoGraphicsItem.h"
#include "GeoDataCoordinates.h"
#include "GeoDataLineString.h"
#include "MarbleGlobal.h"
#include "marble_export.h"

namespace Marble
{

class GeoDataPlacemark;

class MARBLE_EXPORT GeoLineStringGraphicsItem : public GeoGraphicsItem
{
public:
    explicit GeoLineStringGraphicsItem(const GeoDataPlacemark *placemark, const GeoDataLineString *lineString);

    void setLineString( const GeoDataLineString* lineString );
    const GeoDataLineString* lineString() const;
    static GeoDataLineString merge(const QVector<const GeoDataLineString*> &lineStrings);
    void setMergedLineString(const GeoDataLineString &sharedLineString);

    const GeoDataLatLonAltBox& latLonAltBox() const override;

    void paint(GeoPainter* painter, const ViewportParams *viewport, const QString &layer, int tileZoomLevel) override;
    bool contains(const QPoint &screenPosition, const ViewportParams *viewport) const override;

    static quint64 s_previousStyle;

private:
    void paintOutline(GeoPainter *painter, const ViewportParams *viewport) const;
    void paintInline(GeoPainter *painter, const ViewportParams *viewport);
    void paintLabel(GeoPainter *painter, const ViewportParams *viewport) const;

    bool configurePainterForLine(GeoPainter* painter, const ViewportParams *viewport, const bool isOutline = false) const;
    bool configurePainterForLabel(GeoPainter* painter,  const ViewportParams *viewport, LabelPositionFlags &labelPositionFlags) const;

    static bool canMerge(const GeoDataCoordinates &a, const GeoDataCoordinates &b);

    const GeoDataLineString *m_lineString;
    const GeoDataLineString *m_renderLineString;
    GeoDataLineString m_mergedLineString;
    QVector<QPolygonF*> m_cachedPolygons;
    bool m_renderLabel;
};

}

#endif
