#include "Birdy.h"

using namespace bird;
using namespace std;


Birdy::Birdy(glm::ivec2 resolution) {
	pair<vector<VertexFormat>, unsigned int> mainBody;
	pair<vector<VertexFormat>, unsigned int> head;
	pair<vector<VertexFormat>, unsigned int> beak;
	pair<vector<VertexFormat>, unsigned int> lWing;
	pair<vector<VertexFormat>, unsigned int> rWing;

	vector<VertexFormat> vertices;
	unsigned indices_number;

	this->resolution = resolution;

	location = glm::vec3(0, 0, 0);
	wingAngle = 0;
	bodyAngle = 0;
	wingDirection = true;
	speed = INITIAL_SPEED;
	index = 0;
	unmanaged_escaped_ducks = 0;

	mainBody = obj::Object2D::Triangle(location, location + glm::vec3(50, 0, 0),
		location + glm::vec3(25, 100, 0), MAIN_COLOR);
	head = obj::Object2D::Circle(location + glm::vec3(25, 100, 0), 30, HEAD_COLOR);
	beak = obj::Object2D::Triangle(location + glm::vec3(15, 120, 0), location + glm::vec3(25, 150, 0),
		location + glm::vec3(35, 120, 0), BEAK_COLOR);

	
	vertices.reserve(mainBody.first.size() + head.first.size() + beak.first.size());
	vertices.insert(vertices.end(), head.first.begin(), head.first.end());
	vertices.insert(vertices.end(), mainBody.first.begin(), mainBody.first.end());
	vertices.insert(vertices.end(), beak.first.begin(), beak.first.end());
	indices_number = mainBody.second + head.second + beak.second;

	lWing = obj::Object2D::Triangle(location + glm::vec3(25, 30, 0), location + glm::vec3(25, 50, 0),
		location + glm::vec3(-40, 40, 0), WING_COLOR);
	rWing = obj::Object2D::Triangle(location + glm::vec3(25, 30, 0), location + glm::vec3(25, 50, 0),
		location + glm::vec3(90, 40, 0), WING_COLOR);
	
	leftWing = obj::Object2D::CreateMesh("birdyLeftWing", lWing.first, lWing.second);
	rightWing = obj::Object2D::CreateMesh("birdyRightWing", rWing.first, lWing.second);
	body = obj::Object2D::CreateMesh("birdy", vertices, indices_number);
}

void Birdy::MatrixUpdate(float deltaTimeSeconds) {
	aliveTime += deltaTimeSeconds;

	if (isDead())
		DropDead(deltaTimeSeconds);
	else if (isEscaped())
		Escape(deltaTimeSeconds);
	else
		Move(deltaTimeSeconds);

	// body
	bodyMatrix = glm::mat3(1);
	bodyMatrix *= tr2D::Translate(location.x, location.y);
	bodyMatrix *= tr2D::Translate(25, 0);
	bodyMatrix *= tr2D::Rotate(bodyAngle);
	bodyMatrix *= tr2D::Translate(-25, 0);

	// wings
	// wing movement for birds flying animation
	if (wingDirection) {
		if (wingAngle >= WING_ANGLE / 2) {
			wingAngle -= speed * WING_SPEED_RATION * deltaTimeSeconds;
			wingDirection = false;
		}
		else
			wingAngle += speed * WING_SPEED_RATION * deltaTimeSeconds;
	}
	else {
		if (wingAngle <= -WING_ANGLE / 2) {
			wingAngle += speed * WING_SPEED_RATION * deltaTimeSeconds;
			wingDirection = true;
		}
		else
			wingAngle -= speed * WING_SPEED_RATION * deltaTimeSeconds;
	}

	// Matrix generation
	leftWingMatrix = glm::mat3(1);
	rightWingMatrix = glm::mat3(1);

	leftWingMatrix *= tr2D::Translate(location.x , location.y);
	rightWingMatrix *= tr2D::Translate(location.x, location.y);

	leftWingMatrix *= tr2D::Translate(25, 0);
	rightWingMatrix *= tr2D::Translate(25, 0);

	leftWingMatrix *= tr2D::Rotate(bodyAngle);
	rightWingMatrix *= tr2D::Rotate(bodyAngle);

	leftWingMatrix *= tr2D::Translate(-25, 0);
	rightWingMatrix *= tr2D::Translate(-25, 0);

	leftWingMatrix *= tr2D::Translate(25, 40);
	rightWingMatrix *= tr2D::Translate(25, 40);

	if (isDead()) {
		leftWingMatrix *= tr2D::Rotate(WING_ANGLE / 2);
		rightWingMatrix *= tr2D::Rotate(-WING_ANGLE / 2);
	}
	else {
		leftWingMatrix *= tr2D::Rotate(wingAngle);
		rightWingMatrix *= tr2D::Rotate(-wingAngle);
	}

	leftWingMatrix *= tr2D::Translate(-25, -40);
	rightWingMatrix *= tr2D::Translate(-25, -40);
}

