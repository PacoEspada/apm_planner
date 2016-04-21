#include "QsLog.h"
#include "UASInterface.h"
#include "UASManager.h"
#include "UAS.h"
#include "QGCMapTool.h"
#include "ui_QGCMapTool.h"

#include <QAction>
#include <QMenu>

const static int MapToolZoomFactor = 10; // This may need to be different for win/linux/mac
QCPCurve *lidar360;

QGCMapTool::QGCMapTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCMapTool),
    m_uasInterface(NULL)
{
    ui->setupUi(this);

    lidar360 = new QCPCurve(ui->Lidar360plot->xAxis, ui->Lidar360plot->yAxis);

    setupParametricCurveDemo(ui->Lidar360plot);
    setWindowTitle("Lidar Widget soy");
    ui->Lidar360plot->replot();

    // Connect map and toolbar
    ui->toolBar->setMap(ui->map);
    // Connect zoom slider and map
    ui->zoomSlider->setMinimum(ui->map->MinZoom() * MapToolZoomFactor);
    ui->zoomSlider->setMaximum(ui->map->MaxZoom() * MapToolZoomFactor);
    setZoom(ui->map->ZoomReal());

    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setMapZoom(int)));
    connect(ui->map, SIGNAL(zoomChanged(int)), this, SLOT(setZoom(int)));

    connect(UASManager::instance(),SIGNAL(activeUASSet(UASInterface*)),this,SLOT(activeUASSet(UASInterface*)));

    if (UASManager::instance()->getActiveUAS())
    {
        activeUASSet(UASManager::instance()->getActiveUAS());
    }
}

void QGCMapTool::setMapZoom(int zoom)
{
    ui->map->SetZoom(zoom/MapToolZoomFactor);
}

void QGCMapTool::setZoom(int zoom)
{
    ui->zoomSlider->setValue(zoom * MapToolZoomFactor);
    ui->zoomLabel->setText("ZOOM: " + QString::number(zoom));
}

void QGCMapTool::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    emit visibilityChanged(true);
}

void QGCMapTool::hideEvent(QHideEvent* event)
{
    QWidget::hideEvent(event);
    emit visibilityChanged(false);
}

QGCMapTool::~QGCMapTool()
{
    delete ui;
}

void QGCMapTool::activeUASSet(UASInterface *uasInterface)
{
    QLOG_INFO() << "QGCMapTool::activeUASSet";
    if (uasInterface == NULL) {
        QLOG_ERROR() << "uas object NULL";
        return;
    }
    UAS* uas = NULL;
    if (m_uasInterface){
        uas = qobject_cast<UAS*>(m_uasInterface);
        disconnect(m_uasInterface, SIGNAL(globalPositionChanged(UASInterface*,double,double,double,quint64)),
                this, SLOT(globalPositionUpdate(UASInterface*,double,double,double,quint64)));
        disconnect(uas, SIGNAL(gpsHdopChanged(double,QString)), this, SLOT(gpsHdopChanged(int,QString)));
        disconnect(uas, SIGNAL(gpsFixChanged(int,QString)),this, SLOT(gpsFixChanged(int,QString)));
        disconnect(uas, SIGNAL(satelliteCountChanged(int,QString)),
                this, SLOT(satelliteCountChanged(double,QString)));
        disconnect(uas, SIGNAL(lidar360distanceChanged(float,QString)),
                this, SLOT(lidar360distanceChanged(float,QString)));
    }
    m_uasInterface = uasInterface;
    uas = qobject_cast<UAS*>(m_uasInterface);
    connect(m_uasInterface, SIGNAL(globalPositionChanged(UASInterface*,double,double,double,quint64)),
            this, SLOT(globalPositionUpdate()));
    connect(uas, SIGNAL(gpsHdopChanged(double,QString)), this, SLOT(gpsHdopChanged(double,QString)));
    connect(uas, SIGNAL(gpsFixChanged(int,QString)), SLOT(gpsFixChanged(int,QString)));
    connect(uas, SIGNAL(satelliteCountChanged(int,QString)),
            this, SLOT(satelliteCountChanged(int,QString)));
    connect(uas, SIGNAL(lidar360distanceChanged(float,QString)),
            this, SLOT(lidar360distanceChanged(float,QString)));


}

