#include "SpriteAnimationManager.h"
#include "../Input/XMLFileParser.h"
#include "../Input/XMLContainer.h"
#include "../Logger.h"

namespace star
{
	SpriteAnimationManager::SpriteAnimationManager()
		: Singleton<SpriteAnimationManager>()
		, m_Spritesheets()
	{

	}

	SpriteAnimationManager::~SpriteAnimationManager()
	{

	}

	void SpriteAnimationManager::AddSpritesheet(const tstring & file, DirectoryMode mode)
	{
		XMLFileParser parser(file, mode);
		XMLContainer container;
		parser.Read(container);
		
		tstring name = container.GetAttributes()[_T("name")];
		auto it = m_Spritesheets.find(name);
		bool isValid = it == m_Spritesheets.end();
		if(isValid)
		{
			SpriteSheet spritesheet(container);
			m_Spritesheets.insert(std::pair<tstring, SpriteSheet>(name, spritesheet));
		}
		else
		{
			LOG(LogLevel::Warning,
				_T("SpriteAnimationManager::AddSpritesheet: This spritesheet already exists!"),
				STARENGINE_LOG_TAG);
		}
	}
	
	void SpriteAnimationManager::AddSpritesheet(const tstring & file, const tstring & binary_file,
		DirectoryMode mode)
	{
		XMLFileParser parser(file, mode);
		XMLContainer container;
		parser.Read(container, binary_file);
		
		tstring name = container.GetAttributes()[_T("name")];
		auto it = m_Spritesheets.find(name);
		bool isValid = it == m_Spritesheets.end();
		if(isValid)
		{
			SpriteSheet spritesheet(container);
			m_Spritesheets.insert(std::pair<tstring, SpriteSheet>(name, spritesheet));
		}
		else
		{
			LOG(LogLevel::Warning,
				_T("SpriteAnimationManager::AddSpritesheet: This spritesheet already exists!"),
				STARENGINE_LOG_TAG);
		}
	}

	const SpriteSheet & 
		SpriteAnimationManager::GetSpritesheet(const tstring & name) const
	{
		auto it = m_Spritesheets.find(name);
		bool isValid = it != m_Spritesheets.end();
		ASSERT_LOG(isValid,
			_T("SpriteAnimationManager::GetSpritesheet(const tstring & name): Couldn't find \"") + 
			name + tstring(_T("\" in the loaded spritesheets.")),
			STARENGINE_LOG_TAG);
		return m_Spritesheets.at(name);
	}
	
	void SpriteAnimationManager::Clear()
	{
		m_Spritesheets.clear();
	}
}
