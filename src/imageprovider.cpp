/*
 * Copyright (C) 2017 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     zccrs <zccrs@live.com>
 *
 * Maintainer: zccrs <zhangjide@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "imageprovider.h"

#include <QScreen>
#include <QGuiApplication>

ImageProvider::ImageProvider()
    : QQuickImageProvider(Pixmap)
{

}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(requestedSize)

    if (id.startsWith("screen/")) {
        const QString &screen_name = id.mid(7);

        for (QScreen *s : qApp->screens()) {
            if (s->name() == screen_name) {
                const QPixmap &pix = s->grabWindow(0);

                if (size)
                    *size = pix.size();

                return pix;
            }
        }
    }

    return QPixmap();
}
