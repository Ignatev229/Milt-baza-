#ifndef DIALOGVM_H
#define DIALOGVM_H

#include <QObject>

class DialogVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)


public:
    explicit DialogVM(QObject *parent = nullptr);
    static DialogVM * instance();

    void ShowDialog(QString, QString, int iconIndex);
    // Property //  Собственность
    QString title();
    QString content();
    //

private:
    // Property //  Собственность
    QString _title;
    QString _content;
    //

signals:
    // Property //  Собственность
    void titleChanged();
    void contentChanged();
    //

    void openMessageInfo_Signal(int iconIndex);

public slots:
    // Property //  Собственность
    void setTitle(QString);
    void setContent(QString);
    //

};

#endif // DIALOGVM_H
