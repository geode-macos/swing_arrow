#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

#include "modmanager.h"

constexpr int GLOBED_PLAYER_OBJECT_TAG = 3458738;

struct ArrowPlayerObject : geode::Modify<ArrowPlayerObject, PlayerObject> {
	struct Fields {
		geode::Ref<cocos2d::CCSprite> m_arrow = nullptr;
	};

	bool init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4) {
		if (!PlayerObject::init(p0, p1, p2, p3, p4))
			return false;

		auto mm = ModManager::get();

		auto arrow = cocos2d::CCSprite::createWithSpriteFrameName("particle_12_001.png");
		arrow->setVisible(false);
		arrow->setRotation(90);
		arrow->setOpacity(mm.getOpacity());
		arrow->setZOrder(2);
		arrow->setScale(mm.getScale());
		m_mainLayer->addChildAtPosition(arrow, geode::Anchor::Center, ccp(mm.getOffsetX(), mm.getOffsetY()), false);

		auto fields = m_fields.self();

		fields->m_arrow = arrow;

		return true;
	}

	void updatePlayerArt() {
		PlayerObject::updatePlayerArt();

		auto fields = m_fields.self();

		fields->m_arrow->setVisible(m_isSwing && ModManager::get().getEnabled() && GJBaseGameLayer::get() && this->getTag() != GLOBED_PLAYER_OBJECT_TAG);
	}
	
	void resetPlayerIcon() {
		PlayerObject::resetPlayerIcon();

		m_fields->m_arrow->setScale(ModManager::get().getScale());
	}
	
	void playDeathEffect() {
		PlayerObject::playDeathEffect();

		m_fields->m_arrow->runAction(cocos2d::CCEaseInOut::create(cocos2d::CCScaleTo::create(.15f,0), 2));
	}

	void rotateGameplay(int p0, int p1, bool p2, float p3, float p4, bool p5, bool p6) {
		PlayerObject::rotateGameplay(p0, p1, p2, p3, p4, p5, p6);

		auto arrow = m_fields->m_arrow;

		// I don't fucking know
		if (p0 == 4 || p0 == 3)
			arrow->setRotation(-90);
		else
			arrow->setRotation(90);
	}

	void flipGravity(bool p0, bool p1) {
		PlayerObject::flipGravity(p0, p1);

		m_fields->m_arrow->setFlipX(p0);
	}
};