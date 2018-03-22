
#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QCanBusDevice>

#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui {
class ConnectDialog;
}

class QIntValidator;

QT_END_NAMESPACE

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    typedef QPair<QCanBusDevice::ConfigurationKey, QVariant> ConfigurationItem;

    struct Settings {
        QString backendName;
        QString deviceInterfaceName;
        QList<ConfigurationItem> configurations;
        bool useConfigurationEnabled;
    };

    explicit ConnectDialog(QWidget *parent = nullptr);
    ~ConnectDialog();

    Settings settings() const;

private slots:
    void checkCustomSpeedPolicy(int idx);
    void backendChanged(const QString &backend);
    void ok();
    void cancel();

private:
    QString configurationValue(QCanBusDevice::ConfigurationKey key);
    void revertSettings();
    void updateSettings();
    void fillBackends();
    void fillSpeeds();

private:
    Ui::ConnectDialog *m_ui;
    QIntValidator *m_customSpeedValidator;
    Settings m_currentSettings;
};

#endif // CONNECTDIALOG_H
