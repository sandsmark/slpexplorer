#include "widget.h"

#include <QPainter>
#include <QDebug>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QListWidget(parent)
{
    m_interfaceFile.setGameVersion(genie::GV_TC);
    m_interfaceFile.load("/home/sandsmark/src/freeaoe/build/Data/interfac.drs");
    m_palette = m_interfaceFile.getPalFile(50500);
    if (!m_palette) {
        qWarning() << "failed to load palette";
        return;
    }

    std::vector<genie::Color> colors = m_palette->getColors();
    for (unsigned i=0; i<colors.size(); i++) {
        m_colorTable.append(qRgb(colors[i].r, colors[i].g, colors[i].b));
    }

    m_drsFile.setGameVersion(genie::GV_TC);
    m_drsFile.load("/home/sandsmark/src/freeaoe/build/Data/graphics.drs");

    setIconSize(QSize(256, 256));
    loadSlps(&m_interfaceFile);
}

Widget::~Widget()
{

}

QPixmap Widget::getPixmap(genie::SlpFramePtr frame)
{
    if (!m_palette) {
        qWarning() << "No palette set";
        return QPixmap();
    }

    QImage image(frame->img_data.pixel_indexes.data(), frame->getWidth(), frame->getHeight(), frame->getWidth(), QImage::Format_Indexed8);
    image.setColorTable(m_colorTable);

    if (image.width() < 128) {
        return QPixmap::fromImage(image.scaledToWidth(128));
    } else if (image.height() < 128) {
        return QPixmap::fromImage(image.scaledToHeight(128));
    } else {
        return QPixmap::fromImage(image);
    }
}

void Widget::loadSlps(genie::DrsFile *drsFile)
{
    std::vector<uint32_t> ids = drsFile->slpFileIds();
    std::sort(ids.begin(), ids.end());
    for (const int id : ids) {
        genie::SlpFilePtr slp = drsFile->getSlpFile(id);
        if (!slp) {
            qWarning() << "Unable to load SLP file";
            continue;
        }
        for (unsigned frameNum = 0; frameNum < slp->getFrameCount(); frameNum++) {
            genie::SlpFramePtr frame = slp->getFrame(frameNum);
            if (!frame) {
                qWarning() << "Unable to load SLP frame";
                continue;
            }

            QListWidgetItem *item = new QListWidgetItem;
            item->setText(QString::number(id) + " " + QString::number(frameNum));
            item->setIcon(getPixmap(frame));
            addItem(item);
        }
    }
}
