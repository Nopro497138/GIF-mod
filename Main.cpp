#include <Geode/Bindings.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CommentLayer.hpp>
#include <Geode/modify/CCMenuItemImage.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/modify/FLAlertLayer.hpp>

using namespace geode::prelude;

// GIFs aus dem GitHub Repository
std::vector<std::string> gifs = {
    "gif1.gif",
    "gif2.gif"
};

// Diese Funktion lädt die GIFs von GitHub
std::string loadGIFFromGitHub(const std::string& gifName) {
    return "https://github.com/your-repo/your-gif-folder/" + gifName;
}

// Menü anzeigen, wenn das Geometry Dash-Icon gedrückt wird
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Erstelle Geometry Dash Icon und füge es zum Menü hinzu
        auto icon = CCMenuItemImage::create("resources/logo.png", "resources/logo.png", this, menu_selector(MenuLayer::onGeometryDashIconClicked));
        icon->setPosition({50, 50});
        this->addChild(icon);

        return true;
    }

    // Wenn das Icon gedrückt wird, öffne das Menü
    void onGeometryDashIconClicked(CCObject* sender) {
        // Erstelle das Menü, das die GIFs zeigt
        auto menu = CCMenu::create();
        menu->setPosition({0, 0});
        
        for (size_t i = 0; i < gifs.size(); ++i) {
            auto item = CCMenuItemImage::create("resources/logo.png", "resources/logo.png", this, menu_selector(MenuLayer::onGIFClicked));
            item->setTag(i); // Tag ist der Index des GIFs
            menu->addChild(item);
        }

        menu->alignItemsVertically();
        this->addChild(menu);
    }

    // Wenn auf ein GIF geklickt wird, ersetze den Text mit dem GIF-Namen
    void onGIFClicked(CCObject* sender) {
        auto item = dynamic_cast<CCMenuItemImage*>(sender);
        if (item) {
            int gifIndex = item->getTag();
            std::string gifName = gifs[gifIndex];
            std::string gifUrl = loadGIFFromGitHub(gifName);
            std::string commentText = gifName; // Dieser Text wird in den Kommentaren angezeigt

            // Ersetze den Text im Kommentar mit dem Namen des GIFs
            auto commentLayer = dynamic_cast<CommentLayer*>(this->getParent());
            commentLayer->replaceCommentText(commentText);
        }
    }
};

// Kommentar-Schicht modifizieren
class $modify(CommentLayer) {
public:
    // Diese Funktion ersetzt den Kommentartext mit dem GIF-Namen
    void replaceCommentText(const std::string& newText) {
        this->getCommentTextField()->setString(newText.c_str());
    }
};
