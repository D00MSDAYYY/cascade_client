#pragma once

#include "scripting.hpp"

#include <QByteArray>
#include <QObject>

class connection
	: public QObject
	, public scripting::object
{
	Q_OBJECT

public:
	explicit connection( const std::string&	 name,
						 const scripting::engine::ptr ngn_ptr,
						 QObject*			 parent = nullptr )
		: QObject( parent )
		, scripting::object( ngn_ptr )
	{
	}

	virtual ~connection() { }

	// Подключение к устройству
	virtual bool
	connect_device()
		= 0;
	// Отключение от устройства
	virtual void
	disconnect_device()
		= 0;
	// Проверка подключения
	virtual bool
	is_connected() const
		= 0;
	// Отправка данных
	virtual bool
	send_data( const QByteArray& data )
		= 0;

protected:
	virtual sol::object
	make_lua_object_from_this() const
		= 0;
	virtual void
	register_in_lua()
		= 0;
signals:
	// Сигнал о получении данных
	void
	data_received( const QByteArray& data );
	// Сигнал о изменении состояния подключения
	void
	connection_status_changed( bool connected );
	// Сигнал об ошибке
	void
	error_occurred( const QString& errorString );
};

