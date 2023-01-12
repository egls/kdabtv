/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
    id: root
    width: 400; height: 400
    color: "lightblue"

    Rectangle {
        id: greenRectangle
        width: root.width
        height: root.height / 2
         color: "green"
         y: root.height / 2
    }

    Rectangle {
        id: whiteRectangle
        color: "white"
        width: 50
        height: 50
        x: 50
        y: 50
    }

    Rectangle {
        id: blueRectangle
        color: "blue"
        width: 200
        height: 50
        x: 100
        y: 250
    }

}
