#pragma once

#include "connection.hpp"

#include <QTcpSocket>

class tcp_connection : public connection
{
	Q_OBJECT

public:
	explicit tcp_connection( const std::string&	 name,
							 script::engine::ptr ngn_ptr,
							 const QString&		 hostAddress,
							 quint16			 port,
							 QObject*			 parent = nullptr );
	~tcp_connection();

	bool
	connect_device() override;
	void
	disconnect_device() override;
	bool
	is_connected() const override;
	bool
	send_data( const QByteArray& data ) override;

	QString
	hostAddress() const;
	quint16
	port() const;

protected:
	sol::object
	make_lua_object_from_this() const override;
	void
	self_register() override;

private:
	QTcpSocket* m_socket;
	QString		m_hostAddress;
	quint16		m_port;

private slots:
	void
	on_ready_read();
	void
	on_socket_state_changed( QAbstractSocket::SocketState state );
	void
	on_socket_error( QAbstractSocket::SocketError error );
};

