#include "login_vm.h"

LoginVM::LoginVM(QObject *parent)
    : QObject{parent}
{
    InitVariable();
    ReadAccounts();
}


QString LoginVM::username()
{
    return _username;
}

int LoginVM::accessLevel()
{
    return _accessLevel;
}

QString LoginVM::loginInfo()
{
    return _loginInfo;
}

QString LoginVM::loginInfoColor()
{
    return _loginInfoColor;
}

bool LoginVM::isLogin()
{
    return _isLogin;
}


void LoginVM::InitVariable()
{
    setUsername("None");
    setAccessLevel(ACCOUNT_LEVEL::NONE);
    UpdateUserAccessLevel("None", ACCOUNT_LEVEL::NONE);
    qh_accounts = {};
}

void LoginVM::ReadAccounts()
{
    QString path = ConfigApplication::instance()->m_strAccountPath;
    QFile file(path);
    if(!file.exists())
    {
        // create default account // создать учетную запись по умолчанию
        qh_accounts["engineer"] = AccountInfo{"engineer", "V_XZ_VVc25>?", ACCOUNT_LEVEL::ADMINISTRATOR};
        WriteAccounts();
    }
    else
    {
        QString line;
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            line = in.readAll();
            file.close();
        }
        QStringList accountStr = line.split("\n");
        for(int i = 0; i < accountStr.count(); i++)
        {
           if(accountStr[i].contains("[User", Qt::CaseInsensitive))
           {
                AccountInfo accountInfo;
                accountInfo.user = accountStr[++i].split("=")[1];
                accountInfo.level =  (ACCOUNT_LEVEL)(accountStr[++i].split("=")[1].toInt());
                accountInfo.pwd = accountStr[++i].split("=")[1];
                qh_accounts[accountInfo.user] = accountInfo;
           }
        }
    }
}

void LoginVM::WriteAccounts()
{
    QString path = ConfigApplication::instance()->m_strAccountPath;
    QFile file(path);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream( &file );
        stream << "[NUM USER]\n";
        stream << "NoOfUsers=" + QString::number(qh_accounts.count()) + "\n";
        stream << "\n";

        int i = 0;
        foreach(AccountInfo account, qh_accounts)
        {
            stream << QString("[User" + QString::number(i) + "]") + "\n";
            stream << QString("Name=" + QString(account.user)) + "\n";
            stream << QString("Level=" + QString::number(account.level)) + "\n";
            stream << QString("pswd=" + QString(account.pwd)) + "\n";
            stream << "\n";
            i++;
        }
    }
    file.close();
}

QString LoginVM::EncryptPass(QString password)
{
    QString encryptPassword = "";
    password += "ADMN";
    for (auto c: password)
    {
        encryptPassword += QString((char)((int)(c.toLatin1()) - 15));
    }
    return encryptPassword;
}

bool LoginVM::CheckUserName(QString userName)
{
    if(userName == "")
        return false;
    foreach(AccountInfo account, qh_accounts)
    {
        if(account.user == userName)
            return true;
    }
    return false;
}

QString LoginVM::GetPassword(QString userName)
{
    foreach(AccountInfo account, qh_accounts)
    {
        if(account.user == userName)
            return account.pwd;
    }
    return "";
}

AccountInfo LoginVM::GetUserRow(QString userName)
{
    foreach(AccountInfo account, qh_accounts)
    {
        if(account.user == userName)
            return account;
    }
    AccountInfo account;
    return account;
}

