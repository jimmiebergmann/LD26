#include <Engine/Sound.hpp>
#include <iostream>

namespace LDE
{

	// Constructors / destructors
	Sound::Sound( ) :
		m_SfSound( NULL ),
		//m_pSfSoundBuffer( NULL ),
		m_Loaded( false )
	{

	}

	Sound::~Sound( )
	{
		Unload( );
	}
	
	// Public general functions
	bool Sound::Load( std::string p_Path, bool p_Loop )
	{
		if( m_Loaded )
		{
			return false;
		}

		// Load the sound buffer
		//m_pSfSoundBuffer = new sf::SoundBuffer( );
		//sf::SoundBuffer SoundBuffer;
		/*if( !m_SfSoundBuffer.loadFromFile( p_Path ) )
		{
			std::cout << "[Sprite::Load] Can not load the sound buffer." << std::endl;
			return false;
		}

		// Initialize the sound
		m_SfSound = new sf::Sound( m_SfSoundBuffer );
		//m_SfSound->setBuffer( m_pSfSoundBuffer );
		m_SfSound->setLoop( p_Loop );
*/
		// Return true
		m_Loaded = true;
		return true;
	}

	void Sound::Unload( )
	{
		/*if( m_pSfSoundBuffer )
		{
			delete m_pSfSoundBuffer;
			m_pSfSoundBuffer = NULL;
		}*/

		if( m_SfSound )
		{
			delete m_SfSound;
			m_SfSound = NULL;
		}

		m_Loaded = false;
	}

	void Sound::Play( )
	{
		if( m_SfSound )
		{
			m_SfSound->play( );
		}
	}

	void Sound::Pause( )
	{
		if( m_SfSound )
		{
			m_SfSound->pause( );
		}
	}

	void Sound::Stop( )
	{
		if( m_SfSound )
		{
			m_SfSound->stop( );
		}
	}

	// Set function
	void Sound::SetLoop( bool p_Loop )
	{
		if( m_SfSound )
		{
			m_SfSound->setLoop( p_Loop );
		}
	}

}