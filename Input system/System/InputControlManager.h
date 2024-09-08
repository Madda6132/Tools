#pragma once
#include <string>
#include <vector>

#include "InputProfile.h"

namespace Sunder
{
	class Engine;
}

namespace Input
{
	class InputControlManager
	{
	public:
		friend class Sunder::Engine;

		InputProfile& CreateProfile(const std::string& aID);
		inline InputProfile& GetProfile(const std::string& aID) const;

		InputProfile& operator[](const std::string& aID) const;

	private:
		std::map<std::string, InputProfile*> myProfiles;

		InputControlManager();
		~InputControlManager();

		void Update(const float someDeltaTime) const;

	};
}

