#ifndef GAME_ENGINE_PARTICLE_BATCH_2D_HPP
#define GAME_ENGINE_PARTICLE_BATCH_2D_HPP

#include <functional>
#include <memory>
#include <glm/glm.hpp>
#include "Vertex.hpp"
#include "SpriteBatch.hpp"
#include "GLTexture.hpp"

namespace GameEngine 
{
	namespace Rendering
	{
		class Particle2D 
		{
		public:
			glm::vec2 Position = glm::vec2(0.0f);
			glm::vec2 Velocity = glm::vec2(0.0f);
			ColourRGBA8 Colour;
			float Life = 0.0f;
			float Width = 0.0f;
		};

		// Default function pointer
		inline void DefaultParticleUpdate(Particle2D& particle, float deltaTime) 
		{
			particle.Position += particle.Velocity * deltaTime;
		}

		class ParticleBatch2D 
		{
		public:
			ParticleBatch2D();
			~ParticleBatch2D();

			void Init(int maxParticles,
				float decayRate,
				GLTexture texture,
				std::function<void(Particle2D&, float)> updateFunc = DefaultParticleUpdate);

			void Update(float deltaTime);

			void Draw(SpriteBatch& spriteBatch);

			void AddParticle(const glm::vec2& position,
				const glm::vec2& velocity,
				const ColourRGBA8& color,
				float width);

		private:
			int FindFreeParticle();

			std::function<void(Particle2D&, float)> m_updateFunc; ///< Function pointer for custom updates
			float m_decayRate = 0.1f;
			std::vector<Particle2D> m_particles;
			int m_maxParticles = 0;
			int m_lastFreeParticle = 0;
			GLTexture m_texture;
		};
	}
}

#endif