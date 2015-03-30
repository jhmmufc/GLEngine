#include "ParticleBatch2D.hpp"

namespace GameEngine 
{
	namespace Rendering
	{
		ParticleBatch2D::ParticleBatch2D() 
		{
			// Empty
		}


		ParticleBatch2D::~ParticleBatch2D()
		{
			
		}

		void ParticleBatch2D::Init(int maxParticles,
			float decayRate,
			GLTexture texture,
			std::function<void(Particle2D&, float)> updateFunc /* = defaultParticleUpdate */) 
		{
			m_maxParticles = maxParticles;
			m_particles.resize(maxParticles);
			m_decayRate = decayRate;
			m_texture = texture;
			m_updateFunc = updateFunc;
		}

		void ParticleBatch2D::Update(float deltaTime) 
		{
			for (int i = 0; i < m_maxParticles; i++) 
			{
				// Check if it is active
				if (m_particles[i].Life > 0.0f) 
				{
					// Update using function pointer
					m_updateFunc(m_particles[i], deltaTime);
					m_particles[i].Life -= m_decayRate * deltaTime;
				}
			}
		}

		void ParticleBatch2D::Draw(SpriteBatch& spriteBatch) 
		{
			glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
			for (int i = 0; i < m_maxParticles; i++) 
			{
				// Check if it is active
				auto& p = m_particles[i];
				if (p.Life > 0.0f) 
				{
					glm::vec4 destRect(p.Position.x, p.Position.y, p.Width, p.Width);
					spriteBatch.draw(destRect, uvRect, m_texture.ID, 0.0f, p.Colour);
				}
			}
		}

		void ParticleBatch2D::AddParticle(const glm::vec2& position,
			const glm::vec2& velocity,
			const ColourRGBA8& color,
			float width) 
		{
			int particleIndex = FindFreeParticle();

			auto& p = m_particles[particleIndex];

			p.Life = 1.0f;
			p.Position = position;
			p.Velocity = velocity;
			p.Colour = color;
			p.Width = width;
		}

		int ParticleBatch2D::FindFreeParticle() 
		{

			for (int i = m_lastFreeParticle; i < m_maxParticles; i++) 
			{
				if (m_particles[i].Life <= 0.0f) 
				{
					m_lastFreeParticle = i;
					return i;
				}
			}

			for (int i = 0; i < m_lastFreeParticle; i++)
			{
				if (m_particles[i].Life <= 0.0f) 
				{
					m_lastFreeParticle = i;
					return i;
				}
			}

			// No particles are free, overwrite first particle
			return 0;
		}
	}
}