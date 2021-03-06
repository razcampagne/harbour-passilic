/*
 *   Copyright (C) 2018  Daniel Vrátil <dvratil@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef PASSWORDPROVIDER_H_
#define PASSWORDPROVIDER_H_

#include <QObject>
#include <QTimer>

class QProcess;

class PasswordsModel;

class PasswordProvider : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString password READ password NOTIFY passwordChanged)
    Q_PROPERTY(bool valid READ isValid NOTIFY validChanged)
    Q_PROPERTY(int timeout READ timeout NOTIFY timeoutChanged)
    Q_PROPERTY(int defaultTimeout READ defaultTimeout CONSTANT)
    Q_PROPERTY(bool hasError READ hasError NOTIFY errorChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
public:
    ~PasswordProvider() override;

    QString password() const;
    bool isValid() const;
    int timeout() const;
    int defaultTimeout() const;
    bool hasError() const;
    QString error() const;

public Q_SLOTS:
    void requestPassword();
    void cancel();
    void setPassphrase(const QString &passphrase);
    void expirePassword();

Q_SIGNALS:
    void passwordChanged();
    void validChanged();
    void timeoutChanged();
    void errorChanged();

private:
    void setError(const QString &error);
    void setPassword(const QString &password);

    void removePasswordFromClipboard(const QString &password);
    void clearClipboard();

    friend class PasswordsModel;
    explicit PasswordProvider(const QString &path, QObject *parent = nullptr);

    QString mPath;
    QString mPassword;
    QString mError;
    QTimer mTimer;
    int mTimeout = 0;
};

#endif
