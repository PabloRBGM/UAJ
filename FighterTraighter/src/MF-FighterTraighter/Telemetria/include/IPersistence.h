#pragma once
#include "ISerializer.h"
#include <queue>

class IPersistence
{
protected:
	/// <summary>
	/// Serializador de eventos
	/// </summary>
	ISerializer* serializer;
	
	/// <summary>
	/// Cola de eventos
	/// </summary>
	std::queue<TrackerEvent*> eventQueue;
public:
	virtual ~IPersistence() {}
	/// <summary>
	/// Inicializa el serializador
	/// </summary>
	virtual void init() = 0;
	/// <summary>
	/// Envia el evento a la cola de eventos 
	/// </summary>
	virtual void send(TrackerEvent* event) = 0;
	/// <summary>
	/// Vuelca los eventos tras serializarlos en "la persistencia" 
	/// </summary>
	virtual void flush() = 0;
};