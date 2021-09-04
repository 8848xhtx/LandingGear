import QtQuick 2.0
import QtQuick 2.13
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Item {
    width: 500
    height: 500
           Button{
               x: 10
               y: 10
               text: "OK"
   function test(){
       console.log("点击")
   }


               onClicked: {
                           test();
               }
           }

           DelayButton{
               x: 50
               y: 60
               delay: 1000
           }
}
