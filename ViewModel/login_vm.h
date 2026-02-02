#ifndef LOGINVM_H
#define LOGINVM_H

#include <QObject>
#include "../Script/Define/struct_def.h"
#include "../Script/Config/config_application.h"

struct AccountInfo
{
    QString user;
    QString pwd;
    ACCOUNT_LEVEL level;
};

Q_DECLARE_METATYPE(AccountInfo)

class LoginVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(int accessLevel READ accessLevel WRITE setAccessLevel NOTIFY accessLevelChanged)
    Q_PROPERTY(QString loginInfo READ loginInfo WRITE setLoginInfo NOTIFY loginInfoChanged)
    Q_PROPERTY(QString loginInfoColor READ loginInfoColor WRITE setLoginInfoColor NOTIFY loginInfoColorChanged)
    Q_PROPERTY(bool isLogin READ isLogin WRITE setIsLogin NOTIFY isLoginChanged)

public:
    explicit LoginVM(QObject *parent = nullptr);

    //property //собственность
    QString username();
    int accessLevel();
    QString loginInfo();
    QString loginInfoColor();
    bool isLogin();
    //end //конец
    QHash<QString, AccountInfo> qh_accounts;

    void InitVariable();


private:
    //property собственность
    QString _username;
    int _accessLevel;
    QString _loginInfo;
    QString _loginInfoColor;
    bool _isLogin;
    //end //конец

    void ReadAccounts();
    void WriteAccounts();
    QString EncryptPass(QString);
    bool CheckUserName(QString userName);
    QString GetPassword(QString userName);
    AccountInfo GetUserRow(QString userName);
    void UpdateUserAccessLevel(QString user, ACCOUNT_LEVEL level);

signals:
    //property собственность
    void usernameChanged();
    void accessLevelChanged();
    void loginInfoChanged();
    void loginInfoColorChanged();
    bool isLoginChanged();
    //end //конец

    void login_Signals(bool);
    void closeLoginDialog_Qml_Signals();

public slots:
    //property собственность
    void setUsername(QString);
    void setAccessLevel(int);
    void setLoginInfo(QString);
    void setLoginInfoColor(QString);
    void setIsLogin(bool);
    //end //конец

    void login_Slots(QString, QString);
    void logout_Slots();
    void createNewUser_Slots(QString, QString, QString, int);

};

#endif // LOGINVM_H
