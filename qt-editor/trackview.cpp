#include "trackview.h"
#include "trackgroupview.h"

#include <QApplication>
#include <QPainter>
#include <QMenuBar>
#include <QStatusBar>
#include <QKeyEvent>
#include <QScrollBar>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

#include "track.h"

void TrackView::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QRect rect;
	rect.setLeft(0);
	rect.setRight(width());

	int lineSpacing = painter.fontMetrics().lineSpacing();
	int startRow = event->rect().top() / lineSpacing;
	int stopRow = (event->rect().bottom() + lineSpacing - 1) / lineSpacing;
	for (int r = startRow; r < stopRow; ++r) {
		rect.setTop(r * lineSpacing);
		rect.setBottom((r + 1) * lineSpacing);

		QRect clipRect = rect.intersected(event->rect());
		if (r == rowHilight) {
			painter.fillRect(clipRect, palette().highlight());
			painter.setPen(palette().color(QPalette::HighlightedText));
		} else {
			painter.fillRect(clipRect, r % 8 ?
			                 palette().base() : palette().alternateBase());
			painter.setPen(palette().color(QPalette::WindowText));
		}

		QString temp = QString("---");
		if (track->isKeyFrame(r))
			temp.setNum(track->getKeyFrame(r).value);
		painter.drawText(rect, 0, temp, &clipRect);
	}
}

void TrackView::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::FontChange) {
		Q_ASSERT(fontInfo().fixedPitch());
		setFixedWidth(fontMetrics().width(' ') * 16);
	}
}