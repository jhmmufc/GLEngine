#ifndef GAME_ENGINE_PARTICLE_ENGINE_2D_HPP
#define GAME_ENGINE_PARTICLE_ENGINE_2D_HPP

#include <memory>
#include <vector>

namespace GameEngine 
{
	namespace Rendering
	{
		class ParticleBatch2D;
		class SpriteBatch;

		class ParticleEngine2D 
		{
		public:
			ParticleEngine2D() = default;

			void AddParticleBatch(std::shared_ptr<ParticleBatch2D> particleBatch);

			void Update(float deltaTime);

			void Draw(SpriteBatch& spriteBatch);
		private:
			std::vector<std::shared_ptr<ParticleBatch2D>> m_batches;
		};
	}
}

#endif