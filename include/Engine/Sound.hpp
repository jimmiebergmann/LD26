#ifndef __LDE_AUDIO_HPP__
#define __LDE_AUDIO_HPP__

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

namespace LDE
{

	class Sound
	{

	public:

		// Constructors / destructors
		Sound( );
		~Sound( );
		
		// Public general functions
		bool Load( std::string p_Path, bool p_Loop );
		void Unload( );
		void Play( );
		void Pause( );
		void Stop( );

		// Set function
		void SetLoop( bool p_Loop );

	private:

		// Private functions


		// Private variables
		sf::Sound * m_SfSound;
		//sf::SoundBuffer m_SfSoundBuffer;
		bool m_Loaded;


	};

}


#endif