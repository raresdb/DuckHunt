#pragma once

#include "core/gpu/mesh.h"
#include "2DObject.h"

#define HEAD_COLOR glm::vec3(0.2, 0.35, 0.2)
#define MAIN_COLOR glm::vec3(0.35, 0.25, 0.15)
#define BEAK_COLOR glm::vec3(0.9, 0.8, 0.2)
#define WING_COLOR glm::vec3(0.2, 0.2, 0.1)

#define INITIAL_SPEED 400
#define ESCAPE_SPEED 500
#define WING_SPEED_RATION 0.01
#define WING_ANGLE M_PI / 2
#define INITIAL_MAX_ALIVE_TIME 5
#define FALL_ACCELERATION 1000

namespace bird {
	class Birdy {

	public:
		Mesh* leftWing;
		Mesh* rightWing;
		Mesh* body;

		glm::mat3 bodyMatrix;
		glm::mat3 leftWingMatrix;
		glm::mat3 rightWingMatrix;

		/* Generates the meshes for the bird
			Meshes are named birdy, birdyLeftWing and birdyRightWing */
		Birdy(glm::ivec2 resolution);

		// Updates the matrix models
		void MatrixUpdate(float deltaTimeSeconds);

		// Generates the matrices for the initial position of a new bird
		void InitialGeneration();

		// Manages the movement of the bird
		void Move(float deltaTimeSeconds);

		// Manages the escape routine for the bird
		void Escape(float deltaTimeSeconds);

		// Manages the routing for death of the bird
		void DropDead(float deltaTimeSeconds);

		// Manages the routine of shooting
		void try_shoot(glm::vec2 position);

		// Returns whether the current bird has escaped
		bool isEscaped();

		// Returns whether the current bird is dead
		bool isDead();

		// Manages the escaped ducks and resets the number
		unsigned ManageEscapedDucks();

		// Manages the respawn
		bool ManageRespawn();

		// Getter for bird index
		unsigned getIndex();

	private:
		// screen resolution
		glm::ivec2 resolution;

		double wingAngle;;
		double bodyAngle;
		bool wingDirection;
		unsigned speed;
		float aliveTime;
		bool alive;
		bool escaped;
		double fallSpeed;
		unsigned unmanaged_escaped_ducks;
		bool unmanaged_respawn;

		// marks which bird is rendered -> increases only when a bird dies
		unsigned index;

		// marks the location of the left peak of the body triangle before rotation
		glm::vec3 location;
	};
}