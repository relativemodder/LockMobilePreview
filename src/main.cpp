#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>

class $modify(LockMobilePreviewLayer, EditorUI) {
    struct Fields {
        CCKeyboardDispatcher* keyboardDispatcher;
        CCMenuItemSpriteExtra* lockButton;
        bool previewLocked;
    };
    
    bool init(LevelEditorLayer* lel) {
        EditorUI::init(lel);
        m_fields->keyboardDispatcher = CCKeyboardDispatcher::get();

        auto settingsMenu = static_cast<CCMenu*>(getChildByIDRecursive("settings-menu"));

        if (!settingsMenu) {
            log::error("Well, couldn't find settings-menu");
            return true;
        }

        auto initialSprite = CCSprite::createWithSpriteFrameName("GJ_lock_open_001.png");
        
        m_fields->lockButton = CCMenuItemSpriteExtra::create(
            initialSprite, this,
            menu_selector(LockMobilePreviewLayer::onToggleLock)
            );
        settingsMenu->addChild(m_fields->lockButton);
        settingsMenu->updateLayout();

        return true;
    }

    void updateLockButtonSprite() {
        auto spriteName = (
            m_fields->previewLocked
            ? "GJ_lock_open_001.png"
            : "GJ_lock_001.png");
        
        m_fields->lockButton->setSprite(
            CCSprite::createWithSpriteFrameName(spriteName));
    }

    void onToggleLock(CCObject* target) {
        if (!m_fields->previewLocked) {
            lockPreview();
        }
        else {
            unlockPreview();
        }
        
        updateLockButtonSprite();
        m_fields->previewLocked = !m_fields->previewLocked;
    }

    void keyPress(enumKeyCodes key) {
        m_fields->keyboardDispatcher->dispatchKeyboardMSG(key, true, false);
        m_fields->keyboardDispatcher->dispatchKeyboardMSG(key, false, false);
    }

    void lockPreview() {
        keyPress(KEY_F1);
    }

    void unlockPreview() {
        keyPress(KEY_F2);
    }
};