void QGCMapTool::globalPositionUpdate()
{
    ui->latitudeLabel->setText(tr("LAT: %1").arg(m_uasInterface->getLatitude()));
    ui->longitudeLabel->setText(tr("LON: %1").arg(m_uasInterface->getLongitude()));
}

void QGCMapTool::gpsHdopChanged(double value, const QString &)
{
    QString stringHdop = QString::number(value,'g',2);
    ui->hdopLabel->setText(tr("HDOP: %1").arg(stringHdop));
}

void QGCMapTool::gpsFixChanged(int, const QString &)
{
    UAS* uas = dynamic_cast<UAS*>(m_uasInterface);
    ui->fixLabel->setText(tr("FIX: %1").arg(uas->getGpsFixString()));
}

void QGCMapTool::satelliteCountChanged(int value, const QString &)
{
    ui->satsLabel->setText(tr("SATS: %1").arg(value));
}

void QGCMapTool::lidar360distanceChanged(float distance, const QString&)
{
    static double radio = 0.0;

    // Update Lidar360 data
    int pointCount = 180;
    QVector<double> x1(pointCount), y1(pointCount);
    QVector<double> x2(pointCount), y2(pointCount);
    QVector<double> x3(pointCount), y3(pointCount);
    for (int i=0; i<pointCount; ++i)
    {
      double phi = (i/(double)(pointCount-1))*8*M_PI;
      x1[i] = distance * qCos(phi);//qSqrt(phi)*qCos(phi);
      y1[i] = distance * qSin(phi);//qSqrt(phi)*qSin(phi);
      x2[i] = -x1[i];
      y2[i] = -y1[i];
      double t = i/(double)(pointCount-1)*2*M_PI;
      x3[i] = 2*qCos(2*t)+qCos(1*t)+2*qSin(t);
      y3[i] = 2*qSin(2*t)-qSin(1*t);
    }
    // pass the data to the curves:
    lidar360->setData(x1, y1);

    ui->Lidar360plot->replot();

    radio++;
    if(radio == 20.00)
        radio = 0.0;

}

void QGCMapTool::setupParametricCurveDemo(QCustomPlot *customPlot)
{
  // create empty curve objects and add them to customPlot:
  QCPCurve *fermatSpiral2 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
  QCPCurve *deltoidRadial = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
  customPlot->addPlottable(lidar360);
  customPlot->addPlottable(fermatSpiral2);
  customPlot->addPlottable(deltoidRadial);
  // generate the curve data points:
  int pointCount = 180;
  QVector<double> x1(pointCount), y1(pointCount);
  QVector<double> x2(pointCount), y2(pointCount);
  QVector<double> x3(pointCount), y3(pointCount);
  for (int i=0; i<pointCount; ++i)
  {
    double phi = (i/(double)(pointCount-1))*8*M_PI;
    x1[i] = qCos(phi);//qSqrt(phi)*qCos(phi);
    y1[i] = qSin(phi);//qSqrt(phi)*qSin(phi);
    x2[i] = -x1[i];
    y2[i] = -y1[i];
    double t = i/(double)(pointCount-1)*2*M_PI;
    x3[i] = 2*qCos(2*t)+qCos(1*t)+2*qSin(t);
    y3[i] = 2*qSin(2*t)-qSin(1*t);
  }
  // pass the data to the curves:
  lidar360->setData(x1, y1);
  fermatSpiral2->setData(x2, y2);
  deltoidRadial->setData(x3, y3);
  // color the curves:
  lidar360->setPen(QPen(Qt::blue));
  lidar360->setBrush(QBrush(QColor(0, 0, 255, 20)));
  fermatSpiral2->setPen(QPen(QColor(255, 120, 0)));
  fermatSpiral2->setBrush(QBrush(QColor(255, 120, 0, 30)));
  QRadialGradient radialGrad(QPointF(310, 180), 200);
  radialGrad.setColorAt(0, QColor(170, 20, 240, 100));
  radialGrad.setColorAt(0.5, QColor(20, 10, 255, 40));
  radialGrad.setColorAt(1,QColor(120, 20, 240, 10));
  deltoidRadial->setPen(QPen(QColor(170, 20, 240)));
  deltoidRadial->setBrush(QBrush(radialGrad));
  // set some basic customPlot config:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  customPlot->axisRect()->setupFullAxesBox();
  customPlot->rescaleAxes();
}
