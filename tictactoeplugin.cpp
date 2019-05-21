#include "tictactoe.h"
#include "tictactoeplugin.h"

#include <QtPlugin>

tictactoePlugin::tictactoePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void tictactoePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool tictactoePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *tictactoePlugin::createWidget(QWidget *parent)
{
    return new tictactoe(parent);
}

QString tictactoePlugin::name() const
{
    return QLatin1String("tictactoe");
}

QString tictactoePlugin::group() const
{
    return QLatin1String("");
}

QIcon tictactoePlugin::icon() const
{
    return QIcon();
}

QString tictactoePlugin::toolTip() const
{
    return QLatin1String("");
}

QString tictactoePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool tictactoePlugin::isContainer() const
{
    return false;
}

QString tictactoePlugin::domXml() const
{
    return QLatin1String("<widget class=\"tictactoe\" name=\"tictactoe\">\n</widget>\n");
}

QString tictactoePlugin::includeFile() const
{
    return QLatin1String("tictactoe.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(tictactoeplugin, tictactoePlugin)
#endif // QT_VERSION < 0x050000
