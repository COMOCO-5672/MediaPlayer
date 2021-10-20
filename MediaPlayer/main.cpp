#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // QCommandLineParser parser; //分析器
    // parser.addHelpOption();    //帮助
    // parser.addVersionOption(); //版本信息
    // QCommandLineOption p(QStringList() << "p"
    //                                    << "package",
    //                      "set package name of Android", "com.itcast.hello");
    // parser.addOption(p);
    // QCommandLineOption l(QStringList() << "l"
    //                                    << "language",
    //                      "set code language c++ or lua", "c++");
    // parser.addOption(l);

    // //    parser.parse(app.arguments());//解析参数
    // parser.process(app);

    // QString strValue = parser.value("p"); /* package */
    //                                       //  qCritical() <<"p is"<< strValue;
    // printf("p is %s\n", strValue.toUtf8().data());
    // strValue = parser.value("l"); /* language */
    // printf("l is %s\n", strValue.toUtf8().data());

    // qDebug() << parser.positionalArguments(); //获取不带-的参数 如 new……

    QCommandLineParser parser;
    parser.setApplicationDescription(QGuiApplication::translate("main", "Qt")); // 设置应用程序描述信息

    parser.addHelpOption();    // 添加帮助选项 （"-h" 或 "--help"）
    parser.addVersionOption(); // 添加版本选项 ("-v" 或 "--version")

    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions); // 举例说明：将 "-adb" 当成一个选项来看，而不是看成 "-a -b -c"

    //    parser.addPositionalArgument("xxx", QGuiApplication::translate("main", "?????? undefined"));

    QCommandLineOption widthOption(QStringList() << "wid"
                                                 << "width",
                                   QGuiApplication::translate("main", "Width of the covered area (default is 800)."),
                                   QGuiApplication::translate("main", "width"), "800");
    parser.addOption(widthOption);

    QCommandLineOption heightOption(QStringList() << "hei"
                                                  << "height",
                                    QGuiApplication::translate("main", "Height of the covered area (default is 480)."),
                                    QGuiApplication::translate("main", "height"), "480");
    parser.addOption(heightOption);

    QCommandLineOption xOption(QStringList() << "x",
                               QGuiApplication::translate("main", "The x coordinate of the covered area (default is 0)."),
                               QGuiApplication::translate("main", "x"), "0");
    parser.addOption(xOption);

    QCommandLineOption yOption(QStringList() << "y",
                               QGuiApplication::translate("main", "The y coordinate of the covered area (default is 0)."),
                               QGuiApplication::translate("main", "y"), "0");
    parser.addOption(yOption);

    QCommandLineOption colorOption(QStringList() << "c"
                                                 << "color",
                                   QGuiApplication::translate("main", "The color of the covered area (default is black)."),
                                   QGuiApplication::translate("main", "color"), "black");
    parser.addOption(colorOption);

    parser.process(app);

    //    const QStringList args = parser.positionalArguments();

    int width = parser.value(widthOption).toInt();
    int height = parser.value(heightOption).toInt();
    if (0 > width || 0 > height)
    {
        fprintf(stderr, "%s\n", qPrintable(QGuiApplication::translate("main", "Error: Invalid format argument. "
                                                                               "Width and height must be greater than 0.")));
        parser.showHelp(1);
    }
    int x = parser.value(xOption).toInt();
    int y = parser.value(yOption).toInt();
    qDebug() << "end";
    QString color = parser.value(colorOption);

    MainWindow w;
    w.show();
    return app.exec();
}