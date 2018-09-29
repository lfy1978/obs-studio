#pragma once

#include <QThread>
#include <string>

#ifndef DATA_BUFFER_
#define DATA_BUFFER_
typedef struct data_buffer_ {
	char *readptr;     // ������д����͵�����
	char *delptr;      // ������ݵ�ԭʼ�ڴ�ָ���ַ���ͷ��ڴ�ʹ��
	size_t data_size;  // ���������ݵĳ���
	data_buffer_() {
		memset(this, 0, sizeof(DATA_BUFFER));
	}
}DATA_BUFFER, *PDATA_BUFFER;
#endif

class RemotePostThread : public QThread {
	Q_OBJECT

private:
	std::string ticks;    // ʱ���
	std::string boundary; // 
	std::string ContentLength;

private:
	std::string url;
	std::string content_type;
	DATA_BUFFER data_buffer;
	
	// ��ȡurl����� response ͷ����Ϣ
	static size_t WriteBodyCallback(char *ptr, size_t size, size_t nmemb, std::string &str);
	// ��ȡurl����� response [ͷ�� + ����] ��Ϣ
	static size_t WriteHeaderCallback(char *ptr, size_t size, size_t nmemb, std::string &str);
	// ��url����д��request�� post ����
	static size_t ReadCallback(void *ptr, size_t size, size_t nmemb, void *userp);

signals:
	void Result(const QString& header, const QString& body, const QString& error);

protected:
	void run() override;

public:
	inline RemotePostThread(
		std::string url_,
		std::string content_type_ = std::string()
	)
		: url(url_), content_type(content_type_)
	{};

	// �����ڴ��������
	bool PrepareDataHeader();
	bool PrepareData(const std::string& name, const std::string& value);
	bool PrepareDataFromFile(const std::string& name, const std::string& filename);
	bool PrepareDataFoot(bool isFile = false);
};
