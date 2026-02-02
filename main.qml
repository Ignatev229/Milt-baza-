import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material 2.2

Item {

    Loader {
        id: splashScreenLoader
        source: "qrc:/SplashScreenView.qml"
        onLoaded: {
            mainWindowLoader.active = true;
        }
    }

    Loader {
        id: mainWindowLoader
        active: false
        source: "qrc:/MainView.qml"
        asynchronous: true
        onLoaded: {
            item.visible = true;
            splashScreenLoader.item.visible = false;
            splashScreenLoader.source = "";
        }
    }
}
