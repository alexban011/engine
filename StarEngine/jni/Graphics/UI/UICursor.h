#pragma once
#include "../../defines.h"
#include "../../Context.h"
#include "../../Objects/Object.h"

#include <unordered_map>

namespace star
{
	class SpritesheetComponent;

	class UICursor : public Object
	{
	public:
		UICursor(
			const tstring & name,
			const tstring & spriteFile,
			const tstring & spritesheetName
			);
		virtual ~UICursor();

		virtual void AfterInitialized();

		void SetCenterPoint(const vec2 & center);
		void SetCenterPoint(float32 x, float32 y);
		void SetCenterX(float32 x);
		void SetCenterY(float32 y);

		void SetDefaultCenterPosition(const vec2 & center);
		void SetDefaultCenterPosition(float32 x, float32 y);

		virtual void SetState(const tstring & state);

		void SetStateOffset(
			const tstring & state,
			const vec2 & offset
			);

		void SetStateOffset(
			const tstring & state,
			float32 x,
			float32 y
			);

	protected:
		virtual void Update(const Context & context);

		SpritesheetComponent * m_pCursorSprite;
		std::unordered_map<tstring, vec2> m_Offsets;
		vec2 m_DefaultOffset;

	private:
		UICursor(const UICursor &);
		UICursor(UICursor &&);
		UICursor & operator=(const UICursor &);
		UICursor & operator=(UICursor&&);
	};
}
