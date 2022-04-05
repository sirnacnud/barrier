/*
 * barrier -- mouse and keyboard sharing utility
 * Copyright (C) 2022 Duncan Cunningham
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AccessibilityPermissionObserver.h"

#include <QApplication>
#include <QTimer>

#if defined(Q_OS_MAC)
#include <Carbon/Carbon.h>
#endif

AccessibilityPermissionObserver::AccessibilityPermissionObserver(QObject* parent)
    : QObject(parent)
{
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 1090 // mavericks
    m_pTimer = new QTimer(this);

    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(checkAccessibilityPermissions()));
#endif
}

void AccessibilityPermissionObserver::start()
{
    if (m_pTimer) {
        m_pTimer->start(1000);
    }
}

void AccessibilityPermissionObserver::checkAccessibilityPermissions()
{
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 1090 // mavericks
    // There's no API to be notified when this permission changes, so we have to poll it.
    if (!AXIsProcessTrusted()) {
        QApplication::quit();
    }
#endif
}