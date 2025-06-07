#include <QApplication>
#include <QtCharts>
#include "chaos.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("混沌映射分析");
    window.resize(1100, 600);
    double avg_order;

    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
    QLineSeries *series3 = new QLineSeries();
    series1->setName("lojistic映射");
    series2->setName("singer映射");
    series3->setName("cubic映射");

    for(int N = 10; N <= 30; N++)
    {
        avg_order = calculate_average_order(N,1);
        series1->append(N , avg_order);
        avg_order = calculate_average_order(N,2);
        series2->append(N , avg_order);
        avg_order = calculate_average_order(N,3);
        series3->append(N , avg_order);
    }


    QChart *chart = new QChart();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);
    chart->setTitle("混沌映射平均的阶数");
    chart->createDefaultAxes();

    QChartView view(chart);
    view.resize(700, 400);
    view.setRenderHint(QPainter::Antialiasing);

    window.setCentralWidget(&view);
    window.show();

    QGraphicsScene *scene = view.scene();

    for (const QPointF &point : series1->points())
    {
        QString label = QString("%1, %2").arg(point.x()).arg(point.y());
        QGraphicsTextItem *textItem = new QGraphicsTextItem(label);

        QPointF labelPos = chart->mapToPosition(point);
        textItem->setPos(labelPos.x() , labelPos.y() );


        textItem->setDefaultTextColor(Qt::blue);
        textItem->setFont(QFont("Arial", 8));


        scene->addItem(textItem);
    }



    return app.exec();
}
