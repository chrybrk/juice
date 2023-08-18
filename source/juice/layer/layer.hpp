#pragma once

#include "event/event.hpp"
#include "core/timer.hpp"

namespace juice {

	class Layer
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float dt) {}
		virtual void OnEvent(Event& event) {}
	};

}
