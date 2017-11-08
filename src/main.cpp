#include <widget.h>
#include <utils.h>
#include <iostream>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QString>
#include <QStringList>
#include <QApplication>

int main(int argc, char * argv[])
{
    size_t N = 50;

    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Circles");
    QCoreApplication::setApplicationVersion("1.0");
    QCommandLineParser parser;
    parser.setApplicationDescription("Interacting circles");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("N", QApplication::translate("main", "Number of circles"));
    parser.process(a);
    const QStringList args = parser.positionalArguments();
    if (args.empty()) {
        std::cout << "Number of circles not specified, default value will be used instead" << std::endl;
    }
    else {
        bool ok;
        size_t arg = args[0].toUInt(&ok);
        if (!ok) {
            std::cout
                    << "Number of circles specified wrong (must be integer >= 0), default value will be used instead"
                    << std::endl;
        }
        else if (arg > CircleUtils::max_nballs) {
            std::cout
                    << "Number of circles scannot be grater than " 
    		    << CircleUtils::max_nballs
		    << ", set to "
                    << CircleUtils::max_nballs
                    << std::endl;
            N = CircleUtils::max_nballs;
        }
        else {
            N = arg;
        }
    }
    Widget w(500, 500, N);
    w.show();

    return a.exec();
}
