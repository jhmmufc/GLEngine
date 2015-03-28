#pragma once

#include <functional>
#include <glm/glm.hpp>
#include "Vertex.hpp"
#include "SpriteBatch.hpp"
#include "GLTexture.hpp"

namespace GameEngine {
	namespace Rendering{
		class Particle2D {
		public:
			glm::vec2 position = glm::vec2(0.0f);
			glm::vec2 velocity = glm::vec2(0.0f);
			ColourRGBA8 color;
			float life = 0.0f;
			float width = 0.0f;
		};

		// Default function pointer
		inline void defaultParticleUpdate(Particle2D& particle, float deltaTime) {
			particle.position += particle.velocity * deltaTime;
		}

		class ParticleBatch2D {
		public:
			ParticleBatch2D();
			~ParticleBatch2D();

			void init(int maxParticles,
				float decayRate,
				GLTexture texture,
				std::function<void(Particle2D&, float)> updateFunc = defaultParticleUpdate);

			void update(float deltaTime);

			void draw(SpriteBatch* spriteBatch);

			void addParticle(const glm::vec2& position,
				const glm::vec2& velocity,
				const ColourRGBA8& color,
				float width);

		private:
			int findFreeParticle();

			std::function<void(Particle2D&, float)> m_updateFunc; ///< Function pointer for custom updates
			float m_decayRate = 0.1f;
			Particle2D* m_particles = nullptr;
			int m_maxParticles = 0;
			int m_lastFreeParticle = 0;
			GLTexture m_texture;
		};
	}
}