#include "InputControlManager.h"

#include "Binding/Binding_Keyboard_Button.h"
#include "Binding/Binding_Mouse.h"

#include "Action/InputAction_Void.h"
#include "Action/InputAction_Bool.h"
#include "Action/InputAction_Float.h"
#include "Action/InputAction_Vector2f.h"

Input::InputControlManager::InputControlManager()
{
	//Setup all actions and bindings here
	//	{
	//	Profile
			//Actions
				//Bindings
	//	}
	
	//Camera
	{
		auto& profile = CreateProfile("Camera");
		
		//Thrust
		{
			auto& move = profile.CreateAction_Vector2("Thrust");
			move.AddProcess_Normalize();
			{
				Binding_Keyboard_Button& button = move.CreateBinding<Binding_Keyboard_Button>("W");
				button.SetInteraction_Hold();
				button.SetButtons({ Input::KeyCode::W });
				button.SetModification(Input::Binding_Keyboard_Button::Vector2Modification::Y);
			}
			{
				Binding_Keyboard_Button& button = move.CreateBinding<Binding_Keyboard_Button>("S");
				button.SetInteraction_Hold();
				button.SetButtons({ Input::KeyCode::S });
				button.SetModification(Input::Binding_Keyboard_Button::Vector2Modification::Y);
				button.Inverse();
			}
			{
				Binding_Keyboard_Button& button = move.CreateBinding<Binding_Keyboard_Button>("A");
				button.SetInteraction_Hold();
				button.SetButtons({ Input::KeyCode::A });
				button.SetModification(Input::Binding_Keyboard_Button::Vector2Modification::X);
				button.Inverse();
			}
			{
				Binding_Keyboard_Button& button = move.CreateBinding<Binding_Keyboard_Button>("D");
				button.SetInteraction_Hold();
				button.SetButtons({ Input::KeyCode::D });
				button.SetModification(Input::Binding_Keyboard_Button::Vector2Modification::X);
			}
		}

		//UpDown
		{
			auto& upDown = profile.CreateAction_Float("UpDown");
			{
				Binding_Keyboard_Button& button = upDown.CreateBinding<Binding_Keyboard_Button>("Space");
				button.SetButtons({ Input::KeyCode::Space });
				button.SetInteraction_Hold();
			}
			{
				Binding_Keyboard_Button& button = upDown.CreateBinding<Binding_Keyboard_Button>("Ctrl");
				button.SetButtons({ Input::KeyCode::Ctrl });
				button.SetInteraction_Hold();
				button.Inverse();
			}
		}

		//Sprint
		{
			auto& sprint = profile.CreateAction_Bool("Sprint");
			{
				Binding_Keyboard_Button& button = sprint.CreateBinding<Binding_Keyboard_Button>("Shift");
				button.SetButtons({ Input::KeyCode::Shift });
				button.SetInteraction_Hold();
			}
		}

		//Rotating
		{
			auto& rotating = profile.CreateAction_Vector2("Rotating");
			{
				auto& move = rotating.CreateBinding<Binding_Mouse>("Rotating");
				move.SetReturnDelta();
				move.SetInteraction_Hold(0.1f);
				move.SetButtons({ KeyCode::MouseRightButton });
			}
		}
	}

	//Debug
	{
		auto& profile = CreateProfile("Debug");
		{
			{
				auto& togglePlayer = profile.CreateAction_Bool("ToggleCamera");
				{
					auto& button = togglePlayer.CreateBinding<Binding_Keyboard_Button>("Z");
					button.SetInteraction_Press();
					button.SetButtons({ Input::KeyCode::Z });
				}

				auto& toggleDefault = profile.CreateAction_Bool("ToggleDefault");;
				{
					auto& button = toggleDefault.CreateBinding<Binding_Keyboard_Button>("ToggleDefault");
					button.SetInteraction_Press();
					button.SetButtons({ Input::KeyCode::Shift, Input::KeyCode::One });
				}

				auto& toggleWireFrame = profile.CreateAction_Bool("ToggleWireFrame");;
				{
					auto& button = toggleWireFrame.CreateBinding<Binding_Keyboard_Button>("ToggleWireFrame");
					button.SetInteraction_Press();
					button.SetButtons({ Input::KeyCode::Shift, Input::KeyCode::Two });
				}

				auto& toggleAlbedo = profile.CreateAction_Bool("ToggleAlbedo");;
				{
					auto& button = toggleAlbedo.CreateBinding<Binding_Keyboard_Button>("ToggleAlbedo");
					button.SetInteraction_Press();
					button.SetButtons({ Input::KeyCode::Shift, Input::KeyCode::Three });
				}

				auto& toggleNormal = profile.CreateAction_Bool("ToggleNormal");;
				{
					auto& button = toggleNormal.CreateBinding<Binding_Keyboard_Button>("ToggleNormal");
					button.SetInteraction_Press();
					button.SetButtons({ Input::KeyCode::Shift, Input::KeyCode::Four });
				}

				auto& toggleNormalMap = profile.CreateAction_Bool("ToggleNormalMap");;
				{
					auto& button = toggleNormalMap.CreateBinding<Binding_Keyboard_Button>("ToggleNormalMap");
					button.SetInteraction_Press();
					button.SetButtons({ Input::KeyCode::Shift, Input::KeyCode::Five });
				}

				auto& toggleSpecular = profile.CreateAction_Bool("ToggleSpecular");;
				{
					auto& button = toggleSpecular.CreateBinding<Binding_Keyboard_Button>("ToggleSpecular");
					button.SetInteraction_Press();
					button.SetButtons({ Input::KeyCode::Shift, Input::KeyCode::Six });
				}

				auto& toggleDiffus = profile.CreateAction_Bool("ToggleDiffus");;
				{
					auto& button = toggleDiffus.CreateBinding<Binding_Keyboard_Button>("ToggleDiffus");
					button.SetInteraction_Press();
					button.SetButtons({ Input::KeyCode::Shift, Input::KeyCode::Seven });
				}


				auto& exitGame = profile.CreateAction_Bool("EndGame");
				exitGame.AddProcess_Invert();
				{
					auto& button = exitGame.CreateBinding<Binding_Keyboard_Button>("Esc");
					button.SetInteraction_Press();
					button.SetButtons({ Input::KeyCode::Escape });
				}
			}
		}
	}
}

Input::InputControlManager::~InputControlManager()
{
	auto actions = myProfiles.begin();
	while (actions != myProfiles.end())
	{
		delete actions->second;
		actions = myProfiles.erase(actions);
	}
}

Input::InputProfile& Input::InputControlManager::CreateProfile(const std::string& aID)
{
	auto find = myProfiles.find(aID);

	if (find != myProfiles.end())
	{
		return *find->second;
	}

	myProfiles[aID] = new InputProfile();
	return *myProfiles[aID];
}

Input::InputProfile& Input::InputControlManager::GetProfile(const std::string& aID) const
{
	auto find = myProfiles.find(aID);

	if (find == myProfiles.end())
	{
		throw;
	}

	return *find->second;
}

Input::InputProfile& Input::InputControlManager::operator[](const std::string& aID) const
{
	return GetProfile(aID);
}


void Input::InputControlManager::Update(const float someDeltaTime) const
{
	auto profileIT = myProfiles.begin();
	InputProfile* profile = nullptr;

	while (profileIT != myProfiles.end())
	{
		profile = profileIT->second;

		profile->Update(someDeltaTime);
		profileIT++;
	}
}
