#include <QObject>

class QDBusInterface;
class GConfItem;
class QDBusMessage;
class AutoAnswer : public QObject
{
    Q_OBJECT
public:
    AutoAnswer();

public slots:
    void csdStatusUpdate(uint, uint, uint);

private slots:
    void updateActiveKeyValue();
    void updateDelayKeyValue();
    void takeCall();

private:

    QDBusInterface *csdIface;
    GConfItem *activeKey;
    GConfItem *delayKey;

    bool autoAnswering;
    int delayTime;
};
