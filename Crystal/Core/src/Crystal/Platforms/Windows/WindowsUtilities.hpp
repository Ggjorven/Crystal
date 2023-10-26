#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/Utils.hpp"

#include <string>

namespace Crystal 
{

	class WindowsUtils : public Utils
	{
	public:
		// These return empty strings if cancelled

	private:
		virtual std::string OpenFileImplementation(const char* filter) override;
		virtual std::string SaveFileImplementation(const char* filter) override;

		virtual float GetTimeImplementation() override;
	};
}