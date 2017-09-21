#ifndef GAME_ENGINE_VERTEX_HPP
#define GAME_ENGINE_VERTEX_HPP

#include <GL/glew.h>

namespace GameEngine
{
	namespace Rendering
	{
		struct PositionStruct
		{
			float X;
			float Y;
		};

		struct ColourRGBA8 
		{
			ColourRGBA8() : R(0), G(0), B(0), A(0) { }
			ColourRGBA8(GLubyte r, GLubyte g, GLubyte b, GLubyte a) :
				R(r), G(g), B(b), A(a) { }
			GLubyte R;
			GLubyte G;
			GLubyte B;
			GLubyte A;
		};

		struct UVStruct
		{
			float U;
			float V;
		};

		//The vertex definition
		struct Vertex 
		{
			//This is the position struct. When you store a struct or class
			//inside of another struct or class, it is called composition. This is
			//layed out exactly the same in memory as if we had a float position[2],
			//but doing it this way makes more sense.
			PositionStruct Position;

			//4 bytes for r g b a color.
			ColourRGBA8 Colour;

			//UV texture coordinates.
			UVStruct UV;

			void SetPosition(float x, float y) 
			{
				Position.X = x;
				Position.Y = y;
			}

			void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
			{
				Colour.R = r;
				Colour.G = g;
				Colour.B = b;
				Colour.A = a;
			}

			void SetUV(float u, float v) 
			{
				UV.U = u;
				UV.V = v;
			}
		};
	}
}

#endif