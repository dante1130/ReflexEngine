#pragma once

#include "PhysicResolution.hpp"


class ReactResolve: public PhysicResolution{
	public:

		//ReactResolve();
	
		//using engine stuff
		bool usingReactResolve() override;

		// init setup
	    void init(glm::vec3 rot, glm::vec3 pos, float angle) override;

		//Change movement properties
		void addForce(glm::vec3 force, Apply type) override;
	    void addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type) override;
	    void addTorque(glm::vec3 torque, Apply type) override;

	    void addDragForce(float drag) override;
	    void addDragTorque(float ang_drag) override;

		//Set properties
		void setMass(float mass) override;
	    void setCenterOfMass(glm::vec3 p) override;
	    void setVelocity(glm::vec3 vel) override;
	    void setAngVelocity(glm::vec3 ang_vel) override;

		//makes it a trigger
	    void setIsTrigger(bool ean);
};