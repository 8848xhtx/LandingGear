#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

//Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
//enum Camera_Movement {
//	FORWARD,
//	BACKWARD,
//	LEFT,
//	RIGHT
//};
//
//// Default camera values
//const float YAW = -90.0f;
//const float PITCH = 0.0f;
//const float SPEED = 0.25f;
//const float SENSITIVITY = 0.25f;
//const float ZOOM = 45.0f;
//
//
//// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
//class Camera
//{
//public:
//	// camera Attributes
//	glm::vec3 Position;
//	glm::vec3 Front;
//	glm::vec3 Up;
//	glm::vec3 Right;
//	glm::vec3 WorldUp;
//	glm::vec3 mTarget;
//	// euler Angles
//	float Yaw;
//	float Pitch;
//	// camera options
//	float MovementSpeed;
//	float MouseSensitivity;
//	float Zoom;
//
//	// constructor with vectors
//	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
//	{
//		Position = position;
//		WorldUp = up;
//		Yaw = yaw;
//		Pitch = pitch;
//		mTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//		updateCameraVectors();
//	}
//	// constructor with scalar values
//	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
//	{
//		Position = glm::vec3(posX, posY, posZ);
//		WorldUp = glm::vec3(upX, upY, upZ);
//		Yaw = yaw;
//		Pitch = pitch;
//		mTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//
//		updateCameraVectors();
//	}
//
//	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
//	glm::mat4 GetViewMatrix()
//	{
//		//return glm::lookAt(Position, Position + Front, Up);
//		return glm::lookAt(Position, mTarget, Up);
//	}
//
//	// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
//	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
//	{
//		float velocity = MovementSpeed * deltaTime;
//		if (direction == FORWARD)
//			Position += Front * velocity;
//		if (direction == BACKWARD)
//			Position -= Front * velocity;
//		if (direction == LEFT)
//			Position -= Right * velocity;
//		if (direction == RIGHT)
//			Position += Right * velocity;
//
//
//
//
//		//float velocity = MovementSpeed * deltaTime;
//		//if (direction == FORWARD)
//		//	Position += Front * velocity;
//		//if (direction == BACKWARD)
//		//	Position -= Front * velocity;
//		//if (direction == LEFT)
//		//	Position -= Right * velocity;
//		//if (direction == RIGHT)
//		//	Position += Right * velocity;
//		//// make sure the user stays at the ground level
//		//Position.y = 0.0f; // <-- this one-liner keeps the user at the ground level (xz plane)
//	}
//
//	// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
//	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
//	{
//		xoffset *= MouseSensitivity;
//		yoffset *= MouseSensitivity;
//
//		Yaw += xoffset;
//		Pitch += yoffset;
//
//		// make sure that when pitch is out of bounds, screen doesn't get flipped
//		if (constrainPitch)
//		{
//			if (Pitch > 89.0f)
//				Pitch = 89.0f;
//			if (Pitch < -89.0f)
//				Pitch = -89.0f;
//		}
//
//		glm::vec3 focusVector = Position - mTarget;
//		float currentPitch = glm::degrees(glm::asin(focusVector.y / glm::length(focusVector)));
//		float newPitch = currentPitch + Pitch;
//		if (newPitch > 89.0f) {
//			Pitch = 89.0f - currentPitch;
//		}
//		if (newPitch < -89.0f) {
//			Pitch = -89.0f - currentPitch;
//		}
//
//		glm::mat4 rotation(1.0f);
//		rotation = glm::rotate(rotation, glm::radians(Pitch), Right);
//		rotation = glm::rotate(rotation, glm::radians(Yaw), WorldUp);
//
//		focusVector = rotation * glm::vec4(focusVector, 1.0f);
//		Position = focusVector + mTarget;
//		
//		// update Front, Right and Up Vectors using the updated Euler angles
//		updateCameraVectors();
//	}
//
//	void ProcessMouseMove(float xoffset, float yoffset)
//	{
//		float x, y, z;
//		float r = sqrt(Position.x * Position.x + Position.y * Position.y + Position.z * Position.z);
//		float  afa, fi;
//		if (Position.x >= 0)
//		{
//			afa = atan(Position.z / Position.x);
//		}
//		else
//		{
//			afa = atan(Position.z / Position.x) + 3.1415926;
//		}
//		if (Position.y>0)
//		{
//			fi = atan(Position.x / (Position.y*cos(afa)));
//		}
//		else
//		{
//			fi = atan(Position.x / (Position.y*cos(afa))) + 3.1415926;
//		}
//		x = r*sin(fi + (yoffset) / 180.0f*3.1415926)*cos(afa + (xoffset) / 180.0f*3.1415926);
//		y = r*cos(fi + (yoffset) / 180.0f*3.1415926);
//		z = r*sin(fi + (yoffset) / 180.0f*3.1415926)*sin(afa + (xoffset) / 180.0f*3.1415926);
//		Position = glm::vec3(x, y, z);
//	}
//	// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
//	void ProcessMouseScroll(float yoffset)
//	{
//		Zoom -= (float)yoffset;
//		if (Zoom < 1.0f)
//			Zoom = 1.0f;
//		if (Zoom > 45.0f)
//			Zoom = 45.0f;
//	}
//
//private:
//	// calculates the front vector from the Camera's (updated) Euler Angles
//	void updateCameraVectors()
//	{
//		// calculate the new Front vector
//		glm::vec3 front;
//		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//		front.y = sin(glm::radians(Pitch));
//		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//		Front = glm::normalize(front);
//
//		//glm::vec3 focusVector = glm::normalize(Position - mTarget);
//		
//		Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
//		Up = glm::normalize(glm::cross(Right, Front));
//
//		/*glm::vec3 focusVector = glm::normalize(Position - mTarget);
//		Right = glm::normalize(glm::cross(focusVector, WorldUp));
//		Up = glm::normalize(glm::cross(Right, focusVector));*/
//	}
//};


