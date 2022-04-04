import QtQuick 2.9
import QtQuick.Window 2.2
import QtLocation 5.6
import QtPositioning 5.6

Rectangle{
    Plugin{
        id:mapPlugin
        name:"osm"
    }

function addMarker(latitude, longitude)
    {
        var Component = Qt.createComponent("qrc:/marker.qml")
        var item = Component.createObject(this, {
                                              coordinate: QtPositioning.coordinate(latitude, longitude)
                                          })
        mapView.addMapItem(item)
    }

Map{
id:mapView
anchors.fill:parent
plugin: mapPlugin
center:QtPositioning.coordinate(36.899637115337406, 10.189218974581275)
Component.onCompleted:addMarker(36.899530492757584, 10.189209608398533)



zoomLevel:9
}


}