void LoginVM::UpdateUserAccessLevel(QString user, ACCOUNT_LEVEL level)
{
    ConfigApplication::instance()->m_strCurrentAccountName = user;
    setUsername(user);
    QString accessLevel = "None";
    if(level == ACCOUNT_LEVEL::ADMINISTRATOR)
    {
        accessLevel = "Administrator";
        ConfigApplication::instance()->m_strcCurrentAccountLevel = ACCOUNT_LEVEL::ADMINISTRATOR;
        setIsLogin(true);
    }
    else if(level == ACCOUNT_LEVEL::ENGINEER)
    {
        accessLevel = "Engineer";
        ConfigApplication::instance()->m_strcCurrentAccountLevel = ACCOUNT_LEVEL::ENGINEER;
        setIsLogin(false);
    }
    else if(level == ACCOUNT_LEVEL::OPERATOR)
    {
        accessLevel = "Operator";
        ConfigApplication::instance()->m_strcCurrentAccountLevel = ACCOUNT_LEVEL::OPERATOR;
        setIsLogin(false);
    }
    else
    {
        ConfigApplication::instance()->m_strcCurrentAccountLevel = ACCOUNT_LEVEL::NONE;
        setIsLogin(false);
    }
    setAccessLevel(ConfigApplication::instance()->m_strcCurrentAccountLevel);

}

void LoginVM::createNewUser_Slots(QString user, QString pwd, QString confirmPwd, int level)
{
    qDebug() << user << pwd << confirmPwd << level;
    if(user == "")
    {
        setLoginInfo("Type your Username !");
        setLoginInfoColor("red");
        return;
    }
    if(CheckUserName(user))
    {
        setLoginInfo("Username is exist! Type another Username");
        setLoginInfoColor("red");
        return;
    }
    if (pwd != confirmPwd)
    {
        setLoginInfo("Password and Confirm password is not match! Check again.");
        setLoginInfoColor("red");
        return;
    }
    AccountInfo account;
    account.user = user;
    account.level = (ACCOUNT_LEVEL)level;
    account.pwd = EncryptPass(pwd);
    qh_accounts[user] = account;
    WriteAccounts();

    setLoginInfo("Created new account Username: " + user);
    setLoginInfoColor("green");

//    EventLogVM::instance()->AddEventLog("[Login/Out]:   Created new account username: " + user + " with level: " +
//                                        ConfigApplication::instance()->ConvertAccountLevelToString(account.level));


    return;
}

void LoginVM::setUsername(QString value)
{
    if(_username != value){_username = value; emit usernameChanged();}

}

void LoginVM::setAccessLevel(int value)
{
    if(_accessLevel != value){_accessLevel = value; emit accessLevelChanged();}
}

void LoginVM::setLoginInfo(QString value)
{
    if(_loginInfo != value)
    {
        _loginInfo = value;
        emit loginInfoChanged();
    }
}

void LoginVM::setLoginInfoColor(QString value)
{
    if(_loginInfoColor != value)
    {
        _loginInfoColor = value;
        emit loginInfoColorChanged();
    }
}

void LoginVM::setIsLogin(bool value)
{
    if(_isLogin != value)
    {
        _isLogin = value;
        emit isLoginChanged();
    }
}


void LoginVM::login_Slots(QString user, QString pwd)
{

    if(user == "")
    {
        setLoginInfo("Type your Username !");
        setLoginInfoColor("red");
        return;
    }
    QString pw = EncryptPass(pwd);
    if(!CheckUserName(user))
    {
        setLoginInfo("Username is wrong !");
        setLoginInfoColor("red");
        return;
    }
    else if(pw == GetPassword(user))
    {
        qDebug() << "Login Success";
        AccountInfo account = GetUserRow(user);
        UpdateUserAccessLevel(user, account.level);
        emit login_Signals(true);
        emit closeLoginDialog_Qml_Signals();
        ConfigApplication::instance()->WriteDebugLog("Login", user);
    }
    else
    {
        setLoginInfo("Password is wrong !");
        setLoginInfoColor("red");
    }
    qDebug() << user << pwd << pw;

}

void LoginVM::logout_Slots()
{
    if(username() == "None")
        return;
    UpdateUserAccessLevel("None", ACCOUNT_LEVEL::NONE);
    emit login_Signals(false);
    ConfigApplication::instance()->WriteDebugLog("Login", "Logout");
    qDebug() << "LogOut";
}

