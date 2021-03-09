#include "TKB_InputGetter.hpp"
#include <iostream>

namespace tickerable
{
	namespace tasks
	{
		void InputGetter::onEnable() 
		{
		
		}

		void InputGetter::onDisable() 
		{
		
		}

		void InputGetter::Tick(const double& delta_t, const std::vector<Task*>& taskList) 
		{
			//copy inputs

			view.x = aView.x;
			view.y = aView.y;
			view.z = aView.z;

			direction.x = aDirection.x;
			direction.y = aDirection.y;
			direction.z = aDirection.z;

			position.x = aPosition.x;
			position.y = aPosition.y;
			position.z = aPosition.z;
		}

		void InputGetter::setView(glm::vec3 v) 
		{
			aView.x = v.x;
			aView.y = v.y;
			aView.z = v.z;
		}

		void InputGetter::setDirection(glm::vec3 v) 
		{
			aDirection.x = v.x;
			aDirection.y = v.y;
			aDirection.z = v.z;
		}

		void InputGetter::setPosition(double x, double y, double z) 
		{
			aPosition.x = x;
			aPosition.y = y;
			aPosition.z = z;
		}

		const inputGetterTypes::Vec3<double>& InputGetter::getPosition() 
		{
			return position;
		}

		const inputGetterTypes::Vec3<float>& InputGetter::getView() 
		{
			return view;
		}

		const inputGetterTypes::Vec3<float>& InputGetter::getDirection() 
		{
			return direction;
		}

	}
}