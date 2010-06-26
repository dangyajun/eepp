#ifndef EE_AUDIOTSOUNDMANAGER_H
#define EE_AUDIOTSOUNDMANAGER_H

#include "base.hpp"
#include "csound.hpp"
#include "csoundbuffer.hpp"

namespace EE { namespace Audio {

/** @brief A basic template to hold sounds and the respective buffer. */
template <typename T>
class EE_API tSoundManager{
	public:
		bool LoadFromFile( const T& id, const std::string& filepath );
		bool LoadFromMemory( const T& id, const char* Data, std::size_t SizeInBytes );
		bool LoadFromSamples( const T& id, const Int16* Samples, std::size_t SamplesCount, unsigned int ChannelsCount, unsigned int SampleRate );
		bool LoadFromPack( const T& id, cPack* Pack, const std::string& FilePackPath );
		
		cSoundBuffer& GetBuffer( const T& id );

		/** This method will open a new channel if the channel seted for the sound is playing. */
		void Play( const T& id );

		bool Remove( const T& id );

		cSound& operator[] ( const T& id );

		~tSoundManager();
	private:
		typedef struct {
			cSoundBuffer Buf;
			std::vector<cSound> Snd;
		} sSound;
		std::map<T, sSound> tSounds;
};

template <typename T>
bool tSoundManager<T>::LoadFromPack( const T& id, cPack* Pack, const std::string& FilePackPath ) {
	if ( tSounds.find( id ) == tSounds.end() ) { // if id doesn't exists
		if ( tSounds[id].Buf.LoadFromPack( Pack, FilePackPath ) ) {
			tSounds[id].Snd.push_back( cSound( tSounds[id].Buf ) );
			return true;
		}
	}
	return false;
}

template <typename T>
bool tSoundManager<T>::LoadFromFile( const T& id, const std::string& filepath ) {
	if ( tSounds.find( id ) == tSounds.end() ) { // if id doesn't exists
		if ( tSounds[id].Buf.LoadFromFile( filepath ) ) {
			tSounds[id].Snd.push_back( cSound( tSounds[id].Buf ) );
			return true;
		}
	}
	return false;
}

template <typename T>
bool tSoundManager<T>::LoadFromMemory( const T& id, const char* Data, std::size_t SizeInBytes ) {
	if ( tSounds.find( id ) == tSounds.end() ) { // if id doesn't exists
		if ( tSounds[id].Buf.LoadFromMemory( Data, SizeInBytes ) ) {
			tSounds[id].Snd.push_back( cSound( tSounds[id].Buf ) );
			return true;
		}
	}
	return false;
}

template <typename T>
bool tSoundManager<T>::LoadFromSamples( const T& id, const Int16* Samples, std::size_t SamplesCount, unsigned int ChannelsCount, unsigned int SampleRate ) {
	if ( tSounds.find( id ) == tSounds.end() ) { // if id doesn't exists
		if ( tSounds[id].Buf.LoadFromSamples( Samples, SamplesCount, ChannelsCount, SampleRate ) ) {
			tSounds[id].Snd.push_back( cSound( tSounds[id].Buf ) );
			return true;
		}
	}
	return false;
}

template <typename T>
cSoundBuffer& tSoundManager<T>::GetBuffer( const T& id ) {
	if ( tSounds.find( id ) != tSounds.end() )
		return tSounds[id].Buf;
}

template <typename T>
cSound& tSoundManager<T>::operator[] ( const T& id ) {
	if ( tSounds.find( id ) != tSounds.end() )
		return tSounds[id].Snd[0];

	return tSounds[0].Snd[0];
}

template <typename T>
void tSoundManager<T>::Play( const T& id ) {
	if ( tSounds.find( id ) != tSounds.end() ) {
		for ( Uint32 i = 0; i < tSounds[id].Snd.size(); i++ ) {
			// If there is a free slot, use it.
			if ( tSounds[id].Snd[i].GetState() != SOUND_PLAYING ) {
				tSounds[id].Snd[i].Play();
				return;
			}
		}

		// Otherwise create a new one and play it.
		tSounds[id].Snd.push_back( cSound( tSounds[id].Buf ) );
		tSounds[id].Snd[ tSounds[id].Snd.size() - 1 ].Play();
	}
}

template <typename T>
tSoundManager<T>::~tSoundManager() {
	typename std::map<T, sSound>::iterator itr;
	for (itr = tSounds.begin(); itr != tSounds.end(); itr++)
		itr->second.Snd.clear();

	tSounds.clear();
}

template <typename T>
bool tSoundManager<T>::Remove( const T& id ) {
	if ( tSounds.find( id ) != tSounds.end() ) {
		tSounds.erase( id );
		return true;
	}
	return false;
}

typedef tSoundManager<std::string> cSoundManager;
}}

#endif
