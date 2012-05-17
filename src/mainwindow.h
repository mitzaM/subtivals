/**
  *  This file is part of Subtivals.
  *
  *  Subtivals is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  Subtivals is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with Subtivals.  If not, see <http://www.gnu.org/licenses/>
  **/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QList>
#include <QTime>
#include <QMap>
#include <QTableWidget>
#include <QModelIndex>
#include <QString>
#include <QFileSystemWatcher>
#include <QLabel>

#include "script.h"


#define COLUMN_START    0
#define COLUMN_END      1
#define COLUMN_STYLE    2
#define COLUMN_TEXT     3

class ConfigEditor;
class Player;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum State { NODATA, STOPPED, PLAYING, PAUSED};
    void openFile (const QString &p_fileName);
    void closeFile();
    bool eventFilter(QObject*, QEvent*);
    const ConfigEditor * configEditor();
    void showEvent(QShowEvent *);
signals:
    void eventStart(Event *p_event);
    void eventEnd(Event *p_event);
    void eventClear();
    void toggleHide(bool state);
    void screenResizable(bool state);
public slots:
    void refreshDurations();
    void actionDurationCorrection(bool);
    void actionShowCalibration(bool);
    void actionOpen();
    void actionPlay();
    void actionStop();
    void actionConfig(bool);
    void actionPause();
    void actionNext();
    void actionPrevious();
    void actionToggleHide(bool state = true);
    void actionAbout();
    void actionShowHelp();
    void playPulse(qint64 msecsElapsed);
    void eventChanged();
    void actionEnableReload(bool);
    void fileChanged(QString path);
    void reloadScript();
    void actionEventClic(QModelIndex);
    void actionEventSelected(QModelIndex);
    void enableEventSelection();
    void disableEventSelection();
    void search();
    void searchTextChanged(QString);
    void actionAutoHideEnded(bool);
protected:
    bool canNext();
    bool canPrevious();
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent* event);
    void closeEvent(QCloseEvent *);
    void jumpToSubtitle(int row);
    void highlightEvents(qlonglong elapsed);
    QString ts2tc(qint64 p_timestamp);
    void setState(State p_state);
private:
    State m_state;
    Ui::MainWindow *ui;
    Script *m_script;
    Player *m_player;
    QString m_lastScript;
    QString m_lastFolder;
    ConfigEditor* m_preferences;
    QMap<Event *, int> m_tableMapping;
    bool m_selectEvent;
    QTimer m_timerSelection;
    bool m_rowChanged;
    bool m_reloadEnabled;
    QFileSystemWatcher* m_filewatcher;
    QTimer m_timerFileChange;
    bool m_autoHideEnabled;
    QTimer m_timerAutoHide;
    QLabel* m_scriptProperties;
};

#endif // MAINWINDOW_H
