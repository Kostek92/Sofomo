import QtQuick
import app.AppController
import Sofomo

Item {
  id: root
  property int textSize: 15
  property GeolocationDataInfo currentData: AppController.currentData
  Text {
      id: title
      text: "Geolocation data"
      font {
        pixelSize: 25
        bold: true
      }
      anchors.horizontalCenter: parent.horizontalCenter
  }
  Grid
  {
      columns: 2

      spacing: 15
      anchors
      {
          top:title.bottom
          topMargin:10
          bottom:parent.bottom
          left: parent.left
          right: parent.right
      }

      Text
      {
          text: "IP"
          font {
            pixelSize: textSize
            bold: true
          }
      }
      Text {
        text: currentData.ip
        font.pixelSize: textSize
      }

      Text
      {
          font.pixelSize: textSize
          text:"Country"
          font {
            pixelSize: textSize
            bold: true
          }
      }
      Text {
        text: currentData.country
        font.pixelSize: textSize
      }

      Text
      {
          text: "Capital"
          font {
            pixelSize: textSize
            bold: true
          }
      }
      Text {
        text: currentData.capital
        font.pixelSize: textSize
      }

      Text
      {
          text: "City"
          font {
            pixelSize: textSize
            bold: true
          }
      }

      Text {
        text: currentData.city
        font.pixelSize: textSize
      }

      Text
      {
          text: "Latitude"
          font {
            pixelSize: textSize
            bold: true
          }
      }

      Text {
        text: currentData.latitude
        font.pixelSize: textSize
      }
      Text
      {
          text: "Longitude"
          font {
            pixelSize: textSize
            bold: true
          }
      }

      Text {
        text: currentData.longitude
        font.pixelSize: textSize
      }
  }
  function getAnyText(text)
  {
      if (text === "")
      {
          return "-"
      }
      return text
  }
}
