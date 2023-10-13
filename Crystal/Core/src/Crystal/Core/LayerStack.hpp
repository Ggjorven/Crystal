#pragma once

#include <vector>

#include "Crystal/Core/Core.hpp"

#include "Crystal/Core/Layer.hpp"

namespace Crystal
{

	class LayerStack
	{
	public:
		LayerStack();
		virtual ~LayerStack();

		void AddLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void AddOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator				begin()				{ return m_Layers.begin(); }
		std::vector<Layer*>::iterator				end()				{ return m_Layers.end(); }
		std::vector<Layer*>::const_iterator			begin()		const	{ return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator			end()		const	{ return m_Layers.end(); }

		std::vector<Layer*>::reverse_iterator		rbegin()			{ return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator		rend()				{ return m_Layers.rend(); }
		std::vector<Layer*>::const_reverse_iterator rbegin()	const	{ return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend()		const	{ return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_InsertIndex;
	};

}