#ifndef WIDGET_H
#define WIDGET_H

#include <QListWidget>

#include <genie/resource/DrsFile.h>
#include <memory>

class Widget : public QListWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QPixmap getPixmap(genie::SlpFramePtr frame);

    void loadSlps(genie::DrsFile *file);

    genie::DrsFile m_interfaceFile;
    genie::DrsFile m_drsFile;
    genie::PalFilePtr m_palette;
    QVector<QRgb> m_colorTable;
};

#endif // WIDGET_H
