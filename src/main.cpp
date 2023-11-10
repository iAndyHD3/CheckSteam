#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/casts.hpp>

using namespace geode::prelude;

class $modify(MenuLayer)
{
	bool init()
	{
		if(!MenuLayer::init()) return false;
		
		auto menu = this->getChildByID("bottom-menu");
		if(!menu) return true;

		auto ngBtn = geode::cast::safe_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("newgrounds-button"));
		if (!ngBtn) return true;


		auto spr = CircleButtonSprite::createWithSprite(
			"steam.png"_spr,
			1.0f,
			geode::CircleBaseColor::Green,
			geode::CircleBaseSize::MediumAlt
		);
		
		ngBtn->setNormalImage(spr);

		return true;
	}

	void onNewgrounds(CCObject*)
	{
		geode::createQuickPopup(
			"Check Steam",            // title
			"Are you sure you want to\n<cr>Check Steam</c>?",   // content
			"Cancel", "Yes",      // buttons
			[](auto, bool btn2)
			{
				if (btn2)
				{
					bool steamdb = Mod::get()->getSettingValue<bool>("steam-db");
					const char* url = steamdb ? "https://steamdb.info/app/322170/history/" : "steam://store/322170";
					cocos2d::CCApplication::sharedApplication()->openURL(url);
				}
			}
		);
	}
};
