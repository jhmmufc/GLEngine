#include "Camera.hpp"

namespace GameEngine
{
	namespace Rendering
	{
		void Camera::Initialise(int screenWidth, int screenHeight)
		{
			m_screenWidth = screenWidth;
			m_screenHeight = screenHeight;

			// TODO convert to XNA coords where its 0 0 top left
			m_orthoMatrix = glm::ortho(0.0f, static_cast<float>(m_screenWidth), 0.0f, static_cast<float>(m_screenHeight));
		}

		// Updates the camera matrix if needed
		void Camera::Update()
		{
			if (m_updateMatrix)
			{
				//Camera Translation
				glm::vec3 translate(-m_position.x + m_screenWidth / 2.0f, -m_position.y + m_screenHeight / 2.0f, 0.0f);
				m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

				//Camera Scale
				glm::vec3 scale(m_scale, m_scale, 0.0f);
				m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

				m_updateMatrix = false;
			}
		}

		glm::vec2 Camera::ConvertScreenToWorld(const glm::vec2& screenCoords)
		{
			auto result = screenCoords;

			// Invert the y direction
			result.y = m_screenHeight - result.y;

			// Make it so that 0 is the center
			result -= glm::vec2(m_screenWidth / 2.0f, m_screenHeight / 2.0f);

			// Scale the coordinated
			result /= m_scale;

			// finally translate with the camera position
			result += m_position;

			return result;
		}

		// Simple AxisAligned bounding box test
		// to see if a box is inside the camera view
		bool Camera::IsBoxInView(const glm::vec2& position, const glm::vec2& dimensions) const
		{
			glm::vec2 scaledScreenDimensions = glm::vec2(m_screenWidth, m_screenHeight) / (m_scale);

			// The minimum distance before a collision occurs
			const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
			const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

			// Center position of the parameters
			glm::vec2 centerPos = position + dimensions / 2.0f;
			// Center position of the camera
			glm::vec2 centerCameraPos = m_position;
			// Vector from the input to the camera
			glm::vec2 distVec = centerPos - centerCameraPos;

			// Get the depth of the collision
			float xDepth = MIN_DISTANCE_X - abs(distVec.x);
			float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

			// If both the depths are > 0, then we collided
			if (xDepth > 0 && yDepth > 0) 
			{
				// There was a collision
				return true;
			}

			return false;
		}

		void Camera::SetPosition(const glm::vec2& position)
		{
			m_position = position;
			m_updateMatrix = true;
		}

		void Camera::SetScale(float scale)
		{
			m_scale = scale;
			m_updateMatrix = true;
		}

		const glm::vec2& Camera::GetPosition() const
		{
			return m_position;
		}

		float Camera::GetScale() const
		{
			return m_scale;
		}

		const glm::mat4& Camera::GetCameraMatrix() const
		{
			return m_cameraMatrix;
		}
	}
}