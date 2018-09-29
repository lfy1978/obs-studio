#pragma once

#include <QDialog>
#include <QPointer>

namespace Ui {
	class OBSBasicLogin;
}

class OBSBasic;
class WebLoginThread;

class OBSBasicLogin : public QDialog
{
	Q_OBJECT

signals :
	void LoginSucceeded(const QString& data);
	void LoginToMainWindow(const QString& type, const QString& context);

public:
	explicit OBSBasicLogin(QWidget *parent = 0, const QString info = QString());
	~OBSBasicLogin();

private:
	OBSBasic *main;
	QPointer<WebLoginThread> loginThread;
	Ui::OBSBasicLogin *ui;
	bool loading = true;
	bool isClose = false;  // �ǵ���close�����رգ����ǵ��X��ť
	bool isDialog = true;  // �ǶԻ����½
    bool isAutoLogin = false;
    bool isStartWork = false;
	void ClearLogin();

	void LoadLogin();
	void SaveLogin();
	void WebLogin();
	void LoginEnd();
	void EncryptRotateMoveBit(char* dst, const int len, const int key);
    void NormalShow();
    void RemoteShow();

private slots:
	void on_btnRegister_clicked();
	void on_btnLogin_clicked();
	void on_cbxRememberPassword_StateChanged(int state);
    void on_cbxAutoLogin_StateChanged(int state);
	void loginFinished(const QString &text, const QString &error);

public Q_SLOTS:
    virtual int exec();
	virtual void done(int status);
	virtual void accept();
	virtual void reject();
	bool close();
};
