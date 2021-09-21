/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - The Lightweight Desktop Environment
 * https://lxqt-project.org
 *
 * Copyright: 2011-12 Razor Team;  2012-2020 LXQt Project
 * Authors:
 *   Petr Vanek <petr@scribus.info>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "lxqtaboutdialog.h"
#include "ui_lxqtaboutdialog.h"
#include "lxqtaboutdialog_p.h"
#include "technicalinfo.h"
#include "translatorsinfo/translatorsinfo.h"

#include <QDebug>
#include <QDate>
#include <QClipboard>

AboutDialogPrivate::AboutDialogPrivate()
{
    setupUi(this);

    QString css=QStringLiteral("<style TYPE='text/css'> "
                    "body { font-family: sans-serif;} "
                    ".name { font-size: 16pt; } "
                    "a { white-space: nowrap ;} "
                    "h2 { font-size: 10pt;} "
                    "li { line-height: 120%;} "
                    ".techInfoKey { white-space: nowrap ; margin: 0 20px 0 16px; } "
                "</style>")
            ;

    iconLabel->setFixedSize(48, 48);
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(QPixmap(QStringLiteral("/usr/share/icons/koompi.svg")));

    nameLabel->setText(css + titleText());

    aboutBrowser->setHtml(css + aboutText());
    aboutBrowser->viewport()->setAutoFillBackground(false);

    autorsBrowser->setHtml(css + authorsText());
    autorsBrowser->viewport()->setAutoFillBackground(false);

    thanksBrowser->setHtml(css + thanksText());
    thanksBrowser->viewport()->setAutoFillBackground(false);

    // translationsBrowser->setHtml(css + translationsText());
    // translationsBrowser->viewport()->setAutoFillBackground(false);

    TechnicalInfo info;
    techBrowser->setHtml(info.html());
    techBrowser->viewport()->setAutoFillBackground(false);

    connect(techCopyToClipboardButton, &QPushButton::clicked, this, &AboutDialogPrivate::copyToCliboardTechInfo);
    this->setAttribute(Qt::WA_DeleteOnClose);
    show();

}

QString AboutDialogPrivate::titleText() const
{
    return QStringLiteral("<div class=name>%1</div><div class=ver>%2</div>").arg(QStringLiteral("KOOMPI Onelab"),
                tr("Version: %1").arg(QStringLiteral("1.0.1")));

}

QString AboutDialogPrivate::aboutText() const
{
    return QStringLiteral(
        "<p>%1</p>"
        "<p>%2</p>"
        "<p>%3</p>"
        "<p>%4</p>"
        "<p>%5</p>"
        "<p>%6</p>"
        "<p>%7</p>"
        )
        .arg(
            tr("KOOMPI Onelab, together with KOOMPI, are value-added learning and productivity tools built upon the acclaimed Linux operating system and the Single Board RaspberryPi.",
               "About dialog, 'About' tab text"),
            tr("KOOMPI Onelab includes a wide variety of custom applications designed and supported to meet the needs of students and employees.",
               "About dialog, 'About' tab text"),
            tr("%1 © %2-%3", "About dialog, 'About' tab text")
                .arg(QStringLiteral("KOOMPI DevOps Team"), QStringLiteral("2020"), QDate::currentDate().toString(QStringLiteral("yyyy"))),
            tr("Homepage: %1", "About dialog, 'About' tab text")
                .arg(QStringLiteral("<a href=\"https://koompi.org\">https://koompi.org</a>")),
            tr("Wiki: %1", "About dialog, 'About' tab text")
                .arg(QStringLiteral("<a href=\"https://wiki.koompi.org\">https://wiki.koompi.org</a>")),
            tr("Development: %1", "About dialog, 'About' tab text")
                .arg(QStringLiteral("<a href=\"https://github.com/koompi/\">https://github.com/koompi</a>")),
            tr("License: %1", "About dialog, 'About' tab text")
                .arg(QStringLiteral("<a href=\"https://www.gnu.org/licenses/lgpl-2.1.html\">GNU Lesser General Public License version 2.1 or later</a>"
                     " and partly under the "
                     "<a href=\"https://www.gnu.org/licenses/gpl-2.0.html\">GNU General Public License version 2</a>"))
            );
}

QString AboutDialogPrivate::authorsText() const
{
    return QStringLiteral("<p>%1</p><p>%2</p>").arg(
                tr("KOOMPI OS is developed by the <a %1>KOOMPI Team and contributors</a>.", "About dialog, 'Authors' tab text")
                    .arg(QStringLiteral(" href=\"https://github.com/koompi\"")),
                tr("If you are interested in working with our development team, <a %1>join us</a>.", "About dialog, 'Authors' tab text")
                    .arg(QStringLiteral("href=\"https://github.com/orgs/koompi/people\""))
                );
}


QString AboutDialogPrivate::thanksText() const
{
    return QStringLiteral(
                "%1"
                "<ul>"
                "<li>LXQT and all its contributors &lt;<a href=\"https://lxqt.org/\">https://lxqt.org/</a>&gt;</li>"
                "<li>Brilliant PHAL (Technical Mentor)</li>"
                "<li>DevOps Teams</li>"
                "<li>KOOMPI &lt;<a href=\"https://koompi.org/\">https://koompi.org/</a>&gt;</li></li>"
                ).arg(tr("Special thanks to:", "About dialog, 'Thanks' tab text"));
}

// QString AboutDialogPrivate::translationsText() const
// {
//     TranslatorsInfo translatorsInfo;
//     return QStringLiteral("Coming Soon");
// }

AboutDialog::AboutDialog()
{
    d_ptr = new AboutDialogPrivate();
}

void AboutDialogPrivate::copyToCliboardTechInfo()
{
    TechnicalInfo info;
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(info.text());
}
