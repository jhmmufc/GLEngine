#include "ParticleEngine2D.hpp"

#include "ParticleBatch2D.hpp"
#include "SpriteBatch.hpp"

namespace GameEngine 
{
	namespace Rendering
	{
		void ParticleEngine2D::AddParticleBatch(std::shared_ptr<ParticleBatch2D> particleBatch)
		{
			m_batches.push_back(particleBatch);
		}

		void ParticleEngine2D::Update(float deltaTime)
		{
			for (auto& b : m_batches) 
			{
				b->Update(deltaTime);
			}
		}

		void ParticleEngine2D::Draw(SpriteBatch& spriteBatch) 
		{
			for (auto& b : m_batches) 
			{
				spriteBatch.Begin();
				b->Draw(spriteBatch);
				spriteBatch.End();
				spriteBatch.RenderBatches();
			}
		}
	}
}