#ifndef GAME_ENGINE_CAMERA_HPP
#define GAME_ENGINE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine
{
	namespace Rendering
	{
		class Camera
		{
		public:
			Camera() = default;

			void Initialise(int screenWidth, int screenHeight);
			void Update();
			
			glm::vec2 ConvertScreenToWorld(const glm::vec2& screenCoords);

			bool IsBoxInView(const glm::vec2& position, const glm::vec2& dimensions) const;

			void SetPosition(const glm::vec2& pos);
			void SetScale(float scale);

			const glm::vec2& GetPosition() const;
			float GetScale() const;
			const glm::mat4& GetCameraMatrix() const;

		private:
			int m_screenWidth = 800;
			int m_screenHeight = 600;

			float m_scale = 1.0f;

			bool m_updateMatrix = true;

			glm::vec2 m_position = glm::vec2(0.0f, 0.0f);
			glm::mat4 m_cameraMatrix = glm::mat4(1.0f);
			glm::mat4 m_orthoMatrix = glm::mat4(1.0f);
		};
	}
}

#endif