//另一种摄像机类

namespace {
	// Default camera values
	const float SPEED = 0.25f;
	const float DISTANCE = 2.5f;
	const float SENSITIVITY = 0.25f;
	const float ZOOM = 45.0f;
}
namespace {
	const float minDistance = 0.01f;
	const float maxDistance = 50.0f;
	const float maxPitch = 89.0f;
	const float minPitch = -89.0f;
}
class Camera
{
public:
	glm::vec3 mPosition;
	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mWorldUp;
	glm::vec3 mTarget;

	float mMovementSpeed;
	float mMouseSensitivity;
	float mZoom;

	bool mDragging = false;
	bool mPanning = false;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.3f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f))
		: mMovementSpeed(SPEED)
		, mMouseSensitivity(SENSITIVITY)
		, mZoom(ZOOM)
	{
		mPosition = position;
		mWorldUp = up;
		mTarget = target;
		updateCameraVectors();
	}
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float targetX, float targetY, float targetZ)
		: mMovementSpeed(SPEED)
		, mMouseSensitivity(SENSITIVITY)
		, mZoom(ZOOM)
	{
		mPosition = glm::vec3(posX, posY, posZ);
		mWorldUp = glm::vec3(upX, upY, upZ);
		mTarget = glm::vec3(targetX, targetY, targetZ);
		updateCameraVectors();
	}


	glm::mat4 getViewMatrix()
	{
		return glm::lookAt(mPosition, mTarget, mUp);
	}
	void processMouseMovement(float xoffset, float yoffset)
	{
		if (mDragging) {
			xoffset *= mMouseSensitivity;
			yoffset *= mMouseSensitivity;

			float yaw = -xoffset;
			float pitch = -yoffset;

			glm::vec3 focusVector = mPosition - mTarget;

			// pitch constraints
			float currentPitch = glm::degrees(glm::asin(focusVector.y / glm::length(focusVector)));
			float newPitch = currentPitch + pitch;

			if (newPitch > maxPitch) {
				pitch = maxPitch - currentPitch;
			}

			if (newPitch < minPitch) {
				pitch = minPitch - currentPitch;
			}

			glm::mat4 rotation(1.0f);
			rotation = glm::rotate(rotation, glm::radians(pitch), mRight);
			rotation = glm::rotate(rotation, glm::radians(yaw), mWorldUp);

			focusVector = rotation * glm::vec4(focusVector, 1.0f);

			mPosition = focusVector + mTarget;
			updateCameraVectors();
		}
		else if (mPanning) {
			float distance = glm::length(mPosition - mTarget);
			float sensitivity = distance / 1000.0f;
			xoffset *= sensitivity;
			yoffset *= sensitivity;

			glm::vec3 pan = (glm::normalize(mRight) * xoffset) - (glm::normalize(mUp) * yoffset);
			mTarget += pan;
			mPosition += pan;
		}
	}
	void processMousePress(bool leftPressed, bool rightPressed)
	{
		if (leftPressed && rightPressed) {
			mDragging = false;
			mPanning = false;
		}
		else {
			mDragging = leftPressed;
			mPanning = rightPressed;
		}
	}
	void processMouseScroll(float yoffset)
	{
		yoffset *= -SPEED;
		glm::vec3 delta = glm::normalize(mPosition - mTarget) * yoffset;
		glm::vec3 limit = mPosition - mTarget;
		glm::vec3 newPosition = mPosition + delta;

		if (yoffset < 0.0f) {
			// Dolly in
			if (glm::length(delta) >= glm::length(limit) // camera overshoots target
				|| glm::length(newPosition - mTarget) < minDistance)  // camera closer than min distance
			{
				// Set position to minimum distance
				mPosition = (glm::normalize(mPosition - mTarget) * minDistance) + mTarget;
			}
			else {
				mPosition = newPosition;
			}
		}
		else if (yoffset > 0.0f) {
			// Dolly out
			if (glm::length(newPosition - mTarget) > maxDistance) { // camera further than max distance
																	// Set position to maximum distance
				mPosition = (glm::normalize(mPosition - mTarget) * maxDistance) + mTarget;
			}
			else {
				mPosition = newPosition;
			}
		}
	}

private:
	void updateCameraVectors()
	{
		glm::vec3 focusVector = glm::normalize(mPosition - mTarget);
		mRight = glm::normalize(glm::cross(focusVector, mWorldUp));
		mUp = glm::normalize(glm::cross(mRight, focusVector));
	}
};



#endif