void Birdy::InitialGeneration() {
	srand(time(0) * 75);

	bodyAngle = pow(-1, rand()) * (M_PI / 8 + M_PI / 24 * (rand() % 7));
	location = glm::vec3(50 + rand() % (resolution.x - 100), 0, 0);
	aliveTime = 0;
	alive = true;
	fallSpeed = 0;
	escaped = false;
	unmanaged_respawn = true;
}

void Birdy::Move(float deltaTimeSeconds) {
	// body

	// position for the center of the head
	glm::vec3 head_pos = location + glm::vec3(25 * cos(bodyAngle), 25 * sin(bodyAngle), 0) +
		+glm::vec3(100 * cos(bodyAngle + M_PI / 2), 100 * sin(bodyAngle + M_PI / 2), 0);

	// checking bounds for bouncing
	if (head_pos.x >= resolution.x) {
		location.x = resolution.x - sin(bodyAngle) * 30;
		bodyAngle = -bodyAngle;
	}
	else if (head_pos.x <= 0) {
		location.x = -sin(bodyAngle) * 30;
		bodyAngle = -bodyAngle;
	}
	else if (head_pos.y >= resolution.y) {
		location.y = resolution.y + cos(bodyAngle) * 30;
		bodyAngle = M_PI - bodyAngle;
	}
	else if (head_pos.y <= 0) {
		location.y = cos(bodyAngle) * 30;
		bodyAngle = M_PI - bodyAngle;
	}
	// plain forward movement
	else {
		location += glm::vec3(speed * cos(bodyAngle + M_PI / 2) * deltaTimeSeconds,
			speed * sin(bodyAngle + M_PI / 2) * deltaTimeSeconds, 0);
	}
}

bool Birdy::isEscaped() {
	if (!escaped && aliveTime >= INITIAL_MAX_ALIVE_TIME * INITIAL_SPEED / speed) {
		escaped = true; 
		unmanaged_escaped_ducks++;
	}

	return escaped;
}

bool Birdy::isDead() {
	return !alive;
}

void Birdy::Escape(float deltaTimeSeconds) {
	bodyAngle = 0;

	if (location.y >= resolution.y) {
		InitialGeneration();
	}
	else {
		location.y += ESCAPE_SPEED * deltaTimeSeconds;
	}
}

void Birdy::try_shoot(glm::vec2 position) {
	if (isDead() || isEscaped())
		return;

	double x = (position.x - location.x) * cos(-bodyAngle) - (resolution.y -
		position.y - location.y) * sin(-bodyAngle);
	double y = (position.x - location.x) * sin(-bodyAngle) + (resolution.y -
		position.y - location.y) * cos(-bodyAngle);

	if (y >= 0 && y <= 150 && x >= -40 && x <= 50)
		alive = false;
}

void Birdy::DropDead(float deltaTimeSeconds) {
	bodyAngle = M_PI;

	if (location.y <= 0) {
		index++;

		if (!(index % 5))
			speed += INITIAL_SPEED / 2;

		InitialGeneration();
	}
	else {
		location.y -= fallSpeed * deltaTimeSeconds + FALL_ACCELERATION * deltaTimeSeconds * deltaTimeSeconds / 2;
		fallSpeed += FALL_ACCELERATION * deltaTimeSeconds;
	}
}

unsigned Birdy::ManageEscapedDucks() {
	unsigned ducks = unmanaged_escaped_ducks;
	unmanaged_escaped_ducks = 0;

	return ducks;
}

bool Birdy::ManageRespawn() {
	bool resp = unmanaged_respawn;
	unmanaged_respawn = false;

	return resp;
}

unsigned Birdy::getIndex() {
	return index;
}
