//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009 Patrick Spendrin  <ps_ml@gmx.de>
//

#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDebug>

#include "MarbleDirs.h"
#include "GeoDataParser.h"
#include "GeoDataDocument.h"
#include "GeoDataFeature.h"
#include "GeoDataPlacemark.h"
#include "GeoDataPolygon.h"
#include "GeoDataCoordinates.h"

namespace Marble
{

class CopyTest : public QObject {
    Q_OBJECT
    private slots:
        void initTestCase();
        void copyCoordinates();
        void copyLineString();
        void copyLinearRing();
        void copyPoint();
    private:
        QString content;
        QStringList coordString;
        GeoDataCoordinates coord1;
        GeoDataCoordinates coord2;
        GeoDataCoordinates coord3;
};

void CopyTest::initTestCase() {
    MarbleDirs::setMarbleDataPath( DATA_PATH );
    MarbleDirs::setMarblePluginPath( PLUGIN_PATH );

    content = QString( 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<kml xmlns=\"http://earth.google.com/kml/2.1\">\n"
"  <Document>\n"
"    <Placemark>\n"
"      <name>LinearRingTest.kml</name>\n"
"      <Polygon>\n"
"        <outerBoundaryIs>\n"
"          <LinearRing>\n"
"            <coordinates>\n"
"              -122.365662,37.826988,0\n"
"              -122.365202,37.826302,0\n"
"              -122.364581,37.82655,0\n"
"              -122.365038,37.827237,0\n"
"              -122.365662,37.826988,0\n"
"            </coordinates>\n"
"          </LinearRing>\n"
"        </outerBoundaryIs>\n"
"      </Polygon>\n"
"    </Placemark>\n"
"  </Document>\n"
"</kml>" );

    coordString << QString(" 13� 42' 38\"E,  51� 01' 24\"N" );
    coordString << QString(" 14� 42' 38\"E,  52� 01' 24\"N" );
    coordString << QString(" 15� 42' 38\"E,  53� 01' 24\"N" );

    coord1.set(13.7107,51.0235, 123.4, GeoDataCoordinates::Degree);
    coord1.setDetail(2);
    QCOMPARE(coord1.altitude(), 123.4);
    QCOMPARE(coord1.detail(), 2);
    QCOMPARE(coord1.toString(), coordString[0]);
    
    coord2.set(14.7107,52.0235, 133.4, GeoDataCoordinates::Degree);
    coord2.setDetail(3);
    QCOMPARE(coord2.altitude(), 133.4);
    QCOMPARE(coord2.detail(), 3);
    QCOMPARE(coord2.toString(), coordString[1]);

    coord3.set(15.7107,53.0235, 143.4, GeoDataCoordinates::Degree);
    coord3.setDetail(4);
    QCOMPARE(coord3.altitude(), 143.4);
    QCOMPARE(coord3.detail(), 4);
    QCOMPARE(coord3.toString(), coordString[2]);

}

void CopyTest::copyCoordinates() {
    GeoDataCoordinates other = coord1;
    
    // make sure that the coordinate contains the right values
    QCOMPARE(other.altitude(), 123.4);
    QCOMPARE(other.detail(), 2);
    QCOMPARE(other.toString(), coordString[0]);
    
    QVERIFY(coord1 == other);
}

void CopyTest::copyPoint() {
    GeoDataPoint point;

    point.set(13.7107,51.0235, 123.4, GeoDataCoordinates::Degree);
    point.setDetail(2);

    // make sure that the coordinate contains the right values
    QCOMPARE(point.altitude(), 123.4);
    QCOMPARE(point.detail(), 2);
    QCOMPARE(point.toString(), coordString[0]);

    GeoDataPoint other = point;
    
    // make sure that the coordinate contains the right values
    QCOMPARE(other.altitude(), 123.4);
    QCOMPARE(other.detail(), 2);
    QCOMPARE(other.toString(), coordString[0]);
    
    QVERIFY(point == other);
}

void CopyTest::copyLineString() {
    GeoDataLineString lineString;
    lineString.setTessellate(true);
    

    lineString.append(coord1);
    lineString.append(coord2);
    lineString.append(coord3);
    QVERIFY(lineString.size() == 3);

    GeoDataLineString other = lineString;
    QVERIFY(other.size() == 3);

    QCOMPARE(lineString.at(0).altitude(), 123.4);
    QCOMPARE(lineString.at(0).detail(), 2);
    QCOMPARE(lineString.at(0).toString(), coordString[0]);
    
    QCOMPARE(other.at(2).altitude(), 143.4);
    QCOMPARE(other.at(2).detail(), 4);
    QCOMPARE(other.at(2).toString(), coordString[2]);
    
    QVERIFY(other.at(2) == coord3);
}

void CopyTest::copyLinearRing() {
    GeoDataLinearRing linearRing;

    linearRing.setTessellate(true);


    linearRing.append(coord1);
    linearRing.append(coord2);
    linearRing.append(coord3);
    QVERIFY(linearRing.size() == 3);

    GeoDataLinearRing other = linearRing;
    QVERIFY(other.size() == 3);

    QCOMPARE(linearRing.at(0).altitude(), 123.4);
    QCOMPARE(linearRing.at(0).detail(), 2);
    QCOMPARE(linearRing.at(0).toString(), coordString[0]);
    
    QCOMPARE(other.at(2).altitude(), 143.4);
    QCOMPARE(other.at(2).detail(), 4);
    QCOMPARE(other.at(2).toString(), coordString[2]);
    
    QVERIFY(other.at(2) == coord3);
}

}

QTEST_MAIN( Marble::CopyTest )

#include "CopyTest.moc"
