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

class RemoteDataThread : public QThread {
	Q_OBJECT

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
	inline RemoteDataThread(
		std::string url_,
		std::string content_type_ = std::string()
	)
		: url(url_), content_type(content_type_)
	{};

	// ����urlencode����Щ�ӿڲ�ͨ��
	static size_t MyUrlEncode(void* dst, size_t& dst_len, const void* src, size_t len);
	// �����ڴ��������
	bool PrepareData(const std::string& name, const std::string& data);
	bool PrepareData(const std::string& name, void* data, size_t data_size);
	bool PrepareDataFromFile(const std::string& name, const std::string& filename);
};
